json load and save in c++.
There is some interface for user:
	ctor:
		Jscapp jscpp = new Jscpp("root_key");				//这是根的关键词。
	
	file io:
		bool b = jscpp->save(file_path);					//将jscpp的数据按json格式进行保存, b返回函数操作结果是否成功。
		bool b = jscpp->load(file_path);					//将json格式数据，加载到jscpp的jtree中，b返回函数操作结果是否成功。
	
	object io:
		jscpp->set(value, key1, key2, key3, ..., ":");		//这是个变参方法，无返回，设置指定的字段数据。以待赋值开头，冒号结尾。
		
		JNode *n = jscpp->at(key1, key2, key3, ...);		//这是个变参方法，返回的是JNode类型，这里面包含了对应字段的数据类型、关键词、数据。
		bool b = jscpp->isAt(key1, key2, key3, ...);		//这是个变参方法，返回bool，用来检测指定的数据是否存在。
		
	other :
		string s = jscpp->travel();							//遍历内容，并将内容保存于s中。