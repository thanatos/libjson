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

#include "utf8_private.h"
#include "json.h"

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
		else if(*i & 0x80 == 0)
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

