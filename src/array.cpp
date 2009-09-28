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
#include "json.h"

json::Array::Array(const json::Array &a) : Value(TYPE_ARRAY)
{
	try
	{
		for(std::vector<Value *>::const_iterator i = a.m_values.begin();
			i != a.m_values.end();
			++i)
		{
			Value *v = NULL;
			try
			{
				v = (*i)->clone();
				m_values.push_back(v);
			}
			catch(...)
			{
				delete v;
				throw;
			}
		}
	}
	catch(...)
	{
		for(std::vector<Value *>::const_iterator i = m_values.begin();
			i != m_values.end();
			++i)
		{
			delete *i;
		}
		throw;
	}
}

json::Array::~Array()
{
	for(std::vector<Value *>::iterator i = m_values.begin();
		i != m_values.end();
		++i)
	{
		delete *i;
	}
}

void json::Array::swap(json::Array &a)
{
	m_values.swap(a.m_values);
}

json::Array &json::Array::operator = (const json::Array &a)
{
	if(this == &a)
		return *this;
	
	json::Array temp(a);
	swap(temp);
	return *this;
}

void json::Array::pushBack(json::Value *v)
{
	Value *c = NULL;
	try
	{
		c = v->clone();
		m_values.push_back(c);
	}
	catch(...)
	{
		delete c;
		throw;
	}
}

