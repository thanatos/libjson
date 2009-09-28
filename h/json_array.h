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

		void pushBack(Value *v);
		void pushBackTake(Value *v) { m_values.push_back(v); }

		const_iterator begin() const { return m_values.begin(); }
		const_iterator end() const { return m_values.end(); }

		Value *clone() const { return new Array(*this); }

	private:
		std::vector<Value *> m_values;
	};
}

#endif
