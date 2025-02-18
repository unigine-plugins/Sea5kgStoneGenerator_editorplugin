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
// DO NOT EDIT DIRECTLY. This is an auto-generated file. Your changes will be lost.

#pragma once

#include "UnigineBase.h"
#include "UniginePtr.h"
#include "UnigineCallback.h"

namespace Unigine
{


class UNIGINE_API ResourceExternalMemory : public APIInterface
{
public:

	enum TYPE
	{
		TYPE_UNKNOWN,
		TYPE_TEXTURE,
		TYPE_STRUCTURED_BUFFER,
		TYPE_MESH_DYNAMIC_VERTEX_BUFFER,
		TYPE_MESH_DYNAMIC_INDEX_BUFFER,
	};
	void* getWin32Handle() const;
	int getFdHandle() const;
	ResourceExternalMemory::TYPE getType() const;
	unsigned long long getSize() const;
	void closeHandle();
	Event<> &getEventCreateHandle();
	Event<> &getEventCloseHandle();
};
typedef Ptr<ResourceExternalMemory> ResourceExternalMemoryPtr;

} // namespace Unigine
