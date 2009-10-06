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
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
	json::Object o;

	o.setValue("testInt", json::Integer(42));
	o.setValue("testDouble", json::Double(3.14159));
	o.setValue("testString", json::String("Hello World."));
	o.setValue("testBool", json::Bool(false));
	o.setValue("testNull", json::Null());

	json::Object o2;

	o2.setValue("aSubKey", json::String("Some text."));

	o.setValue("testObject", o2);

	json::Array arr;
	arr.pushBack(json::Integer(42));
	arr.pushBack(json::Integer(1337));
	arr.pushBack(json::String("Even more text."));

	o.setValue("anArray", arr);

	json::Object::const_iterator i;

	for(i = o.begin(); i != o.end(); ++i)
	{
		cout << "Key: " << i.key() << ", Value: " << i.value() << endl;
	}

	std::stringstream ss;

	json::generate(o, ss);

	cout << "JSON:" << endl << ss.str() << endl;

	ss.str("");
	
	json::generate(o, ss, true);
	cout << "JSON:" << endl << ss.str() << endl;

	cout << "------------------------------" << endl;

	json::Value *v;

	ss.str("{ \"key1\": 42, \"key2\": \"value2\" , \"key3\" : -29.9, \"key4\": null,"
	"\"key8\": true, \"key9\": false, \"key10\": [2, 3, 4]}");

	v = json::parse(ss);

	ss.str("");
	
	json::generate(*dynamic_cast<json::Object *>(v), ss);

	cout << ss.str() << endl;

	return 0;
}

