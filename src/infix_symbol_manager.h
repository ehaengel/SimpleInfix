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
#include "infix_parser_utility.h"
#include "infix_symbol.h"

#ifndef INFIX_SYMBOL_MANAGER_H
#define INFIX_SYMBOL_MANAGER_H


class InfixSymbolManager
{
public:
	InfixSymbolManager();
	~InfixSymbolManager();

	/////////////////////
	// Data management //
	/////////////////////

	// Set InfixSymbolManager data
	int SetLogFileManager(LogFileManager* logfile_manager);

	// Get InfixSymbolManager data

	////////////////////////////
	// Infix parser functions //
	////////////////////////////

	int Initialize();

	int CreateNewSymbol(string expression, complex<double> value);
	InfixSymbol* FindSymbol(string expression);

	int SetSymbolValue(string expression, complex<double> value);

	/////////////////////////
	// Debugging functions //
	/////////////////////////

	int Print();

private:
	///////////////////////
	// Internal use data //
	///////////////////////

	InfixSymbolList infix_symbol_list;

	LogFileManager* logfile_manager;
};

#endif
