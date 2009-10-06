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

#include <stack>
#include <cstdlib>
#include <climits>

#include "json.h"
#include "utf8_private.h"

void check_stream(std::istream &s)
{
	if(!s)
	{
		if(s.eof())
			throw json::ParseException("Unexpected EOF in input stream.");
		else
			throw json::ParseException("I/O error in input.");
	}
}


void read_string(std::istream &s, const std::string &str)
{
	std::string::const_iterator i;
	char c;

	for(i = str.begin(); i != str.end(); ++i)
	{
		s.get(c);
		check_stream(s);
		if(c != *i)
			throw json::ParseException("Expected \"" + str + "\" input, but didn't find it.");
	}
}

bool try_to_read(std::istream &s, char c_want)
{
	char c_have;

	c_have = s.peek();
	check_stream(s);
	
	if(c_have == c_want)
	{
		s.ignore();
		check_stream(s);
		return true;
	}
	return false;
}

void read_digits_from_stream(std::istream &s, std::string &str, bool need_one)
{
	while(true)
	{
		char c = s.peek();
		check_stream(s);

		if(c >= '0' && c <= '9')
		{
			s.ignore();
			check_stream(s);
			str += c;
			need_one = false;
		}
		else
			break;
	}

	if(need_one)
	{
		// We needed a digit, but one didn't get read...
		throw json::ParseException();
	}
}

json::Value *read_json_numeric(std::istream &s)
{
	std::string numeric_text;
	char c;

	if(try_to_read(s, '-'))
		numeric_text += '-';

	if(!try_to_read(s, '0'))
	{
		// Read in whole digits
		c = s.peek();
		check_stream(s);
		if(!(c >= '1' && c <= '9'))
		{
			throw json::ParseException();
		}
		
		numeric_text += c;
		s.ignore();
		check_stream(s);

		read_digits_from_stream(s, numeric_text, false);
	}
	else
	{
		// It was a 0.
		numeric_text += '0';
	}

	if(try_to_read(s, '.'))
	{
		// A decimal point.
		numeric_text += '.';

		// Read the digits!
		read_digits_from_stream(s, numeric_text, true);
	}

	c = s.peek();
	check_stream(s);
	if(c == 'e' || c == 'E')
	{
		s.ignore();
		check_stream(s);
		numeric_text += 'e';

		read_digits_from_stream(s, numeric_text, true);
	}

	long long ll;
	char *endptr;

	ll = strtoll(numeric_text.c_str(), &endptr, 10);
	if(endptr == numeric_text.c_str() + numeric_text.size())
	{
		// Yay, a number.
		if(ll <= INT_MAX && ll >= INT_MIN)
		{
			return new json::Integer(ll);
		}
		else return new json::Integer64(ll);
	}

	double d;
	
	d = strtod(numeric_text.c_str(), &endptr);
	if(endptr == numeric_text.c_str() + numeric_text.size())
	{
		return new json::Double(d);
	}

	throw json::ParseException();
}

std::string read_json_string_basic(std::istream &s)
{
	char c;
	std::string text;

	// Read opening quote.
	c = s.get();
	if(!s || c != '\"')
		throw json::ParseException();
	
	while(true)
	{
		c = s.get();
		check_stream(s);

		if(c == '\"')
			break;

		// Characters below 0x20 must be escaped.
		if(c < 0x20)
			throw json::ParseException();

		if(c == '\\')
		{
			char escape_code = s.get();
			check_stream(s);

			if(escape_code == '\"')
				text += '\"';
			else if(escape_code == '\\')
				text += '\\';
			else if(escape_code == '/')
				text += '/';
			else if(escape_code == 'b')
				text += 0x08;
			else if(escape_code == 'f')
				text += 0x0C;
			else if(escape_code == 'n')
				text += '\n';
			else if(escape_code == 'r')
				text += '\r';
			else if(escape_code == 't')
				text += '\t';
			else if(escape_code == 'u')
			{
				char four_hex[5] = {0};
				for(int i = 0; i < 4; ++i)
				{
					four_hex[i] = s.get();
					check_stream(s);
					if(!((four_hex[i] >= '0' && four_hex[i] <= '9')
						|| (four_hex[i] >= 'A' && four_hex[i] <= 'F')
						|| (four_hex[i] >= 'a' && four_hex[i] <= 'f')))
					{
						throw json::ParseException();
					}
				}

				unsigned int code = strtoul(four_hex, NULL, 16);
				text += to_utf8(code);
			}
			else
				throw json::ParseException();
		}
		else
			text += c;
	}

	check_is_valid_utf8(text);
	return text;
}

