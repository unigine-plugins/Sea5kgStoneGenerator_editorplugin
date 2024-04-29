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

#include "UnigineBase.h"
#include "UnigineHash.h"
#include "UnigineMathLib.h"
#include <type_traits>

#ifdef __clang__
	#pragma GCC diagnostic push
	// Remove the warning: 'foo' overrides a member function but is not marked 'override'
	#pragma GCC diagnostic ignored "-Winconsistent-missing-override"
#endif

namespace Unigine
{

class EventBase;

class UNIGINE_API EventConnection : public InstancePool<EventConnection>
{
public:
	UNIGINE_INLINE EventConnection() = default;
	UNIGINE_INLINE virtual ~EventConnection() { disconnect(); }
	void disconnect();
	UNIGINE_INLINE bool isEnabled() const { return enabled; }
	UNIGINE_INLINE void setEnabled(bool mode) { enabled = mode; }
	UNIGINE_INLINE bool isValid() const { return event != nullptr; }
	EventConnection(EventConnection &&other) = delete;
	EventConnection(const EventConnection &other) = delete;
	EventConnection &operator=(EventConnection &&other) = delete;
	EventConnection &operator=(const EventConnection &other) = delete;

protected:
	UNIGINE_INLINE virtual void clear() { event = nullptr; }

private:
	friend class EventBase;
	friend class CallbackBase;

	EventBase *event{nullptr};
	bool enabled{true};
};

class EventConnections
{
public:
	UNIGINE_INLINE EventConnections() = default;
	EventConnections(EventConnections &&other) = delete;
	EventConnections(const EventConnections &other) = delete;
	EventConnections &operator=(EventConnections &&other) = delete;
	EventConnections &operator=(const EventConnections &other) = delete;

	virtual ~EventConnections() { disconnectAll(); }
	UNIGINE_INLINE bool empty() const { return connections.size() == 0; }

	UNIGINE_INLINE void disconnectAll()
	{
		while (connections.size())
			delete connections.takeLast();
	}

private:

	friend class EventBase;
	Vector<EventConnection *> connections;
};

////////////////////////////////////////////////////////////////////////////////
// Base callback class.
////////////////////////////////////////////////////////////////////////////////
class CallbackBase
{
public:
	virtual ~CallbackBase()
	{
		if (connection)
			connection->clear();
	}

	virtual void run() = 0;

	template <class A0>
	void run(A0 a0);

	template <class A0, class A1>
	void run(A0 a0, A1 a1);

	template <class A0, class A1, class A2>
	void run(A0 a0, A1 a1, A2 a2);

	template <class A0, class A1, class A2, class A3>
	void run(A0 a0, A1 a1, A2 a2, A3 a3);

	template <class A0, class A1, class A2, class A3, class A4>
	void run(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4);

	virtual uint32_t getHash() = 0;

	template<class A1>
	UNIGINE_INLINE static uint32_t hashCall(const A1 &a1) { return Math::hashCast64To32(Hasher<A1>::create(a1)); }
	template<class A1, class A2>
	UNIGINE_INLINE static uint32_t hashCall(const A1 &a1, const A2 &a2) { return Math::hashMixer(hashCall(a1), hashCall(a2)); }

protected:

	bool is_enabled() const
	{
		if (connection == nullptr)
			return true;
		return connection->isEnabled();
	}

private:

