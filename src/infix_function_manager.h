#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <string>
#include <vector>
#include <complex>
using namespace std;

// Logfile manager
#include "logfile_manager/logfile_manager.h"

// Simple Infix library
#include "infix_parser_tree_node.h"

#include "infix_function_node.h"
#include "infix_common_functions.h"

#ifndef INFIX_FUNCTION_MANAGER_H
#define INFIX_FUNCTION_MANAGER_H

class InfixFunctionManager
{
public:
	InfixFunctionManager();
	~InfixFunctionManager();

	/////////////////////
	// Data management //
	/////////////////////

	// Set InfixFunctionManager data
	int AppendFunctionInstance(InfixFunctionNode* function_instance);

	int SetLogFileManager(LogFileManager* logfile_manager);

	// Get InfixFunctionManager data
	size_t GetFunctionInstanceCount();
	InfixFunctionNode* GetFunctionInstance(size_t index);

	////////////////////////////
	// Infix parser functions //
	////////////////////////////

	int Initialize();

	/////////////////////////
	// Debugging functions //
	/////////////////////////

	int Print();

private:
	////////////////////////////
	// Internal use functions //
	////////////////////////////

	int LoadCommonFunctions();

	///////////////////////
	// Internal use data //
	///////////////////////

	InfixFunctionNodeList function_instance_list;
	LogFileManager* logfile_manager;
};

#endif
