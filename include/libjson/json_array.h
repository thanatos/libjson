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
#ifndef LIBJSON__JSON_ARRAY_H
#define LIBJSON__JSON_ARRAY_H

#include "json.h"

#include <vector>

namespace json
{
	class Array : public Value
	{
	public:
		typedef std::vector<Value *>::const_iterator const_iterator;

		Array() : Value(TYPE_ARRAY) { }
		Array(const Array &a);
		virtual ~Array();

		void swap(json::Array &a);
		json::Array &operator = (const json::Array &a);

		Value *operator [] (int index) { return m_values[index]; }

		void pushBack(const Value *v);
		void pushBack(const Value &v) { pushBack(&v); }
		void pushBackTake(Value *v) { m_values.push_back(v); }

		const_iterator begin() const { return m_values.begin(); }
		const_iterator end() const { return m_values.end(); }

		Value *clone() const { return new Array(*this); }

	private:
		std::vector<Value *> m_values;
	};
}

#endif
