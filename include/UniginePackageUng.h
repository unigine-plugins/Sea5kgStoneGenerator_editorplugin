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


class UNIGINE_API PackageUng : public APIInterface
{
public:

	enum
	{
		COMPRESSION_NONE = 0,
		COMPRESSION_BEST_SPEED = 1,
		COMPRESSION_BEST_SIZE = 2,
	};
	static int isSupported();
	static Ptr<PackageUng> create(const char *password = 0, int compression_type = 2);
	bool load(const char *name);
	bool createPackage(const char *name);
	Ptr<PackageUng> clone();
	void close();
	int getNumFiles() const;
	const char *getFileName(int num);
	bool selectFile(const char *name, size_t &size);
	bool readFile(unsigned char *data, size_t size);
	bool writeFile(const char *name, const unsigned char *data, size_t size);
	bool removeFile(const char *name);
	bool removeFile(int num);
	int getCompressionType() const;
	bool containsFile(const char *name) const;
	int findFile(const char *name) const;
	size_t getFileSize(int num) const;
};
typedef Ptr<PackageUng> PackageUngPtr;

} // namespace Unigine
