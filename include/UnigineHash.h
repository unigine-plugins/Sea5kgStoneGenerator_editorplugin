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

#include <UnigineMemory.h>
#include <UnigineVector.h>

#include <cstring>
#include <iterator>
#include <type_traits>

#ifndef USE_SSE
	#define USE_SSE
#endif

#ifdef USE_SSE
	#include <emmintrin.h>
	#include <tmmintrin.h>
#endif

#if defined(_MSC_VER) && !defined(__clang__)
	#include <intrin.h>
#endif

namespace Unigine
{

UNIGINE_INLINE unsigned int murmur3Mixer(unsigned int value)
{
	value ^= 0xdeadbeef;
	value ^= value >> 16;
	value *= 0x85ebca6b;
	value ^= value >> 13;
	value *= 0xc2b2ae35;
	value ^= value >> 16;
	return value;
}

UNIGINE_INLINE unsigned long long murmur3Mixer(unsigned long long value)
{
	value ^= 0x2127599bf4325c37ULL;
	value ^= value >> 33;
	value *= 0xff51afd7ed558ccdULL;
	value ^= value >> 33;
	value *= 0xc4ceb9fe1a85ec53ULL;
	value ^= value >> 33;
	return value;
}

template<bool IsBig>
struct HashTypeDispatch
{
	using Type = unsigned int;
};
template<>
struct HashTypeDispatch<true>
{
	using Type = unsigned long long;
};

template<typename Type>
struct Hasher
{
	using HashType = uintptr_t;
	UNIGINE_INLINE static HashType create(const Type &t)
	{
		UNIGINE_UNUSED(t)
		static_assert(sizeof(Type) == 0 && false, "Hash function undefined.");
		return 0;
	}
};

template<typename Type>
struct Hasher<Type *>
{
	using HashType = unsigned long long;
	UNIGINE_INLINE static HashType create(Type *t)
	{
		return murmur3Mixer(reinterpret_cast<unsigned long long>(t));
	}
};

template<typename Type>
struct Hasher<const Type *>
{
	using HashType = unsigned long long;
	UNIGINE_INLINE static HashType create(const Type *t)
	{
		return murmur3Mixer(reinterpret_cast<unsigned long long>(t));
	}
};

#define UNIGINE_DECLARE_DEFAULT_HASHER(TYPE)                                                       \
	template<>                                                                                     \
	struct Hasher<TYPE>                                                                            \
	{                                                                                              \
		using HashType = HashTypeDispatch<(sizeof(TYPE) > 4)>::Type;                               \
		UNIGINE_INLINE static HashType create(TYPE t)                                              \
		{                                                                                          \
			return HashType(murmur3Mixer(HashType(t)));                                            \
		}                                                                                          \
	};                                                                                             \
	template<>                                                                                     \
	struct Hasher<unsigned TYPE>                                                                   \
	{                                                                                              \
		using HashType = HashTypeDispatch<(sizeof(unsigned TYPE) > 4)>::Type;                      \
		UNIGINE_INLINE static HashType create(unsigned TYPE t)                                     \
		{                                                                                          \
			return HashType(murmur3Mixer(HashType(t)));                                            \
		}                                                                                          \
	};

UNIGINE_DECLARE_DEFAULT_HASHER(char)
UNIGINE_DECLARE_DEFAULT_HASHER(int)
UNIGINE_DECLARE_DEFAULT_HASHER(short)
UNIGINE_DECLARE_DEFAULT_HASHER(long int)
UNIGINE_DECLARE_DEFAULT_HASHER(long long int)
#undef UNIGINE_DECLARE_DEFAULT_HASHER

namespace Internal
{

UNIGINE_INLINE int countTrailingZeroes(unsigned char x)
{
	assert(x);
#if defined(_MSC_VER) && !defined(__clang__)
	return (int)_tzcnt_u32(x);
#else
	return __builtin_ctz(x);
#endif
}

UNIGINE_INLINE int countTrailingZeroes(unsigned short int x)
{
	assert(x);
#if defined(_MSC_VER) && !defined(__clang__)
	return (int)_tzcnt_u32(x);
#else
	return __builtin_ctz(x);
#endif
}

UNIGINE_INLINE int countTrailingZeroes(unsigned int x)
{
	assert(x);
#if defined(_MSC_VER) && !defined(__clang__)
	return (int)_tzcnt_u32(x);
#else
	return __builtin_ctz(x);
#endif
}

UNIGINE_INLINE int countTrailingZeroes(unsigned long long int x)
{
	assert(x);
#if defined(_MSC_VER) && !defined(__clang__)
	return (int)_tzcnt_u64(x);
#else
	return __builtin_ctzll(x);
#endif
}

UNIGINE_INLINE int countBitSet(unsigned char x)
{
#if defined(_MSC_VER) && !defined(__clang__)
	return __popcnt16(x);
#else
	return __builtin_popcount(x);
#endif
}

UNIGINE_INLINE int countBitSet(unsigned short int x)
{
#if defined(_MSC_VER) && !defined(__clang__)
	return __popcnt16(x);
#else
	return __builtin_popcount(x);
#endif
}

UNIGINE_INLINE int countBitSet(unsigned int x)
{
#if defined(_MSC_VER) && !defined(__clang__)
	return __popcnt(x);
#else
	return __builtin_popcount(x);
#endif
}

UNIGINE_INLINE int countBitSet(unsigned long long int x)
{
#if defined(_MSC_VER) && !defined(__clang__)
	return static_cast<int>(__popcnt64(x));
#else
	return __builtin_popcountll(x);
#endif
}

enum Control : char
{
	CONTROL_EMPTY = -128, // 0b10000000
	CONTROL_REMAP = -3, // 0b11111101
	CONTROL_DELETED = -2, // 0b11111110
	CONTROL_END = -1 // 0b11111111
};
static_assert(sizeof(Control) == 1, "Unexpected char size");

UNIGINE_INLINE bool isEmptyOrDeleted(Control c)
{
	return c < CONTROL_END;
}
UNIGINE_INLINE bool isFull(Control c)
{
	return (c & 0b10000000) == 0;
}

using ControlHash = unsigned char;

template<class T, int SignificantBits>
class BitMask
{
public:
	UNIGINE_INLINE explicit BitMask(T mask)
		: mask_(mask)
	{}

