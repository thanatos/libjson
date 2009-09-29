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
#include "json.h"

void json::String::set(const std::string &str)
{
	int continuation_bytes = 0;

	for(std::string::const_iterator i = str.begin(); i != str.end(); ++i)
	{
		if(continuation_bytes > 0)
		{
			// This should be a continuation byte.
			if(0x80 != (*i & 0xC0))
				throw json::InvalidUtf8Exception();
			--continuation_bytes;
		}
		else if((*i & 0xC0) == 0xC0)
		{
			continuation_bytes = 1;
		}
		else if((*i & 0xE0) == 0xE0)
		{
			continuation_bytes = 2;
		}
		else if((*i & 0xF0) == 0xF0)
		{
			continuation_bytes = 3;
		}
	}

	if(continuation_bytes > 0)
		throw json::InvalidUtf8Exception();

	// Everything is good. Yay.
	m_value = str;
}

