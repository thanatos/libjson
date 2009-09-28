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