	UNIGINE_INLINE explicit operator bool() const { return mask_ != 0; }

	UNIGINE_INLINE int lowestBitSet() const { return trailingZeroes(); }

	UNIGINE_INLINE int trailingZeroes() const { return countTrailingZeroes(mask_); }
	UNIGINE_INLINE int allBitSet() const { return countBitSet(mask_); }

	UNIGINE_INLINE BitMask &operator++()
	{
		mask_ &= mask_ - 1;
		return *this;
	}

	UNIGINE_INLINE BitMask begin() const { return *this; }
	UNIGINE_INLINE BitMask end() const { return BitMask(0); }

	UNIGINE_INLINE int operator*() const { return lowestBitSet(); }

	UNIGINE_INLINE friend bool operator==(const BitMask &l, const BitMask &r) { return l.mask_ == r.mask_; }
	UNIGINE_INLINE friend bool operator!=(const BitMask &l, const BitMask &r) { return l.mask_ != r.mask_; }

private:
	T mask_;
};

#ifdef USE_SSE

struct GroupSse
{
	static constexpr size_t Width = 16;
	using BitMask = Internal::BitMask<unsigned short int, Width>;
	UNIGINE_INLINE GroupSse() = default;

	UNIGINE_INLINE explicit GroupSse(const Control *ctrl)
	{
		load(ctrl);
	}

	UNIGINE_INLINE void load(const Control *ctrl)
	{
		group = _mm_loadu_si128(reinterpret_cast<const __m128i *>(ctrl));
	}

	UNIGINE_INLINE void loadAligned(const Control *ctrl)
	{
		group = _mm_load_si128(reinterpret_cast<const __m128i *>(ctrl));
	}

	UNIGINE_INLINE static __m128i createMatch(ControlHash hash)
	{
		return _mm_set1_epi8(static_cast<char>(hash));
	}

	UNIGINE_INLINE BitMask match(__m128i match) const
	{
		return BitMask{static_cast<unsigned short int>(
			_mm_movemask_epi8(_mm_cmpeq_epi8(match, group)))};
	}

	UNIGINE_INLINE BitMask maskEmpty() const
	{
		return BitMask{static_cast<unsigned short int>(
			_mm_movemask_epi8(_mm_sign_epi8(group, group)))};
	}

	UNIGINE_INLINE BitMask maskEmptyOrRemap() const
	{
		auto special = _mm_set1_epi8(static_cast<char>(CONTROL_DELETED));
		return BitMask{static_cast<unsigned short int>(
			_mm_movemask_epi8(_mm_cmpgt_epi8(special, group)))};
	}

	UNIGINE_INLINE BitMask maskDeleted() const
	{
		auto special = _mm_set1_epi8(static_cast<char>(CONTROL_DELETED));
		return BitMask{static_cast<unsigned short int>(
			_mm_movemask_epi8(_mm_cmpeq_epi8(special, group)))};
	}

	UNIGINE_INLINE BitMask maskDeleted(int offset) const
	{
		auto special = _mm_set1_epi8(static_cast<char>(CONTROL_DELETED));
		return BitMask{static_cast<unsigned short int>(
			_mm_movemask_epi8(_mm_cmpeq_epi8(special, group)) << offset)};
	}

	UNIGINE_INLINE int countLeadingEmptyOrDeleted() const
	{
		auto special = _mm_set1_epi8(static_cast<char>(CONTROL_END));
		return countTrailingZeroes(
			static_cast<unsigned int>(_mm_movemask_epi8(_mm_cmpgt_epi8(special, group)) + 1));
	}

	UNIGINE_INLINE BitMask maskFull() const
	{
		return BitMask{static_cast<unsigned short int>(_mm_movemask_epi8(group) ^ 0xffff)};
	}

	__m128i group;
};

#endif

struct GroupPortable
{
	static constexpr size_t Width = 8;
	using BitMask = Internal::BitMask<unsigned char, Width>;
	static constexpr unsigned long long int MaskOne  = 0x0101010101010101ULL;
	static constexpr unsigned long long int MaskSign = 0x8080808080808080ULL;

	UNIGINE_INLINE GroupPortable() = default;

	UNIGINE_INLINE explicit GroupPortable(const Control *ctrl)
	{
		load(ctrl);
	}

	UNIGINE_INLINE void load(const Control *ctrl)
	{
		data = *reinterpret_cast<const unsigned long long int *>(ctrl);
	}

	UNIGINE_INLINE void loadAligned(const Control *ctrl) { load(ctrl); }

	UNIGINE_INLINE static unsigned long long int createMatch(ControlHash hash)
	{
		return MaskOne * hash;
	}

	UNIGINE_INLINE BitMask match(unsigned long long int match) const
	{
		unsigned long long int x = data ^ match;
		return BitMask{move_mask((x - MaskOne) & ~x & MaskSign)};
	}

	UNIGINE_INLINE BitMask maskEmpty() const
	{
		return BitMask{match_byte(CONTROL_EMPTY)};
	}

	UNIGINE_INLINE BitMask maskEmptyOrRemap() const
	{
		return BitMask{static_cast<unsigned char>(match_byte(CONTROL_EMPTY) | match_byte(CONTROL_REMAP))};
	}

	UNIGINE_INLINE BitMask maskDeleted() const
	{
		return BitMask{match_byte(CONTROL_DELETED)};
	}

	UNIGINE_INLINE BitMask maskDeleted(int offset) const
	{
		return BitMask{static_cast<unsigned char>(match_byte(CONTROL_DELETED) << offset)};
	}

	UNIGINE_INLINE int countLeadingEmptyOrDeleted() const
	{
		return countTrailingZeroes(static_cast<unsigned int>(
			match_byte(CONTROL_EMPTY) | match_byte(CONTROL_DELETED)) + 1);
	}

	UNIGINE_INLINE BitMask maskFull() const
	{
		return BitMask{static_cast<unsigned char>(move_mask(data & MaskSign) ^ 0b11111111)};
	}

private:
	UNIGINE_INLINE unsigned char match_byte(char match) const
	{
		unsigned char mask = 0;
		for (size_t i = 0; i < Width; ++i)
			mask |= (data_byte[i] == static_cast<unsigned char>(match)) << i;
		return mask;
	}

