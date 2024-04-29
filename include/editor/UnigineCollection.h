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

#include <UniginePtr.h>
#include <UnigineString.h>
#include <UnigineVector.h>

#include "UnigineEditorGlobal.h"

namespace UnigineEditor
{


/// <summary> This class is used to represent a collection of values (boolean, integer, float, or string) that can represent a set of import parameters for an asset.</summary>
class UNIGINE_EDITOR_API Collection : public Unigine::APIInterface
{
public:

	/// <summary> Value type.</summary>
	enum TYPE
	{
		/// <summary> No type.</summary>
		TYPE_NONE = 0,
		/// <summary> Boolean value type.</summary>
		TYPE_BOOL,
		/// <summary> Integer value type.</summary>
		TYPE_INT,
		/// <summary> Float value type.</summary>
		TYPE_FLOAT,
		/// <summary> String value type.</summary>
		TYPE_STRING,
	};
		/// <summary> Creates a new empty collection.</summary>
	static Unigine::Ptr<Collection> create();
		/// <summary> Clears the collection by removing all elements.</summary>
	void clear();
	/// <summary> Checks if the collection is empty or has any elements. </summary>
	/// <returns> <b>true</b> if the collection is empty; otherwise, <b>false</b>. </returns>
	bool isEmpty() const;
	/// <summary> Checks if the collection contains a value element with the specified name.</summary>
	/// <param name='value_name'> Name of the collection element to be checked.</param>
	/// <returns> <b>true</b> if the collection contains an element with the specified name; otherwise, <b>false</b>.</returns>
	bool hasValue(const char *value_name) const;
		/// <summary> Returns the list of names of all elements in the collection as a vector of strings.</summary>
	/// <returns> The list of names of all elements in the collection.</returns>
	Unigine::Vector<Unigine::String> getNames() const;
	/// <summary> Saves to the vector of strings specified as the argument the list of names of all elements in the collection.</summary>
	/// <param name='names'> The vector to store the names of all elements in the collection.</param>
	void getNames(Unigine::Vector<Unigine::String> &names) const;
	/// <summary> Removes a value element with the specified name from the collection.</summary>
	/// <param name='value_name'> Name of the collection element to be removed.</param>
	/// <returns> <b>true</b> if the element with the specified name is removed successfully; otherwise, <b>false</b>.</returns>
	bool remove(const char *value_name);
	///<summary> Returns the type of a value element with the specified name (see <see cref='TYPE'/>).</summary>
	/// <param name='value_name'>Name of the collection element.</param>
	/// <returns> The type of the value element with the specified name.</returns>
	Collection::TYPE getType(const char *value_name) const;
	/// <summary>Sets a new boolean value for the collection element with the specified name.</summary>
	/// <param name='value_name'>Name of the collection element to be updated.</param>
	/// <param name='value'>New boolean value to be set.</param>
	void setBool(const char *value_name, bool value);
	/// <summary>Returns the current boolean value of the collection element with the specified name.</summary>
	/// <param name='value_name'>Name of the collection element.</param>
	/// <param name='default_value'>Default boolean value to be returned in case the requested value does not exist or cannot be converted to the specified type.</param>
	/// <returns> The current boolean value of the collection element with the specified name.</returns>
	bool getBool(const char *value_name, bool default_value = false) const;
	/// <summary>Sets a new integer value for the collection element with the specified name.</summary>
	/// <param name='value_name'>Name of the collection element to be updated.</param>
	/// <param name='value'>New integer value to be set.</param>
	void setInt(const char *value_name, int value);
	/// <summary>Returns the current integer value of the collection element with the specified name.</summary>
	/// <param name='value_name'>Name of the collection element.</param>
	/// <param name='default_value'>Default integer value to be returned in case the requested value does not exist or cannot be converted to the specified type.</param>
	/// <returns> The current integer value of the collection element with the specified name.</returns>
	int getInt(const char *value_name, int default_value = 0) const;
	/// <summary>Sets a new float value for the collection element with the specified name.</summary>
	/// <param name='value_name'>Name of the collection element to be updated.</param>
	/// <param name='value'>New float value to be set.</param>
	void setFloat(const char *value_name, float value);
	/// <summary>Returns the current float value of the collection element with the specified name.</summary>
	/// <param name='value_name'>Name of the collection element.</param>
	/// <param name='default_value'>Default float value to be returned in case the requested value does not exist or cannot be converted to the specified type.</param>
	/// <returns> The current float value of the collection element with the specified name.</returns>
	float getFloat(const char *value_name, float default_value = 0) const;
	/// <summary>Sets a new string value for the collection element with the specified name.</summary>
	/// <param name='value_name'>Name of the collection element to be updated.</param>
	/// <param name='value'>New string value to be set.</param>
	void setString(const char *value_name, const char *value);
	/// <summary>Returns the current string value of the collection element with the specified name.</summary>
	/// <param name='value_name'>Name of the collection element.</param>
	/// <param name='default_value'>Default value to be returned in case the requested value does not exist or cannot be converted to the specified type.</param>
	/// <returns> The current string value of the collection element with the specified name.</returns>
	Unigine::String getString(const char *value_name, const char *default_value = nullptr) const;
};
typedef Unigine::Ptr<Collection> CollectionPtr;

} // namespace UnigineEditor
