#include "Jscpp.h"

using namespace jc;
using namespace std;

//需要注意，对于Object，这里只释放了它的vector<指针>的存储空间，它其中指针所对应的空间应有外部释放。
JVal::~JVal()
{
	switch (mType)
	{
	case JDOUBLE:
		delete mData.pDouble;	break;
	case JSTRING:
		delete mData.pString;	break;
	case JBOOL:
		delete mData.pBool;		break;
	case JOBJECT:
		delete mData.pKeyValue;
		break;
	default:		break;
	}
}

void JVal::SetData(const JVal &val)
{
	switch (val.mType)
	{
	case JDOUBLE:
		SetData(*val.mData.pDouble);
		break;
	case JSTRING:
		SetData(*val.mData.pString);
		break;
	case JBOOL:
		SetData(*val.mData.pBool);
		break;
	case JOBJECT:
		SetData(*val.mData.pKeyValue);
		break;
	default:	
		assert(false);
		break;
	}
}

void JVal::SetData(const double &val)
{
	this->mData.pDouble = new double(val);
	this->mType = JDOUBLE;
}

void JVal ::SetData(const string &val)
{
	this->mData.pString = new string(val);
	this->mType = JSTRING;
}

void JVal::SetData(const bool &val)
{
	this->mData.pBool = new bool(val);
	this->mType = JBOOL;
}

void JVal::SetData(const vector<JNode *> &val)
{
	this->mData.pKeyValue = new vector<JNode *>(0);
	for (int i = 0; i < val.size(); i++)
	{
		this->mData.pKeyValue->push_back(val[i]);
	}
	this->mType = JOBJECT;
}
