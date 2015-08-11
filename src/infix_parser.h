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
#include "infix_parser_tree.h"

#include "infix_symbol_manager.h"
#include "infix_function_manager.h"

#ifndef SIMPLE_INFIX_PARSER_H
#define SIMPLE_INFIX_PARSER_H

class InfixParser
{
public:
	InfixParser();
	~InfixParser();

	/////////////////////
	// Data management //
	/////////////////////

	// Set InfixParser data
	int SetExpression(string expression);
	int SetLogFileManager(LogFileManager* logfile_manager);

	// Get InfixParser data
	InfixSymbolManager* GetSymbolManager();

	////////////////////////////
	// Infix parser functions //
	////////////////////////////

	//Call initialize when InfixParser is created
	int Initialize();

	//Call this to parse and evaluate the infix expression
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

	//Memory management
	int FreeData();
	int FreeParserData();

	///////////////////////
	// Internal use data //
	///////////////////////

	string expression;

	InfixParserTree* infix_parser_tree;

	InfixSymbolManager* infix_symbol_manager;
	InfixFunctionManager* infix_function_manager;

	LogFileManager* logfile_manager;
};

#endif
