#ifndef LIBJSON__JSON_PRIMITIVES_H
#define LIBJSON__JSON_PRIMITIVES_H

#include "json.h"

#include <string>

namespace json
{
	class String : public Value
	{
	public:
		String() : Value(TYPE_STRING) { }
		String(const std::string &s) : Value(TYPE_STRING), m_value(s) { }

		std::string value() const throw() { return m_value; }
		void set(const std::string &s) { m_value = s; }

		Value *clone() const { return new String(*this); }
	private:
		std::string m_value;
	};

	class Double : public Value
	{
	public:
		Double() : Value(TYPE_FLOAT), m_value(0) { }
		Double(double d) : Value(TYPE_FLOAT), m_value(0) { set(d); }
		Double(const Double &d) : Value(TYPE_FLOAT), m_value(d.m_value) { }

		double value() const throw() { return m_value; }
		double set(double d)
		{
			// TODO: Check for illegal values (inf, nan, etc)
			m_value = d;
		}

		Value *clone() const { return new Double(*this); }
	private:
		double m_value;
	};

	class Integer : public Value
	{
	public:
		Integer() : Value(TYPE_INTEGER), value(0) { }
		Integer(int i) : Value(TYPE_INTEGER), value(i) { }
		Integer(const Integer &i) : Value(TYPE_INTEGER), value(i.value) { }

		int value;

		Value *clone() const { return new Integer(*this); }
	};

	class Bool : public Value
	{
	public:
		Bool() : Value(TYPE_BOOL), value(false) { }
		Bool(bool b) : Value(TYPE_BOOL), value(b) { }
		Bool(const Bool &b) : Value(TYPE_BOOL), value(b.value) { }

		bool value;

		Value *clone() const { return new Bool(*this); }
	};

	class Null : public Value
	{
	public:
		Null() : Value(TYPE_NULL) { }
		Null(const Null &n) : Value(TYPE_NULL) { }

		Value *clone() const { return new Null(*this); }
	};
}

#endif

