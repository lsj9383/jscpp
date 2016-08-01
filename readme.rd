json load and save in c++.
There is some interface for user:
	function :
		1).list<string> JPath(key1, key2, ... ":");
		以":"结尾的变参函数。将变参函数所描绘的路径，转换为list<string>
			
	Jscpp class :
		ctor:
			Jscapp jscpp = new Jscpp("root_key");
			初始化jscpp，顶层关键词为"root_key"，虽然逻辑上存在，但是其实它是隐藏起的只是个占位符，任何函数都不会依赖于该关键词。
				
		file io:
			1).bool b = jscpp->save(file_path);
			将jscpp的数据按json格式进行保存, b返回函数操作结果是否成功。
				
			2). bool b = jscpp->load(file_path);
			将json格式数据，加载到jscpp的jtree中，b返回函数操作结果是否成功。
		
		object io:
			1).jscpp->set(list<string> jpath, JVal jvalue);
			无返回。jvalue支持隐式转换。
				
			2).JVal n = jscpp->get(list<string> jpath);
			返回的是JVal类型，这里面包含了对应字段的数据类型与数据。
				
			3).bool b = jscpp->isAt(list<string> jpath);
			返回bool，用来检测指定的数据是否存在。
			
		other :
			1).string s = jscpp->travel();
			遍历内容，并将内容保存于s中。
		
note：
	1).对于stirng型的value参数，一定要用string("xxxx");，若直接用"xxxx"会被编译器匹配为bool类型，以致报错。
	2).对于double型的value参数，要用加小数点，否则会被翻译为int型。