	friend EventBase;
	EventConnection *connection{nullptr};
	virtual int get_arity() const { return 0; }
};

////////////////////////////////////////////////////////////////////////////////
template <class A0>
class CallbackBase1 : public CallbackBase
{
public:
	void run() override { UNIGINE_ASSERT(0 && "CallbackBase1::run(): called"); }
	virtual void run(A0 a0) = 0;

private:
	int get_arity() const override { return 1; }
};

template <class A0, class A1>
class CallbackBase2 : public CallbackBase
{
public:
	void run() override { UNIGINE_ASSERT(0 && "CallbackBase2::run(): called"); }
	virtual void run(A0 a0, A1 a1) = 0;

private:
	int get_arity() const override { return 2; }
};

template <class A0, class A1, class A2>
class CallbackBase3 : public CallbackBase
{
public:
	void run() override { UNIGINE_ASSERT(0 && "CallbackBase3::run(): called"); }
	virtual void run(A0 a0, A1 a1, A2 a2) = 0;

private:
	int get_arity() const override { return 3; }
};

template <class A0, class A1, class A2, class A3>
class CallbackBase4 : public CallbackBase
{
public:
	void run() override { UNIGINE_ASSERT(0 && "CallbackBase4::run(): called"); }
	virtual void run(A0 a0, A1 a1, A2 a2, A3 a3) = 0;

private:
	int get_arity() const override { return 4; }
};

template <class A0, class A1, class A2, class A3, class A4>
class CallbackBase5 : public CallbackBase
{
public:
	void run() override { UNIGINE_ASSERT(0 && "CallbackBase5::run(): called"); }
	virtual void run(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) = 0;

private:
	int get_arity() const override { return 5; }
};

////////////////////////////////////////////////////////////////////////////////
template <class A0>
void CallbackBase::run(A0 a0)
{
	if (!this->is_enabled())
		return;

	switch (get_arity())
	{
		case 0: run(); break;
		case 1: static_cast<CallbackBase1<A0> *>(this)->run(a0); break;
		default: UNIGINE_ASSERT(0 && "Unigine::CallbackBase::run(): wrong size");
	}
}

template <class A0, class A1>
void CallbackBase::run(A0 a0, A1 a1)
{
	if (!this->is_enabled())
		return;

	switch (get_arity())
	{
		case 0: run(); break;
		case 1: static_cast<CallbackBase1<A0> *>(this)->run(a0); break;
		case 2: static_cast<CallbackBase2<A0, A1> *>(this)->run(a0, a1); break;
		default: UNIGINE_ASSERT(0 && "Unigine::CallbackBase::run(): wrong size");
	}
}

template <class A0, class A1, class A2>
void CallbackBase::run(A0 a0, A1 a1, A2 a2)
{
	if (!this->is_enabled())
		return;

	switch (get_arity())
	{
		case 0: run(); break;
		case 1: static_cast<CallbackBase1<A0> *>(this)->run(a0); break;
		case 2: static_cast<CallbackBase2<A0, A1> *>(this)->run(a0, a1); break;
		case 3: static_cast<CallbackBase3<A0, A1, A2> *>(this)->run(a0, a1, a2); break;
		default: UNIGINE_ASSERT(0 && "Unigine::CallbackBase::run(): wrong size");
	}
}

template <class A0, class A1, class A2, class A3>
void CallbackBase::run(A0 a0, A1 a1, A2 a2, A3 a3)
{
	if (!this->is_enabled())
		return;

	switch (get_arity())
	{
		case 0: run(); break;
		case 1: static_cast<CallbackBase1<A0> *>(this)->run(a0); break;
		case 2: static_cast<CallbackBase2<A0, A1> *>(this)->run(a0, a1); break;
		case 3: static_cast<CallbackBase3<A0, A1, A2> *>(this)->run(a0, a1, a2); break;
		case 4: static_cast<CallbackBase4<A0, A1, A2, A3> *>(this)->run(a0, a1, a2, a3); break;
		default: UNIGINE_ASSERT(0 && "Unigine::CallbackBase::run(): wrong size");
	}
}

template <class A0, class A1, class A2, class A3, class A4>
void CallbackBase::run(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
{
	if (!this->is_enabled())
		return;

	switch (get_arity())
	{
		case 0: run(); break;
		case 1: static_cast<CallbackBase1<A0> *>(this)->run(a0); break;
		case 2: static_cast<CallbackBase2<A0, A1> *>(this)->run(a0, a1); break;
		case 3: static_cast<CallbackBase3<A0, A1, A2> *>(this)->run(a0, a1, a2); break;
		case 4: static_cast<CallbackBase4<A0, A1, A2, A3> *>(this)->run(a0, a1, a2, a3); break;
		case 5: static_cast<CallbackBase5<A0, A1, A2, A3, A4> *>(this)->run(a0, a1, a2, a3, a4); break;
		default: UNIGINE_ASSERT(0 && "Unigine::CallbackBase::run(): wrong size");
	}
}

////////////////////////////////////////////////////////////////////////////////
/// Free function callbacks.
////////////////////////////////////////////////////////////////////////////////
template <class Func>
class Callback0 : public CallbackBase
{
public:
	Callback0(Func func)
		: func(func)
	{}

	void run() override { if (!this->is_enabled()) return; func(); }

	uint32_t getHash() override { return this->hashCall(func); }

private:
	Func func;
};

template <class Base, class Func, class A0>
class Callback1 : public Base
{
public:
	Callback1(Func func)
		: func(func)
	{}
	Callback1(Func func, A0 a0)
		: func(func), a0(a0)
	{}

	void run() override { if (!this->is_enabled()) return; func(a0); }
	virtual void run(A0 arg0) { if (!this->is_enabled()) return; func(arg0); }

	uint32_t getHash() override { return this->hashCall(func); }

private:
	Func func;
	typename std::decay<A0>::type a0;
};

template <class Base, class Func, class A0, class A1>
class Callback2 : public Base
{
public:
	Callback2(Func func)
		: func(func)
	{}
	Callback2(Func func, A1 a1)
		: func(func), a1(a1)
	{}
	Callback2(Func func, A0 a0, A1 a1)
		: func(func), a0(a0), a1(a1)
	{}

	void run() override { if (!this->is_enabled()) return; func(a0, a1); }
	virtual void run(A0 arg0) { if (!this->is_enabled()) return; func(arg0, a1); }
	virtual void run(A0 arg0, A1 arg1) { if (!this->is_enabled()) return; func(arg0, arg1); }

	uint32_t getHash() override { return this->hashCall(func); }

private:
	Func func;
	typename std::decay<A0>::type a0;
	typename std::decay<A1>::type a1;
};

template <class Base, class Func, class A0, class A1, class A2>
class Callback3 : public Base
{
public:
	Callback3(Func func)
		: func(func)
	{}
	Callback3(Func func, A2 a2)
		: func(func), a2(a2)
	{}
	Callback3(Func func, A1 a1, A2 a2)
		: func(func), a1(a1), a2(a2)
	{}
	Callback3(Func func, A0 a0, A1 a1, A2 a2)
		: func(func), a0(a0), a1(a1), a2(a2)
	{}

	void run() override { if (!this->is_enabled()) return; func(a0, a1, a2); }
	virtual void run(A0 arg0) { if (!this->is_enabled()) return; func(arg0, a1, a2); }
	virtual void run(A0 arg0, A1 arg1) { if (!this->is_enabled()) return; func(arg0, arg1, a2); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2) { if (!this->is_enabled()) return; func(arg0, arg1, arg2); }

	uint32_t getHash() override { return this->hashCall(func); }

private:
	Func func;
	typename std::decay<A0>::type a0;
	typename std::decay<A1>::type a1;
	typename std::decay<A2>::type a2;
};

template <class Base, class Func, class A0, class A1, class A2, class A3>
class Callback4 : public Base
{
public:
	Callback4(Func func)
		: func(func)
	{}
	Callback4(Func func, A3 a3)
		: func(func), a3(a3)
	{}
	Callback4(Func func, A2 a2, A3 a3)
		: func(func), a2(a2), a3(a3)
	{}
	Callback4(Func func, A1 a1, A2 a2, A3 a3)
		: func(func), a1(a1), a2(a2), a3(a3)
	{}
	Callback4(Func func, A0 a0, A1 a1, A2 a2, A3 a3)
		: func(func), a0(a0), a1(a1), a2(a2), a3(a3)
	{}

	void run() override { if (!this->is_enabled()) return; func(a0, a1, a2, a3); }
	virtual void run(A0 arg0) { if (!this->is_enabled()) return; func(arg0, a1, a2, a3); }
	virtual void run(A0 arg0, A1 arg1) { if (!this->is_enabled()) return; func(arg0, arg1, a2, a3); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2) { if (!this->is_enabled()) return; func(arg0, arg1, arg2, a3); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2, A3 arg3) { if (!this->is_enabled()) return; func(arg0, arg1, arg2, arg3); }

	uint32_t getHash() override { return this->hashCall(func); }

private:
	Func func;
	typename std::decay<A0>::type a0;
	typename std::decay<A1>::type a1;
	typename std::decay<A2>::type a2;
	typename std::decay<A3>::type a3;
};

template <class Base, class Func, class A0, class A1, class A2, class A3, class A4>
class Callback5 : public Base
{
public:
	Callback5(Func func)
		: func(func)
	{}
	Callback5(Func func, A4 a4)
		: func(func), a4(a4)
	{}
	Callback5(Func func, A3 a3, A4 a4)
		: func(func), a3(a3), a4(a4)
	{}
	Callback5(Func func, A2 a2, A3 a3, A4 a4)
		: func(func), a2(a2), a3(a3), a4(a4)
	{}
	Callback5(Func func, A1 a1, A2 a2, A3 a3, A4 a4)
		: func(func), a1(a1), a2(a2), a3(a3), a4(a4)
	{}
	Callback5(Func func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
		: func(func), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4)
	{}

	void run() override { if (!this->is_enabled()) return; func(a0, a1, a2, a3, a4); }
	virtual void run(A0 arg0) { if (!this->is_enabled()) return; func(arg0, a1, a2, a3, a4); }
	virtual void run(A0 arg0, A1 arg1) { if (!this->is_enabled()) return; func(arg0, arg1, a2, a3, a4); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2) { if (!this->is_enabled()) return; func(arg0, arg1, arg2, a3, a4); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2, A3 arg3) { if (!this->is_enabled()) return; func(arg0, arg1, arg2, arg3, a4); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4) { if (!this->is_enabled()) return; func(arg0, arg1, arg2, arg3, arg4); }

	uint32_t getHash() override { return this->hashCall(func); }

private:
	Func func;
	typename std::decay<A0>::type a0;
	typename std::decay<A1>::type a1;
	typename std::decay<A2>::type a2;
	typename std::decay<A3>::type a3;
	typename std::decay<A4>::type a4;
};

////////////////////////////////////////////////////////////////////////////////
/// Free function callback factories.
////////////////////////////////////////////////////////////////////////////////
template <class Ret>
CallbackBase *MakeCallback(Ret (*func)())
{
	return new Callback0<Ret (*)()>(func);
}

template <class Ret, class A0>
CallbackBase1<A0> *MakeCallback(Ret (*func)(A0))
{
	return new Callback1<CallbackBase1<A0>, Ret (*)(A0), A0>(func);
}

template <class Ret, class A0>
CallbackBase *MakeCallback(Ret (*func)(A0), A0 a0)
{
	return new Callback1<CallbackBase, Ret (*)(A0), A0>(func, a0);
}

template <class Ret, class A0, class A1>
CallbackBase2<A0, A1> *MakeCallback(Ret (*func)(A0, A1))
{
	return new Callback2<CallbackBase2<A0, A1>, Ret (*)(A0, A1), A0, A1>(func);
}

template <class Ret, class A0, class A1>
CallbackBase1<A0> *MakeCallback(Ret (*func)(A0, A1), A1 a1)
{
	return new Callback2<CallbackBase1<A0>, Ret (*)(A0, A1), A0, A1>(func, a1);
}

template <class Ret, class A0, class A1>
CallbackBase *MakeCallback(Ret (*func)(A0, A1), A0 a0, A1 a1)
{
	return new Callback2<CallbackBase, Ret (*)(A0, A1), A0, A1>(func, a0, a1);
}

template <class Ret, class A0, class A1, class A2>
CallbackBase3<A0, A1, A2> *MakeCallback(Ret (*func)(A0, A1, A2))
{
	return new Callback3<CallbackBase3<A0, A1, A2>, Ret (*)(A0, A1, A2), A0, A1, A2>(func);
}

template <class Ret, class A0, class A1, class A2>
CallbackBase2<A0, A1> *MakeCallback(Ret (*func)(A0, A1, A2), A2 a2)
{
	return new Callback3<CallbackBase2<A0, A1>, Ret (*)(A0, A1, A2), A0, A1, A2>(func, a2);
}

template <class Ret, class A0, class A1, class A2>
CallbackBase1<A0> *MakeCallback(Ret (*func)(A0, A1, A2), A1 a1, A2 a2)
{
	return new Callback3<CallbackBase1<A0>, Ret (*)(A0, A1, A2), A0, A1, A2>(func, a1, a2);
}

template <class Ret, class A0, class A1, class A2>
CallbackBase *MakeCallback(Ret (*func)(A0, A1, A2), A0 a0, A1 a1, A2 a2)
{
	return new Callback3<CallbackBase, Ret (*)(A0, A1, A2), A0, A1, A2>(func, a0, a1, a2);
}

template <class Ret, class A0, class A1, class A2, class A3>
CallbackBase4<A0, A1, A2, A3> *MakeCallback(Ret (*func)(A0, A1, A2, A3))
{
	return new Callback4<CallbackBase4<A0, A1, A2, A3>, Ret (*)(A0, A1, A2, A3), A0, A1, A2, A3>(func);
}

template <class Ret, class A0, class A1, class A2, class A3>
CallbackBase3<A0, A1, A2> *MakeCallback(Ret (*func)(A0, A1, A2, A3), A3 a3)
{
	return new Callback4<CallbackBase3<A0, A1, A2>, Ret (*)(A0, A1, A2, A3), A0, A1, A2, A3>(func, a3);
}

template <class Ret, class A0, class A1, class A2, class A3>
CallbackBase2<A0, A1> *MakeCallback(Ret (*func)(A0, A1, A2, A3), A2 a2, A3 a3)
{
	return new Callback4<CallbackBase2<A0, A1>, Ret (*)(A0, A1, A2, A3), A0, A1, A2, A3>(func, a2, a3);
}

template <class Ret, class A0, class A1, class A2, class A3>
CallbackBase1<A0> *MakeCallback(Ret (*func)(A0, A1, A2, A3), A1 a1, A2 a2, A3 a3)
{
	return new Callback4<CallbackBase1<A0>, Ret (*)(A0, A1, A2, A3), A0, A1, A2, A3>(func, a1, a2, a3);
}

template <class Ret, class A0, class A1, class A2, class A3>
CallbackBase *MakeCallback(Ret (*func)(A0, A1, A2, A3), A0 a0, A1 a1, A2 a2, A3 a3)
{
	return new Callback4<CallbackBase, Ret (*)(A0, A1, A2, A3), A0, A1, A2, A3>(func, a0, a1, a2, a3);
}

template <class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase5<A0, A1, A2, A3, A4> *MakeCallback(Ret (*func)(A0, A1, A2, A3, A4))
{
	return new Callback5<CallbackBase5<A0, A1, A2, A3, A4>, Ret (*)(A0, A1, A2, A3, A4), A0, A1, A2, A3, A4>(func);
}

template <class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase4<A0, A1, A2, A3> *MakeCallback(Ret (*func)(A0, A1, A2, A3, A4), A4 a4)
{
	return new Callback5<CallbackBase4<A0, A1, A2, A3>, Ret (*)(A0, A1, A2, A3, A4), A0, A1, A2, A3, A4>(func, a4);
}

template <class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase3<A0, A1, A2> *MakeCallback(Ret (*func)(A0, A1, A2, A3, A4), A3 a3, A4 a4)
{
	return new Callback5<CallbackBase3<A0, A1, A2>, Ret (*)(A0, A1, A2, A3, A4), A0, A1, A2, A3, A4>(func, a3, a4);
}

template <class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase2<A0, A1> *MakeCallback(Ret (*func)(A0, A1, A2, A3, A4), A2 a2, A3 a3, A4 a4)
{
	return new Callback5<CallbackBase2<A0, A1>, Ret (*)(A0, A1, A2, A3, A4), A0, A1, A2, A3, A4>(func, a2, a3, a4);
}

template <class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase1<A0> *MakeCallback(Ret (*func)(A0, A1, A2, A3, A4), A1 a1, A2 a2, A3 a3, A4 a4)
{
	return new Callback5<CallbackBase1<A0>, Ret (*)(A0, A1, A2, A3, A4), A0, A1, A2, A3, A4>(func, a1, a2, a3, a4);
}

template <class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase *MakeCallback(Ret (*func)(A0, A1, A2, A3, A4), A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
{
	return new Callback5<CallbackBase, Ret (*)(A0, A1, A2, A3, A4), A0, A1, A2, A3, A4>(func, a0, a1, a2, a3, a4);
}

////////////////////////////////////////////////////////////////////////////////
/// Member function callbacks.
////////////////////////////////////////////////////////////////////////////////
template <class Class, class Func>
class CallbackObject0 : public CallbackBase
{
public:
	CallbackObject0(Class *object, Func func)
		: object(object), func(func)
	{}

	void run() override { if (!this->is_enabled()) return; (object->*func)(); }
	uint32_t getHash() override { return this->hashCall(object, reinterpret_cast<void *&>(func)); }

private:
	Class *object;
	Func func;
};

template <class Base, class Class, class Func, class A0>
class CallbackObject1 : public Base
{
public:
	CallbackObject1(Class *object, Func func)
		: object(object), func(func)
	{}
	CallbackObject1(Class *object, Func func, A0 a0)
		: object(object), func(func), a0(a0)
	{}

	void run() override { if (!this->is_enabled()) return; (object->*func)(a0); }
	virtual void run(A0 arg0) { if (!this->is_enabled()) return; (object->*func)(arg0); }

	uint32_t getHash() override { return this->hashCall(object, reinterpret_cast<void *&>(func)); }

private:
	Class *object;
	Func func;
	typename std::decay<A0>::type a0;
};

template <class Base, class Class, class Func, class A0, class A1>
class CallbackObject2 : public Base
{
public:
	CallbackObject2(Class *object, Func func)
		: object(object), func(func)
	{}
	CallbackObject2(Class *object, Func func, A1 a1)
		: object(object), func(func), a1(a1)
	{}
	CallbackObject2(Class *object, Func func, A0 a0, A1 a1)
		: object(object), func(func), a0(a0), a1(a1)
	{}

	void run() override { if (!this->is_enabled()) return; (object->*func)(a0, a1); }
	virtual void run(A0 arg0) { if (!this->is_enabled()) return; (object->*func)(arg0, a1); }
	virtual void run(A0 arg0, A1 arg1) { if (!this->is_enabled()) return; (object->*func)(arg0, arg1); }

	uint32_t getHash() override { return this->hashCall(object, reinterpret_cast<void *&>(func)); }

private:
	Class *object;
	Func func;
	typename std::decay<A0>::type a0;
	typename std::decay<A1>::type a1;
};

template <class Base, class Class, class Func, class A0, class A1, class A2>
class CallbackObject3 : public Base
{
public:
	CallbackObject3(Class *object, Func func)
		: object(object), func(func)
	{}
	CallbackObject3(Class *object, Func func, A2 a2)
		: object(object), func(func), a2(a2)
	{}
	CallbackObject3(Class *object, Func func, A1 a1, A2 a2)
		: object(object), func(func), a1(a1), a2(a2)
	{}
	CallbackObject3(Class *object, Func func, A0 a0, A1 a1, A2 a2)
		: object(object), func(func), a0(a0), a1(a1), a2(a2)
	{}

	void run() override { if (!this->is_enabled()) return; (object->*func)(a0, a1, a2); }
	virtual void run(A0 arg0) { if (!this->is_enabled()) return; (object->*func)(arg0, a1, a2); }
	virtual void run(A0 arg0, A1 arg1) { if (!this->is_enabled()) return; (object->*func)(arg0, arg1, a2); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2) { if (!this->is_enabled()) return; (object->*func)(arg0, arg1, arg2); }

	uint32_t getHash() override { return this->hashCall(object, reinterpret_cast<void *&>(func)); }

private:
	Class *object;
	Func func;
	typename std::decay<A0>::type a0;
	typename std::decay<A1>::type a1;
	typename std::decay<A2>::type a2;
};

template <class Base, class Class, class Func, class A0, class A1, class A2, class A3>
class CallbackObject4 : public Base
{
public:
	CallbackObject4(Class *object, Func func)
		: object(object), func(func)
	{}
	CallbackObject4(Class *object, Func func, A3 a3)
		: object(object), func(func), a3(a3)
	{}
	CallbackObject4(Class *object, Func func, A2 a2, A3 a3)
		: object(object), func(func), a2(a2), a3(a3)
	{}
	CallbackObject4(Class *object, Func func, A1 a1, A2 a2, A3 a3)
		: object(object), func(func), a1(a1), a2(a2), a3(a3)
	{}
	CallbackObject4(Class *object, Func func, A0 a0, A1 a1, A2 a2, A3 a3)
		: object(object), func(func), a0(a0), a1(a1), a2(a2), a3(a3)
	{}

	void run() override { if (!this->is_enabled()) return; (object->*func)(a0, a1, a2, a3); }
	virtual void run(A0 arg0) { if (!this->is_enabled()) return; (object->*func)(arg0, a1, a2, a3); }
	virtual void run(A0 arg0, A1 arg1) { if (!this->is_enabled()) return; (object->*func)(arg0, arg1, a2, a3); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2) { if (!this->is_enabled()) return; (object->*func)(arg0, arg1, arg2, a3); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2, A3 arg3) { if (!this->is_enabled()) return; (object->*func)(arg0, arg1, arg2, arg3); }

	uint32_t getHash() override { return this->hashCall(object, reinterpret_cast<void *&>(func)); }

private:
	Class *object;
	Func func;
	typename std::decay<A0>::type a0;
	typename std::decay<A1>::type a1;
	typename std::decay<A2>::type a2;
	typename std::decay<A3>::type a3;
};

template <class Base, class Class, class Func, class A0, class A1, class A2, class A3, class A4>
class CallbackObject5 : public Base
{
public:
	CallbackObject5(Class *object, Func func)
		: object(object), func(func)
	{}
	CallbackObject5(Class *object, Func func, A4 a4)
		: object(object), func(func), a4(a4)
	{}
	CallbackObject5(Class *object, Func func, A3 a3, A4 a4)
		: object(object), func(func), a3(a3), a4(a4)
	{}
	CallbackObject5(Class *object, Func func, A2 a2, A3 a3, A4 a4)
		: object(object), func(func), a2(a2), a3(a3), a4(a4)
	{}
	CallbackObject5(Class *object, Func func, A1 a1, A2 a2, A3 a3, A4 a4)
		: object(object), func(func), a1(a1), a2(a2), a3(a3), a4(a4)
	{}
	CallbackObject5(Class *object, Func func, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
		: object(object), func(func), a0(a0), a1(a1), a2(a2), a3(a3), a4(a4)
	{}

	void run() override { if (!this->is_enabled()) return; (object->*func)(a0, a1, a2, a3, a4); }
	virtual void run(A0 arg0) { if (!this->is_enabled()) return; (object->*func)(arg0, a1, a2, a3, a4); }
	virtual void run(A0 arg0, A1 arg1) { if (!this->is_enabled()) return; (object->*func)(arg0, arg1, a2, a3, a4); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2) { if (!this->is_enabled()) return; (object->*func)(arg0, arg1, arg2, a3, a4); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2, A3 arg3) { if (!this->is_enabled()) return; (object->*func)(arg0, arg1, arg2, arg3, a4); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4) { if (!this->is_enabled()) return; (object->*func)(arg0, arg1, arg2, arg3, arg4); }

	uint32_t getHash() override { return this->hashCall(object, reinterpret_cast<void *&>(func)); }

private:
	Class *object;
	Func func;
	typename std::decay<A0>::type a0;
	typename std::decay<A1>::type a1;
	typename std::decay<A2>::type a2;
	typename std::decay<A3>::type a3;
	typename std::decay<A4>::type a4;
};

////////////////////////////////////////////////////////////////////////////////
/// Member functions callback factories.
////////////////////////////////////////////////////////////////////////////////
template <class Class, class Ret>
CallbackBase *MakeCallback(Class *object, Ret (Class::*func)())
{
	return new CallbackObject0<Class, Ret (Class::*)()>(object, func);
}

template <class Class, class Ret>
CallbackBase *MakeCallback(Class *object, Ret (Class::*func)() const)
{
	return new CallbackObject0<Class, Ret (Class::*)() const>(object, func);
}

template <class Class, class Ret, class A0>
CallbackBase1<A0> *MakeCallback(Class *object, Ret (Class::*func)(A0))
{
	return new CallbackObject1<CallbackBase1<A0>, Class, Ret (Class::*)(A0), A0>(object, func);
}

template <class Class, class Ret, class A0>
CallbackBase1<A0> *MakeCallback(Class *object, Ret (Class::*func)(A0) const)
{
	return new CallbackObject1<CallbackBase1<A0>, Class, Ret (Class::*)(A0) const, A0>(object, func);
}

template <class Class, class Ret, class A0>
CallbackBase *MakeCallback(Class *object, Ret (Class::*func)(A0), A0 a0)
{
	return new CallbackObject1<CallbackBase, Class, Ret (Class::*)(A0), A0>(object, func, a0);
}

template <class Class, class Ret, class A0>
CallbackBase *MakeCallback(Class *object, Ret (Class::*func)(A0) const, A0 a0)
{
	return new CallbackObject1<CallbackBase, Class, Ret (Class::*)(A0) const, A0>(object, func, a0);
}

template <class Class, class Ret, class A0, class A1>
CallbackBase2<A0, A1> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1))
{
	return new CallbackObject2<CallbackBase2<A0, A1>, Class, Ret (Class::*)(A0, A1), A0, A1>(object, func);
}

template <class Class, class Ret, class A0, class A1>
CallbackBase2<A0, A1> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1) const)
{
	return new CallbackObject2<CallbackBase2<A0, A1>, Class, Ret (Class::*)(A0, A1) const, A0, A1>(object, func);
}

