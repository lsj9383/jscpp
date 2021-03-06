
#include "Jscpp.h"
#include "JFunction.h"

using namespace std;
using namespace jc;


//将int转换为字符串

static bool isArray(JNode *jn);
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

bool JTree::isAt(std::list<std::string> path) const
{
	return _isAt(root, path);
}

std::string JTree::travel(void) const
{
	assert(root != NULL);	//确保jtree不为空，才可以遍历
	return _travel(root, 0);
}

const JVal &JTree::_get(JNode *cn, std::list<std::string> path) const
{
	if (path.size() == 0)		//到路径尾了
	{
		return cn->GetValue();
	}

	string key = path.front();
	const vector<JNode*> *jobjects = cn->GetValue().GetData().pKeyValue;

	//搜索是否存在目标关键词
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

	//get搜寻失败
	assert(false);
	return JVal();
}

bool JTree::_isAt(JNode *cn, std::list<std::string> path) const
{
	//找到path都没了都有，那就证明这条路径是存在的
	if (path.size() == 0)
	{
		return true;
	}

	string key = path.front();
	const vector<JNode*> *jobjects = cn->GetValue().GetData().pKeyValue;

	//搜索是否存在目标关键词
	if (cn->GetValue().GetType() == JOBJECT)
	{
		for (int i = 0; i < jobjects->size(); i++)
		{
			if (key == jobjects->at(i)->GetKey())
			{
				path.pop_front();
				return _isAt(jobjects->at(i), path);
			}
		}
	}

	//get搜寻失败
	return false;
}

void JTree::_set(JNode *cn, std::list<std::string> path, const JVal &jval)
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

std::string JTree::_travel(JNode *cnode, int deep) const
{
	assert(cnode != NULL);	//确保jtree不为空，才可以遍历
	string retString;

	if (cnode->GetValue().GetType() == JOBJECT)
	{
		if (!isArray(cnode))
		{	//非数组
			if (deep != 0)
				retString = "\n";
			retString += prespace(deep * 3) + "{\n";
			for (int i = 0; i < cnode->GetValue().GetData().pKeyValue->size(); i++)
			{
				retString = retString + prespace((deep + 1) * 3) + "\"" + cnode->GetValue().GetData().pKeyValue->at(i)->GetKey() + "\" : ";
				retString += _travel(cnode->GetValue().GetData().pKeyValue->at(i), deep + 1);
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
		{	//数组，注意数组也属于JOBJECT，只是key比较特殊
			if (deep != 0)
				retString = "\n";
			retString += prespace(deep * 3) + "[";
			for (int i = 0; i < cnode->GetValue().GetData().pKeyValue->size(); i++)
			{
				retString += _travel(cnode->GetValue().GetData().pKeyValue->at(i), deep + 1);
				//key:value间的分隔符
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

static string prespace(int n)
{
	string ret;
	while (n--)
	{
		ret += " ";
	}
	return ret;
}

static bool isArray(JNode *jn)
{
	assert(jn->GetValue().GetType() == JOBJECT);

	for (int i = 0; i < jn->GetValue().GetData().pKeyValue->size(); i++)
	{
		if (jn->GetValue().GetData().pKeyValue->at(i)->GetKey().length() < 3)	return false;
		string s = jn->GetValue().GetData().pKeyValue->at(i)->GetKey();
		if (s[0] == '#' && s[1] == '#')
		{	//前缀正确
			return isnum(s.substr(2, s.size() - 2));
		}
		else
		{
			return false;
		}
	}
}
