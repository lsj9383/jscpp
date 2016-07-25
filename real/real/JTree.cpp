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
	root = new JNode(_root_key);
	root->InitObject();
}

void JTree::set(std::list<std::string> path, JVal jval)
{
	_set(root, path, jval);
}

JVal JTree::get(std::list<std::string> path)
{
	return _get(root, path);
}

std::string JTree::travel(void)
{
	assert(root != NULL);	//确保jtree不为空，才可以遍历
	return _travel(root, 0);
}

JVal JTree::_get(JNode *cn, std::list<std::string> path)
{

	if (path.size() == 0)		//到路径尾了
	{
		return cn->GetValue();
	}

	string key = path.front();
	//搜索是否存在目标关键词
	if (cn->GetValue().GetType() == JOBJECT)
	{
		for (int i = 0; i < cn->GetValue().GetData().pKeyValue->size(); i++)
		{
			if (key == cn->GetValue().GetData().pKeyValue->at(i)->GetKey())
			{
				path.pop_front();
				return _get(cn->GetValue().GetData().pKeyValue->at(i), path);
			}
		}
	}

	//get搜寻失败
	assert(false);
	return JVal();
}

void JTree::_set(JNode *cn, std::list<std::string> path, JVal jval)
{
	if (path.size() == 0)		//到路径尾了
	{
		cn->SetValue(jval);
		return;
	}

	string key = path.front();
	bool isExist = false;
	JNode *nextJNode = NULL;

	//搜索是否存在目标关键词
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

	//根据关键词进行创建
	if (!isExist)
	{
		nextJNode = new JNode(key);

		if (path.size() > 1)					//大于1时说明后面还有对象.
		{
			nextJNode->InitObject();			//因此newJNode的value应该是object.
		}

		if (cn->GetValue().GetType() == JOBJECT)
		{
			cn->AddObject(nextJNode);		//当前节点为对象时
		}
		else
		{
			return;							//当前节点为数组时的添加方式
		}
	}

	//递归
	path.pop_front();
	_set(nextJNode, path, jval);
}

std::string JTree::_travel(JNode *cnode, int deep)
{
	assert(cnode != NULL);	//确保jtree不为空，才可以遍历
	string retString;

	if (cnode->GetValue().GetType() == JOBJECT)
	{
		if (deep != 0)
			retString = "\n";
		retString += prespace(deep*3) + "{\n";
		for (int i = 0; i < cnode->GetValue().GetData().pKeyValue->size(); i++)
		{
			retString = retString + prespace((deep+1) * 3) + "\"" + cnode->GetValue().GetData().pKeyValue->at(i)->GetKey() + "\" : ";
			retString += _travel(cnode->GetValue().GetData().pKeyValue->at(i), deep+1);
			//key:value间的分隔符
			if (i != cnode->GetValue().GetData().pKeyValue->size() - 1)
			{
				retString += ",";
			}
			retString += "\n";
		}
		retString += prespace(deep * 3) + "}";
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
	//为JObject类型，应该释放完其子节点.
	if (cn->GetValue().GetType() == JOBJECT)
	{
		for (int i = cn->GetValue().GetData().pKeyValue->size()-1; i >= 0; i--)
		{ 
			_freeTree(cn->GetValue().GetData().pKeyValue->at(i));			//释放掉第i各节点.
			cn->GetValue().GetData().pKeyValue->pop_back();				//将第i个节点的指针从vector中排出.
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
