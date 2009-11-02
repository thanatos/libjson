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

#include <string>
#include <cassert>
#include <stdint.h>

#include "utf8_private.h"
#include "json.h"

std::string to_utf8(uint32_t code_point)
{
	std::string text;

	if(code_point < 0x80)
		text += char(code_point);
	else if(code_point < 0x800)
	{
		text += char(0xC0 | (code_point >> 6));
		text += char(0x80 | (code_point & 0x3F));
	}
	else if(code_point < 0x10000)
	{
		text += char(0xE0 | (code_point >> 12));
		text += char(0x80 | ((code_point >> 6) & 0x3F));
		text += char(0x80 | (code_point & 0x3F));
	}
	else if(code_point <= 0x10FFFF)
	{
		text += char(0xF0 | (code_point >> 18));
		text += char(0x80 | ((code_point >> 12) & 0x3F));
		text += char(0x80 | ((code_point >> 6) & 0x3F));
		text += char(0x80 | (code_point & 0x3F));
	}
	else
		throw json::InvalidUtf8Exception();

	return text;
}

void check_is_valid_utf8(const std::string &str)
{
	if(!is_valid_utf8(str))
		throw json::InvalidUtf8Exception();
}

bool is_valid_utf8(const std::string &str)
{
	std::string::const_iterator i;
	int continuation_bytes = 0, total_continuation_bytes = 0;
	uint32_t code_point = 0;

	for(i = str.begin(); i != str.end(); ++i)
	{
		if(continuation_bytes > 0)
		{
			if((*i & 0xC0) != 0x80)
				return false;
			
			code_point <<= 6;
			code_point |= *i & 0x3F;

			--continuation_bytes;
			if(continuation_bytes == 0)
			{
				if(total_continuation_bytes == 1
					&& code_point < 0x80)
				{
					return false;
				}
				else if(total_continuation_bytes == 2
					&& code_point < 0x800)
				{
					return false;
				}
				else if(total_continuation_bytes == 3
					&& code_point < 0x10000)
				{
					return false;
				}
			}
		}
		else if((*i & 0x80) == 0)
		{
			// skip.
			continue;
		}
		else if((*i & 0xE0) == 0xC0)
		{
			code_point = *i & 0x1F;
			total_continuation_bytes = continuation_bytes = 1;
		}
		else if((*i & 0xF0) == 0xE0)
		{
			code_point = *i & 0x0F;
			total_continuation_bytes = continuation_bytes = 2;
		}
		else if((*i & 0xF8) == 0xF0)
		{
			code_point = *i & 0x07;
			total_continuation_bytes = continuation_bytes = 3;
		}
		else return false;
	}

	if(continuation_bytes > 0)
		return false;
	return true;
}

int is_surrogate_pair(uint16_t code_unit)
{
	if(code_unit >= 0xD800 && code_unit <= 0xDBFF)
		return 1;
	else if(code_unit >= 0xDC00 && code_unit <= 0xDFFF)
		return 2;
	else
		return 0;
}

uint32_t decode_surrogate_pair(uint16_t first_code_unit, uint16_t second_code_unit)
{
	// whoever is calling us should do this check currently...
	// So far, our one caller is the string parser, and it returns a parse error.
	assert(is_surrogate_pair(first_code_unit) == 1
		|| is_surrogate_pair(second_code_unit) == 2);

	return ((first_code_unit - 0xD800) << 10)
		| (second_code_unit - 0xDC00);
}

