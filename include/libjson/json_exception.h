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
#ifndef LIBJSON__JSON_EXCEPTION_H
#define LIBJSON__JSON_EXCEPTION_H

#include <stdexcept>

namespace json
{
	class InvalidFloatingPointException : public std::domain_error
	{
	public:
		InvalidFloatingPointException(const std::string &msg) : std::domain_error(msg) { }
	};

	class InvalidUtf8Exception : public std::runtime_error
	{
	public:
		InvalidUtf8Exception(const std::string &msg) : std::runtime_error(msg) { }
		InvalidUtf8Exception() : std::runtime_error("An invalid UTF-8 string was passed to a function expecting one.") { }
	};

	class ParseException : public std::runtime_error
	{
	public:
		ParseException() : std::runtime_error("Parse error in JSON text.") { }
		ParseException(const std::string &msg) : std::runtime_error(msg) { }
	};
}

#endif
