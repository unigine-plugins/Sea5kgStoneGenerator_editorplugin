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

#include <UnigineMemory.h>
#include <UnigineThread.h>

#include <UnigineVector.h>
#include <UnigineHashMap.h>
#include <UnigineMap.h>
#include <UnigineSet.h>
#include <UnigineEvent.h>

#include <type_traits>

namespace Unigine
{

class UnigineBaseObject;
class APIInterface;

#ifndef UNIGINE_EMBED
	#define UNIGINE_BASE_OBJECT \
		Unigine::APIInterface *create_interface() override;
	#define UNIGINE_BASE_OBJECT_IMMEDIATE_DELETE \
		Unigine::APIInterface *create_interface() override; \
		void delete_safe() override { delete_force(); }
#else
	#define UNIGINE_BASE_OBJECT \
		Unigine::APIInterface *create_interface() override { return nullptr; }
	#define UNIGINE_BASE_OBJECT_IMMEDIATE_DELETE \
		Unigine::APIInterface *create_interface() override { return nullptr; } \
		void delete_safe() override { delete_force(); }
#endif

struct UNIGINE_API DestroyObjectsVector : public Vector<UnigineBaseObject *> {};

class UNIGINE_API UnigineBaseObject
{
public:
	UnigineBaseObject() {}
	virtual ~UnigineBaseObject();

	UnigineBaseObject(const UnigineBaseObject &) = delete;
	UnigineBaseObject &operator=(const UnigineBaseObject&) = delete;
	UnigineBaseObject(UnigineBaseObject &&other) noexcept;
	UnigineBaseObject &operator=(UnigineBaseObject &&other) noexcept;

	APIInterface *getInterface();

	template<typename T>
	T *getInterface() { return static_cast<T*>(getInterface()); }
	bool hasInterface() const { return api_interface != nullptr; }

	bool isDeletedLater() const { return AtomicGet(&deleted_later_id) != -1; }

	void deleteLater();
	void deleteForce();

public: //internal
	static void processDeleteQueue();

protected:
	friend APIInterface;

	virtual void delete_safe();
	void delete_later();
	void delete_force();

	virtual APIInterface * create_interface() = 0;

	APIInterface *volatile api_interface { nullptr };

	int deleted_later_id = -1;

	static ReentrantMutex global_mutex;
	static DestroyObjectsVector deleted_later_objects;
};

#ifndef UNIGINE_EMBED
	template<class T, class = typename std::enable_if<!std::is_convertible<T*, UnigineBaseObject*>::value, void>::type>
	inline APIInterface *getAPIInterface(T *) { return nullptr; }
	inline APIInterface *getAPIInterface(UnigineBaseObject *object) { return object ? object->getInterface() : nullptr; }
#else
	template<class T>
	inline APIInterface *getAPIInterface(T *) { return nullptr; }
#endif

// api interface
class UNIGINE_API APIInterface
{
public:
	APIInterface() = default;
	virtual ~APIInterface() = 0;

	void counterInc()
	{
		AtomicAdd(&counter, 1);
	}
	void counterDec()
	{
		const int old_counter = AtomicAdd(&counter, -1);
		if (old_counter == 1)
		{
			if (isNull())
				delete this;
			else if (isOwner() && isValid())
				obj->delete_safe();
		}
	}
	int getAPIInterfaceCounter() const { return AtomicGet(&counter); }

	void setOwner(bool owner_) { owner = owner_; }
	bool isOwner() const { return owner; }
	int isValid() const { return obj != nullptr; }
	int isNull() const { return obj == nullptr; }
	int isDeleted() const { return is_deleted; }

	template<typename T>
	T *getInternalObject() const { return static_cast<T*>(obj); }

	UnigineBaseObject *getInternalObject() const { return obj; }

	Event<APIInterface *> &getEventAPIInterfaceDestroy() { return event_destroy.create(); }

protected:
	void setInternalObject(UnigineBaseObject *const obj_)
	{
		obj = obj_;
		is_deleted = obj_->isDeletedLater();
	}

protected:
	friend UnigineBaseObject;
	template<typename OtherType>
	friend class Ptr;

	void object_destructor()
	{
		is_deleted = 1;
		obj = nullptr;
		if (counter == 0)
			delete this;
	}