	UNIGINE_INLINE static unsigned char move_mask(unsigned long long int m)
	{
		unsigned char mask = 0;
		for (size_t i = 0; i < Width; ++i)
			mask |= (((m >> (i * 8)) & 0b10000000) != 0) << i;
		return mask;
	}

	union
	{
		unsigned long long int data;
		unsigned char data_byte[Width];
	};
};

#ifdef USE_SSE
	using Group = GroupSse;
#else
	using Group = GroupPortable;
#endif

template<class Counter, size_t Width>
class ProbeSeq
{
public:
	UNIGINE_INLINE ProbeSeq(size_t hash, Counter capacity)
		: offset_(getIndex(hash, capacity))
		, capacity_(capacity)
		, index_(0)
	{
	}

	UNIGINE_INLINE Counter offset() const { return offset_; }
	UNIGINE_INLINE Counter offset(size_t i) const { return getIndex(offset_ + i, capacity_); }
	UNIGINE_INLINE Counter index() const { return index_; }

	UNIGINE_INLINE static Counter getIndex(size_t pos, Counter capacity)
	{
		return static_cast<Counter>(pos >= capacity ? pos % capacity : pos);
	}
	UNIGINE_INLINE void next()
	{
		index_ += Width;
		offset_ = getIndex(offset_ + Width, capacity_);
	}

private:
	Counter offset_;
	Counter capacity_;
	Counter index_;
};

template<class A, class B>
struct IsSame
	: std::is_same<std::remove_cv_t<std::remove_reference_t<A>>,
		  std::remove_cv_t<std::remove_reference_t<B>>>
{
};

template<class A, class B>
struct IsBaseOf
	: std::is_base_of<std::remove_cv_t<std::remove_reference_t<A>>,
		  std::remove_cv_t<std::remove_reference_t<B>>>
{
};

template<class Policy, class Counter>
class Hash
{
	using Key = typename Policy::Key;
	using Element = typename Policy::Element;
	using Slot = typename Policy::Slot;
	using ProbeSeq = Internal::ProbeSeq<Counter, Group::Width>;
	using HashType = typename Policy::HashType;

public:

	static constexpr size_t LoadFactorPercent = 85;
	static constexpr size_t MinCapacity = 16;

	class Iterator
	{
		friend class Hash;

	public:
		using key_type = Key;
		using value_type = Element;
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type *;
		using reference = value_type &;

		UNIGINE_INLINE Iterator() = default;

		UNIGINE_INLINE Iterator(Control *ctrl, Slot *slot, Counter pos)
			: ctrl_(ctrl + pos)
			, slot_(slot + pos)
		{
			assert(ctrl_ && isFull(*ctrl_));
		}

		UNIGINE_INLINE Iterator(Control *ctrl, Slot *slot)
			: ctrl_(ctrl)
			, slot_(slot)
		{
			assert(ctrl_);
			skip_empty_or_deleted();
		}

		UNIGINE_INLINE reference operator*() const
		{
			assert(ctrl_);
			return Policy::element(*slot_);
		}
		UNIGINE_INLINE pointer operator->() const
		{
			assert(ctrl_);
			return &Policy::element(*slot_);
		}

		UNIGINE_INLINE Iterator &operator++()
		{
			assert(ctrl_);
			++ctrl_;
			++slot_;
			skip_empty_or_deleted();
			return *this;
		}

		UNIGINE_INLINE Iterator operator++(int)
		{
			auto tmp = *this;
			++*this;
			return tmp;
		}

		UNIGINE_INLINE friend bool operator==(const Iterator &l, const Iterator &r) { return l.ctrl_ == r.ctrl_; }
		UNIGINE_INLINE friend bool operator!=(const Iterator &l, const Iterator &r) { return l.ctrl_ != r.ctrl_; }

	private:
		void skip_empty_or_deleted()
		{
			Group g;
			while (isEmptyOrDeleted(*ctrl_))
			{
				g.load(ctrl_);
				int shift = g.countLeadingEmptyOrDeleted();
				ctrl_ += shift;
				slot_ += shift;
			}

			ctrl_ = *ctrl_ == CONTROL_END ? nullptr : ctrl_;
		}

		Control *ctrl_{};
		Slot *slot_{};
	};

	class ConstIterator
	{
		friend class Hash;

	public:
		using key_type = Key;
		using value_type = Element;
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using pointer = const value_type *;
		using reference = const value_type &;

		UNIGINE_INLINE ConstIterator() = default;

		UNIGINE_INLINE ConstIterator(Iterator it)
			: it_(std::move(it))
		{}

		UNIGINE_INLINE reference operator*() const { return *it_; }
		UNIGINE_INLINE pointer operator->() const { return it_.operator->(); }

		UNIGINE_INLINE ConstIterator &operator++()
		{
			++it_;
			return *this;
		}
		UNIGINE_INLINE ConstIterator operator++(int) { return it_++; }

		UNIGINE_INLINE friend bool operator==(const ConstIterator &l, const ConstIterator &r)
		{
			return l.it_ == r.it_;
		}

		UNIGINE_INLINE friend bool operator!=(const ConstIterator &l, const ConstIterator &r)
		{
			return l.it_ != r.it_;
		}

	private:
		Iterator it_;
	};

	using iterator = Iterator;
	using const_iterator = ConstIterator;
	using size_type = Counter;

	Hash() = default;

	Hash(const Hash &o)
	{
		reserve(o.size());
		o.traverse_full_slots([this](const Slot *slot) { append_non_existent_slot(*slot); });
	}

	Hash &operator=(const Hash &o)
	{
		if (this == &o)
			return *this;

		clear();
		reserve(o.size());
		o.traverse_full_slots([this](const Slot *slot) { append_non_existent_slot(*slot); });
		return *this;
	}

	Hash(Hash &&o)
	{
		swap(o);
		o.clear();
	}

	Hash &operator=(Hash &&o)
	{
		if (this == &o)
			return *this;

		swap(o);
		o.clear();
		return *this;
	}

	~Hash() { destroy(); }

	template<class T>
	Hash(std::initializer_list<T> init)
	{
		reserve(init.size());
		emplaceRange(init.begin(), init.end());
	}

