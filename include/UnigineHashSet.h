/* Copyright (C) 2005-2025, UNIGINE. All rights reserved.
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

#include <utility>

namespace Unigine
{

namespace Internal
{
template<class Key>
struct HashSetData
{
	using HashType = typename Hasher<Key>::HashType;

	template<class K, std::enable_if_t<!IsSame<K, HashSetData>::value, int> = 0>
	UNIGINE_INLINE HashSetData(HashType h, K&& k)
		: hash(h)
		, key(std::forward<K>(k))
	{}

	UNIGINE_INLINE friend bool operator==(const HashSetData &l, const HashSetData &r) { return l.hash == r.hash && l.key == r.key; }
	UNIGINE_INLINE friend bool operator!=(const HashSetData &l, const HashSetData &r) { return !(l == r); }

	const HashType hash;
	const Key key;
};

template<typename T>
struct FlatHashSetPolicy
{

	using Key = T;
	using Slot = HashSetData<Key>;
	using Element = HashSetData<Key>;
	using HashType = typename Hasher<Key>::HashType;

	UNIGINE_INLINE static HashType hash(const Slot &s) { return s.hash; }
	UNIGINE_INLINE static const Key &key(const Slot &s) { return s.key; }

	template<class... Args>
	UNIGINE_INLINE static void construct(Slot &slot, HashType hash, Args &&...args)
	{
		new (&slot) Slot(hash, std::forward<Args>(args)...);
	}

	UNIGINE_INLINE static void construct(Slot &slot, const Slot &from) { new (&slot) Slot{from.hash, from.key}; }

	UNIGINE_INLINE static void construct(Slot &slot, Slot &&from)
	{
		new (&slot) Slot{from.hash, std::move(const_cast<Key &>(from.key))};
	}

	UNIGINE_INLINE static void swap(Slot &s0, Slot &s1)
	{
		std::swap(const_cast<HashType &>(s0.hash), const_cast<HashType &>(s1.hash));
		std::swap(const_cast<Key &>(s0.key), const_cast<Key &>(s1.key));
	}

	template<class... Args>
	UNIGINE_INLINE static void replace(Slot &, Args &&...)
	{}

	UNIGINE_INLINE static Element &element(Slot &slot) { return slot; }

	UNIGINE_INLINE static void destruct(Slot &slot) { slot.~Slot(); }
};

template<typename T>
struct BucketHashSetPolicy
{

	using Key = T;
	using Slot = HashSetData<Key> *;
	using Element = HashSetData<Key>;
	using HashType = typename Hasher<Key>::HashType;

	UNIGINE_INLINE static HashType hash(const Slot &s) { return s->hash; }
	UNIGINE_INLINE static const Key &key(const Slot &s) { return s->key; }

	template<class... Args>
	UNIGINE_INLINE static void construct(Slot &slot, HashType hash, Args &&...args)
	{
		slot = new (Memory::allocatePool<sizeof(Element)>()) Element{hash, std::forward<Args>(args)...};
	}

	UNIGINE_INLINE static void construct(Slot &slot, const Slot &from)
	{
		slot = new (Memory::allocatePool<sizeof(Element)>()) Element{from->hash, from->key};
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
	UNIGINE_INLINE static void replace(Slot &, Args &&...)
	{}

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
class HashSetBase : public Hash<Policy, Counter>
{
	using Base = Hash<Policy, Counter>;
public:
	using Parent = Hash<Policy, Counter>;
	using Key = typename Policy::Key;
	using Iterator = typename Base::Iterator;
	using ConstIterator = typename Base::ConstIterator;
	using value_type = Key;

	using Base::Base;

	using Base::append;
	void append(const Key &key) { Parent::emplace(key); }
	void append(Key &&key) { Parent::emplace(std::move(key)); }

	using Base::insert;
	void insert(const Key &key) { Parent::emplace(key); }
	void insert(Key &&key) { Parent::emplace(std::move(key)); }

	template<class K>
	Self &operator+=(const K &k)
	{
		Parent::emplace(k);
		return self();
	}
	Self &operator+=(const Self &o)
	{
		Parent::emplace(o);
		return self();
	}
	template<class K>
	Self &operator-=(const K &k)
	{
		Parent::erase(k);
		return self();
	}
	Self &operator-=(const Self &o)
	{
		Parent::subtract(o);
		return self();
	}

	static Self fromKeys(const Key *keys, size_t size)
	{
		Self result;
		result.reserve(size);
		for (size_t i = 0; i < size; ++i)
		{
			result.insert(keys[i]);
		}
		return result;
	}

	static Self fromKeys(const Vector<Key> &keys) { return fromKeys(keys.get(), keys.size()); }

	static Self fromKeys(Vector<Key> &&keys)
	{
		const auto size = keys.size();
		Self result;
		result.reserve(size);
		for (auto i = 0; i < size; ++i)
			result.insert(std::move(keys[i]));
		keys.clear();
		return result;
	}

private:
	Self &self() { return static_cast<Self &>(*this); }
};

} // namespace Internal

template<class Key, class Counter = unsigned int>
class HashSet
	: public Internal::HashSetBase<HashSet<Key, Counter>, Internal::FlatHashSetPolicy<Key>, Counter>
{
	using Base
		= Internal::HashSetBase<HashSet<Key, Counter>, Internal::FlatHashSetPolicy<Key>, Counter>;

public:
	using Base::Base;
};

template<class Key, class Counter = unsigned int>
class BucketHashSet
	: public Internal::HashSetBase<BucketHashSet<Key, Counter>, Internal::BucketHashSetPolicy<Key>,
		  Counter>
{
	using Base = Internal::HashSetBase<BucketHashSet<Key, Counter>, Internal::BucketHashSetPolicy<Key>,
		Counter>;

public:
	using Base::Base;
};

} // namespace Unigine
