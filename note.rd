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
	1.JNode
	key:value数据用一个node来进行表示
	struct JNode
	{
		string key;
		UVal value;
		ValueType type;
	}
	key是个string类型，指明了关键字。
	value是个UVal类型，是个union，稍后定义。
	type是个ValueType，是个enum，定义了value实际所用的类型，稍后定义。
	
	2.UVal
	union UVal
	{
		int *pInt;
		double *pDouble;
		string *pString;
		bool *pBool;
		vector<node *> *pKeyValue;
		vector<Uval> *pArray;
	}
	所有的字段全是指针型，这样在内存中，Uval始终只会占一个地址的空间。
	需要注意的是，当type指示当前node为一个Json Object时，使用的指针是pKeyValue，这个指针中保存的指针是指向node数据的。
	
	3.JValueType
	enum JValueType
	{
		JINT,			//json int
		JDOUBLE,		//json double
		JSTRING,		//json string
		JBOOL,			//json boolean
		JOBJECT,		//json object
		JARRAY,			//json array
		JNULL			//json null
	}
	指示了node中的value可能的类型。
	JNULL代指该node无可用value。
	
二、关键类设计
	以上是数据结构的一种逻辑组织，代码组织将其稍微变形
	1.JNode
		构造函数
			JNode(key, value);建立一个key:value的node， type会根据value自行设置。
			JNode();建立一个key:value都为空，type为JNULL的node。
		接口:
			SetKey(Key), 重新设置key。
			SetValue(value), 重新设置value，type会根据value自行设置。
		析构：
			在JNode释放时，将会自动释放掉里面value的空间。