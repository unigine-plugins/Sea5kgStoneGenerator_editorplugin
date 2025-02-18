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

#include <type_traits>

#include "UnigineVector.h"
#include "UnigineCallback.h"
#include "UnigineThread.h"

namespace Unigine
{
struct ConnectionId;
using EventConnectionId = ConnectionId *;

class EventBase
{
public:

	virtual bool empty() const { return callbacks.empty(); }
	virtual void setEnabled(bool mode) { enabled = mode; }
	virtual bool isEnabled() const { return enabled; }

protected:

	friend EventConnection;

	virtual ~EventBase()
	{
		ScopedReentrantLock lock(mutex);
		assert(invoke_stack.empty());

		while (callbacks.size())
			delete callbacks.takeLast();
	}

	EventBase() = default;
	EventBase(const EventBase &) = delete;
	EventBase &operator = (const EventBase &) = delete;
	EventBase(EventBase &&) = delete;
	EventBase &operator =(EventBase &&) = delete;

	virtual EventConnectionId append(CallbackBase *callback)
	{
		ScopedReentrantLock lock(mutex);
		callbacks.append(callback);
		return reinterpret_cast<EventConnectionId>(callback);
	}

	EventConnectionId add(EventConnection &connection, CallbackBase *callback)
	{
		if (connection.isValid())
			connection.disconnect();
		connection.event = this;
		callback->connection = &connection;
		return append(callback);
	}

	template <typename Class>
	typename std::enable_if<!std::is_base_of<EventConnections, Class>::value, EventConnectionId>::type
	add_unsafe(Class &obj, CallbackBase *callback)
	{
		UNIGINE_UNUSED(obj)
		return append(callback);
	}

	template <typename Class>
	typename std::enable_if<!std::is_base_of<EventConnections, Class>::value, EventConnectionId>::type
	add(EventConnection &c, Class &obj, CallbackBase *callback)
	{
		UNIGINE_UNUSED(obj)
		return add(c, callback);
	}

	EventConnectionId add(EventConnection &c, EventConnections &obj, CallbackBase *callback)
	{
		UNIGINE_UNUSED(obj)
		return add(c, callback);
	}

	EventConnectionId add(EventConnections &connections, CallbackBase *callback)
	{
		if (connections.empty_connections.empty())
		{
			for (int i = 0; i < connections.connections.size(); i++)
			{
				if (connections.connections[i]->isValid())
					continue;
				connections.empty_connections.append(connections.connections[i]);
				connections.connections.removeFast(i);
				i--;
			}
		}

		EventConnection *connection = nullptr;
		if (connections.empty_connections.size() > 0)
		{
			connection = connections.empty_connections.takeLast();
		} else
		{
			connection = new EventConnection();
		}

		connection->event = this;
		callback->connection = connection;
		connections.connections.append(connection);
		return append(callback);
	}

	virtual bool remove(CallbackBase *callback)
	{
		ScopedReentrantLock lock(mutex);
		int id = callbacks.findIndex(callback);
		if (id == -1)
			return false;

		for (auto invoke : invoke_stack)
			invoke->remove(id);

		callbacks.remove(id);
		delete callback;

		return true;
	}

	virtual bool remove(EventConnection *connection)
	{
		ScopedReentrantLock lock(mutex);
		int id = 0;
		while (id < callbacks.size() && (callbacks[id]->connection != connection))
			++id;
		if (id >= callbacks.size())
			return false;

		CallbackBase *callback = callbacks[id];

		for (auto invoke : invoke_stack)
			invoke->remove(id);

		callbacks.remove(id);
		delete callback;

		return true;
	}

	virtual bool remove(uint32_t hash)
	{
		ScopedReentrantLock lock(mutex);
		for (int i = 0; i < callbacks.size(); ++i)
		{
			if (callbacks[i]->getHash() == hash)
			{
				auto callback = callbacks[i];

				for (auto invoke : invoke_stack)
					invoke->remove(i);

				callbacks.remove(i);
				delete callback;
				return true;
			}
		}

		return false;
	}

	static void swap(EventBase &first, EventBase &second)
	{
		assert(first.invoke_stack.empty());
		assert(second.invoke_stack.empty());

		for (int i = 0; i < first.callbacks.size(); i++)
		{
			CallbackBase *callback = first.callbacks[i];
			if (callback->connection)
				callback->connection->event = &second;
		}

		for (int i = 0; i < second.callbacks.size(); i++)
		{
			CallbackBase *callback = second.callbacks[i];
			if (callback->connection)
				callback->connection->event = &first;
		}

		first.callbacks.swap(second.callbacks);
	}

	struct Invoke
	{
		void remove(int index)
		{
			if (index <= current)
				--current;
			if (index <= size)
				--size;
		}
		int current;
		int size;
	};

