#ifndef __JSON_FUNCTION_H
#define __JSON_FUNCTION_H

#include <string>
#include <sstream>

inline bool isnum(std::string s)
{
	std::stringstream sin(s);
	double t;
	char p;
	if (!(sin >> t))
		return false;
	if (sin >> p)
		return false;
	else
		return true;
}

inline std::string getstring(int n)
{
	std::stringstream newstr;
	newstr << n;
	return newstr.str();
}

inline std::string getstring(double n)
{
	std::stringstream newstr;
	newstr << n;
	return newstr.str();
}

inline std::string getstring(bool n)
{
	if (n)	return "true";
	else	return "false";
}

#endif