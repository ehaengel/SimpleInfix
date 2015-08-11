#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <string>
#include <vector>
#include <complex>
using namespace std;

// Simple Infix library
#include "infix_parser_utility.h"
#include "infix_function_node.h"

#ifndef INFIX_COMMON_FUNCTIONS_H
#define INFIX_COMMON_FUNCTIONS_H

class InfixSine : InfixFunctionNode
{
public:
	InfixSine();
	~InfixSine();

	complex<double> Evaluate();
	InfixFunctionNode* CreateNewInstance();
};

class InfixCosine : InfixFunctionNode
{
public:
	InfixCosine();
	~InfixCosine();

	complex<double> Evaluate();
	InfixFunctionNode* CreateNewInstance();
};

#endif