	bool enabled{true};
	mutable ReentrantMutex mutex;
	Vector<CallbackBase*> callbacks;
	Vector<Invoke*, char> invoke_stack;
};

UNIGINE_INLINE void EventConnection::disconnect()
{
	if (event)
		event->remove(this);
}

template <typename...> struct EventTypeList;
template <typename S, typename... Args> struct RemoveLastImpl;

template <std::size_t... I, typename... Args>
struct RemoveLastImpl<std::index_sequence<I...>, Args...>
{
	using T = EventTypeList<std::tuple_element_t<I, std::tuple<Args...>>...>;
};

template<typename... Args>
struct RemoveLast
{
	using T = typename RemoveLastImpl<std::make_index_sequence<sizeof...(Args) - 1>, Args...>::T;
};

template<typename T>
class EventHelper;

template<>
class EventHelper<EventTypeList<>> : public EventBase
{
public:

	template<typename F, typename... Extra>
	EventConnectionId connectUnsafe(F(*f)(Extra... extra), Extra... extra)
	{
		return this->append(MakeCallback(f, extra ...));
	}

	template<typename F, typename... Extra>
	EventConnectionId connect(EventConnection &c, F(*f)(Extra... extra), Extra... extra)
	{
		return this->add(c, MakeCallback(f, extra ...));
	}

	template<typename F, typename... Extra>
	EventConnectionId connect(EventConnections &c, F(*f)(Extra... extra), Extra... extra)
	{
		return this->add(c, MakeCallback(f, extra ...));
	}

	template <typename Class, typename F, typename ...Extra>
	EventConnectionId connectUnsafe(Class *object, F(Class::*f)(Extra... extra), Extra... extra)
	{
		return this->add_unsafe(*object, MakeCallback(object, f, extra...));
	}

	template <typename Class, typename F, typename ...Extra>
	EventConnectionId connect(Class *object, F(Class::*f)(Extra... extra), Extra... extra)
	{
		return this->add(*object, MakeCallback(object, f, extra...));
	}

	template <typename Class, typename F, typename ...Extra>
	EventConnectionId connect(EventConnection &c, Class *object, F(Class::*f)(Extra... extra), Extra... extra)
	{
		return this->add(c, *object, MakeCallback(object, f, extra...));
	}

	template <typename Class, typename F, typename ...Extra>
	EventConnectionId connect(EventConnections &c, Class *object, F(Class::*f)(Extra... extra), Extra... extra)
	{
		return this->add(c, MakeCallback(object, f, extra...));
	}

	template <typename L, typename std::enable_if<std::is_class<L>::value, bool>::type=false>
	typename std::enable_if<LambdaTraits<L>::arity == 0, EventConnectionId>::type
	connectUnsafe(const L &l)
	{
		return this->append(MakeCallback(l));
	}

	template <typename L, typename std::enable_if<std::is_class<L>::value, bool>::type=false>
	typename std::enable_if<LambdaTraits<L>::arity == 0, EventConnectionId>::type
	connect(EventConnection &c, const L &l)
	{
		return this->add(c, MakeCallback(l));
	}

	template <typename L, typename std::enable_if<std::is_class<L>::value, bool>::type=false>
	typename std::enable_if<LambdaTraits<L>::arity == 0, EventConnectionId>::type
	connect(EventConnections &c, const L &l)
	{
		return this->add(c, MakeCallback(l));
	}

	template <typename F>
	bool disconnect(F(*f)())
	{
		return this->remove(CallbackBase::hashCall(f));
	}

	template <typename Class, typename F>
	void disconnect(Class *object, F(Class::*f))
	{
		this->remove(CallbackBase::hashCall(object, reinterpret_cast<void *&>(f)));
	}

	bool disconnect(EventConnectionId callback) { return this->remove(reinterpret_cast<CallbackBase *>(callback)); }
};

template <typename ...T>
struct LambdaHelper
{

};

template <typename ...Args>
class EventHelper<EventTypeList<Args...>> : public EventHelper<typename RemoveLast<Args...>::T>
{
public:

	using EventHelper<typename RemoveLast<Args...>::T>::connect;
	using EventHelper<typename RemoveLast<Args...>::T>::connectUnsafe;
	using EventHelper<typename RemoveLast<Args...>::T>::disconnect;

	template <typename F, typename... Extra>
	EventConnectionId connectUnsafe(F(*f)(Args... args, Extra... extra), Extra... extra)
	{
		return this->append(MakeCallback(f, extra ...));
	}

	template <typename F, typename... Extra>
	EventConnectionId connect(EventConnection &c, F(*f)(Args... args, Extra... extra), Extra... extra)
	{
		return this->add(c, MakeCallback(f, extra ...));
	}

	template <typename F, typename... Extra>
	EventConnectionId connect(EventConnections &c, F(*f)(Args... args, Extra... extra), Extra... extra)
	{
		return this->add(c, MakeCallback(f, extra ...));
	}

	template <typename Class, typename F, typename ...Extra>
	EventConnectionId connectUnsafe(Class *object, F(Class::*f)(Args... args, Extra... extra), Extra... extra)
	{
		return this->add_unsafe(*object, MakeCallback(object, f, extra...));
	}