template <class Class, class Ret, class A0, class A1>
CallbackBase1<A0> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1), A1 a1)
{
	return new CallbackObject2<CallbackBase1<A0>, Class, Ret (Class::*)(A0, A1), A0, A1>(object, func, a1);
}

template <class Class, class Ret, class A0, class A1>
CallbackBase1<A0> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1) const, A1 a1)
{
	return new CallbackObject2<CallbackBase1<A0>, Class, Ret (Class::*)(A0, A1) const, A0, A1>(object, func, a1);
}

template <class Class, class Ret, class A0, class A1>
CallbackBase *MakeCallback(Class *object, Ret (Class::*func)(A0, A1), A0 a0, A1 a1)
{
	return new CallbackObject2<CallbackBase, Class, Ret (Class::*)(A0, A1), A0, A1>(object, func, a0, a1);
}

template <class Class, class Ret, class A0, class A1>
CallbackBase *MakeCallback(Class *object, Ret (Class::*func)(A0, A1) const, A0 a0, A1 a1)
{
	return new CallbackObject2<CallbackBase, Class, Ret (Class::*)(A0, A1) const, A0, A1>(object, func, a0, a1);
}

template <class Class, class Ret, class A0, class A1, class A2>
CallbackBase3<A0, A1, A2> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2))
{
	return new CallbackObject3<CallbackBase3<A0, A1, A2>, Class, Ret (Class::*)(A0, A1, A2), A0, A1, A2>(object, func);
}

