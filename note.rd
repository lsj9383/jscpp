一、JSON结构

	1.一个对象就是一对大括号，里面的有多个key:value字段, key:value间以逗号隔开
	{
		key:value,
		key:value,
	}

	2.一个数组就是一个对中括号，里面有多个value，value间以逗号隔开
	[
		value,
		value,
		value
	]

	3.key:value的value有多种类型:
	1).整数
	2).浮点数
	3).字符串
	4).布尔型
	5).对象
	6).数组

二、关键数据结构：
	(以下程序只是个逻辑表示，并不代表能运行)
	1.JNode, json node
	key:value数据用一个node来进行表示
	struct JNode
	{
		string key;
		JVal value;
	}
	key是个string类型，指明了关键字。
	value是个JVal类型，稍后定义，里面包含了值的类型与数据（指针）。
	
	2.JData, json data
	union JData
	{
		double *pDouble;
		string *pString;
		bool *pBool;
		vector<node *> *pKeyValue;
	}
	所有的字段全是指针型，这样在内存中，JVal始终只会占一个地址的空间。
	需要注意的是，当type指示当前node为一个Json Object时，使用的指针是pKeyValue，这个指针中保存的指针是指向node数据的。
	并且需要指出，当type指数当前node为一个Json Array时，只用的指针仍然为pKeyValue，因为可以认为数组是一个特殊的对象，特殊之处在于省略了key，并且key按顺序设置 。
	
	3.JType
	enum JType
	{
		JDOUBLE,		//json double
		JSTRING,		//json string
		JBOOL,			//json boolean
		JOBJECT,		//json object
		JNULL			//json null
	}
	指示了node中的value可能的类型。
	JNULL代指该node无可用value。
	这里面没有为数组 和 int留出类型位置。
	
	1).对于数组。
		在工程中，数组的组织形式和对象是相同的，只是在打印出来的时候会根据实际的类型进行转化为数组形式打印。
		因此，数组其实是一个特殊的对象，特殊在于对象里面有多个key:value,而数组里面是多个value，省略了key。
		因此可以把数组视为key不用人为干涉，并且从小到大排序的一个对象。
	2).对于int
		虽然JVal的接口可以传入int数据，但是在内部是将int转换为double来进行存储的，没有别的原因，这是为了简化操作。
	
	4.JValue
	struct JVal
	{
		JType type;
		JData data;
	};
	记录了一个数据的类型，以及数据的值（指针）。
	
二、关键类设计
	以上是数据结构的一种逻辑组织，代码组织将其稍微变形
	1.JVal
		构造函数:
			JVal(data),初始化value的值，类型会根据值而自信确定。
		接口:
			SetData(data), 拷贝value的值到JVal对象中，类型会根据值而自行确定。
		应该指出，JVal支持int double bool string vector<JNode*> 到 JVal的隐式转换。
		
	2.JNode
		构造函数
			JNode(key, value);建立一个key:value的node.
				需要注意，这里的value是JVal类型，并且支持隐式转换。
			JNode();建立一个key:value为空的node.
		接口:
			SetKey(Key), 重新设置key。
			SetValue(value), 重新设置JVal类型的value，支持隐式转换。
			AddObject(newObject), 给JNode添加新的对象，也就是一个Node
		析构：
			在JNode释放时，将会自动释放掉里面value的空间。
			
	3.JTree
		用于管理node的树空间。这是一个多叉树。
		树的节点有三种类型:
			1、叶子节点(非JOBJECT 非ARRAY型节点)。
			2、对象节点，以JNode*指向子节点。
			3、数组节点，子节点是特殊的UVal类型。
		构造函数：
		接口：
			set
			travel, 采用DFS遍历tree，并将返回值放在字符串中。需要明确的是，一个对象需要打印的内容为
				{
					key:...,
					key:...,
					key:...
				}
				其中的...由递归进行打印。
	4.Jscpp
		Jscpp是作为包装代理类的概念存在的，封装了对JTree的操作，使接口更为人性化，用户不用直接对JTree进行操作。
		
		
三、原理性设计
	1.set设置值。
		核心代码在JTree::_set.采用递归进行。
		该函数可以翻译为，将cn的相对路径所指的node设置jvalue。若不存在该路径，则会自行创建该路径。
		cn，为当前node
		path，是当前node剩下的路径，其中path[0]应该为cn的某个子节点。若path为0，那么就将jvalue直接设置在cn中。
		jvalue，要设置的值。
		void JTree::_set(JNode *cn, deque path, JVal jvalue)
		{
			//由于路径已空，因此就是将当前cn的值进行设置。也是递归结束条件。
			if(path.size()==0)
			{
				cn.setValue(jvalue);
			}
			
			//搜索是否存在关键词，若找到，则直接设置下一个节点nextJNode
			
			//若没找到，则人为创建新节点，并且设置下个节点nextJNode.
			if(!isExit)
			{
				JNode *newJNode = new JNode(key);		//此时并不指定该节点类型，因为要更加该节点的下一个路径来决定当前节点是什么节点。
				if(path.size() == 1)					//对于path长度==1，不作任何处理，因为它是叶节点，对叶节点的赋值将在下次递归的时候自行完成。
				{}
				else
				{
					if (next path means JObject)		//当下个节点意味着key的时候，设置该节点类型为对象。
					{}
					else								//否则下个节点是数组索引的时候，设置该节点类型为数组。
					{}
				}
				//将新节点添加到当前节点下
			}
			
			path.pop_front();							//选用了下一个节点，因此path的头位置的关键字应该被pop掉，nextJNode的关键词就是才被pop掉的。
			_set(nextNode, jtype, path, jval);			//递归
		}
	2.travel，返回遍历的结果字符串。
		核心代码在JTree::_travel中。采用深度优先搜索的递归实现进行遍历。
		1).对于一个对象型node，产生
			{
				key1:....,
				key2:....,
			}
			其中，...是一个value的递归实现。
		2).对于一个数组型对象，产生
			[
				...,
				...
			]
			其中，...是一个value的递归实现。
		3).普通对象，产生
			直接值
		总结===>一个递归实现产生一个value，若是对象型会打印下一层的关键词。
	3.load，将文件中的数据转换为json数据。
		1).将整个文件的数据缓存至内存中。
		2).将json中的数组数据，转换为特殊的对象数据，以便统一处理。
		3).将字符串的value数据中的所有path:value提取出来，均是字符串形式。
		4).将字符串形式转换为JPath和JValue形式。
		5).将所有的路径对应的值进行添加。