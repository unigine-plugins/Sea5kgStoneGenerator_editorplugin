/* Copyright (C) 2005-2024, UNIGINE. All rights reserved.
*
* This file is a part of the UNIGINE 2 SDK.
*
* Your use and / or redistribution of this software in source and / or
* binary form, with or without modification, is subject to: (i) your
* ongoing acceptance of and compliance with the terms and conditions of
* the UNIGINE License Agreement; and (ii) your inclusion of this notice
* in any version of this software that you use or redistribute.
* A copy of the UNIGINE License Agreement is available by contacting
* UNIGINE. at http://unigine.com/
*/

#pragma once

#include <UnigineHash.h>
#include <UniginePair.h>

#include <type_traits>

namespace Unigine
{

namespace Internal
{
template<class Key, class Value>
struct HashMapData
{
	using HashType = typename Hasher<Key>::HashType;
	template<class K, std::enable_if_t<!IsSame<K, HashMapData>::value, int> = 0>
	UNIGINE_INLINE HashMapData(HashType h, K &&k)
		: hash(h)
		, key(std::forward<K>(k))
		, data()
	{}
	template<class K, class... Args, std::enable_if_t<!IsSame<K, HashMapData>::value, int> = 0>
	UNIGINE_INLINE HashMapData(HashType h, K &&k, Args &&...args)
		: hash(h)
		, key(std::forward<K>(k))
		, data(std::forward<Args>(args)...)
	{}

	UNIGINE_INLINE friend bool operator==(const HashMapData &l, const HashMapData &r)
	{
		return l.hash == r.hash && l.key == r.key && l.data == r.data;
	}
	UNIGINE_INLINE friend bool operator!=(const HashMapData &l, const HashMapData &r) { return !(l == r); }

	const HashType hash;
	const Key key;
	Value data;
};

template<class K, class V>
struct FlatHashMapPolicy
{
	using Key = K;
	using Value = V;
	using Slot = HashMapData<Key, Value>;
	using Element = HashMapData<Key, Value>;
	using HashType = typename Hasher<Key>::HashType;

	UNIGINE_INLINE static HashType hash(const Slot &s) { return s.hash; }
	UNIGINE_INLINE static const Key &key(const Slot &s) { return s.key; }

	template<class... Args>
	UNIGINE_INLINE static void construct(Slot &slot, HashType hash, Args &&...args)
	{
		new (&slot) Slot(hash, std::forward<Args>(args)...);
	}
	UNIGINE_INLINE static void construct(Slot &slot, const Slot &from) { new (&slot) Slot(from); }
	UNIGINE_INLINE static void construct(Slot &slot, Slot &&from)
	{
		new (&slot) Slot(from.hash, std::move(const_cast<Key &>(from.key)), std::move(from.data));
	}

	UNIGINE_INLINE static void swap(Slot &s0, Slot &s1)
	{
		std::swap(const_cast<HashType &>(s0.hash), const_cast<HashType &>(s1.hash));
		std::swap(const_cast<Key &>(s0.key), const_cast<Key &>(s1.key));
		std::swap(s0.data, s1.data);
	}

	template<class... Args>
	UNIGINE_INLINE static void replace(Slot &slot, Args &&...args)
	{
		slot.data = Value(std::forward<Args>(args)...);
	}
	UNIGINE_INLINE static void replace(Slot &slot, const Slot &from) { slot.data = from.data; }
	UNIGINE_INLINE static void replace(Slot &slot, Slot &&from) { slot.data = std::move(from.data); }

	UNIGINE_INLINE static Element &element(Slot &slot) { return slot; }

	UNIGINE_INLINE static void destruct(Slot &slot) { slot.~Slot(); }
};

template<class K, class V>
struct BucketHashMapPolicy
{
	using Key = K;
	using Value = V;
	using Slot = HashMapData<Key, Value> *;
	using Element = HashMapData<Key, Value>;
	using HashType = typename Hasher<Key>::HashType;

	UNIGINE_INLINE static HashType hash(const Slot &s) { return s->hash; }
	UNIGINE_INLINE static const Key &key(const Slot &s) { return s->key; }

	template<class... Args>
	UNIGINE_INLINE static void construct(Slot &slot, HashType hash, Args &&...args)
	{
		slot = new (Memory::allocatePool<sizeof(Element)>()) Element(hash, std::forward<Args>(args)...);
	}
	UNIGINE_INLINE static void construct(Slot &slot, const Slot &from)
	{
		slot = new (Memory::allocatePool<sizeof(Element)>()) Element(from->hash, from->key, from->data);
	}
	UNIGINE_INLINE static void construct(Slot &slot, Slot &&from)
	{
		slot = from;
		from = nullptr;
	}

	UNIGINE_INLINE static void swap(Slot &s0, Slot &s1)
	{
		Slot temp = s0;
		s0 = s1;
		s1 = temp;
	}

	template<class... Args>
	UNIGINE_INLINE static void replace(Slot &slot, Args &&...args)
	{
		slot->data.~Value();
		new (&slot->data) Value(std::forward<Args>(args)...);
	}
	UNIGINE_INLINE static void replace(Slot &slot, const Slot &from) { slot->data = from->data; }
	UNIGINE_INLINE static void replace(Slot &slot, Slot &&from) { std::swap(slot, from); }

	UNIGINE_INLINE static Element &element(Slot &slot) { return *slot; }

	UNIGINE_INLINE static void destruct(Slot &slot)
	{
		if (!slot)
			return;
		slot->~Element();
		Memory::deallocatePool<sizeof(Element)>(slot);
	}
};

template<class Self, class Policy, class Counter>
class HashMapBase : public Hash<Policy, Counter>
{
	using Base = Hash<Policy, Counter>;
public:
	using Key = typename Policy::Key;
	using Value = typename Policy::Value;
	using Slot = typename Policy::Slot;
	using Iterator = typename Base::Iterator;
	using ConstIterator = typename Base::ConstIterator;
	using Parent = Hash<Policy, Counter>;