	void delete_later()
	{
		if (isNull() || is_deleted)
			return;

		{
			ScopedLock lock(deleted_mutex);
			if (is_deleted)
				return;
			is_deleted = 1;
		}

		obj->delete_later();
	}
	void delete_force()
	{
		if (isNull() || is_deleted)
			return;

		{
			ScopedLock lock(deleted_mutex);
			if (is_deleted)
				return;
			is_deleted = 1;
		}

		if (obj->isDeletedLater())
		{
			obj = nullptr;
		} else
		{
			obj->delete_force();
			// warning: 'this' may be already dead here
			// this->obj is nulled during APIInterface::object_destructor
		}
	}

	UnigineBaseObject *obj{nullptr};
	EventHolder<EventInvoker<APIInterface *>> event_destroy;

	volatile int counter{0};
	Mutex deleted_mutex;
	bool owner{false};
	volatile bool is_deleted = 0;
};

inline APIInterface::~APIInterface()
{
	if (event_destroy.isNull())
		return;
	event_destroy.get()->run(this);
}

// Smart pointer api interface
template <typename Type>
class Ptr
{
public:

	Ptr(std::nullptr_t): ptr(nullptr) {}
	Ptr(): ptr(nullptr) {}

	Ptr(UnigineBaseObject *obj, bool take_ownership)
	{
		ptr = nullptr;
		if (obj)
			ptr = static_cast<Type*>(obj->getInterface());
		if (ptr && take_ownership)
			api_interface()->setOwner(true);
		grab();
	}

	Ptr(const Ptr &pointer)
		: ptr(pointer.ptr)
	{
		grab();
	}

	Ptr(Ptr &&pointer)
		: ptr(pointer.ptr)
	{
		pointer.ptr = nullptr;
	}

	template<typename OtherType, class = typename std::enable_if<std::is_convertible<OtherType *, Type *>::value, void>::type>
	Ptr(const Ptr<OtherType> &pointer)
	{
		Type *new_val = static_cast<OtherType *>(pointer.ptr);
		ptr = new_val;
		grab();
	}

	template <typename OtherType, class = typename std::enable_if<std::is_convertible<OtherType *, Type *>::value, void>::type>
	Ptr(Ptr<OtherType> &&pointer)
	{
		Type *new_val = static_cast<OtherType *>(pointer.ptr);
		ptr = new_val;
		pointer.ptr = nullptr;
	}

	explicit Ptr(Type *pointer): ptr(pointer) { grab(); }

	~Ptr() { clear(); }

	Ptr &operator=(std::nullptr_t)
	{
		clear();
		return *this;
	}

	Ptr &operator=(const Ptr &pointer)
	{
		if (ptr == pointer.ptr)
			return *this;

		clear();
		ptr = pointer.ptr;
		grab();
		return *this;
	}

	Ptr &operator=(Ptr &&pointer)
	{
		if (this == &pointer)
			return *this;

		clear();
		ptr = pointer.ptr;
		pointer.ptr = nullptr;
		return *this;
	}

	template<typename OtherType, class = typename std::enable_if<std::is_convertible<OtherType *, Type *>::value, void>::type>
	Ptr<Type> &operator=(const Ptr<OtherType> &pointer)
	{
		Type *new_val = static_cast<OtherType *>(pointer.ptr);
		if (new_val == ptr)
			return *this;

		clear();
		ptr = new_val;
		grab();
		return *this;
	}

	template <typename OtherType, class = typename std::enable_if<std::is_convertible<OtherType *, Type *>::value, void>::type>
	Ptr<Type> &operator=(Ptr<OtherType> &&pointer)
	{
		Type *new_val = static_cast<OtherType *>(pointer.ptr);

		clear();
		ptr = new_val;
		pointer.ptr = nullptr;
		return *this;
	}

	template<typename OtherType>
	Ptr<Type> &operator=(const OtherType *pointer)
	{
		Type *new_val = static_cast<OtherType *>(pointer);
		if (new_val == ptr)
			return *this;

		clear();
		ptr = new_val;
		grab();
		return *this;
	}

	Type *get() const
	{
		if (!ptr || api_interface()->isNull())
			return nullptr;
		return ptr;
	}
	Type *operator->() const
	{
		assert(!isNull());
		return get();
	}
	Type &operator*() const
	{
		assert(!isNull());
		return *get();
	}