	template<class K, class... Args, std::enable_if_t<!IsBaseOf<Hash, K>::value && !Internal::IsBaseOf<Vector<Key>, K>::value, int> = 0>
	UNIGINE_INLINE Iterator append(K &&key, Args &&...args)
	{
		return emplace(std::forward<K>(key), std::forward<Args>(args)...);
	}

	UNIGINE_INLINE void append(const Hash &o) { emplace(o); }
	UNIGINE_INLINE void append(Hash &&o) { emplace(std::move(o)); }

	template <typename T, typename C, typename A>
	UNIGINE_INLINE void append(const Vector<T, C, A> &vector) { emplace(vector); }
	template <typename T, typename C, typename A>
	UNIGINE_INLINE void append(Vector<T, C, A> &&vector) { emplace(std::move(vector)); }

	template<class K, class... Args, std::enable_if_t<!IsBaseOf<Hash, K>::value && !Internal::IsBaseOf<Vector<Key>, K>::value, int> = 0>
	UNIGINE_INLINE Iterator insert(K &&key, Args &&...args)
	{
		return emplace(std::forward<K>(key), std::forward<Args>(args)...);
	}
	UNIGINE_INLINE void insert(const Hash &o) { emplace(o); }
	UNIGINE_INLINE void insert(Hash &&o) { emplace(std::move(o)); }
	template <typename T, typename C, typename A>
	UNIGINE_INLINE void insert(const Vector<T, C, A> &vector) { emplace(vector); }
	template <typename T, typename C, typename A>
	UNIGINE_INLINE void insert(Vector<T, C, A> &&vector) { emplace(std::move(vector)); }

	template<class K, class... Args, std::enable_if_t<!IsBaseOf<Hash, K>::value && !Internal::IsBaseOf<Vector<Key>, K>::value, int> = 0>
	UNIGINE_INLINE Iterator emplace(K &&k, Args &&...args)
	{
		Counter pos;
		const HashType hash = create_hash(k);
		find_or_prepare_emplace(hash, k, pos)
			? construct_slot(pos, hash, std::forward<K>(k), std::forward<Args>(args)...)
			: replace_slot(pos, std::forward<Args>(args)...);
		return iterator_at(pos);
	}

	template<class K, class... Args>
	UNIGINE_INLINE Iterator emplace_noreplace(K &&k, Args &&...args)
	{
		Counter pos;
		const HashType hash = create_hash(k);
		if (find_or_prepare_emplace(hash, k, pos))
			construct_slot(pos, hash, std::forward<K>(k), std::forward<Args>(args)...);
		return iterator_at(pos);
	}

	template <typename T, typename C, typename A>
	void emplace(const Vector<T, C, A> &vector)
	{
		reserve(size() + vector.size());
		for (const T &v : vector)
			emplace(v);
	}

	template <typename T, typename C, typename A>
	void emplace(Vector<T, C, A> &&vector)
	{
		reserve(size() + vector.size());
		for (T &v : vector)
			emplace(std::move(v));
		vector.clear();
	}

	void emplace(const Hash &o)
	{
		if (this == &o)
			return;

		reserve(size() + o.size());
		o.traverse_full_slots([this](const Slot *slot) {
			Counter pos;
			find_or_prepare_emplace(hash(slot), key(slot), pos)
				? construct_slot(pos, *slot)
				: replace_slot(pos, *slot);
		});
	}

	void emplace(Hash &&o)
	{
		if (this == &o)
			return;

		reserve(size() + o.size());
		o.traverse_full_slots([this](Slot *slot) {
			Counter pos;
			find_or_prepare_emplace(hash(slot), key(slot), pos)
				? construct_slot(pos, std::move(*slot))
				: replace_slot(pos, std::move(*slot));
		});
		o.clear();
	}

	template<class InputIt>
	void emplaceRange(InputIt first, InputIt last)
	{
		for (; first != last; ++first)
		{
			emplace(*first);
		}
	}

	template<typename K>
	UNIGINE_INLINE bool contains(const K &k) const
	{
		Counter pos;
		return data && do_find(k, pos);
	}

	template<typename K>
	UNIGINE_INLINE Iterator find(const K &key)
	{
		Counter pos;
		return data && do_find(key, pos) ? iterator_at(pos) : end();
	}

	template<typename K>
	UNIGINE_INLINE ConstIterator find(const K &key) const
	{
		return const_cast<Hash *>(this)->find(key);
	}

	template<typename K>
	UNIGINE_INLINE Element *findFast(const K &key) const
	{
		Counter pos;
		return data && do_find(key, pos) ? &Policy::element(get_slot_data()[pos]) : nullptr;
	}

	Unigine::Vector<Key> keys() const
	{
		Unigine::Vector<Key> result;
		getKeys(result);
		return result;
	}

	void getKeys(Vector<Key> &keys) const
	{
		keys.clear();
		keys.allocate(size());
		traverse_full_slots([&keys](const Slot *slot) { keys.appendFast(key(slot)); });
	}

	const Key &getKey(size_t index) const
	{
		auto it = begin();
		while (index)
		{
			--index;
			++it;
		}
		return key(*it);
	}

	template<class K, std::enable_if_t<!IsBaseOf<Hash, K>::value, int> = 0>
	UNIGINE_INLINE bool remove(const K &k)
	{
		return erase(k);
	}
	void remove(Iterator it) { erase(it); }
	void remove(ConstIterator it) { erase(it); }
	void remove(const Hash &o) { erase(o); }
	template <typename T, typename C, typename A>
	void remove(const Vector<T, C, A> &v) { erase(v); }

	Iterator erase(Iterator it)
	{
		assert(it.ctrl_);
		destroy_slot(it.slot_, it.ctrl_);
		if (isFull(*it.ctrl_))
			return it;
		it.skip_empty_or_deleted();
		return it;
	}
	ConstIterator erase(ConstIterator it) { return erase(it.it_); }

	template<class K, std::enable_if_t<!IsBaseOf<Hash, K>::value, int> = 0>
	UNIGINE_INLINE bool erase(const K &k)
	{
		Counter pos;
		if (!do_find(k, pos))
			return false;

		destroy_slot(get_slot_data() + pos, get_controls_data() + pos);
		return true;
	}