template <class Class, class Ret, class A0, class A1, class A2>
CallbackBase3<A0, A1, A2> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2) const)
{
	return new CallbackObject3<CallbackBase3<A0, A1, A2>, Class, Ret (Class::*)(A0, A1, A2) const, A0, A1, A2>(object, func);
}

template <class Class, class Ret, class A0, class A1, class A2>
CallbackBase2<A0, A1> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2), A2 a2)
{
	return new CallbackObject3<CallbackBase2<A0, A1>, Class, Ret (Class::*)(A0, A1, A2), A0, A1, A2>(object, func, a2);
}

template <class Class, class Ret, class A0, class A1, class A2>
CallbackBase2<A0, A1> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2) const, A2 a2)
{
	return new CallbackObject3<CallbackBase2<A0, A1>, Class, Ret (Class::*)(A0, A1, A2) const, A0, A1, A2>(object, func, a2);
}

template <class Class, class Ret, class A0, class A1, class A2>
CallbackBase1<A0> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2), A1 a1, A2 a2)
{
	return new CallbackObject3<CallbackBase1<A0>, Class, Ret (Class::*)(A0, A1, A2), A0, A1, A2>(object, func, a1, a2);
}

template <class Class, class Ret, class A0, class A1, class A2>
CallbackBase1<A0> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2) const, A1 a1, A2 a2)
{
	return new CallbackObject3<CallbackBase1<A0>, Class, Ret (Class::*)(A0, A1, A2) const, A0, A1, A2>(object, func, a1, a2);
}