	void clear()
	{
		if (ptr)
			api_interface()->counterDec();
		ptr = 0;
	}

	template<typename T>
	T *getInternalObject() const
	{
		if (!ptr || api_interface()->isNull())
			return nullptr;
		return api_interface()->template getInternalObject<T>();
	}

	bool isValid() const { return get() != nullptr; }
	bool isNull() const { return get() == nullptr; }
	bool isDeleted() const { return isNull() || api_interface()->isDeleted(); }
	explicit operator bool() const { return isValid(); }

	void deleteLater() const
	{
		if (!isNull())
			api_interface()->delete_later();
	}
	void deleteForce() const
	{
		if (!isNull())
			api_interface()->delete_force();
	}
	void deleteForce()
	{
		if (!isNull())
			api_interface()->delete_force();
		clear();
	}

	UNIGINE_DECLARE_USE_MEMORY

private:
	template<typename OtherType>
	friend class Ptr;

	void grab()
	{
		if (ptr)
			api_interface()->counterInc();
	}
	APIInterface *api_interface() const { return static_cast<APIInterface *>(ptr); }

	Type *ptr;
};

template<typename PtrType, typename OtherType>
bool operator==(const Ptr<PtrType> &lhs, const OtherType &rhs) { return lhs.get() == rhs; }
template<typename PtrType, typename OtherType>
bool operator==(const OtherType &lhs, const  Ptr<PtrType> &rhs) { return lhs == rhs.get(); }
template<typename PtrType, typename OtherType>
bool operator!=(const Ptr<PtrType> &lhs, const OtherType &rhs) { return lhs.get() != rhs; }
template<typename PtrType, typename OtherType>
bool operator!=(const OtherType &lhs, const  Ptr<PtrType> &rhs) { return lhs != rhs.get(); }
template<typename LeftType, typename RightType>
bool operator==(const Ptr<LeftType> &lhs, const Ptr<RightType> &rhs) { return lhs.get() == rhs.get(); }
template<typename LeftType, typename RightType>
bool operator!=(const Ptr<LeftType> &lhs, const Ptr<RightType> &rhs) { return lhs.get() != rhs.get(); }
template<typename LeftType, typename RightType>
bool operator<(const Ptr<LeftType> &lhs, const Ptr<RightType> &rhs) { return lhs.get() < rhs.get(); }

template<typename To, typename From>
Ptr<To> static_ptr_cast(const Ptr<From> &ptr) { return Ptr<To>(static_cast<To*>(ptr.get())); }
template<typename To, typename From>
Ptr<To> dynamic_ptr_cast(const Ptr<From> &ptr) { return Ptr<To>(dynamic_cast<To *>(ptr.get())); }
template<typename To, typename From>
Ptr<To> checked_ptr_cast(const Ptr<From> &ptr)
{
	if (!To::convertible(ptr.get()))
		return nullptr;
	return Ptr<To>(static_cast<To *>(ptr.get()));
}

typedef Ptr<APIInterface> BaseObjectPtr;

template<typename ...Args>
class EventInterfaceInvoker : public EventInvoker<Args...>
{
public:

	void internal_set_data(EventBase *event, APIInterface *i, EventConnectionId(*f)(void *, void *, EventConnection *), EventConnection *connection)
	{
		engine_event = event;
		api_interface = i;
		connection_func = f;
		internal_connection = connection;
	}

	bool internal_need_init()
	{
		return engine_event == nullptr;
	}

	void internal_clear()
	{
		if (!this->callbacks.empty())
		{
			if (api_interface)
				api_interface->counterDec();
			while (this->callbacks.size())
				delete this->callbacks.takeLast();
		}

		engine_event = nullptr;
		api_interface = nullptr;
		connection_func = nullptr;
		if (internal_connection)
			internal_connection->disconnect();
		internal_connection = nullptr;
	}

	bool empty() const override
	{
		assert(engine_event != nullptr);
		return this->callbacks.empty() || engine_event->empty();
	}

	void setEnabled(bool mode) override
	{
		assert(engine_event != nullptr);
		EventBase::setEnabled(mode);
		engine_event->setEnabled(mode);
	}