void eat_whitespace(std::istream &s)
{
	char c;

	while(true)
	{
		c = s.peek();
		check_stream(s);

		if(c == ' ' || c == '\t' || c == '\r' || c == '\n')
		{
			s.ignore();
			check_stream(s);
		}
		else
			break;
	}
}

json::Value *read_json_object_or_array(std::istream &s)
{
	char c;

	c = s.peek();
	check_stream(s);

	if(c == '[')
	{
		s.ignore();
		check_stream(s);
		eat_whitespace(s);
		return new json::Array();
	}
	else if(c == '{')
	{
		s.ignore();
		check_stream(s);
		eat_whitespace(s);
		return new json::Object();
	}
	else
		throw json::ParseException();
}

json::Value *read_json_value(std::istream &s)
{
	char c;
	c = s.peek();
	check_stream(s);

	if(c == 'n')
	{
		read_string(s, "null");
		return new json::Null();
	}
	else if(c == 't')
	{
		read_string(s, "true");
		return new json::Bool(true);
	}
	else if(c == 'f')
	{
		read_string(s, "false");
		return new json::Bool(false);
	}
	else if(c == '\"')
	{
		std::string str;
		str = read_json_string_basic(s);
		return new json::String(str);
	}
	else if(c == '-'
		|| (c >= '0' && c <= '9'))
	{
		return read_json_numeric(s);
	}
	else return read_json_object_or_array(s);
}

void parse_item(std::istream &s, std::stack<json::Value *> &struct_stack)
{
	// Get the object/array:
	json::Array *arr = NULL;
	json::Object *obj = NULL;
	if(struct_stack.top()->type() == json::TYPE_ARRAY)
		arr = dynamic_cast<json::Array *>(struct_stack.top());
	else
		obj = dynamic_cast<json::Object *>(struct_stack.top());

	
	// See if we've reached the end:
	char c = s.peek();
	check_stream(s);
	if((arr && c == ']')
		|| (obj && c == '}'))
	{
		s.ignore();
		check_stream(s);
		struct_stack.pop();

		if(!struct_stack.empty())
		{
			eat_whitespace(s);
		}

		return;
	}

	// Check for a comma:
	if((arr && !arr->empty())
		|| (obj && !obj->empty()))
	{
		if(c != ',')
			throw json::ParseException("Expected \',\' token.");

		s.ignore();
		check_stream(s);
		eat_whitespace(s);
	}


	// Read in a key if this is an object
	std::string key;
	if(obj)
	{
		key = read_json_string_basic(s);
		eat_whitespace(s);
		char colon = s.get();
		check_stream(s);
		if(colon != ':')
			throw json::ParseException("Expected \':\' token.");
		eat_whitespace(s);
	}


	// Read in the actual value:
	json::Value *v = NULL;
	try
	{
		v = read_json_value(s);
		if(arr)
			arr->pushBackTake(v);
		else
			obj->takeValue(key, v);
	}
	catch(...)
	{
		delete v;
		throw;
	}

	if(v->type() == json::TYPE_ARRAY
		|| v->type() == json::TYPE_OBJECT)
	{
		struct_stack.push(v);
	}

	eat_whitespace(s);
}

json::Value *json::parse(std::istream &s)
{
	std::stack<json::Value *> struct_stack;
	json::Value *base_object = NULL;

	eat_whitespace(s);
	try
	{
		struct_stack.push(base_object = read_json_object_or_array(s));

		while(!struct_stack.empty())
		{
			parse_item(s, struct_stack);
		}
	}
	catch(...)
	{
		delete base_object;
		throw;
	}
	return base_object;
}

