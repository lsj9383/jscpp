#include <stdarg.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Jscpp.h"
#include "JFunction.h"

using namespace std;
using namespace jc;

static string preArrayProcess(const string &content);
static bool parseStringObject(const string &scontent, vector<string> &skeys, vector<string> &svalues);
static void JPathJValueTransfer(const vector<string> &jpaths_jvalues, vector<list<string>> &jpaths, vector<JVal> &jvals);

Jscpp::Jscpp(string _root_key)
{
	jtree = new JTree(_root_key);
}

bool Jscpp::load(char *file_path)
{
	ifstream ifs(file_path);
	string sbuf, s;
	vector<string> jpaths_jvalues;
	vector<JVal> jvals;
	vector<list<string>> jpaths;


	//���������ļ����ݵ��ַ���s��
	while (ifs >> sbuf)
	{
		s += sbuf;
	}
	if (s.length() == 0)	return false;

	s = preArrayProcess(s);								//��s�е������ͣ�ת��Ϊ���������
	jpaths_jvalues = _JPathsJValues(s, string());		//��s�е�����·����ֵ��ȡ�������ַ�����ʽ
	JPathJValueTransfer(jpaths_jvalues, jpaths, jvals);	//���ַ�����ʽ��path valueת��ΪJPath��JValue��ʽ


	//��path value��ӵ�������
	auto jpaths_ite = jpaths.cbegin();
	auto jvals_ite = jvals.cbegin();

	for (;	jpaths_ite!= jpaths.cend() &&
	jvals_ite != jvals.cend();		jpaths_ite++, jvals_ite++)
	{
		jtree->set(*jpaths_ite, *jvals_ite);
	}

	//����
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
	assert(jtree);
	return jtree->travel();
}

void Jscpp::set(std::list<std::string> path, const JVal &jval)
{
	assert(jtree);
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

vector<string> Jscpp::_JPathsJValues(std::string s, std::string &ppaths)
{
	vector<string> ret;

	if (s.front() == '{' && s.back() == '}')
	{	/* JObject */
		vector<string> subret;
		vector<string> svals;
		vector<string> cpaths;		//child paths

		//��������s���õ�������key�Լ���Ӧ��value���ַ���
		parseStringObject(s, cpaths, svals);

		for (int i = 0; i < cpaths.size(); i++)
		{
			subret = _JPathsJValues(svals[i], ppaths + " " + cpaths[i]);
			for (int j = 0; j < subret.size(); j++)
			{
				ret.push_back(subret[j]);
			}
		}
	}
	else
	{	/* JValue */
		ret.push_back(ppaths + " : " + s);
	}

	return ret;
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
static bool parseStringObject(const string &scontent, vector<string> &skeys, vector<string> &svalues)
{
	const char *content = scontent.c_str();
	vector<int> indexs;
	string chars;
	int  noteBrace=0;		//�����Ż���
	bool auxFlag=true;				//������־

	int cend = scontent.length();
	assert((content[0] == '{' && content[cend - 1] == '}') || (content[0] == '[' && content[cend - 1] == ']'));

	for (int cnt = 0; cnt < cend; cnt++)
	{
		//1).���ݴ������������bufferBrace���г����
		if (content[cnt] == '{')
		{
			noteBrace++;
		}
		else if (content[cnt] == '}')
		{
			if (noteBrace == 0)	return false;
			noteBrace--;
		}

		if (content[cnt] == ',' || noteBrace == 0)
		{
			auxFlag = true;
		}

		//2).�������������ѹ��chars��index.
		if (((noteBrace == 1 && content[cnt] != '}') || (noteBrace == 0 && content[cnt] == '}')) && auxFlag &&
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

static void JPathJValueTransfer(const vector<string> &jpaths_jvalues, vector<list<string>> &jpaths, vector<JVal> &jvals)
{
	for (int i = 0; i < jpaths_jvalues.size(); i++)
	{
		string sbuf;
		list<string> jpath;
		JVal jval;

		istringstream ss(jpaths_jvalues[i]);		//transform to istringstream!

		//1).��ȡ�õ�·��
		while (ss >> sbuf)
		{
			if (sbuf != ":")
			{
				jpath.push_back(sbuf);
			}
			else
				break;
		}

		//2).��ȡֵ
		ss >> sbuf;
		if (isnum(sbuf))
		{
			jval.SetData(stod(sbuf));
		}

		if (sbuf == "true")
		{
			jval.SetData(true);
		}

		if (sbuf == "false")
		{
			jval.SetData(false);
		}

		if (sbuf.front()=='"' && sbuf.back()=='"')
		{
			jval.SetData(sbuf.substr(1, sbuf.length()-2));
		}

		//3).����ֵ��·��
		jpaths.push_back(jpath);
		jvals.push_back(jval);
	}
}

static string preArrayProcess(const string &content)
{
	string chars;
	vector<int> jindexs;
	vector<bool> isArray;
	
	for (int i = 0; i < content.length(); i++)
	{
		switch (content.at(i))
		{
		case '[':
			isArray.push_back(true);
			jindexs.push_back(0);
			break;
		case '{':
			isArray.push_back(false);
			jindexs.push_back(0);
			break;
		case ']':
		case '}':
			isArray.pop_back();
			jindexs.pop_back();
		default:
			break;
		}

		if (content.at(i) == '[')
		{
			chars += '{';
		}
		else if (content.at(i) == ']')
		{
			chars += '}';
		}
		else
		{
			chars += content.at(i);
		}

		if (content.at(i) == '[' || content.at(i) == ',')
		{
			if (isArray.back())
			{
				chars += (string("\"") + JIndex(jindexs.back()++) + string("\":"));
			}
		}

	}

	return chars;
}