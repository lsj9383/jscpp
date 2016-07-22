#include <stdarg.h>
#include <fstream>
#include "Jscpp.h"

using namespace std;
using namespace jp;

Jscpp::Jscpp(string _root_key)
{
	jtree = new JTree(_root_key);
}

std::string Jscpp::travel(void)
{
	assert(jtree!=NULL);	//确保jtree不为空，才可以遍历
	return jtree->travel();
}

void Jscpp::set(int value, ...)
{
	va_list pArg;
	va_start(pArg, value);
	deque<string> path;
	char * s = NULL;

	do
	{
		s = va_arg(pArg, char *);
		path.push_back(string(s));
	}while(strcmp(s, ":"));

	path.pop_back();			//把刚刚添加进去的":"弄出来
	va_end(pArg);

	jtree->set(value, path);
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