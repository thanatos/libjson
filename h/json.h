#ifndef LIBJSON__JSON_H
#define LIBJSON__JSON_H

#include <iostream>
#include <string>

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

	class Value
	{
	public:
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

#include<json_array.h>
#include<json_object.h>
#include<json_primitives.h>

namespace json
{
	void generate(const json::Object &obj, std::ostream &out, bool pretty_print = false, const std::string &indent = "\t");
	void generate(const json::Array &obj, std::ostream &out, bool pretty_print = false, const std::string &indent = "\t");
}

#endif

