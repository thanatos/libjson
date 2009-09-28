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
#ifndef LIBJSON__GENERATOR_PRIVATE_H
#define LIBJSON__GENERATOR_PRIVATE_H

#include <iostream>
#include <stack>
#include <string>

#include "json.h"

namespace json
{

	enum StackType
	{
		STACK_OBJECT,
		STACK_ARRAY,
	};

	struct JsonStackItem
	{
		StackType type;
		const Value *item;
		json::Object::const_iterator i_object;
		json::Array::const_iterator i_array;

		JsonStackItem(const json::Object &obj) :
			type(STACK_OBJECT),
			item(&obj),
			i_object(obj.begin()),
			i_array()
		{
		}

		JsonStackItem(const json::Array &arr) :
			type(STACK_ARRAY),
			item(&arr),
			i_object(),
			i_array(arr.begin())
		{
		}
	};

	class GeneratorState
	{
	public:
		GeneratorState(const json::Object &obj, std::ostream &out_stream, bool pretty_print, const std::string &indent);
		GeneratorState(const json::Array &arr, std::ostream &out_stream, bool pretty_print, const std::string &indent);
	
		bool loop();
	
		void loopObject();
		void loopArray();
	
		void outputIndent();
	
		void handleItem(const json::Value *v);
		void generateBasic(const json::Value *v);
	
		void startArray(const json::Array *arr);
		void startObject(const json::Object *obj);

		static std::string transformString(const std::string &s);

	private:
		std::stack<JsonStackItem> m_stack;
		std::ostream &m_out;
		bool m_pretty_print;
		std::string m_indent;
	};
}

#endif

