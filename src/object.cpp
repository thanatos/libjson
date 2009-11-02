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

json::Object::Object(const json::Object &o) :
	json::Value(TYPE_OBJECT)
{
	try
	{
		for(MapType::const_iterator i = o.m_members.begin();
			i != o.m_members.end();
			++i)
		{
			Value *v = NULL;
			try
			{
				v = i->second->clone();
				m_members.insert(std::make_pair(i->first, v));
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
		for(MapType::iterator i = m_members.begin();
			i != m_members.end();
			++i)
		{
			delete i->second;
		}
		throw;
	}
}

json::Object::~Object()
{
	for(MapType::iterator i = m_members.begin();
		i != m_members.end();
		++i)
	{
		delete i->second;
	}
}

void json::Object::swap(json::Object &o)
{
	o.m_members.swap(o.m_members);
}

json::Object &json::Object::operator = (const json::Object &o)
{
	if(this == &o)
		return *this;

	json::Object temp(o);
	swap(temp);
	return *this;
}

json::Value &json::Object::getValue(const std::string &key)
{
	MapType::iterator i = m_members.find(key);

	if(i == m_members.end())
		throw json::InvalidKeyException();

	return *(i->second);
}

const json::Value &json::Object::getValue(const std::string &key) const
{
	MapType::const_iterator i = m_members.find(key);
	
	if(i == m_members.end())
		throw json::InvalidKeyException();

	return *(i->second);
}

void json::Object::setValue(const std::string &key, const Value &val)
{
	setValue(key, &val);
}

void json::Object::setValue(const std::string &key, const Value *val)
{
	Value *v = NULL;
	try
	{
		v = val->clone();
		takeValue(key, v);
	}
	catch(...)
	{
		delete v;
		throw;
	}
}

void json::Object::takeValue(const std::string &key, Value *val)
{
	std::pair<MapType::iterator, bool> result;

	result = m_members.insert(std::make_pair(key, val));
	if(result.second == false)
	{
		delete m_members[key];
		m_members[key] = val;
	}
}

void json::Object::removeValue(const std::string &key)
{
	MapType::iterator i = m_members.find(key);
	if(i != m_members.end())
	{
		delete i->second;
		m_members.erase(i);
	}
}

bool json::Object::hasValue(const std::string &key) const
{
	MapType::const_iterator i = m_members.find(key);

	return i != m_members.end();
}

