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
