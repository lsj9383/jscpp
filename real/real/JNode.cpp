#include "Jscpp.h"

using namespace std;
using namespace jp;

JNode::~JNode()
{
	switch (mType)
	{
	case JINT	:	delete mValue.pInt;		break;
	case JDOUBLE:	delete mValue.pDouble;	break;
	case JSTRING:	delete mValue.pString;	break;
	case JBOOL	:	delete mValue.pBool;	break;
	default:		break;
	}
}

void JNode::SetValue(const int &val)
{
	this->mValue.pInt = new int;
	*this->mValue.pInt = val;
	this->mType = JINT;
}

void JNode::SetValue(const double &val)
{
	this->mValue.pDouble = new double;
	*this->mValue.pDouble = val;
	this->mType = JDOUBLE;
}

void JNode::SetValue(const string &val)
{
	this->mValue.pString = new string(val);
	this->mType = JSTRING;
}

void JNode::SetValue(const bool &val)
{
	this->mValue.pBool = new bool;
	*this->mValue.pBool = val;
	this->mType = JBOOL;
}


void JNode::SetValue(const vector<JNode *> &val)
{
	this->mValue.pKeyValue = new vector<JNode *>(0);
	for (int i = 0; i < val.size(); i++)
	{
		this->mValue.pKeyValue->push_back(val[i]);
	}
	this->mType = JOBJECT;
}

void JNode::AddObject(const JNode* newObject)
{
	assert(this->mType == JOBJECT);		//要在当前node中添加newObject，那当前node必须为JOBJECT才能添加成功。
	this->mValue.pKeyValue->push_back((JNode *)newObject);
}

