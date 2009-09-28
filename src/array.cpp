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

