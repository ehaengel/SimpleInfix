#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <string>
#include <vector>
#include <complex>
using namespace std;

// Log File Manager library
#include "logfile_manager/logfile_manager.h"

// Simple Infix library
#include "infix_parser_utility.h"

#include "infix_parser_tree_node.h"
#include "infix_operator_node.h"

#include "infix_function_node.h"
#include "infix_function_manager.h"

#include "infix_symbol_manager.h"

#ifndef INFIX_PARSER_TREE_H
#define INFIX_PARSER_TREE_H

class InfixParserTree;
typedef int (InfixParserTree::*InfixParseRoutine)(InfixParserTreeNode*, int&);

class InfixParserTree
{
public:
	InfixParserTree();
	~InfixParserTree();

	/////////////////////
	// Data management //
	/////////////////////

	// Set InfixParserTree data
	int SetExpression(string expression);

	int SetInfixFunctionManager(InfixFunctionManager* function_manager);
	int SetInfixSymbolManager(InfixSymbolManager* symbol_manager);

	int SetLogFileManager(LogFileManager* logfile_manager);

	// Get InfixParserTree data
	size_t GetTreeNodeCount();
	InfixParserTreeNode* GetTreeNode(size_t index);

	////////////////////////////
	// Infix parser functions //
	////////////////////////////

	int RunParser();

	complex<double> Evaluate();

	/////////////////////////
	// Debugging functions //
	/////////////////////////

	int Print();
	int WriteDOTFile(string filename);

private:
	////////////////////////////
	// Internal use functions //
	////////////////////////////

	int InitializeParser();

	int ParseUntilDone(int& found_parseable_expression, InfixParseRoutine parse_routine);

	int ParsePlusMinus(InfixParserTreeNode* tree_node, int& expression_parseable);
	int ParseTimesDivide(InfixParserTreeNode* tree_node, int& expression_parseable);
	int ParsePower(InfixParserTreeNode* tree_node, int& expression_parseable);
	int ParseParenthesis(InfixParserTreeNode* tree_node, int& expression_parseable);
	int ParseFunction(InfixParserTreeNode* tree_node, int& expression_parseable);

	InfixParserTreeNode* CreateNewNode(int node_type, string node_expr);

	int UpdateSymbolValues();

	///////////////////////
	// Internal use data //
	///////////////////////

	string expression;
	InfixParserTreeNodeList tree_node_list;

	InfixFunctionManager* function_manager;
	InfixSymbolManager* symbol_manager;

	LogFileManager* logfile_manager;
};

#endif

