#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <string>
#include <vector>
#include <complex>
using namespace std;

// Simple Infix library
#include "infix_parser_tree_node.h"

#ifndef INFIX_FUNCTION_NODE_H
#define INFIX_FUNCTION_NODE_H

class InfixFunctionNode : InfixParserTreeNode
{
public:
	InfixFunctionNode();
	~InfixFunctionNode();

	/////////////////////
	// Data management //
	/////////////////////

	// Set InfixFunctionNode data
	int AppendFunctionIdentifier(string function_identifier);
	int SetInputCount(size_t input_count);

	// Get InfixFunctionNode data
	size_t GetFunctionIdentifierCount();
	string GetFunctionIdentifier(size_t index);

	size_t GetInputCount();
	complex<double> GetInputValue(size_t index);

	////////////////////////////
	// Infix parser functions //
	////////////////////////////

	virtual complex<double> Evaluate();
	virtual InfixFunctionNode* CreateNewInstance();

	/////////////////////////
	// Debugging functions //
	/////////////////////////

	virtual int Print();

protected:
	////////////////////////////
	// Internal use functions //
	////////////////////////////

	int CollectInputValuesFromChildNodes();

	///////////////////////
	// Internal use data //
	///////////////////////

	vector<string> function_identifier_list;
	vector< complex<double> > input_value_list;
};

typedef vector<InfixFunctionNode*> InfixFunctionNodeList;

#endif
