#include <stdarg.h>
#include <fstream>
#include <iostream>
#include "Jscpp.h"

using namespace std;
using namespace jc;

static bool resloveStringObject(const string &scontent, vector<string> &skeys, vector<string> &svalues);

Jscpp::Jscpp(string _root_key)
{
	jtree = new JTree(_root_key);
}

bool Jscpp::load(char *file_path)
{
	ifstream ifs(file_path);
	string sbuf, s;
	vector<list<string>> jpaths;
	vector<JVal> jvals;
	vector<string> skeys;
	vector<string> svalues;

	//���������ļ����ݵ��ַ���s��
	while (ifs >> sbuf)
	{
		s += sbuf;
	}

	//
	//	_findKeyValue(jpaths, jvals);
	resloveStringObject(s, skeys, svalues);
	for (int i = 0; i < skeys.size(); i++)
	{
		cout << i << " : " << skeys[i] << " - " << svalues[i] << endl;
	}

	/*
	auto jpaths_ite = jpaths.cbegin();
	auto jvals_ite = jvals.cbegin();

	for (;	jpaths_ite!= jpaths.cend() &&
	jvals_ite != jvals.cend();		jpaths_ite++, jvals_ite++)
	{
	jtree->set(*jpaths_ite, *jvals_ite);
	}
	*/

	ifs.close();
	return true;
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

std::string Jscpp::travel(void) const
{
	assert(jtree!=NULL);	//ȷ��jtree��Ϊ�գ��ſ��Ա���
	return jtree->travel();
}

void Jscpp::set(std::list<std::string> path, const JVal &jval)
{
	jtree->set(path, jval);
}

const JVal &Jscpp::get(std::list<std::string> path) const
{
	assert(jtree);
	return jtree->get(path);
}

bool Jscpp::isAt(std::list<std::string> path) const
{
	assert(jtree);
	return jtree->isAt(path);
}

bool Jscpp::_findPathValue( vector<list<string>> &jpaths, vector<JVal> &jvals)
{

	return false;
}

std::list<std::string> JPath(char* s1, ...)
{
	va_list pArg;
	va_start(pArg, s1);
	list<string> path(1, s1);
	char * s = NULL;

	do
	{
		s = va_arg(pArg, char *);
		path.push_back(string(s));
	} while (strcmp(s, ":"));
	path.pop_back();			//�Ѹո���ӽ�ȥ��":"Ū����
	va_end(pArg);

	return path;
}

char * JIndex(int index)
{
	char *s = new char [256];
	sprintf_s(s, 256, "##%d", index);
	return s;
}


//�����ַ�����ʽ�Ķ��󣬽����еĹؼ��ʺͶ�Ӧ��value��string����ʽ��������
static bool resloveStringObject(const string &scontent, vector<string> &skeys, vector<string> &svalues)
{
	const char *content = scontent.c_str();
	vector<int> indexs;
	string chars;
	vector<char> bufferBrace;		//�����Ż���
	bool auxFlag=true;				//������־

	int cend = scontent.length();
	assert(content[0]=='{' && content[cend-1]=='}');

	for (int cnt = 0; cnt < cend; cnt++)
	{
		//1).���ݴ������������bufferBrace���г����
		if (content[cnt] == '{')
		{
			bufferBrace.push_back('{');
		}
		else if (content[cnt] == '}')
		{
			if (bufferBrace.size() == 0)	return false;
			bufferBrace.pop_back();
		}

		if (content[cnt] == ',' || bufferBrace.size() == 0)
		{
			auxFlag = true;
		}

		//2).�������������ѹ��chars��index.
		if (((bufferBrace.size() == 1 && content[cnt] != '}') || (bufferBrace.size() == 0 && content[cnt] == '}')) && auxFlag &&
			(content[cnt] == '{' || content[cnt] == '}' || content[cnt] == '"' || content[cnt] == ':' || content[cnt] == ','))
		{
			chars.push_back(content[cnt]);
			indexs.push_back(cnt);
		}

		//2).���ݸ��������������bufferAux���г����
		if (content[cnt] == ':')
		{
			auxFlag = false;
		}
	}

	for (int i = 1; i < indexs.size(); i += 4)
	{
		skeys.push_back(scontent.substr(indexs[i]+1, indexs[i+1] - indexs[i] - 1));
		svalues.push_back(scontent.substr(indexs[i+2]+1, indexs[i+3] - indexs[i+2] - 1));
	}

	return true;
}