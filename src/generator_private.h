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
		GeneratorState(const json::Object &obj, std::ostream &out_stream);
		GeneratorState(const json::Array &arr, std::ostream &out_stream);
	
		bool loop();
	
		void loopObject();
		void loopArray();
	
		void outputIndent();
	
		void handleItem(const json::Value *v);
		void generateBasic(const json::Value *v);
	
		void startArray(const json::Array *arr);
		void startObject(const json::Object *obj);

		static std::string transformString(const std::string &s);

		void setPrettyPrint(bool pretty_print) { m_pretty_print = pretty_print; }
		void setIndent(const std::string &indent) { m_indent = indent; }
	
	private:
		std::stack<JsonStackItem> m_stack;
		std::ostream &m_out;
		bool m_pretty_print;
		std::string m_indent;
	};
}

#endif

