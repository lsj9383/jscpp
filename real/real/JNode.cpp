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
	assert(mVal.GetType() == JOBJECT);		//Ҫ�ڵ�ǰnode�����newObject���ǵ�ǰnode����ΪJOBJECT������ӳɹ���
	this->mVal.GetData().pKeyValue->push_back((JNode *)newObject);
}