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
	�ڹ����У��������֯��ʽ�Ͷ�������ͬ�ģ�ֻ���ڴ�ӡ������ʱ������ʵ�ʵ����ͽ���ת��Ϊ������ʽ��ӡ��
	��ˣ�������ʵ��һ������Ķ����������ڶ��������ж��key:value,�����������Ƕ��value��ʡ����key��
	��˿��԰�������Ϊkey������Ϊ���棬���Ҵ�С���������һ������

	3.key:value��value�ж�������:
	1).����
	2).������
	3).�ַ���
	4).������
	5).����
	6).����

�����ؼ����ݽṹ��
	(���³���ֻ�Ǹ��߼���ʾ����������������)
	1.JNode, json node
	key:value������һ��node�����б�ʾ
	struct JNode
	{
		string key;
		JVal value;
	}
	key�Ǹ�string���ͣ�ָ���˹ؼ��֡�
	value�Ǹ�JVal���ͣ��Ժ��壬���������ֵ�����������ݣ�ָ�룩��
	
	2.JData, json data
	union JData
	{
		int *pInt;
		double *pDouble;
		string *pString;
		bool *pBool;
		vector<node *> *pKeyValue;
	}
	���е��ֶ�ȫ��ָ���ͣ��������ڴ��У�JValʼ��ֻ��ռһ����ַ�Ŀռ䡣
	��Ҫע����ǣ���typeָʾ��ǰnodeΪһ��Json Objectʱ��ʹ�õ�ָ����pKeyValue�����ָ���б����ָ����ָ��node���ݵġ�
	������Ҫָ������typeָ����ǰnodeΪһ��Json Arrayʱ��ֻ�õ�ָ����ȻΪpKeyValue����Ϊ������Ϊ������һ������Ķ�������֮������ʡ����key������key��˳������ ��
	
	3.JType
	enum JType
	{
		JINT,			//json int
		JDOUBLE,		//json double
		JSTRING,		//json string
		JBOOL,			//json boolean
		JOBJECT,		//json object
		JARRAY,			//json array
		JNULL			//json null
	}
	ָʾ��node�е�value���ܵ����͡�
	JNULL��ָ��node�޿���value��
	
	4.JValue
	struct JVal
	{
		JType type;
		JData data;
	};
	��¼��һ�����ݵ����ͣ��Լ����ݵ�ֵ��ָ�룩��
	
�����ؼ������
	���������ݽṹ��һ���߼���֯��������֯������΢����
	1.JVal
		���캯��:
			JVal(data),��ʼ��value��ֵ�����ͻ����ֵ������ȷ����
		�ӿ�:
			SetData(data), ����value��ֵ��JVal�����У����ͻ����ֵ������ȷ����
		Ӧ��ָ����JVal֧��int double bool string vector<JNode*> �� JVal����ʽת����
		
	2.JNode
		���캯��
			JNode(key, value);����һ��key:value��node.
				��Ҫע�⣬�����value��JVal���ͣ�����֧����ʽת����
			JNode();����һ��key:valueΪ�յ�node.
		�ӿ�:
			SetKey(Key), ��������key��
			SetValue(value), ��������JVal���͵�value��֧����ʽת����
			AddObject(newObject), ��JNode����µĶ���Ҳ����һ��Node
		������
			��JNode�ͷ�ʱ�������Զ��ͷŵ�����value�Ŀռ䡣
			
	3.JTree
		���ڹ���node�����ռ䡣����һ���������
		���Ľڵ�����������:
			1��Ҷ�ӽڵ�(��JOBJECT ��ARRAY�ͽڵ�)��
			2������ڵ㣬��JNode*ָ���ӽڵ㡣
			3������ڵ㣬�ӽڵ��������UVal���͡�
		���캯����
		�ӿڣ�
			set
			travel, ����DFS����tree����������ֵ�����ַ����С���Ҫ��ȷ���ǣ�һ��������Ҫ��ӡ������Ϊ
				{
					key:...,
					key:...,
					key:...
				}
				���е�...�ɵݹ���д�ӡ��
	4.Jscpp
		Jscpp����Ϊ��װ������ĸ�����ڵģ���װ�˶�JTree�Ĳ�����ʹ�ӿڸ�Ϊ���Ի����û�����ֱ�Ӷ�JTree���в�����
		
		
����ԭ�������
	1.set����ֵ��
		���Ĵ�����JTree::_set.���õݹ���С�
		�ú������Է���Ϊ����cn�����·����ָ��node����jvalue���������ڸ�·����������д�����·����
		cn��Ϊ��ǰnode
		path���ǵ�ǰnodeʣ�µ�·��������path[0]Ӧ��Ϊcn��ĳ���ӽڵ㡣��pathΪ0����ô�ͽ�jvalueֱ��������cn�С�
		jvalue��Ҫ���õ�ֵ��
		void JTree::_set(JNode *cn, deque path, JVal jvalue)
		{
			//����·���ѿգ���˾��ǽ���ǰcn��ֵ�������á�Ҳ�ǵݹ����������
			if(path.size()==0)
			{
				cn.setValue(jvalue);
			}
			
			//�����Ƿ���ڹؼ��ʣ����ҵ�����ֱ��������һ���ڵ�nextJNode
			
			//��û�ҵ�������Ϊ�����½ڵ㣬���������¸��ڵ�nextJNode.
			if(!isExit)
			{
				JNode *newJNode = new JNode(key);		//��ʱ����ָ���ýڵ����ͣ���ΪҪ���Ӹýڵ����һ��·����������ǰ�ڵ���ʲô�ڵ㡣
				if(path.size() == 1)					//����path����==1�������κδ�����Ϊ����Ҷ�ڵ㣬��Ҷ�ڵ�ĸ�ֵ�����´εݹ��ʱ��������ɡ�
				{}
				else
				{
					if (next path means JObject)		//���¸��ڵ���ζ��key��ʱ�����øýڵ�����Ϊ����
					{}
					else								//�����¸��ڵ�������������ʱ�����øýڵ�����Ϊ���顣
					{}
				}
				//���½ڵ���ӵ���ǰ�ڵ���
			}
			
			path.pop_front();							//ѡ������һ���ڵ㣬���path��ͷλ�õĹؼ���Ӧ�ñ�pop����nextJNode�Ĺؼ��ʾ��ǲű�pop���ġ�
			_set(nextNode, jtype, path, jval);			//�ݹ�
		}
	2.travel�����ر����Ľ���ַ�����
		���Ĵ�����JTree::_travel�С�����������������ĵݹ�ʵ�ֽ��б�����
		1).����һ��������node������
			{
				key1:....,
				key2:....,
			}
			���У�...��һ��value�ĵݹ�ʵ�֡�
		2).����һ�������Ͷ��󣬲���
			[
				...,
				...
			]
			���У�...��һ��value�ĵݹ�ʵ�֡�
		3).��ͨ���󣬲���
			ֱ��ֵ
		�ܽ�===>һ���ݹ�ʵ�ֲ���һ��value�����Ƕ����ͻ��ӡ��һ��Ĺؼ��ʡ