	bool isEnabled() const override
	{
		assert(engine_event != nullptr);
		return engine_event->isEnabled();
	}

protected:

	EventConnectionId append(CallbackBase *c) override
	{
		assert(engine_event != nullptr);
		if (this->callbacks.empty())
		{
			if (api_interface)
				api_interface->counterInc();
			if (connection_func)
				connection_func(this, engine_event, internal_connection);
		}
		return EventBase::append(c);
	}

	bool remove(CallbackBase *callback) override
	{
		bool result = EventBase::remove(callback);
		if (result && this->callbacks.empty())
		{
			if (api_interface)
				api_interface->counterDec();
			if (internal_connection)
				internal_connection->disconnect();
		}
		return result;
	}

	bool remove(EventConnection *connection) override
	{
		bool result = EventBase::remove(connection);
		if (result && this->callbacks.empty())
		{
			if (api_interface)
				api_interface->counterDec();
			if (internal_connection)
				internal_connection->disconnect();
		}
		return result;
	}

	bool remove(uint32_t hash) override
	{
		bool result = EventBase::remove(hash);
		if (result && this->callbacks.empty())
		{
			if (api_interface)
				api_interface->counterDec();
			if (internal_connection)
				internal_connection->disconnect();
		}
		return result;
	}

private:

	APIInterface *api_interface{nullptr};
	EventBase *engine_event{nullptr};
	EventConnectionId(*connection_func)(void *, void *, EventConnection *){nullptr};
	EventConnection *internal_connection{nullptr};
};

template<typename T>
class UNIGINE_API EventInterfaceConnection : public EventConnection
{
public:
	EventInterfaceConnection() = default;
	EventInterfaceConnection(EventInterfaceConnection &&other) = delete;
	EventInterfaceConnection(const EventInterfaceConnection &other) = delete;
	EventInterfaceConnection &operator=(EventInterfaceConnection &&other) = delete;
	EventInterfaceConnection &operator=(const EventInterfaceConnection &other) = delete;
	~EventInterfaceConnection() = default;
	void internal_set_data(T *event_interface)
	{
		i = event_interface;
	}
protected:
	void clear() override
	{
		EventConnection::clear();
		if (i)
		{
			i->internal_clear();
			i = nullptr;
		}
	}
private:
	T *i{nullptr};
};

namespace Internal
{

template <typename Type>
struct PointerWrapper
{
	PointerWrapper(Type *ptr_): ptr(ptr_) {}
	PointerWrapper(Type &ref): ptr(&ref) {}

	operator Type *() const { return ptr; }
	operator Type &() const { assert(ptr != nullptr); return *ptr; }

	Type *ptr;
};

template <typename Type>
PointerWrapper<Type> WrapPointer(Type *ptr) { return PointerWrapper<Type>(ptr); }

template <typename Type>
PointerWrapper<Type> WrapPointer(Type &ref) { return PointerWrapper<Type>(ref); }

template <typename Type>
PointerWrapper<Type> GetInternalObject(APIInterface *obj)
{
	return PointerWrapper<Type>(obj ? obj->getInternalObject<Type>() : nullptr);
}

template <typename Type, typename APIClass>
PointerWrapper<Type> GetInternalObject(const Ptr<APIClass> &obj)
{
	return GetInternalObject<Type>(obj.get());
}

namespace Conversion
{
template<typename To, typename From>
To api_convert(From from)
{
	return from;
}
template<typename To, typename From>
To api_convert(From *from)
{
	return To(from, false);
}
template<typename To, typename From>
To api_convert(Ptr<From> from)
{
	return GetInternalObject<typename std::remove_pointer<To>::type>(from.get());
}
} // namespace Conversion

template <typename From, typename To>
VectorStack<To> api_wrap(const Vector<From> &v)
{
	VectorStack<To> ret;
	ret.allocate(v.size());
	for (int i = 0; i < v.size(); i++)
		ret.appendFast(Conversion::api_convert<To>(v[i]));
	return ret;
}

// SetToSet
template <typename From, typename To>
Set<To> api_wrap(const Set<From> &v)
{
	Set<To> ret;
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it)
		ret.append(Conversion::api_convert<To>(it->key));
	return ret;
}

} // namespace Internal
} // namespace Unigine
