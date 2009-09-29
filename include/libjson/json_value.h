/*
 * Copyright (c) 2009 Roy Wellington IV
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef LIBJSON__JSON_VALUE_H
#define LIBJSON__JSON_VALUE_H

namespace json
{
	enum ValueType
	{
		TYPE_OBJECT,
		TYPE_ARRAY,
		// Numerics
		TYPE_FLOAT,
		TYPE_INTEGER,
		TYPE_INTEGER64,
		// Others
		TYPE_STRING,
		TYPE_BOOL,
		TYPE_NULL
	};

	/**
	 * \brief A JSON data type.
	 * A class representing an item of JSON data. This is a base class to one
	 * of the many JSON types.
	 */
	class Value
	{
	public:
		/// Get the type of the value.
		ValueType type() const { return m_type; }

		virtual ~Value() { }
		virtual Value *clone() const = 0;

	protected:
		Value(ValueType type) :
			m_type(type)
		{ }

	private:
		ValueType m_type;
	};
}

#endif

