#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <string>
#include <vector>
#include <complex>
using namespace std;

// Simple Infix library
#include "infix_parser_tree_node.h"

#ifndef INFIX_OPERATOR_NODE_H
#define INFIX_OPERATOR_NODE_H

class InfixOperatorNode : InfixParserTreeNode
{
public:
	InfixOperatorNode();
	~InfixOperatorNode();

	/////////////////////
	// Data management //
	/////////////////////

	// Set InfixOperatorNode data
	int SetOperatorType(int operator_type);

	// Get InfixOperatorNode data
	int GetOperatorType();

	//Operator type
	enum
	{
		NO_OPERATION = 0,
		ADDITION_OPERATOR = 1,
		SUBTRACTION_OPERATOR = 2,
		MULTIPLICATION_OPERATOR = 3,
		DIVISION_OPERATOR = 4,
		POWER_OPERATOR = 5,
		PARENTHESIS_OPERATOR = 6
	};

	////////////////////////////
	// Infix parser functions //
	////////////////////////////

	complex<double> Evaluate();

	/////////////////////////
	// Debugging functions //
	/////////////////////////

	int Print();

private:
	///////////////////////
	// Internal use data //
	///////////////////////

	int operator_type;
};

#endif