	template <typename Class, typename F, typename ...Extra>
	EventConnectionId connect(Class *object, F(Class::*f)(Args... args, Extra... extra), Extra... extra)
	{
		return this->add(*object, MakeCallback(object, f, extra...));
	}

	template <typename Class, typename F, typename ...Extra>
	EventConnectionId connect(EventConnection &c, Class *object, F(Class::*f)(Args... args, Extra... extra), Extra... extra)
	{
		return this->add(c, MakeCallback(object, f, extra...));
	}

	template <typename Class, typename F, typename ...Extra>
	EventConnectionId connect(EventConnections &c, Class *object, F(Class::*f)(Args... args, Extra... extra), Extra... extra)
	{
		return this->add(c, MakeCallback(object, f, extra...));
	}

	template
	<
		typename L,
		typename std::enable_if<std::is_class<L>::value && !std::is_base_of<EventConnection, L>::value && !std::is_base_of<EventConnections, L>::value, bool>::type = false
	>
	typename std::enable_if<LambdaTraits<L>::arity == sizeof...(Args) && std::is_same<typename LambdaTraits<L>::args, std::tuple<Args...>>::value, EventConnectionId>::type
	connectUnsafe(const L &l, LambdaHelper<Args...> a = LambdaHelper<Args...>{})
	{
		UNIGINE_UNUSED(a)
		return this->append(MakeCallback(l));
	}

	template
	<
		typename L,
		typename std::enable_if<std::is_class<L>::value, bool>::type = false
	>
	typename std::enable_if<LambdaTraits<L>::arity == sizeof...(Args) && std::is_same<typename LambdaTraits<L>::args, std::tuple<Args...>>::value, EventConnectionId>::type
	connect(EventConnection &c, const L &l, LambdaHelper<Args...> a = LambdaHelper<Args...>{})
	{
		UNIGINE_UNUSED(a)
		return this->add(c, MakeCallback(l));
	}

	template
	<
		typename L,
		typename std::enable_if<std::is_class<L>::value, bool>::type = false
	>
	typename std::enable_if<LambdaTraits<L>::arity == sizeof...(Args) && std::is_same<typename LambdaTraits<L>::args, std::tuple<Args...>>::value, EventConnectionId>::type
	connect(EventConnections &c, const L &l, LambdaHelper<Args...> a = LambdaHelper<Args...>{})
	{
		UNIGINE_UNUSED(a)
		return this->add(c, MakeCallback(l));
	}

	template <typename F>
	bool disconnect(F(*f)(Args... args))
	{
		return this->remove(CallbackBase::hashCall(f));
	}

	template<typename Class, typename F, typename... Extra>
	bool disconnect(Class *object, F(Class::*f)(Args... args, Extra... extra))
	{
		return this->remove(CallbackBase::hashCall(object, reinterpret_cast<void *&>(f)));
	}
};

template<typename... Args>
class Event : public EventHelper<EventTypeList<Args...>>
{
protected:
	Event() { }
	~Event() { }
};

template <typename... Args>
class EventInvoker : public Event<Args...>
{
public:

	EventInvoker() { }

	void run(Args... args)
	{
		if (!this->isEnabled())
			return;

		if (this->callbacks.empty())
			return;

		ScopedReentrantLock lock(this->mutex);

		if (this->callbacks.empty())
			return;

		EventBase::Invoke invoke;
		invoke.size = this->callbacks.size();
		invoke.current = 0;
		this->invoke_stack.append(&invoke);

		{
			for (; invoke.current < invoke.size; ++invoke.current)
			{
				CallbackBase *callback = this->callbacks[invoke.current];
				call(callback, args...);
			}
		}

		this->invoke_stack.removeLast();
	}

	static void swap(EventInvoker<Args...> &first, EventInvoker<Args...> &second)
	{
		EventBase::swap(first, second);
	}

private:
	template <typename... Fwd>
	static void call(CallbackBase *c, Fwd &&...args) { c->run<Args...>(args...); }
	static void call(CallbackBase *c) { c->run(); }
};

template<typename T>
class UNIGINE_API EventHolder
{
public:

	UNIGINE_INLINE EventHolder() = default;
	UNIGINE_INLINE EventHolder(const EventBase &) = delete;
	UNIGINE_INLINE EventHolder &operator = (const EventHolder &) = delete;
	UNIGINE_INLINE EventHolder(EventHolder &&) = delete;
	UNIGINE_INLINE EventHolder &operator =(EventHolder &&) = delete;
	UNIGINE_INLINE ~EventHolder() { destroy(); }
	UNIGINE_INLINE bool isNull() const { return event == nullptr; }
	UNIGINE_INLINE bool isValid() const { return event != nullptr; }
	UNIGINE_INLINE T &create() { if (event == nullptr) event = new T(); return *event; }
	UNIGINE_INLINE T *get() const { return event; }

	UNIGINE_INLINE void destroy()
	{
		if (event)
			delete event;
		event = nullptr;
	}

private:
	T *event{nullptr};
};

}
