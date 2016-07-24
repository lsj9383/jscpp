#include <stdarg.h>
#include <fstream>
#include "Jscpp.h"

using namespace std;
using namespace jc;

Jscpp::Jscpp(string _root_key)
{
	jtree = new JTree(_root_key);
}

std::string Jscpp::travel(void)
{
	assert(jtree!=NULL);	//确保jtree不为空，才可以遍历
	return jtree->travel();
}

void Jscpp::setByDeque(JValueType jtype, std::deque<std::string> path, UVal jval)
{
	jtree->set(jtype, path, jval);
}

void Jscpp::set(JValueType jtype, ...)
{
	va_list pArg;
	va_start(pArg, jtype);
	deque<string> path;
	char * s = NULL;
	UVal jval;

	do
	{
		s = va_arg(pArg, char *);
		path.push_back(string(s));
	} while (strcmp(s, ":"));
	path.pop_back();			//把刚刚添加进去的":"弄出来

	//allocate memroy and set value.
	switch (jtype)
	{
	case JINT:	
		jval.pInt = new int;  *jval.pInt = va_arg(pArg, int);			
		break;
	case JDOUBLE:	
		jval.pDouble = new double; *jval.pDouble = va_arg(pArg, double);
		break;
	case JBOOL:	
		jval.pBool = new bool; *jval.pBool = va_arg(pArg, bool);		
		break;
	case JSTRING:	
		jval.pString = new string; *jval.pString = va_arg(pArg, string); 
		break;
	default:	break;
	}
	va_end(pArg);

	jtree->set(jtype, path, jval);

	//release memory.
	switch (jtype)
	{
	case JINT	:	delete jval.pInt;		break;
	case JDOUBLE:	delete jval.pDouble;	break;
	case JBOOL	:	delete jval.pBool;		break;
	case JSTRING:	delete jval.pString;	break;
	default:	break;
	}
}

bool Jscpp::save(char * file_path)
{
	if (jtree == NULL)	return false;

	ofstream ofs(file_path);
	string s = travel();
	ofs << s << endl;
	ofs.close();
	return true;
}

std::deque<std::string> PathDeque(char* s1, ...)
{
	va_list pArg;
	va_start(pArg, s1);
	deque<string> path(1, s1);
	char * s = NULL;

	do
	{
		s = va_arg(pArg, char *);
		path.push_back(string(s));
	} while (strcmp(s, ":"));
	path.pop_back();			//把刚刚添加进去的":"弄出来
	va_end(pArg);

	return path;
}