	void erase(const Hash &o) { subtract(o); }
	template <typename T, typename C, typename A>
	void erase(const Vector<T, C, A> &v) { subtract(v); }

	template <typename T, typename C, typename A>
	UNIGINE_INLINE void subtract(const Vector<T, C, A> &vector)
	{
		for (const T &v : vector)
			remove(v);
	}

	void subtract(const Hash &o)
	{
		if (this == &o)
		{
			clear();
			return;
		}
		o.traverse_full_slots([this](const Slot *slot) { erase(key(slot)); });
	}

	void clear()
	{
		if (!data || length == 0)
			return;

		traverse_full_slots([this](Slot *slot) { Policy::destruct(*slot); });
		length = 0;
		reset_controls();
	}

	void destroy()
	{
		if (!data)
			return;

		traverse_full_slots([this](Slot *slot) { Policy::destruct(*slot); });
		Memory::deallocate(data);
		capacity = 0;
		length = 0;
		data = nullptr;
	}

	void reserve(size_t size)
	{
		const size_t new_capacity = capacity_for(size);
		assert(get_max_size() >= new_capacity && "Unigine::Hash::reserve: Counter is small");
		if (new_capacity <= capacity)
			return;

		rehash(static_cast<Counter>(new_capacity));
	}

	void shrink()
	{
		if (!data)
			return;

		if (empty())
		{
			destroy();
			return;
		}

		const size_t new_capacity = capacity_for(size());
		if (new_capacity < capacity)
			rehash(static_cast<Counter>(new_capacity));
	}

	UNIGINE_INLINE Iterator begin() { return empty() ? end() : Iterator(get_controls_data(), get_slot_data()); }
	UNIGINE_INLINE Iterator end() { return {}; }

	UNIGINE_INLINE ConstIterator begin() const { return const_cast<Hash *>(this)->begin(); }
	UNIGINE_INLINE ConstIterator end() const { return {}; }

	UNIGINE_INLINE ConstIterator cbegin() const { return begin(); }
	UNIGINE_INLINE ConstIterator cend() const { return {}; }

	UNIGINE_INLINE Counter size() const { return length; }
	UNIGINE_INLINE Counter space() const { return capacity; }
	UNIGINE_INLINE size_t getMemoryUsage() const { return sizeof(*this) + get_controls_size(capacity) + get_slots_size(capacity); }
	UNIGINE_INLINE bool empty() const { return size() == 0; }

	UNIGINE_INLINE void swap(Hash &o)
	{
		std::swap(data, o.data);
		std::swap(length, o.length);
		std::swap(capacity, o.capacity);
	}

	template<typename K>
	UNIGINE_INLINE Counter getNumProbes(const K &key) const
	{
		if (!data)
			return 0;

		const HashType hash = create_hash(key);
		const Control *controls = get_controls_data();
		const ControlHash control_hash = remove_sign_bit(hash);
		ProbeSeq seq = create_probe(hash);

		Counter pos = seq.offset();
		if (controls[pos] == control_hash && equal(pos, hash, key))
			return 1;

		Group g;
		const auto group_control_hash = Group::createMatch(control_hash);
		Counter probes = 0;
		do
		{
			g.load(controls + seq.offset());
			for (int i : g.match(group_control_hash))
			{
				++probes;
				pos = seq.offset(i);
				if (equal(pos, hash, key))
					return probes;
			}

			if (g.maskEmpty())
				return probes;
			seq.next();
		} while (seq.index() < capacity);

		return probes;
	}
	UNIGINE_INLINE const Control *getControls() const { return get_controls_data(); }

	friend bool operator==(const Hash &l, const Hash &r)
	{
		if (&l == &r)
			return true;

		if (l.length != r.length)
			return false;

		const Hash *a = &l;
		const Hash *b = &r;
		if (a->capacity > b->capacity)
			std::swap(a, b);

		Counter pos_b;
		for (const auto &it : *a)
		{
			if (!b->do_find(it.hash, it.key, pos_b))
				return false;
			if (it != Policy::element(b->get_slot_data()[pos_b]))
				return false;
		}
		return true;
	}

	friend bool operator!=(const Hash &l, const Hash &r) { return !(l == r); }

protected:
	template<typename K>
	UNIGINE_INLINE static HashType create_hash(const K &key)
	{
		return Hasher<Key>::create(key);
	}

	template<class K, std::enable_if_t<std::is_integral<K>::value, bool> = true>
	bool equal(Counter pos, HashType /*hash*/, const K &k) const
	{
		return key_at(pos) == k;
	}

	template<typename K, std::enable_if_t<!std::is_integral<K>::value, bool> = true>
	bool equal(Counter pos, HashType hash, const K &k) const
	{
		const Element &e = Policy::element(get_slot_data()[pos]);
		return e.hash == hash && e.key == k;
	}

	UNIGINE_INLINE static HashType hash(const Slot &slot) { return Policy::hash(slot); }
	UNIGINE_INLINE static HashType hash(const Slot *slot) { return Policy::hash(*slot); }
	UNIGINE_INLINE HashType hash_at(Counter offset) const { return hash(get_slot_data()[offset]); }

	UNIGINE_INLINE static const Key &key(const Slot &slot) { return Policy::key(slot);}
	UNIGINE_INLINE static const Key &key(const Slot *slot) { return Policy::key(*slot);}
	UNIGINE_INLINE const Key &key_at(Counter offset) const { return key(get_slot_data()[offset]); }

	UNIGINE_INLINE Iterator iterator_at(Counter pos) { return Iterator{get_controls_data(), get_slot_data(), pos}; }

	UNIGINE_INLINE void reset_controls()
	{
		reset_controls(get_controls_data(), capacity);
	}

	UNIGINE_INLINE static void reset_controls(Control *controls, size_t capacity)
	{
		std::memset(controls, CONTROL_EMPTY, get_controls_size(capacity));
		controls[capacity - 1] = CONTROL_END;
	}

	UNIGINE_INLINE void set_control(Counter pos, Control v)
	{
		set_control(get_controls_data(), pos, capacity, v);
	}

