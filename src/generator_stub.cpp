#include "json.h"
#include "generator_private.h"

void json::generate(const json::Object &obj, std::ostream &out, bool pretty_print, const std::string &indent)
{
	GeneratorState s(obj, out);

	s.setPrettyPrint(pretty_print);
	s.setIndent(indent);

	while(s.loop());
}

void json::generate(const json::Array &arr, std::ostream &out, bool pretty_print, const std::string &indent)
{
	GeneratorState s(arr, out);

	s.setPrettyPrint(pretty_print);
	s.setIndent(indent);

	while(s.loop());
}

