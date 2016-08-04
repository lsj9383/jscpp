# Jscpp —— json的c++实现
![](https://github.com/lsj9383/jscpp/blob/master/icon/jscpp.jpg?raw=true)
<p align="center">
	<img src="https://github.com/lsj9383/jscpp/blob/master/icon/json.jpg?raw=true" alt="JSON"/>
</p>
`Jscpp`是一个c++类，Jscpp对象中以`树形结构`保存了json数据，并提供了一系列方法以进行对json数据的操作。这些操作包括:<br>
* 读取json文件中的数据到Jscpp对象
* 将Jscpp对象中的数据写入json文件
* Jscpp对象的json数据的写入/读取

## 文件结构
当前git根路径下的文件作用:<br>
* /include/, Jscpp头文件。
* /src/, Jscpp源文件。
* /lib/, Jscpp静态库。
* /Jscpp/, visual studio2013编译Jscpp静态库的工程。
* /demo/, visual studio2013使用Jscpp的示例。<br>

## 编程说明
### 公共函数:
```cpp
/***************************************************************************************
functioin 	: JPath
param		: (key1, key2, ... ":") 参数不定,以冒号结尾,key1等需要时string类型
return 		: list<string>
description	: 将key1, key2, ...写入链表list<string>
*****************************************************************************************/
list<string> JPath(key1, key2, ... ":");
```

### 类
#### 1.JVal
Json Value, 是Jscpp直接使用的数据<br>
JVal对象支持直接赋值，是深拷贝。
```cpp
class JVal
{
	/* ctor and de-ctor */
public:
	JVal(const JVal &_value);
	JVal(const int &_data);
	JVal(const double &_data);
	JVal(const std::string &_data);
	JVal(const bool &_data);
	~JVal();
	
	/* interface */
public:
	JVal& operator=(const JVal &_value);

	const JType& GetType();
	const JData& GetData();

	void SetData(const JVal &val);							//保证相同的独立的JVal值.
	void SetData(const int &val);							//保证相同的独立的double值.
	void SetData(const double &val);						//保证相同的独立的double值.
	void SetData(const std::string &val);					//保证相同的独立的string值.
	void SetData(const bool &val);							//保证相同的独立的bool值.
	
	...
};
```
#### 2.Jscpp
不支持隐式转换，也不支持Jscpp之间的赋值。
```cpp
class Jscpp
{
	/* ctor and de-ctor */
public:
	explicit Jscpp(std::string _root_key = "root");
	~Jscpp();
	
	/* interface */
public:
	bool save(char * file_path);
	bool load(char *file_path);
	void set(std::list<std::string> path, const JVal &jval);
	const JVal& get(std::list<std::string> path) const;
	bool isAt(std::list<std::string> path) const;
	std::string travel(void) const;
	
	...
};
```
=
具体说明:
```cpp
/***************************************************************************************
functioin 	: Jscpp(构造函数)
param		: rootkey 根关键词
return 		: Jscpp对象.
description	: 创建根关键字为rootkey的jscpp对象.
*****************************************************************************************/
Jscapp jscpp = new Jscpp(string rootkey);

/***************************************************************************************
interface 	: save
param		: file_path 文件路径
return 		: 操作是否成功
description	: 将当前jscpp对象中的数据以json数据的格式，保存到指定文件中
*****************************************************************************************/
bool b = jscpp->save(string file_path);

/***************************************************************************************
interface 	: load
param		: file_path 文件路径
return 		: 操作是否成功
description	: 将指定路径的json文件中的数据，导入jscpp对象
*****************************************************************************************/
bool b = jscpp->load(string file_path);

/***************************************************************************************
interface 	: set
param		: jpath json数据的路径, jvalue 待写入的数据(支持强制转换)
return 		: void
description	: 将jpath的值设为jvalue, 若jpath不存在，则生成该jpath
*****************************************************************************************/
void jscpp->set(list<string> jpath, JVal jvalue);

/***************************************************************************************
interface 	: get
param		: jpath json数据的路径
return 		: jval 读取出的值
description	: 将jpath中的jval读取出来。
*****************************************************************************************/
JVal jval = jscpp->get(list<sring> jpath);

/***************************************************************************************
interface 	: isAt
param		: jpath json数据的路径格式
return 		: 是否存在
description	: 判断jpath是否存在
*****************************************************************************************/
bool b = jscpp->isAt(list<string> jpath);

/***************************************************************************************
interface 	: travel
param		: no
return 		: string 
description	: 遍历Jscpp对象内部的json数据，并以json文件格式的方式放回.
*****************************************************************************************/
string s = jscpp->travel();
```

		
note：<br>
	1).对于stirng型的value参数，一定要用string("xxxx");，若直接用"xxxx"会被编译器匹配为bool类型，以致报错。<br>
	2).对于double型的value参数，要用加小数点，否则会被翻译为int型。<br>
	