	UNIGINE_INLINE void set_control(Counter pos, ControlHash v)
	{
		set_control(get_controls_data(), pos, capacity, static_cast<Control>(v));
	}

	UNIGINE_INLINE static void set_control(Control *ctrl, Counter pos, size_t capacity, ControlHash v)
	{
		set_control(ctrl, pos, capacity, static_cast<Control>(v));
	}

	UNIGINE_INLINE static void set_control(Control *ctrl, Counter pos, size_t capacity, Control v)
	{
		assert(pos < (capacity - 1));
		ctrl[pos] = v;
		// Special for correct ring traverse
		if (pos < get_tail_elements())
			ctrl[capacity + pos] = v;
	}

	template<class Fn>
	UNIGINE_INLINE void traverse_full_slots(Fn fn) const
	{
		Control *ctrl = get_controls_data();
		Slot *slot = get_slot_data();
		size_t remaining = size();
		Group g;
		while (remaining)
		{
			g.loadAligned(ctrl);
			for (int i : g.maskFull())
			{
				assert(remaining > 0 && "Unigine::Hash::traverse_full_slots: hash was broken");
				--remaining;
				fn(slot + i);
			}
			ctrl += Group::Width;
			slot += Group::Width;
		}
	}

	UNIGINE_INLINE void rehash() { rehash_with_remap(0, grow_to(capacity)); }
	UNIGINE_INLINE void rehash(Counter new_capacity) { rehash_with_remap(0, new_capacity); }
	UNIGINE_INLINE Counter rehash_with_remap(Counter remap) { return rehash_with_remap(remap, grow_to(capacity)); }

	Counter rehash_expand_with_remap(Counter remap, Counter new_capacity)
	{
		Control *controls = get_controls_data();
		Slot *old_slots = get_slot_data();
		Slot *new_slots = get_slot_data(data, new_capacity);

		// move slots
		size_t remaining = capacity - 1;
		if ((new_slots - old_slots) == 0)
		{
			const size_t temp_slot_index = new_capacity - 2;
			while (remaining)
			{
				assert(remaining > 0 && "Unigine::Hash::rehash: hash was broken");
				--remaining;
				if (!isFull(controls[remaining]))
					continue;

				Policy::construct(new_slots[temp_slot_index], std::move(old_slots[remaining]));
				Policy::destruct(old_slots[remaining]);
				Policy::construct(new_slots[remaining], std::move(new_slots[temp_slot_index]));
				Policy::destruct(new_slots[temp_slot_index]);
			}
		}
		else
		{
			while (remaining)
			{
				assert(remaining > 0 && "Unigine::Hash::rehash: hash was broken");
				--remaining;
				if (!isFull(controls[remaining]))
					continue;
				Policy::construct(new_slots[remaining], std::move(old_slots[remaining]));
				Policy::destruct(old_slots[remaining]);
			}
		}

		// prepare controls
		std::memset(controls + capacity, CONTROL_EMPTY, get_controls_size(new_capacity) - sizeof(Control) * capacity);
		controls[new_capacity - 1] = CONTROL_END;

		for (Counter i = 0; i < capacity; ++i)
			controls[i] = isFull(controls[i]) ? CONTROL_REMAP : CONTROL_EMPTY;

		std::memcpy(controls + sizeof(Control) * new_capacity, controls, sizeof(Control) * get_tail_elements());

		// remap
		size_t new_remap = std::numeric_limits<size_t>::max();
		Group g;
		for (Counter i = 0; i < capacity - 1; ++i)
		{
			if (controls[i] != CONTROL_REMAP)
				continue;

			const HashType h = hash(new_slots + i);
			ProbeSeq seq(h, new_capacity);

			Counter new_pos = seq.offset();
			if (controls[new_pos] != CONTROL_EMPTY && controls[new_pos] != CONTROL_REMAP)
			{
				do
				{
					g.load(controls + seq.offset());

					if (auto empty_slots = g.maskEmptyOrRemap())
					{
						new_pos = seq.offset(empty_slots.lowestBitSet());
						break;
					}
					seq.next();
				} while (seq.index() < new_capacity);
			}
			new_remap = new_remap == std::numeric_limits<size_t>::max() && remap == i
				? new_pos : new_remap;

			Control old_control = controls[new_pos];
			set_control(controls, new_pos, new_capacity, remove_sign_bit(h));
			if (new_pos == i)
				continue;

			if (old_control == CONTROL_REMAP)
			{
				Policy::swap(new_slots[new_pos], new_slots[i]);
				remap = remap == new_pos ? i : remap;
				--i;
			}
			else if (old_control == CONTROL_EMPTY)
			{
				set_control(controls, i, new_capacity, CONTROL_EMPTY);

				Policy::construct(new_slots[new_pos], std::move(new_slots[i]));
				Policy::destruct(new_slots[i]);
			}
		}

		capacity = new_capacity;
		return static_cast<Counter>(new_remap);
	}
	Counter rehash_with_remap(Counter remap, Counter new_capacity)
	{
		if (!data)
		{
			data = allocate_for(new_capacity);
			capacity = new_capacity;
			reset_controls();
			return remap;
		}

		if (new_capacity > capacity && try_reallocate_for(data, new_capacity))
		{
			return rehash_expand_with_remap(remap, new_capacity);
		}

		char *new_data = allocate_for(new_capacity);
		Control *new_controls = get_controls_data(new_data, new_capacity);
		Slot *new_slots = get_slot_data(new_data, new_capacity);
		reset_controls(new_controls, new_capacity);

		Control *old_controls = get_controls_data();
		Slot *old_slots = get_slot_data();

		size_t remaining = size();
		Group g_new;
		Group g_old;

		while (remaining)
		{
			g_old.loadAligned(old_controls);
			for (int i : g_old.maskFull())
			{
				assert(remaining > 0 && "Unigine::Hash::rehash: hash was broken");
				--remaining;
				const HashType h = hash(old_slots + i);
				ProbeSeq seq(h, new_capacity);

				Counter new_pos = seq.offset();
				if (new_controls[new_pos] == CONTROL_EMPTY)
				{
					goto move_data;
				}

				do
				{
					g_new.load(new_controls + seq.offset());

					if (auto empty_slots = g_new.maskEmpty())
					{
						new_pos = seq.offset(empty_slots.lowestBitSet());
						goto move_data;
					}
					seq.next();
				} while (seq.index() < new_capacity);

				move_data:
					set_control(new_controls, new_pos, new_capacity, remove_sign_bit(h));
					Policy::construct(new_slots[new_pos], std::move(old_slots[i]));
					Policy::destruct(old_slots[i]);
					static_assert(sizeof(Slot) >= sizeof(Counter), "Unigine::Hash::rehash: remap impossible, slot size is small");
					*reinterpret_cast<Counter *>(old_slots + i) = new_pos;
			}

			old_controls += Group::Width;
			old_slots += Group::Width;
		}

		Counter new_remap = *reinterpret_cast<Counter *>(get_slot_data() + remap);

		Memory::deallocate(data);
		data = new_data;
		capacity = new_capacity;
		return new_remap;
	}
protected:
	template<class... Args>
	UNIGINE_INLINE void construct_slot(Counter &pos, Args &&...args)
	{
		++length;
		Policy::construct(get_slot_data()[pos], std::forward<Args>(args)...);
		if(is_rehash_needed(length))
			pos = rehash_with_remap(pos);
	}

