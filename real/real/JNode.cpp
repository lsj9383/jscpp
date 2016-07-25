#include "Jscpp.h"

using namespace std;
using namespace jc;

void JNode::InitObject()
{
	vector<JNode*> initKeyValue;

	SetValue(JVal(initKeyValue));
}

void JNode::AddObject(const JNode* newObject)
{
	assert(mVal.GetType() == JOBJECT);		//要在当前node中添加newObject，那当前node必须为JOBJECT才能添加成功。
	this->mVal.GetData().pKeyValue->push_back((JNode *)newObject);
}