template <class Class, class Ret, class A0, class A1, class A2>
CallbackBase *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2), A0 a0, A1 a1, A2 a2)
{
	return new CallbackObject3<CallbackBase, Class, Ret (Class::*)(A0, A1, A2), A0, A1, A2>(object, func, a0, a1, a2);
}

template <class Class, class Ret, class A0, class A1, class A2>
CallbackBase *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2) const, A0 a0, A1 a1, A2 a2)
{
	return new CallbackObject3<CallbackBase, Class, Ret (Class::*)(A0, A1, A2) const, A0, A1, A2>(object, func, a0, a1, a2);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3>
CallbackBase4<A0, A1, A2, A3> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3))
{
	return new CallbackObject4<CallbackBase4<A0, A1, A2, A3>, Class, Ret (Class::*)(A0, A1, A2, A3), A0, A1, A2, A3>(object, func);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3>
CallbackBase4<A0, A1, A2, A3> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3) const)
{
	return new CallbackObject4<CallbackBase4<A0, A1, A2, A3>, Class, Ret (Class::*)(A0, A1, A2, A3) const, A0, A1, A2, A3>(object, func);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3>
CallbackBase3<A0, A1, A2> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3), A3 a3)
{
	return new CallbackObject4<CallbackBase3<A0, A1, A2>, Class, Ret (Class::*)(A0, A1, A2, A3), A0, A1, A2, A3>(object, func, a3);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3>
CallbackBase3<A0, A1, A2> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3) const, A3 a3)
{
	return new CallbackObject4<CallbackBase3<A0, A1, A2>, Class, Ret (Class::*)(A0, A1, A2, A3) const, A0, A1, A2, A3>(object, func, a3);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3>
CallbackBase2<A0, A1> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3), A2 a2, A3 a3)
{
	return new CallbackObject4<CallbackBase2<A0, A1>, Class, Ret (Class::*)(A0, A1, A2, A3), A0, A1, A2, A3>(object, func, a2, a3);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3>
CallbackBase2<A0, A1> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3) const, A2 a2, A3 a3)
{
	return new CallbackObject4<CallbackBase2<A0, A1>, Class, Ret (Class::*)(A0, A1, A2, A3) const, A0, A1, A2, A3>(object, func, a2, a3);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3>
CallbackBase1<A0> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3), A1 a1, A2 a2, A3 a3)
{
	return new CallbackObject4<CallbackBase1<A0>, Class, Ret (Class::*)(A0, A1, A2, A3), A0, A1, A2, A3>(object, func, a1, a2, a3);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3>
CallbackBase1<A0> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3) const, A1 a1, A2 a2, A3 a3)
{
	return new CallbackObject4<CallbackBase1<A0>, Class, Ret (Class::*)(A0, A1, A2, A3) const, A0, A1, A2, A3>(object, func, a1, a2, a3);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3>
CallbackBase *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3), A0 a0, A1 a1, A2 a2, A3 a3)
{
	return new CallbackObject4<CallbackBase, Class, Ret (Class::*)(A0, A1, A2, A3), A0, A1, A2, A3>(object, func, a0, a1, a2, a3);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3>
CallbackBase *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3) const, A0 a0, A1 a1, A2 a2, A3 a3)
{
	return new CallbackObject4<CallbackBase, Class, Ret (Class::*)(A0, A1, A2, A3) const, A0, A1, A2, A3>(object, func, a0, a1, a2, a3);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase5<A0, A1, A2, A3, A4> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3, A4))
{
	return new CallbackObject5<CallbackBase5<A0, A1, A2, A3, A4>, Class, Ret (Class::*)(A0, A1, A2, A3, A4), A0, A1, A2, A3, A4>(object, func);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase5<A0, A1, A2, A3, A4> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3, A4) const)
{
	return new CallbackObject5<CallbackBase5<A0, A1, A2, A3, A4>, Class, Ret (Class::*)(A0, A1, A2, A3, A4) const, A0, A1, A2, A3, A4>(object, func);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase4<A0, A1, A2, A3> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3, A4), A4 a4)
{
	return new CallbackObject5<CallbackBase4<A0, A1, A2, A3>, Class, Ret (Class::*)(A0, A1, A2, A3, A4), A0, A1, A2, A3, A4>(object, func, a4);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase4<A0, A1, A2, A3> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3, A4) const, A4 a4)
{
	return new CallbackObject5<CallbackBase4<A0, A1, A2, A3>, Class, Ret (Class::*)(A0, A1, A2, A3, A4) const, A0, A1, A2, A3, A4>(object, func, a4);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase3<A0, A1, A2> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3, A4), A3 a3, A4 a4)
{
	return new CallbackObject5<CallbackBase3<A0, A1, A2>, Class, Ret (Class::*)(A0, A1, A2, A3, A4), A0, A1, A2, A3, A4>(object, func, a3, a4);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase3<A0, A1, A2> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3, A4) const, A3 a3, A4 a4)
{
	return new CallbackObject5<CallbackBase3<A0, A1, A2>, Class, Ret (Class::*)(A0, A1, A2, A3, A4) const, A0, A1, A2, A3, A4>(object, func, a3, a4);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase2<A0, A1> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3, A4), A2 a2, A3 a3, A4 a4)
{
	return new CallbackObject5<CallbackBase2<A0, A1>, Class, Ret (Class::*)(A0, A1, A2, A3, A4), A0, A1, A2, A3, A4>(object, func, a2, a3, a4);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase2<A0, A1> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3, A4) const, A2 a2, A3 a3, A4 a4)
{
	return new CallbackObject5<CallbackBase2<A0, A1>, Class, Ret (Class::*)(A0, A1, A2, A3, A4) const, A0, A1, A2, A3, A4>(object, func, a2, a3, a4);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase1<A0> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3, A4), A1 a1, A2 a2, A3 a3, A4 a4)
{
	return new CallbackObject5<CallbackBase1<A0>, Class, Ret (Class::*)(A0, A1, A2, A3, A4), A0, A1, A2, A3, A4>(object, func, a1, a2, a3, a4);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase1<A0> *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3, A4) const, A1 a1, A2 a2, A3 a3, A4 a4)
{
	return new CallbackObject5<CallbackBase1<A0>, Class, Ret (Class::*)(A0, A1, A2, A3, A4) const, A0, A1, A2, A3, A4>(object, func, a1, a2, a3, a4);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3, A4), A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
{
	return new CallbackObject5<CallbackBase, Class, Ret (Class::*)(A0, A1, A2, A3, A4), A0, A1, A2, A3, A4>(object, func, a0, a1, a2, a3, a4);
}

