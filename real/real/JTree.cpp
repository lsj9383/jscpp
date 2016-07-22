#include <sstream>
#include "Jscpp.h"

using namespace std;
using namespace jc;


//��intת��Ϊ�ַ���
static string getstring(int n);
static string getstring(double n);
static string getstring(bool n);
static string prespace(int n);

JTree::JTree(string _root_key)
{
	vector<JNode *> initKeyValue;
	root = new JNode(_root_key, initKeyValue);
}

void JTree::set(JValueType jtype, std::deque<std::string> path, UVal jval)
{
	_set(root, jtype, path, jval);
}

std::string JTree::travel(void)
{
	assert(root != NULL);	//ȷ��jtree��Ϊ�գ��ſ��Ա���
	return _travel(root, 0);
}

void JTree::_set(JNode *cn, JValueType jtype, std::deque<std::string> path, UVal jval)
{
	if (path.size() == 0)
	{
		switch (jtype)
		{
		case JINT	:	cn->SetValue(*jval.pInt);			break;
		case JDOUBLE:	cn->SetValue(*jval.pDouble);		break;
		case JBOOL	:	cn->SetValue(*jval.pBool);			break;
		case JSTRING:	cn->SetValue(*jval.pString);		break;
		default		:	assert(false);						break;
		}
		return;
	}

	string key = path[0];
	bool isExist = false;
	JNode *nextJNode = NULL;

	//�����Ƿ����Ŀ��ؼ���
	if (cn->GetType() == JOBJECT)
	{
		for (int i = 0; i < cn->GetValue().pKeyValue->size(); i++)
		{
			if (key == cn->GetValue().pKeyValue->at(i)->GetKey())
			{
				nextJNode = cn->GetValue().pKeyValue->at(i);
				isExist = true;
			}
		}
	}

	//���ݹؼ��ʽ��д���
	if (!isExist)
	{
		JNode *newJNode = new JNode(key);
		vector<JNode*> initKeyValue;

		if (path.size() > 1)				//����1ʱ˵�����滹�ж���.�����Ҫ�Ѻ������������Ϊ
		{
			newJNode->SetValue(initKeyValue);
		}
		nextJNode = newJNode;

		if (cn->GetType() == JOBJECT)		
		{ 
			cn->AddObject(newJNode);		//��ǰ�ڵ�Ϊ����ʱ
		}
		else
		{
			return;							//��ǰ�ڵ�Ϊ����ʱ����ӷ�ʽ
		}
	}

	//�ݹ�
	path.pop_front();
	_set(nextJNode, jtype, path, jval);
}

std::string JTree::_travel(JNode *cnode, int deep)
{
	assert(cnode != NULL);	//ȷ��jtree��Ϊ�գ��ſ��Ա���
	string retString;

	if (cnode->GetType() == JOBJECT)
	{
		if (deep != 0)
			retString = "\n";
		retString += prespace(deep*3) + "{\n";
		for (int i = 0; i < cnode->GetValue().pKeyValue->size(); i++)
		{
			retString = retString + prespace((deep+1) * 3) + "\"" + cnode->GetValue().pKeyValue->at(i)->GetKey() + "\" : ";
			retString += _travel(cnode->GetValue().pKeyValue->at(i), deep+1);
			//key:value��ķָ���
			if (i != cnode->GetValue().pKeyValue->size() - 1)
			{
				retString += ",";
			}
			retString += "\n";
		}
		retString += prespace(deep * 3) + "}";
	}
	else
	{
		switch (cnode->GetType())
		{
		case JINT	: retString = getstring((int)*cnode->GetValue().pInt); break;
		case JDOUBLE: retString = getstring((double)*cnode->GetValue().pDouble); break;
		case JBOOL	: retString = getstring((bool)*cnode->GetValue().pBool); break;
		case JSTRING: retString = "\"" + *cnode->GetValue().pString + "\""; break;
		}
	}

	return retString;
}

void JTree::_freeTree(JNode *cn)
{
	//ΪJObject���ͣ�Ӧ���ͷ������ӽڵ�.
	if (cn->GetType() == JOBJECT)
	{
		for (int i = cn->GetValue().pKeyValue->size()-1; i >= 0; i--)
		{ 
			_freeTree(cn->GetValue().pKeyValue->at(i));			//�ͷŵ���i���ڵ�.
			cn->GetValue().pKeyValue->pop_back();				//����i���ڵ��ָ���vector���ų�.
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