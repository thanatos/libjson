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

	json::Object::const_iterator i;

	for(i = o.begin(); i != o.end(); ++i)
	{
		cout << "Key: " << i.key() << ", Value: " << i.value() << endl;
	}

	std::stringstream ss;

	json::generate(o, ss);

	cout << "JSON:" << endl << ss.str() << endl;

	return 0;
}