template <class Class, class Ret, class A0, class A1, class A2, class A3, class A4>
CallbackBase *MakeCallback(Class *object, Ret (Class::*func)(A0, A1, A2, A3, A4) const, A0 a0, A1 a1, A2 a2, A3 a3, A4 a4)
{
	return new CallbackObject5<CallbackBase, Class, Ret (Class::*)(A0, A1, A2, A3, A4) const, A0, A1, A2, A3, A4>(object, func, a0, a1, a2, a3, a4);
}

////////////////////////////////////////////////////////////////////////////////
/// Callable callbacks.
////////////////////////////////////////////////////////////////////////////////
template <class T>
class CallbackCallable : public CallbackBase
{
public:
	CallbackCallable(const T &f) : func(f) {}

	void run() override { if (!this->is_enabled()) return; func(); }

	uint32_t getHash() override { return this->hashCall(reinterpret_cast<void *&>(func)); }

private:
	T func;
};

template <class T, class A0>
class CallbackCallable1 : public CallbackBase1<A0>
{
public:
	CallbackCallable1(const T &f) : func(f) {}

	void run() override { if (!this->is_enabled()) return; func(a0); }
	void run(A0 arg0) override { if (!this->is_enabled()) return; func(arg0); }

	uint32_t getHash() override { return this->hashCall(reinterpret_cast<void *&>(func)); }

private:
	T func;
	typename std::decay<A0>::type a0;
};

