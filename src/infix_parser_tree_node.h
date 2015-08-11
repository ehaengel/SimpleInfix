#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <string>
#include <vector>
#include <complex>
using namespace std;

// Logfile manager library
#include "logfile_manager/logfile_manager.h"

// Infix parser library
#include "infix_parser_utility.h"

#include "infix_symbol.h"
#include "infix_symbol_manager.h"

#ifndef INFIX_PARSER_TREE_NODE_H
#define INFIX_PARSER_TREE_NODE_H

class InfixParserTreeNode;
typedef vector<InfixParserTreeNode*> InfixParserTreeNodeList;

class InfixParserTreeNode
{
public:
	InfixParserTreeNode();
	virtual ~InfixParserTreeNode();

	/////////////////////
	// Data management //
	/////////////////////

	// Set InfixParserTreeNode data
	int SetExpression(string expression);
	int SetNodeValue(complex<double> node_value);

	int SetChildNode(size_t index, InfixParserTreeNode* child_node);
	int AppendChildNode(InfixParserTreeNode* child_node);

	int SetParentNode(InfixParserTreeNode* parent_node, size_t parent_child_index);

	int SetLogFileManager(LogFileManager* logfile_manager);

	// Get InfixParserTreeNode data
	string GetExpression();
	int GetNodeType();

	size_t GetChildCount();
	InfixParserTreeNode* GetChild(size_t index);

	InfixParserTreeNode* GetParentNode();
	size_t GetParentChildIndex();

	enum
	{
		IRREDUCIBLE_NODE = 0,
		OPERATOR_NODE = 1,
		FUNCTION_NODE = 2
	};

	////////////////////////////
	// Infix parser functions //
	////////////////////////////

	virtual complex<double> Evaluate();

	int TestIsNumeric();

	/////////////////////////
	// Debugging functions //
	/////////////////////////

	virtual int Print();

protected:
	////////////////////////////
	// Internal use functions //
	////////////////////////////

	int CleanExpression();

	///////////////////////
	// Internal use data //
	///////////////////////

	string expression;

	int node_type;
	complex<double> node_value;

	size_t parent_child_index;
	InfixParserTreeNode* parent_node;

	InfixParserTreeNodeList child_node_list;

	LogFileManager* logfile_manager;
};

#endif
