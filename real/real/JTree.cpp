#include <sstream>
#include "Jscpp.h"

using namespace std;
using namespace jp;


//将int转换为字符串
static string getstring(const int n);
static string prespace(int n);

JTree::JTree(string _root_key)
{
	vector<JNode *> initKeyValue;
	root = new JNode(_root_key, initKeyValue);
}

void JTree::set(int value, std::deque<std::string> path)
{
	_set(root, value, path);
}

std::string JTree::travel(void)
{
	assert(root != NULL);	//确保jtree不为空，才可以遍历
	return _travel(root, 0);
}


void JTree::_set(JNode *cn, int value, std::deque<std::string> path)
{
	if (path.size() == 0)
	{
		cn->SetValue(value);
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
		if (path.size() > 1)				//大于1时说明后面还有对象.因此需要把后面的内容设置为
		{
			vector<JNode*> initKeyValue;
			newJNode->SetValue(initKeyValue);
		}
		nextJNode = newJNode;
		cn->AddObject(newJNode);
	}

	//递归
	path.pop_front();
	_set(nextJNode, value, path);
}

std::string JTree::_travel(JNode *cnode, int deep)
{
	assert(cnode != NULL);	//确保jtree不为空，才可以遍历
	string retString;

	if (cnode->GetType() == JOBJECT)
	{
		retString = "\n" + prespace(deep*3) + "{\n";
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
		case JINT: retString = getstring(*cnode->GetValue().pInt);break;
		}
	}

	return retString;
}

static string getstring(const int n)
{
	stringstream newstr;
	newstr << n;
	return newstr.str();
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