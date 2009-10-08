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
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

#include "json.h"

#include "generator_private.h"

json::GeneratorState::GeneratorState(const json::Object &obj, std::ostream &out_stream, bool pretty_print, const std::string &indent) :
	m_out(out_stream), m_pretty_print(pretty_print), m_indent(indent)
{
	startObject(&obj);
}

json::GeneratorState::GeneratorState(const json::Array &arr, std::ostream &out_stream, bool pretty_print, const std::string &indent) :
	m_out(out_stream), m_pretty_print(pretty_print), m_indent(indent)
{
	startArray(&arr);
}

bool json::GeneratorState::loop()
{
	if(m_stack.top().type == json::STACK_OBJECT)
		loopObject();
	else
		loopArray();

	return !m_stack.empty();
}

void json::GeneratorState::loopObject()
{
	const json::Object *obj = dynamic_cast<const json::Object*>(m_stack.top().item);

	if(m_stack.top().i_object == obj->end())
	{
		m_stack.pop();
		if(m_pretty_print)
		{
			m_out << '\n';
			outputIndent();
		}
		m_out << '}';
		return;
	}

	if(m_stack.top().i_object != obj->begin())
	{
		m_out << ',';
		if(m_pretty_print)
			m_out << '\n';
		else
			m_out << ' ';
	}

	if(m_pretty_print)
		outputIndent();

	m_out << '\"' << transformString(m_stack.top().i_object.key()) << '\"';
	m_out << ": ";
	// Get the sub-object.
	const Value *v = m_stack.top().i_object.value();
	// Increment now, before we handle the object.
	// Calling handleItem() might change our stack, so we've got to do this this way.
	++(m_stack.top().i_object);
	// And last, do it:
	handleItem(v);
}

void json::GeneratorState::loopArray()
{
	const json::Array *arr = dynamic_cast<const json::Array *>(m_stack.top().item);

	if(m_stack.top().i_array == arr->end())
	{
		m_stack.pop();
		if(m_pretty_print)
		{
			m_out << '\n';
			outputIndent();
		}
		m_out << ']';
		return;
	}

	if(m_stack.top().i_array != arr->begin())
	{
		m_out << ',';
		if(m_pretty_print)
			m_out << '\n';
		else
			m_out << ' ';
	}

	if(m_pretty_print)
		outputIndent();

	// Get the sub-object
	const Value *v = *(m_stack.top().i_array);
	// Increment now, before we handle the object.
	// Calling handleItem() might change our stack, so we've got to do this this way.
	++(m_stack.top().i_array);
	// And last, do it:
	handleItem(v);
}

void json::GeneratorState::outputIndent()
{
	int stop = m_stack.size();
	for(int i = 0; i < stop; ++i)
	{
		m_out << m_indent;
	}
}

void json::GeneratorState::handleItem(const json::Value *v)
{
	if(v->type() == json::TYPE_ARRAY)
		startArray(dynamic_cast<const json::Array *>(v));
	else if(v->type() == json::TYPE_OBJECT)
		startObject(dynamic_cast<const json::Object *>(v));
	else
		generateBasic(v);
}

void json::GeneratorState::startArray(const json::Array *arr)
{
	if(m_pretty_print)
	{
		if(!m_stack.empty())
			m_out << '\n';
		outputIndent();
		m_out << "[\n";
	}
	else
	{
		m_out << '[';
	}
	m_stack.push(JsonStackItem(*arr));
}

void json::GeneratorState::startObject(const json::Object *obj)
{
	if(m_pretty_print)
	{
		if(!m_stack.empty())
			m_out << '\n';
		outputIndent();
		m_out << "{\n";
	}
	else
	{
		m_out << '{';
	}
	m_stack.push(JsonStackItem(*obj));
}

std::string json::GeneratorState::transformString(const std::string &s)
{
	std::stringstream ss;

	for(std::string::const_iterator i = s.begin(); i != s.end(); ++i)
	{
		if(*i == '\"' || *i == '\\' || *i == '/')
			ss << '\\' << *i;
		// Backspace
		else if(*i == 0x08)
			ss << "\\b";
		// Form feed
		else if(*i == 0x0C)
			ss << "\\f";
		// line feed
		else if(*i == 0x0A)
			ss << "\\n";
		// carriage return
		else if(*i == 0x0D)
			ss << "\\r";
		// tab
		else if(*i == 0x09)
			ss << "\\t";
		else if((unsigned char)(*i) < 0x20)
		{
			ss << "\\u" << std::hex << std::setw(4) << std::setfill('0') << int((unsigned char)*i);
		}
		else ss << *i;
	}
	return ss.str();
}

void json::GeneratorState::generateBasic(const Value *v)
{
	switch(v->type())
	{
	case json::TYPE_INTEGER:
		{
			const json::Integer *i = dynamic_cast<const json::Integer *>(v);
			m_out << i->value;
			break;
		}
	case json::TYPE_BIGINTEGER:
		{
			const json::BigInteger *i = dynamic_cast<const json::BigInteger *>(v);
			m_out << i->value;
			break;
		}
	case json::TYPE_DOUBLE:
		{
			const json::Double *d = dynamic_cast<const json::Double *>(v);
			m_out << d->value();
			break;
		}
	case json::TYPE_BOOL:
		{
			const json::Bool *b = dynamic_cast<const json::Bool *>(v);
			m_out << (b->value ? "true" : "false");
			break;
		}
	case json::TYPE_NULL:
		m_out << "null";
		break;
	case json::TYPE_STRING:
		{
			const json::String *s = dynamic_cast<const json::String *>(v);
			m_out << "\"" << transformString(s->value()) << "\"";
			break;
		}
	}
}

