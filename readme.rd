json load and save in c++.
There is some interface for user:
	ctor:
		Jscapp jscpp = new Jscpp("root_key");
	
	file io:
		1).bool b = jscpp->save(file_path);
		将jscpp的数据按json格式进行保存, b返回函数操作结果是否成功。
			
		2). bool b = jscpp->load(file_path);
		将json格式数据，加载到jscpp的jtree中，b返回函数操作结果是否成功。
	
	object io:
		1).jscpp->set(jtype, key1, key2, key3, ..., ":", jvalue);
		这是个变参方法，无返回，设置指定的字段数据。jtype是jvalue的类型，jvalue是要设置的值。
			
		2).JNode *n = jscpp->at(key1, key2, key3, ...);
		这是个变参方法，返回的是JNode类型，这里面包含了对应字段的数据类型、关键词、数据。
			
		3).bool b = jscpp->isAt(key1, key2, key3, ...);
		这是个变参方法，返回bool，用来检测指定的数据是否存在。
		
	other :
		1).string s = jscpp->travel();
		遍历内容，并将内容保存于s中。
		
note：
	1).对于stirng型的value参数，一定要用string("xxxx");，若直接用"xxxx"会被编译器匹配为bool类型，以致报错。
	2).对于double型的value参数，要用加小数点，否则会被翻译为int型。