#ifndef __Jscpp_H
#define __Jscpp_H

#include <vector>
#include <string>

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
		JNode(std::string _key, const int &_value) : mKey(_key){ SetValue(_value); }
		JNode(std::string _key, const double &_value) : mKey(_key){ SetValue(_value); }
		JNode(std::string _key, const std::string &_value) : mKey(_key){ SetValue(_value); }
		JNode(std::string _key, const bool &_value) : mKey(_key){ SetValue(_value); }
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
		
		/* member fun */

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
		virtual ~JTree(){}

		/* interface */
	public:

		/* member fun */
	private:

		/* member var */
	private:
		JNode *root;
	};

	class Jscpp
	{
		/* ctor and de-ctor */
	public:
		Jscpp() :jtree(NULL){}
		virtual ~Jscpp(){}

		/* interface */

		/* member fun */

		/* member var */
	private :
		JTree* jtree;			//json tree
	};
};

#endif