	template<class... Args>
	UNIGINE_INLINE void replace_slot(Counter pos, Args &&...args)
	{
		Policy::replace(get_slot_data()[pos], std::forward<Args>(args)...);
	}

	UNIGINE_INLINE void analize_line(Counter pos, Counter &start, Counter &num, Counter &deleted)
	{
		start = pos;
		num = 0;
		deleted = 0;

		Control *controls = get_controls_data();
		Group group;

		ProbeSeq seq = create_probe(start);
		do
		{
			group.load(controls + seq.offset());
			if (auto empty_slots = group.maskEmpty())
			{
				int group_index = empty_slots.lowestBitSet();
				deleted += group.maskDeleted(Group::Width - group_index - 1).allBitSet();
				num += group_index;
				break;
			}

			num += Group::Width;
			deleted += group.maskDeleted().allBitSet();
			seq.next();
		} while (seq.index() < capacity);

		if (seq.index() >= capacity)
		{
			start = 0;
			num = capacity;
		}
	}

	void rehash_line(Counter start, Counter num)
	{
		Control *controls = get_controls_data();
		Slot *slot_data = get_slot_data();

		for (Counter i = start, j = 0; j < num; ++j)
		{
			if(isFull(controls[i]))
				set_control(i, CONTROL_REMAP);
			else if(controls[i] == CONTROL_DELETED)
				set_control(i, CONTROL_EMPTY);

			i = ProbeSeq::getIndex(i + 1, capacity);
		}

		Group group;
		for (Counter i = 0; i < num; ++i)
		{
			Counter index = ProbeSeq::getIndex(start + i, capacity);
			if (controls[index] != CONTROL_REMAP)
				continue;

			const HashType h = hash(slot_data + index);
			ProbeSeq seq = create_probe(h);
			do
			{
				group.load(controls + seq.offset());

				if (auto empty_slots = group.maskEmptyOrRemap())
				{
					int group_index = empty_slots.lowestBitSet();
					Counter new_index = seq.offset(group_index);

					if (new_index == index)
					{
						set_control(index, remove_sign_bit(h));
					}
					else if (controls[new_index] == CONTROL_EMPTY)
					{
						set_control(index, CONTROL_EMPTY);
						set_control(new_index, remove_sign_bit(h));

						Policy::construct(slot_data[new_index], std::move(slot_data[index]));
						Policy::destruct(slot_data[index]);
					}
					else if (controls[new_index] == CONTROL_REMAP)
					{
						set_control(new_index, remove_sign_bit(h));
						Policy::swap(slot_data[new_index], slot_data[index]);
						--i;
					}

					break;
				}
				seq.next();
			} while (seq.index() < capacity);
		}
	}

	UNIGINE_INLINE void destroy_slot(Slot *slot, Control *ctrl)
	{
		if (--length == 0)
		{
			reset_controls();
			Policy::destruct(*slot);
			return;
		}

		Counter pos = static_cast<Counter>(ctrl - get_controls_data());
		Control deleted_control_type = is_next_empty(pos) ? CONTROL_EMPTY : CONTROL_DELETED;
		set_control(pos, deleted_control_type);
		Counter deleted_slot_index = ProbeSeq::getIndex(hash(slot), capacity);
		Policy::destruct(*slot);

		if (deleted_control_type == CONTROL_DELETED)
		{
			Counter start;
			Counter deleted;
			Counter num;
			analize_line(deleted_slot_index, start, num, deleted);

			if ((deleted > 0 && is_rehash_needed(deleted + length)) ||
				(deleted > 1 && num == capacity) ||
				(deleted > (Group::Width * 2) && num >= (capacity / 2)) ||
				(deleted > (Group::Width * 2) && num > (Group::Width * 8)))
			{
				rehash_line(start, num);
			}
		}
	}

	UNIGINE_INLINE bool is_next_empty(Counter pos) const
	{
		const Control *ctrl = get_controls_data();
		return ctrl[pos != (capacity - 2) ? pos + 1 : pos + 2] == CONTROL_EMPTY;
	}

	template<class K>
	UNIGINE_INLINE bool do_find(const K &k, Counter &pos) const
	{
		return data && do_find(create_hash(k), k, pos);
	}

	template<class K>
	UNIGINE_INLINE bool do_find(HashType hash, const K &k, Counter &pos) const
	{
		assert(data);
		const Control *controls = get_controls_data();
		const ControlHash control_hash = remove_sign_bit(hash);
		ProbeSeq seq = create_probe(hash);

		pos = seq.offset();
		if (controls[pos] == control_hash && equal(pos, hash, k))
			return true;

		Group g;
		const auto group_control_hash = Group::createMatch(control_hash);
		do
		{
			g.load(controls + seq.offset());
			for (int i : g.match(group_control_hash))
			{
				pos = seq.offset(i);
				if (equal(pos, hash, k))
					return true;
			}

			if (g.maskEmpty())
				return false;
			seq.next();
		} while (seq.index() < capacity);

		return false;
	}

