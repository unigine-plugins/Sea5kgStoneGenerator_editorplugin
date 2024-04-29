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
// DO NOT EDIT DIRECTLY. This is an auto-generated file. Your changes will be lost.

#pragma once

#include "UnigineBase.h"
#include "UniginePtr.h"

namespace Unigine
{


class UNIGINE_API ResourceFence : public APIInterface
{
public:
	static Ptr<ResourceFence> create();
	void setEnabled(bool enabled);
	bool isEnabled() const;
	void* getWin32Handle() const;
	int getFdHandle() const;
	unsigned long long getValue() const;
	unsigned long long incrementValue();
	void waitGPU();
	void closeHandle();
};
typedef Ptr<ResourceFence> ResourceFencePtr;

} // namespace Unigine