	using Base::Base;
	HashMapBase() = default;

	HashMapBase(std::initializer_list<Pair<Key, Value>> init)
	{
		Parent::reserve(init.size());
		for (const auto &v : init)
		{
			Parent::emplace(v.first, v.second);
		}
	}

	using Base::append;
	Iterator append(const Key &key, const Value &value) { return Parent::emplace(key, value); }
	Iterator append(const Key &key, Value &&value) { return Parent::emplace(key, std::move(value)); }
	Iterator append(Key &&key, const Value &value) { return Parent::emplace(std::move(key), value); }
	Iterator append(Key &&key, Value &&value)
	{
		return Parent::emplace(std::move(key), std::move(value));
	}
	template<class K, std::enable_if_t<!Internal::IsBaseOf<Base, K>::value && !Internal::IsBaseOf<Vector<Key>, K>::value, int> = 0>
	Value &append(K &&k)
	{
		return Parent::emplace_noreplace(std::forward<K>(k))->data;
	}

	using Base::insert;
	Iterator insert(const Key &key, const Value &value) { return Parent::emplace(key, value); }
	Iterator insert(const Key &key, Value &&value) { return Parent::emplace(key, std::move(value)); }
	Iterator insert(Key &&key, const Value &value) { return Parent::emplace(std::move(key), value); }
	Iterator insert(Key &&key, Value &&value)
	{
		return Parent::emplace(std::move(key), std::move(value));
	}
	template<class K, std::enable_if_t<!Internal::IsBaseOf<Base, K>::value && !Internal::IsBaseOf<Vector<Key>, K>::value, int> = 0>
	Value &insert(K &&k)
	{
		return Parent::emplace_noreplace(std::forward<K>(k))->data;
	}

	template<class K>
	Value take(const K &k, const Value &def)
	{
		auto it = Parent::find(k);
		return it != Parent::end() ? take(it) : def;
	}

	template<class K>
	Value take(const K &k)
	{
		auto it = Parent::find(k);
		return it != Parent::end() ? take(it) : Value{};
	}

	Value take(Iterator it)
	{
		Value result = std::move(it->data);
		Parent::erase(it);
		return result;
	}

	Value take(ConstIterator it) { return take(it.it_); }

	using Base::contains;

	template<class K, class V>
	bool contains(const K &k, const V &v) const
	{
		auto it = Parent::find(k);
		return it != Parent::end() && it->data == v;
	}

	template<class V>
	Iterator findData(const V &v)
	{
		auto e = Parent::end();
		for (auto it = Parent::begin(); it != e; ++it)
		{
			if (it->data == v)
				return it;
		}
		return e;
	}

	template<class V>
	ConstIterator findData(const V &v) const
	{
		return const_cast<HashMapBase *>(this)->findData(v);
	}

	template<class V>
	void removeData(const V &v)
	{
		auto it = const_cast<HashMapBase *>(this)->findData(v);
		if (it != Parent::end())
			Parent::remove(it);
	}

	template<class K>
	Value &get(K &&k)
	{
		return append(std::forward<K>(k));
	}

	template<class K>
	const Value &get(const K &k) const
	{
		Counter pos;
		bool result = Parent::do_find(k, pos);
		assert(result); UNIGINE_UNUSED(result);
		return Policy::element(Parent::get_slot_data()[pos]).data;
	}

	template<class K>
	const Value &get(const K &k, const Value &value) const
	{
		Counter pos;
		return Parent::do_find(k, pos) ? Policy::element(Parent::get_slot_data()[pos]).data : value;
	}

	template<typename K>
	Value &operator[](K &&k)
	{
		return get(std::forward<K>(k));
	}

	template<typename K>
	const Value &operator[](const K &k) const
	{
		return get(k);
	}

	template<typename K>
	Value value(const K &k) const
	{
		Counter pos;
		return Parent::do_find(k, pos) ? Policy::element(Parent::get_slot_data()[pos]).data : Value{};
	}

	template<typename K>
	const Value &value(const K &k, const Value &value) const
	{
		return get(k, value);
	}

	template<typename K>
	const Value &valueRef(const K &k) const
	{
		return Parent::get(k);
	}

	template<typename K>
	const Value &valueRef(const K &k, const Value &value) const
	{
		return get(k, value);
	}

	Vector<Value> values() const
	{
		Vector<Value> values;
		getValues(values);
		return values;
	}

	void getValues(Vector<Value> &values) const
	{
		values.clear();
		values.allocate(Parent::size());
		Parent::traverse_full_slots([&values](Slot *slot) { values.appendFast(Policy::element(*slot).data); });
	}
};

} // namespace Internal

template<class Key, class Value, class Counter = unsigned int>
class HashMap
	: public Internal::HashMapBase<HashMap<Key, Value, Counter>,
		  Internal::FlatHashMapPolicy<Key, Value>, Counter>
{
	using Base = Internal::HashMapBase<HashMap<Key, Value, Counter>,
		Internal::FlatHashMapPolicy<Key, Value>, Counter>;

public:
	using Base::Base;
};


template<class Key, class Value, class Counter = unsigned int>
class BucketHashMap
	: public Internal::HashMapBase<HashMap<Key, Value, Counter>,
		  Internal::BucketHashMapPolicy<Key, Value>, Counter>
{
	using Base = Internal::HashMapBase<HashMap<Key, Value, Counter>,
		Internal::BucketHashMapPolicy<Key, Value>, Counter>;

public:
	using Base::Base;
};

} // namespace Unigine
