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

json::Value *json::Object::getValue(const std::string &key)
{
	MapType::iterator i = m_members.find(key);

	return i == m_members.end() ? NULL : i->second;
}

const json::Value *json::Object::getValue(const std::string &key) const
{
	MapType::const_iterator i = m_members.find(key);

	return i == m_members.end() ? NULL : i->second;
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
	m_members.insert(std::make_pair(key, val));
}

void json::Object::removeValue(const std::string &key)
{
	m_members.erase(key);
}

