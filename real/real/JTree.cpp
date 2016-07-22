#include <sstream>
#include "Jscpp.h"

using namespace std;
using namespace jc;


//将int转换为字符串
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
	assert(root != NULL);	//确保jtree不为空，才可以遍历
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

	//搜索是否存在目标关键词
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

	//根据关键词进行创建
	if (!isExist)
	{
		JNode *newJNode = new JNode(key);
		vector<JNode*> initKeyValue;

		if (path.size() > 1)				//大于1时说明后面还有对象.因此需要把后面的内容设置为
		{
			newJNode->SetValue(initKeyValue);
		}
		nextJNode = newJNode;

		if (cn->GetType() == JOBJECT)		
		{ 
			cn->AddObject(newJNode);		//当前节点为对象时
		}
		else
		{
			return;							//当前节点为数组时的添加方式
		}
	}

	//递归
	path.pop_front();
	_set(nextJNode, jtype, path, jval);
}

std::string JTree::_travel(JNode *cnode, int deep)
{
	assert(cnode != NULL);	//确保jtree不为空，才可以遍历
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
			//key:value间的分隔符
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
	//为JObject类型，应该释放完其子节点.
	if (cn->GetType() == JOBJECT)
	{
		for (int i = cn->GetValue().pKeyValue->size()-1; i >= 0; i--)
		{ 
			_freeTree(cn->GetValue().pKeyValue->at(i));			//释放掉第i各节点.
			cn->GetValue().pKeyValue->pop_back();				//将第i个节点的指针从vector中排出.
		}
	}

	//cn此时为可删除节点.
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