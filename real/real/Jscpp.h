#ifndef __Jscpp_H
#define __Jscpp_H

#include <vector>
#include <list>
#include <deque>
#include <string>
#include <assert.h>

/* function */
std::list<std::string> JPath(char* s1, ...);

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
		JARRAY,			//json array
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
		JType GetType(){ return mType; }
		JData GetData(){ return mData; }

		void SetData(const JVal &val);
		void SetData(const int &val);
		void SetData(const double &val);
		void SetData(const std::string &val);
		void SetData(const bool &val);
		void SetData(const std::vector<JNode *> &val);

	private:
		JType mType;
		JData mData;
	};
	
	class JNode
	{
		/* ctor and de-ctor*/
	public:
		JNode(){ }
		JNode(std::string _key):mKey(_key){ }
		JNode(std::string _key, const JVal &_value) : mKey(_key){ SetValue(_value); }
		~JNode(){ }

		/* interface */
	public:
		/* IO */
		std::string GetKey(){ return mKey; }
		JVal GetValue(){ return mVal; }

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
		JTree(std::string _root_key = "root");
		~JTree()
		{
			_freeTree(root);
			root = NULL;
		}

		/* interface */
	public:
		void set(std::list<std::string> path, JVal jval);
		JVal get(std::list<std::string> path);

		std::string travel(void);

		/* member fun */
	private:
		void _set(JNode *cnode, std::list<std::string> path, JVal jval);
		JVal _get(JNode *cnode, std::list<std::string> path);

		std::string _travel(JNode *cnode, int deep);
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
		Jscpp(std::string _root_key = "root");
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
		/* file io */
		bool save(char * file_path);

		/* object io */
		void set(std::list<std::string> path, JVal jval);
		JVal get(std::list<std::string> path);

		/* other */
		std::string travel(void);
		/* member fun */

		/* member var */
	private :
		JTree* jtree;			//json tree
	};
};

#endif