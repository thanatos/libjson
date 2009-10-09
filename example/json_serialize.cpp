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
#include <sstream>
#include <string>

#include <json/json.h>

using namespace std;

void output_json(stringstream &ss, const string &description, const string &title)
{
	string line("==============================");
	cout << "JSON, " << description << ":" << endl;
	cout << "== " << title << " " << line.substr(0, line.size() - title.size() - 4) << endl;
	cout << ss.str() << endl;
	cout << line << endl;
}

void output_single(json::Value &v, const string &description, bool pretty)
{
	stringstream ss;

	json::Object *obj = NULL;
	json::Array *arr = NULL;

	if(v.type() == json::TYPE_ARRAY)
	{
		arr = dynamic_cast<json::Array *>(&v);
		json::generate(*arr, ss, pretty);
	}
	else
	{
		obj = dynamic_cast<json::Object *>(&v);
		json::generate(*obj, ss, pretty);
	}

	output_json(ss, description, pretty ? "Pretty-print" : "Compact");
}

void output_both(json::Value &v, const string &description)
{
	output_single(v, description, true);
	output_single(v, description, false);
}

int main()
{
	json::Array arr;

	for(int i = 0; i < 10; ++i)
	{
		arr.pushBack(json::Integer(i));
	}

	output_both(arr, "integers 0 - 9");
	
	return 0;
}