	template<class K>
	UNIGINE_INLINE bool find_or_prepare_emplace(HashType hash, const K &k, Counter &pos)
	{
		if (capacity == 0)
			rehash();

		const ControlHash control_hash = remove_sign_bit(hash);
		const Control *controls = get_controls_data();
		ProbeSeq seq = create_probe(hash);

		pos = seq.offset();
		if (controls[pos] == CONTROL_EMPTY || (controls[pos] == CONTROL_DELETED && is_next_empty(pos)))
		{
			set_control(pos, control_hash);
			return true;
		}

		if (controls[pos] == control_hash && equal(pos, hash, k))
			return false;

		const size_t start_index = seq.offset();
		Group g;
		const auto group_control_hash = Group::createMatch(control_hash);

		constexpr size_t MAX_INDEX = std::numeric_limits<size_t>::max();
		size_t empty_slot_index = MAX_INDEX;
		size_t deleted_slot_index = MAX_INDEX;
		do
		{
			// Looking for slot with same key.
			g.load(controls + seq.offset());
			for (int i : g.match(group_control_hash))
			{
				pos = seq.offset(i);
				if (equal(pos, hash, k))
					return false;
			}

			if (deleted_slot_index == MAX_INDEX)
			{
				if (auto deleted_slots = g.maskDeleted())
					deleted_slot_index = seq.index() + deleted_slots.lowestBitSet();
			}

			if (auto empty_slots = g.maskEmpty())
			{
				empty_slot_index = seq.index() + empty_slots.lowestBitSet();
				break;
			}
			seq.next();
		} while(seq.index() < capacity);

		size_t free_slot = deleted_slot_index < empty_slot_index
			? deleted_slot_index : empty_slot_index;

		assert(free_slot != MAX_INDEX);
		pos = ProbeSeq::getIndex(start_index + free_slot, capacity);
		assert(controls[pos] == CONTROL_EMPTY || controls[pos] == CONTROL_DELETED);
		set_control(pos, control_hash);
		return true;
	}

	template<class T>
	UNIGINE_INLINE void append_non_existent_slot(T &&old_slot)
	{
		const HashType h = hash(&old_slot);
		const Control *controls = get_controls_data();
		ProbeSeq seq = create_probe(h);
		Counter pos = seq.offset();
		if (controls[pos] == CONTROL_EMPTY)
		{
			set_control(pos, remove_sign_bit(h));
			construct_slot(pos, std::forward<T>(old_slot));
			return;
		}

		Group g;
		do
		{
			g.load(controls + seq.offset());

			if (auto empty_slots = g.maskEmpty())
			{
				pos = seq.offset(empty_slots.lowestBitSet());
				set_control(pos, remove_sign_bit(h));
				construct_slot(pos, std::forward<T>(old_slot));
				break;
			}
			seq.next();
		} while (seq.index() < capacity);
	}

	UNIGINE_INLINE static size_t get_max_size() { return std::numeric_limits<Counter>::max(); }
	UNIGINE_INLINE static Counter grow_to(size_t new_capacity)
	{
		assert(size_t(new_capacity) < get_max_size() && "Hash::grow_to: capacity limit");
		new_capacity = new_capacity < MinCapacity
			? MinCapacity
			: new_capacity + new_capacity / 2;
		new_capacity = normalize_capacity(new_capacity);
		return Counter(new_capacity > get_max_size() ? get_max_size() : new_capacity);
	}

	UNIGINE_INLINE static size_t normalize_capacity(size_t capacity)
	{
		capacity = (capacity & (MinCapacity - 1)) == 0
			? capacity
			: ((capacity / MinCapacity) + 1) * MinCapacity;
		assert((capacity & (MinCapacity - 1)) == 0);
		return capacity;
	}

	UNIGINE_INLINE static size_t capacity_for(size_t n)
	{
		size_t new_capacity = (n * 100 + (LoadFactorPercent - 1)) / LoadFactorPercent;
		new_capacity = normalize_capacity(new_capacity);
		return new_capacity;
	}

	UNIGINE_INLINE bool is_rehash_needed(Counter size) const
	{
		return capacity == 0 ||
			(static_cast<size_t>(size) * 100 >= static_cast<size_t>(capacity) * LoadFactorPercent);
	}

	UNIGINE_INLINE static char *allocate_for(size_t n)
	{
		assert(n >= MinCapacity);
		return reinterpret_cast<char *>(Unigine::Memory::allocate(get_slots_size(n) + get_controls_size(n)));
	}

	UNIGINE_INLINE static bool try_reallocate_for(char *data, size_t n)
	{
		assert(n >= MinCapacity);
		return Unigine::Memory::tryReallocate(data, get_slots_size(n) + get_controls_size(n));
	}

	UNIGINE_INLINE static size_t get_tail_elements() { return Group::Width - 1; }

	UNIGINE_INLINE static ControlHash remove_sign_bit(size_t hash) { return hash & 0x7F; }

	UNIGINE_INLINE static size_t get_controls_size(size_t n) { return sizeof(Control) * (n + MinCapacity); }
	UNIGINE_INLINE static size_t get_slots_size(size_t n) { return sizeof(Slot) * (n - 1); }

	UNIGINE_INLINE ProbeSeq create_probe(HashType hash) const { return ProbeSeq(hash, capacity); }

	UNIGINE_INLINE static Control *get_controls_data(char *data, Counter /*capacity*/) { return reinterpret_cast<Control *>(data); }
	UNIGINE_INLINE static Slot *get_slot_data(char *data, Counter capacity) { return reinterpret_cast<Slot *>(data + get_controls_size(capacity)); }
	UNIGINE_INLINE Control *get_controls_data() const { return get_controls_data(data, capacity); }
	UNIGINE_INLINE Slot *get_slot_data() const { return get_slot_data(data, capacity); }

	// Hash layout
	// E - empty
	// F - full, used 7-bit part of hash, for fast matchs
	// D - deleted
	// END - used for iterators
	// Name  |      Controls       |  Controls Tail  |    Slots     |
	// State | EEEEFDEEEEEEEEE END | EEEEFDEEEEEEEEEE|              |
	// Num   |     capacity()      | Group::Widdth   |capacity() - 1|

	char *data{};
	Counter length{};
	Counter capacity{};
};

} // namespace Internal

} // namespace Unigine
