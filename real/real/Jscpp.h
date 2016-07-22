#ifndef __Jscpp_H
#define __Jscpp_H

#include <vector>
#include <list>
#include <deque>
#include <string>
#include <assert.h>

namespace jp
{
	class JNode;
	enum JValueType
	{
		JINT,			//json int
		JDOUBLE,		//json double
		JSTRING,		//json string
		JBOOL,			//json boolean
		JOBJECT,		//json object
		JARRAY,			//json array
		JNULL			//json null
	};

	union UVal
	{
		int *pInt;
		double *pDouble;
		std::string *pString;
		bool *pBool;
		std::vector<JNode *> *pKeyValue;
		std::vector<UVal> *pArray;
	};

	class JNode
	{
		/* ctor and de-ctor*/
	public:
		JNode(){ mType = JNULL; }
		JNode(std::string _key):mKey(_key){ mType = JNULL; }
		JNode(std::string _key, const int &_value) : mKey(_key){ SetValue(_value); }
		JNode(std::string _key, const double &_value) : mKey(_key){ SetValue(_value); }
		JNode(std::string _key, const std::string &_value) : mKey(_key){ SetValue(_value); }
		JNode(std::string _key, const bool &_value) : mKey(_key){ SetValue(_value); }
		JNode(std::string _key, const std::vector<JNode *> &_value) : mKey(_key){ SetValue(_value); }
		virtual ~JNode();

		/* interface */
	public:
		/* IO */
		std::string GetKey(){ return mKey; }
		UVal GetValue(){ return mValue; }			//用户根据
		JValueType GetType(){ return mType; }

		void SetKey(std::string k){ mKey = k; }
		void SetValue(const int &val);
		void SetValue(const double &val);
		void SetValue(const std::string &val);
		void SetValue(const bool &val);
		void SetValue(const std::vector<JNode *> &val);
	
		void AddObject(const JNode* newObject);

		/* member fun */
	private:

		/* membber var */
	private:
		std::string mKey;
		UVal mValue;
		JValueType mType;
	};

	class JTree
	{
		/* ctor and de-ctor */
	public:
		JTree() :root(NULL){}
		JTree(std::string _root_key = "root");
		virtual ~JTree(){}

		/* interface */
	public:
		void set(int value, std::deque<std::string> path);
		std::string travel(void);

		/* member fun */
	private:
		void _set(JNode *cnode, int value, std::deque<std::string> path);
		std::string _travel(JNode *cnode, int deep);

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
		virtual ~Jscpp(){}

		/* interface */
	public:
		/* file io */
		bool save(char * file_path);

		/* object io */
		void set(int value, ...);

		/* other */
		std::string travel(void);
		/* member fun */

		/* member var */
	private :
		JTree* jtree;			//json tree
	};
};

#endif