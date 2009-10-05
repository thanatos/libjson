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
#include "json_exception.h"

#include <cmath>
#include <string>

namespace json
{
	/**
	 * \brief JSON string primitive.
	 */
	class String : public Value
	{
	public:
		/// Creates a new, empty string.
		String() : Value(TYPE_STRING) { }
		/// Creates a new string from s. s should be UTF-8 encoded.
		String(const std::string &s) : Value(TYPE_STRING), m_value(s) { }

		/// Gets the value of the string as a UTF-8 string.
		std::string value() const throw() { return m_value; }
		/**
		 * Sets the value of the string.
		 * \param str The UTF-8 encoded string to set this string to.
		 * \exception InvalidUtf8Exception The passed string is not valid UTF-8.
		 */
		void set(const std::string &str);

		/// Clones this string.
		Value *clone() const { return new String(*this); }
	private:
		std::string m_value;
	};

	/**
	 * \brief JSON floating-point primitive.
	 */
	class Double : public Value
	{
	public:
		Double() : Value(TYPE_DOUBLE), m_value(0) { }
		Double(double d) : Value(TYPE_DOUBLE), m_value(0) { set(d); }
		Double(const Double &d) : Value(TYPE_DOUBLE), m_value(d.m_value) { }

		double value() const throw() { return m_value; }
		double set(double d)
		{
			// Check for illegal values (inf, nan, etc)
			if(!std::isfinite(d))
				throw InvalidFloatingPointException("Non-finite double passed to json::Double.");
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

	class Integer64 : public Value
	{
	public:
		Integer64() : Value(TYPE_INTEGER64), value(0) { }
		Integer64(int64_t i) : Value(TYPE_INTEGER64), value(i) { }
		Integer64(const Integer64 &i) : Value(TYPE_INTEGER64), value(i.value) { }
		Integer64(const Integer &i) : Value(TYPE_INTEGER64), value(i.value) { }

		int64_t value;

		Value *clone() const { return new Integer64(*this); }
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

