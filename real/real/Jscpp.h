#ifndef __Jscpp_H
#define __Jscpp_H

#include <vector>
#include <list>
#include <deque>
#include <string>
#include <assert.h>

/* function */
std::list<std::string> JPath(char* s1, ...);
char * JIndex(int index);

namespace jc
{
	class JNode;

	/* enum unit */
	enum JType
	{
		JINT,			//json int
		JDOUBLE,		//json double
		JSTRING,		//json string
		JBOOL,			//json boolean
		JOBJECT,		//json object
		JNULL			//json null
	};

	/* union unit */
	union JData
	{
		int *pInt;
		double *pDouble;
		std::string *pString;
		bool *pBool;
		std::vector<JNode *> *pKeyValue;
	};

	///* class unit */
	class JVal
	{
		/* ctor and de-ctor */
	public:
		~JVal();
		JVal():mType(JNULL){}
		JVal(const JVal &_value){ SetData(_value); }
		JVal(const int &_data) { SetData(_data); }
		JVal(const double &_data) { SetData(_data); }
		JVal(const std::string &_data) { SetData(_data); }
		JVal(const bool &_data) { SetData(_data); }
		JVal(const std::vector<JNode *> &_data) { SetData(_data); }

		/* interface */
	public:
		JVal& operator=(const JVal &_value){ SetData(_value); return *this; }

		const JType& GetType() const { return mType; }
		const JData& GetData() const { return mData; }

		void SetData(const JVal &val);						//保证相同的独立的JVal值.
		void SetData(const int &val);						//保证相同的独立的int值.
		void SetData(const double &val);					//保证相同的独立的double值.
		void SetData(const std::string &val);				//保证相同的独立的string值.
		void SetData(const bool &val);						//保证相同的独立的bool值.
		void SetData(const std::vector<JNode *> &val);		//保证相同的独立的vector中的指针值.

	private:
		JType mType;
		JData mData;
	};
	
	class JNode
	{
		/* ctor and de-ctor*/
	public:
		JNode(const std::string &_key):mKey(_key){ }
		JNode(const std::string &_key, const JVal &_value) : mKey(_key){ SetValue(_value); }

		/* interface */
	public:
		/* IO */
		const std::string &GetKey() const{ return mKey; }
		const JVal& GetValue() const { return mVal; }

		void SetKey(std::string k){ mKey = k; }
		void SetValue(const JVal &val){ mVal.SetData(val); }
	
		void InitObject();
		void AddObject(const JNode* newObject);

		/* member fun */
	private:

		/* membber var */
	private:
		std::string mKey;
		JVal mVal;
	};

	class JTree
	{
		/* ctor and de-ctor */
	public:
		JTree() :root(NULL){}
		explicit JTree(std::string _root_key = "root");
		JTree(const JTree &jtree) = delete;

		~JTree()
		{
			_freeTree(root);
			root = NULL;
		}

		/* interface */
	public:
		JTree& operator=(const JTree& jtree) = delete;
		void set(std::list<std::string> path, const JVal &jval);
		const JVal &get(std::list<std::string> path) const;
		bool isAt(std::list<std::string> path) const;
		std::string travel(void) const ;
		
		/* member fun */
	private:
		void _set(JNode *cnode, std::list<std::string> path, const JVal &jval);
		const JVal &_get(JNode *cnode, std::list<std::string> path) const;
		bool _isAt(JNode *cnode, std::list<std::string> path) const;
		std::string _travel(JNode *cnode, int deep) const;

		void _freeTree(JNode *cn);

		/* member var */
	private:
		JNode *root;
	};

	class Jscpp
	{
		/* ctor and de-ctor */
	public:
		Jscpp() :jtree(NULL){}
		explicit Jscpp(std::string _root_key = "root");
		Jscpp(const Jscpp &jscpp) = delete;

		~Jscpp()
		{ 
			if (jtree)
			{
				delete jtree;
			}
			jtree = NULL;
		}

		/* interface */
	public:
		const Jscpp& operator=(const Jscpp &jscpp) = delete;

		/* file io */
		bool save(char * file_path);
		bool load(char *file_path);

		/* object io */
		void set(std::list<std::string> path, const JVal &jval);
		const JVal& get(std::list<std::string> path) const;
		bool isAt(std::list<std::string> path) const;

		/* other */
		std::string travel(void) const;
		/* member fun */

		/* member var */
	private :
		JTree* jtree;			//json tree
	};
};

#endif