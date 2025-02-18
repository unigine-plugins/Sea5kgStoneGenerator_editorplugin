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

#include "UnigineBase.h"

namespace Unigine
{

class Memory
{
public:

	static constexpr int MAX_POOLS = 256;
	struct StaticPoolSetings
	{
		int alloc_size[MAX_POOLS];
		int pool_size[MAX_POOLS];
	};

	// initialize memory manager
	UNIGINE_API static bool initPools(StaticPoolSetings *static_pools, int dynamic_pool_size, bool stats);
	UNIGINE_API static void clearPools();
	UNIGINE_API static void logInfo();
	UNIGINE_API static void calcStaticPoolSetings(StaticPoolSetings &static_pools, int overflow, int max_size, float scale);

	// managed memory
	UNIGINE_API static void *allocate(size_t size);
	UNIGINE_API static void deallocate(void *ptr);
	UNIGINE_INLINE static void deallocate(void *ptr, size_t size) { UNIGINE_UNUSED(size); deallocate(ptr); }
	UNIGINE_API static void *reallocate(void *ptr, size_t size);
	UNIGINE_API static bool tryReallocate(void *ptr, size_t size);

	// statistics
	UNIGINE_API static bool isStatisticsEnabled();
	UNIGINE_API static void updateFrame();

	UNIGINE_API static size_t getMemoryUsage();
	UNIGINE_API static size_t getStaticPoolUsage();
	UNIGINE_API static size_t getDynamicPoolUsage();
	UNIGINE_API static size_t getInstancePoolUsage();

	UNIGINE_API static int getLiveAllocations();
	UNIGINE_API static int getMaxAllocations();
	UNIGINE_API static int getFrameAllocations();

	struct Pool
	{
		mutable volatile char locked{0};
		bool init{false};
		void **pool{nullptr};
		long long alloc_size{0};
		long long size{0};
		long long capacity{0};
	};

private:
	UNIGINE_API static void *allocate_pool(Pool &pool, size_t size);
	UNIGINE_API static void deallocate_pool(Pool &pool, size_t free_limit, void *ptr);

	template <size_t SIZE>
	class PoolAllocator
	{
	public:
		static const size_t FREE_LIMIT = (1024ULL * 1024ULL * 5ULL / SIZE); //5Mb
		static Pool pool;

		UNIGINE_INLINE static void *allocate() { return allocate_pool(pool, SIZE); }
		UNIGINE_INLINE static void deallocate(void *ptr) { return deallocate_pool(pool, FREE_LIMIT, ptr); }
	};
	UNIGINE_INLINE static constexpr size_t get_pool_size(size_t size)
	{
		return (size % 16ULL) ? (size + 16ULL - size % 16ULL) : size;
	}

public:

	template <size_t SIZE>
	UNIGINE_INLINE static void *allocatePool()
	{
		return PoolAllocator<get_pool_size(SIZE)>::allocate();
	}

	template <size_t SIZE>
	UNIGINE_INLINE static void deallocatePool(void *ptr)
	{
		return PoolAllocator<get_pool_size(SIZE)>::deallocate(ptr);
	}
};

template <size_t SIZE>
Memory::Pool Memory::PoolAllocator<SIZE>::pool;

//////////////////////////////////////////////////////////////////////////
// SystemPool
//////////////////////////////////////////////////////////////////////////

template <class Type>
class SystemPool
{
public:
	static UNIGINE_INLINE void *operator new(size_t mem_size_)
	{
		assert(mem_size_ == sizeof(Type) && "SystemPool::operator new(): bad object size");
		return ::malloc(mem_size_);
	}
	static UNIGINE_INLINE void operator delete(void *ptr_)
	{
		::free(ptr_);
	}
	static UNIGINE_INLINE void operator delete(void *ptr_, size_t mem_size_)
	{
		UNIGINE_UNUSED(mem_size_);
		assert(mem_size_ == sizeof(Type) && "SystemPool::operator delete(): bad object size");
		::free(ptr_);
	}
};

//////////////////////////////////////////////////////////////////////////
// InstancePool
//////////////////////////////////////////////////////////////////////////

template <class Type>
class InstancePool
{
public:
	UNIGINE_INLINE InstancePool() {}
	UNIGINE_INLINE ~InstancePool() {}

	static UNIGINE_INLINE void *operator new(size_t mem_size_)
	{
		assert(mem_size_ == sizeof(Type) && "InstancePool::operator new(): bad object size");
		UNIGINE_UNUSED(mem_size_);
		return Memory::allocatePool<sizeof(Type)>();
	}
	static UNIGINE_INLINE void operator delete(void *ptr_)
	{
		return Memory::deallocatePool<sizeof(Type)>(ptr_);
	}
	static UNIGINE_INLINE void operator delete(void *ptr_, size_t mem_size_)
	{
		assert(mem_size_ == sizeof(Type) && "InstancePool::operator delete(): bad object size");
		UNIGINE_UNUSED(mem_size_);
		return Memory::deallocatePool<sizeof(Type)>(ptr_);
	}

	static UNIGINE_INLINE void *operator new[](size_t mem_size_) { return Memory::allocate(mem_size_); }
	static UNIGINE_INLINE void operator delete[](void *ptr_) { Memory::deallocate(ptr_); }
	static UNIGINE_INLINE void operator delete[](void *ptr_, size_t mem_size_) { Memory::deallocate(ptr_, mem_size_); }
};

/// Unigine Base class; managed using Unigine allocator by default
class Base
{
public:
	UNIGINE_DECLARE_USE_MEMORY
};

} // namespace

