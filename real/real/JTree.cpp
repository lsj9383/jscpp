#include <sstream>
#include "Jscpp.h"

using namespace std;
using namespace jc;


//��intת��Ϊ�ַ���

static bool isArray(JNode *jn);
static string getstring(int n);
static string getstring(double n);
static string getstring(bool n);
static string prespace(int n);

JTree::JTree(string _root_key)
{
	root = new JNode(_root_key);
	root->InitObject();
}

void JTree::set(std::list<std::string> path, const JVal &jval)
{
	_set(root, path, jval);
}

const JVal &JTree::get(std::list<std::string> path) const
{
	return _get(root, path);
}

std::string JTree::travel(void) const
{
	assert(root != NULL);	//ȷ��jtree��Ϊ�գ��ſ��Ա���
	return _travel(root, 0);
}

const JVal &JTree::_get(JNode *cn, std::list<std::string> path) const
{

	if (path.size() == 0)		//��·��β��
	{
		return cn->GetValue();
	}

	string key = path.front();
	const vector<JNode*> *jobjects = cn->GetValue().GetData().pKeyValue;

	//�����Ƿ����Ŀ��ؼ���
	if (cn->GetValue().GetType() == JOBJECT)
	{
		for (int i = 0; i < jobjects->size(); i++)
		{
			if (key == jobjects->at(i)->GetKey())
			{
				path.pop_front();
				return _get(jobjects->at(i), path);
			}
		}
	}

	//get��Ѱʧ��
	assert(false);
	return JVal();
}

void JTree::_set(JNode *cn, std::list<std::string> path, const JVal &jval)
{
	if (path.size() == 0)		//��·��β��
	{
		cn->SetValue(jval);
		return;
	}

	string key = path.front();
	bool isExist = false;
	JNode *nextJNode = NULL;

	//�����Ƿ����Ŀ��ؼ���
	if (cn->GetValue().GetType() == JOBJECT)
	{
		for (int i = 0; i < cn->GetValue().GetData().pKeyValue->size(); i++)
		{
			if (key == cn->GetValue().GetData().pKeyValue->at(i)->GetKey())
			{
				nextJNode = cn->GetValue().GetData().pKeyValue->at(i);
				isExist = true;
			}
		}
	}

	//���ݹؼ��ʽ��д���
	if (!isExist)
	{
		nextJNode = new JNode(key);

		if (path.size() > 1)					//����1ʱ˵�����滹�ж���.
		{
			nextJNode->InitObject();			//���newJNode��valueӦ����object.
		}

		if (cn->GetValue().GetType() == JOBJECT)
		{
			cn->AddObject(nextJNode);		//��ǰ�ڵ�Ϊ����ʱ
		}
		else
		{
			return;							//��ǰ�ڵ�Ϊ����ʱ����ӷ�ʽ
		}
	}

	//�ݹ�
	path.pop_front();
	_set(nextJNode, path, jval);
}

std::string JTree::_travel(JNode *cnode, int deep) const
{
	assert(cnode != NULL);	//ȷ��jtree��Ϊ�գ��ſ��Ա���
	string retString;

	if (cnode->GetValue().GetType() == JOBJECT)
	{
		if (!isArray(cnode))
		{	//������
			if (deep != 0)
				retString = "\n";
			retString += prespace(deep * 3) + "{\n";
			for (int i = 0; i < cnode->GetValue().GetData().pKeyValue->size(); i++)
			{
				retString = retString + prespace((deep + 1) * 3) + "\"" + cnode->GetValue().GetData().pKeyValue->at(i)->GetKey() + "\" : ";
				retString += _travel(cnode->GetValue().GetData().pKeyValue->at(i), deep + 1);
				//key:value��ķָ���
				if (i != cnode->GetValue().GetData().pKeyValue->size() - 1)
				{
					retString += ",";
				}
				retString += "\n";
			}
			retString += prespace(deep * 3) + "}";
		}
		else
		{	//���飬ע������Ҳ����JOBJECT��ֻ��key�Ƚ�����
			if (deep != 0)
				retString = "\n";
			retString += prespace(deep * 3) + "[";
			for (int i = 0; i < cnode->GetValue().GetData().pKeyValue->size(); i++)
			{
				retString += _travel(cnode->GetValue().GetData().pKeyValue->at(i), deep + 1);
				//key:value��ķָ���
				if (i != cnode->GetValue().GetData().pKeyValue->size() - 1)
				{
					retString += ",";
				}
				else
				{
					retString += "\n";
				}
			}
			retString += prespace(deep * 3) + "]";
		}
	}
	else
	{
		switch (cnode->GetValue().GetType())
		{
		case JINT	: retString = getstring((int)*cnode->GetValue().GetData().pInt); break;
		case JDOUBLE: retString = getstring((double)*cnode->GetValue().GetData().pDouble); break;
		case JBOOL: retString = getstring((bool)*cnode->GetValue().GetData().pBool); break;
		case JSTRING: retString = "\"" + *cnode->GetValue().GetData().pString + "\""; break;
		}
	}

	return retString;
}

void JTree::_freeTree(JNode *cn)
{
	//ΪJObject���ͣ�Ӧ���ͷ������ӽڵ�.
	if (cn->GetValue().GetType() == JOBJECT)
	{
		for (int i = cn->GetValue().GetData().pKeyValue->size()-1; i >= 0; i--)
		{ 
			_freeTree(cn->GetValue().GetData().pKeyValue->at(i));			//�ͷŵ���i���ڵ�.
			cn->GetValue().GetData().pKeyValue->pop_back();				//����i���ڵ��ָ���vector���ų�.
		}
	}

	//cn��ʱΪ��ɾ���ڵ�.
	delete cn;
}

static string getstring(int n)
{
	stringstream newstr;
	newstr << n;
	return newstr.str();
}

static string getstring(double n)
{
	stringstream newstr;
	newstr << n;
	return newstr.str();
}

static string getstring(bool n)
{
	if (n)	return "true";
	else	return "false";
}

static string prespace(int n)
{
	string ret;
	while (n--)
	{
		ret += " ";
	}
	return ret;
}

static bool isnum(string s)
{
	stringstream sin(s);
	double t;
	char p;
	if (!(sin >> t))
		return false;
	if (sin >> p)
		return false;
	else
		return true;
}

static bool isArray(JNode *jn)
{
	assert(jn->GetValue().GetType() == JOBJECT);

	for (int i = 0; i < jn->GetValue().GetData().pKeyValue->size(); i++)
	{
		if (jn->GetValue().GetData().pKeyValue->at(i)->GetKey().length() < 3)	return false;
		string s = jn->GetValue().GetData().pKeyValue->at(i)->GetKey();
		if (s[0] == '#' && s[1] == '#')
		{	//ǰ׺��ȷ
			return isnum(s.substr(2, s.size() - 2));
		}
		else
		{
			return false;
		}
	}
}