template <class T, class A0, class A1>
class CallbackCallable2 : public CallbackBase2<A0, A1>
{
public:
	CallbackCallable2(const T &f) : func(f) {}

	void run() override { if (!this->is_enabled()) return; func(a0, a1); }
	virtual void run(A0 arg0) { if (!this->is_enabled()) return; func(arg0, a1); }
	void run(A0 arg0, A1 arg1) override { if (!this->is_enabled()) return; func(arg0, arg1); }

	uint32_t getHash() override { return this->hashCall(reinterpret_cast<void *&>(func)); }

private:
	T func;
	typename std::decay<A0>::type a0;
	typename std::decay<A1>::type a1;
};

template <class T, class A0, class A1, class A2>
class CallbackCallable3 : public CallbackBase3<A0, A1, A2>
{
public:
	CallbackCallable3(const T &f) : func(f) {}

	void run() override { if (!this->is_enabled()) return; func(a0, a1, a2); }
	virtual void run(A0 arg0) { if (!this->is_enabled()) return; func(arg0, a1, a2); }
	virtual void run(A0 arg0, A1 arg1) { if (!this->is_enabled()) return; func(arg0, arg1, a2); }
	void run(A0 arg0, A1 arg1, A2 arg2) override { if (!this->is_enabled()) return; func(arg0, arg1, arg2); }

	uint32_t getHash() override { return this->hashCall(reinterpret_cast<void *&>(func)); }

private:
	T func;
	typename std::decay<A0>::type a0;
	typename std::decay<A1>::type a1;
	typename std::decay<A2>::type a2;
};

