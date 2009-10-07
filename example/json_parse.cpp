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
#include <iostream>
#include <string>
#include <sstream>
#include <locale.h>

#include "json.h"

using namespace std;

void print_object(json::Object &o)
{
	json::Object::const_iterator i;

	for(i = o.begin(); i != o.end(); ++i)
	{
		if((*i)->type() == json::TYPE_STRING)
		{
			cout << "JSON string: \"" + dynamic_cast<const json::String *>(*i)->value() << "\"\n";
		}
	}
}

int main()
{
	setlocale(LC_ALL, "");

	string json_text = "{ \"some_text\": \"Test... \\u00a320\" }";

	json::Value *v;
	json::Object *obj;

	v = json::parse(json_text);
	obj = dynamic_cast<json::Object *>(v);
	print_object(*obj);

	stringstream ss;
	json::generate(*obj, ss);
	cout << ss.str() << endl;
}
