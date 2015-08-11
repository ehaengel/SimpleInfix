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

#ifndef INFIX_SYMBOL_H
#define INFIX_SYMBOL_H

class InfixSymbol
{
public:
	InfixSymbol();
	~InfixSymbol();

	/////////////////////
	// Data management //
	/////////////////////

	// Set InfixSymbol data
	int SetExpression(string expression);
	int SetValue(complex<double> value);

	int SetLogFileManager(LogFileManager* logfile_manager);

	// Get InfixSymbol data
	string GetExpression();
	complex<double> GetValue();

	////////////////////////////
	// Infix parser functions //
	////////////////////////////

	/////////////////////////
	// Debugging functions //
	/////////////////////////

	int Print();

private:
	///////////////////////
	// Internal use data //
	///////////////////////

	string expression;
	complex<double> value;

	LogFileManager* logfile_manager;
};

typedef vector<InfixSymbol*> InfixSymbolList;

#endif