template <class T, class A0, class A1, class A2, class A3>
class CallbackCallable4 : public CallbackBase4<A0, A1, A2, A3>
{
public:
	CallbackCallable4(const T &f) : func(f) {}

	void run() override { if (!this->is_enabled()) return; func(a0, a1, a2, a3); }
	virtual void run(A0 arg0) { if (!this->is_enabled()) return; func(arg0, a1, a2, a3); }
	virtual void run(A0 arg0, A1 arg1) { if (!this->is_enabled()) return; func(arg0, arg1, a2, a3); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2) { if (!this->is_enabled()) return; func(arg0, arg1, arg2, a3); }
	void run(A0 arg0, A1 arg1, A2 arg2, A3 arg3) override { if (!this->is_enabled()) return; func(arg0, arg1, arg2, arg3); }

	uint32_t getHash() override { return this->hashCall(reinterpret_cast<void *&>(func)); }

private:
	T func;
	typename std::decay<A0>::type a0;
	typename std::decay<A1>::type a1;
	typename std::decay<A2>::type a2;
	typename std::decay<A3>::type a3;
};

template <class T, class A0, class A1, class A2, class A3, class A4>
class CallbackCallable5 : public CallbackBase5<A0, A1, A2, A3, A4>
{
public:
	CallbackCallable5(const T &f) : func(f) {}

	void run() override { if (!this->is_enabled()) return; func(a0, a1, a2, a3, a4); }
	virtual void run(A0 arg0) { if (!this->is_enabled()) return; func(arg0, a1, a2, a3, a4); }
	virtual void run(A0 arg0, A1 arg1) { if (!this->is_enabled()) return; func(arg0, arg1, a2, a3, a4); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2) { if (!this->is_enabled()) return; func(arg0, arg1, arg2, a3, a4); }
	virtual void run(A0 arg0, A1 arg1, A2 arg2, A3 arg3) { if (!this->is_enabled()) return; func(arg0, arg1, arg2, arg3, a4); }
	void run(A0 arg0, A1 arg1, A2 arg2, A3 arg3, A4 arg4) override { if (!this->is_enabled()) return; func(arg0, arg1, arg2, arg3, arg4); }

	virtual uint32_t getHash() override { return this->hashCall(reinterpret_cast<void *&>(func)); }

private:
	T func;
	typename std::decay<A0>::type a0;
	typename std::decay<A1>::type a1;
	typename std::decay<A2>::type a2;
	typename std::decay<A3>::type a3;
	typename std::decay<A4>::type a4;
};

template <typename T>
struct LambdaTraits : public LambdaTraits<decltype(&T::operator())>
{

};

template <typename Class, typename ReturnType, typename ...Args>
struct LambdaTraits<ReturnType(Class::*)(Args...) const>
{
	enum
	{
		arity = sizeof...(Args)
	};

	typedef ReturnType result;

	template <size_t i>
	struct arg
	{
		typedef typename std::tuple_element<i, std::tuple<Args... >>::type type;
	};

	typedef std::tuple<Args...> args;
};

////////////////////////////////////////////////////////////////////////////////
/// Callable callback factories.
////////////////////////////////////////////////////////////////////////////////
template <class T>
class CallableToCallbackTransformer
{
public:
	CallableToCallbackTransformer(const T &f) : func(f) {}

	template <class A0>
	operator CallbackBase1<A0> *() {return new CallbackCallable1<T, A0>(func); }

	template <class A0, class A1>
	operator CallbackBase2<A0, A1> *() { return new CallbackCallable2<T, A0, A1>(func); }

	template <class A0, class A1, class A2>
	operator CallbackBase3<A0, A1, A2> *() { return new CallbackCallable3<T, A0, A1, A2>(func); }

	template <class A0, class A1, class A2, class A3>
	operator CallbackBase4<A0, A1, A2, A3> *() { return new CallbackCallable4<T, A0, A1, A2, A3>(func); }

	template <class A0, class A1, class A2, class A3, class A4>
	operator CallbackBase5<A0, A1, A2, A3, A4> *() { return new CallbackCallable5<T, A0, A1, A2, A3, A4>(func); }

	template <typename L = T>
	operator typename std::enable_if<LambdaTraits<L>::arity == 0, CallbackBase *>::type
	() { return new CallbackCallable<T>(func); }

	template <typename L = T>
	operator typename std::enable_if<LambdaTraits<L>::arity == 1, CallbackBase *>::type
	() {return new CallbackCallable1<T, typename LambdaTraits<L>::template arg<0>::type>(func); }

	template <typename L = T>
	operator typename std::enable_if<LambdaTraits<L>::arity == 2, CallbackBase *>::type
	() { return new CallbackCallable2<T, typename LambdaTraits<L>::template arg<0>::type, typename LambdaTraits<L>::template arg<1>::type>(func); }

	template <typename L = T>
	operator typename std::enable_if<LambdaTraits<L>::arity == 3, CallbackBase *>::type
	() { return new CallbackCallable3<T, typename LambdaTraits<L>::template arg<0>::type, typename LambdaTraits<L>::template arg<1>::type, typename LambdaTraits<L>::template arg<2>::type>(func); }

	template <typename L = T>
	operator typename std::enable_if<LambdaTraits<L>::arity == 4, CallbackBase *>::type
	() { return new CallbackCallable4<T, typename LambdaTraits<L>::template arg<0>::type, typename LambdaTraits<L>::template arg<1>::type, typename LambdaTraits<L>::template arg<2>::type, typename LambdaTraits<L>::template arg<3>::type>(func); }

	template <typename L = T>
	operator typename std::enable_if<LambdaTraits<L>::arity == 5, CallbackBase *>::type
	() { return new CallbackCallable5<T, typename LambdaTraits<L>::template arg<0>::type, typename LambdaTraits<L>::template arg<1>::type, typename LambdaTraits<L>::template arg<2>::type, typename LambdaTraits<L>::template arg<3>::type, typename LambdaTraits<L>::template arg<4>::type>(func); }

private:
	T func;
};

template<class Callable>
CallableToCallbackTransformer<Callable> MakeCallback(const Callable &f) { return f; }

} // namespace Unigine

#ifdef __clang__
	#pragma GCC diagnostic pop
#endif

