һ��JSON�ṹ

	1.һ���������һ�Դ����ţ�������ж��key:value�ֶ�, key:value���Զ��Ÿ���
	{
		key:value,
		key:value,
	}

	2.һ���������һ���������ţ������ж��value��value���Զ��Ÿ���
	[
		value,
		value,
		value
	]

	3.key:value��value�ж�������:
	1).����
	2).������
	3).�ַ���
	4).������
	5).����
	6).����

�����ؼ����ݽṹ��
	(���³���ֻ�Ǹ���ʾ����������������)
	1.key:value������һ��node�����б�ʾ
	struct node
	{
		string key;
		Uval value;
		ValueType type;
	}
	key�Ǹ�string���ͣ�ָ���˹ؼ��֡�
	value�Ǹ�Uval���ͣ��Ǹ�union���Ժ��塣
	type�Ǹ�ValueType���Ǹ�enum��������valueʵ�����õ����ͣ��Ժ��塣
	
	2.Uval
	union Uval
	{
		int *pInt;
		double *pDouble;
		string *pString;
		bool *pBool;
		vector<node *> *pKeyValue;
		vector<Uval> *pArray;
	}
	���е��ֶ�ȫ��ָ���ͣ��������ڴ��У�Uvalʼ��ֻ��ռһ����ַ�Ŀռ䡣
	��Ҫע����ǣ���typeָʾ��ǰnodeΪһ��Json Objectʱ��ʹ�õ�ָ����pKeyValue�����ָ���б����ָ����ָ��node���ݵġ�
	
	3.ValueType
	enum ValueType
	{
		JINT,			//json int
		JDOUBLE,		//json double
		JSTRING,		//json string
		JBOOL,			//json boolean
		JOBJECT,		//json object
		JARRAY			//json array
	}
	ָʾ��node�е�value���ܵ����͡