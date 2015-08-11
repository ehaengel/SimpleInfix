#include "infix_symbol.h"

InfixSymbol::InfixSymbol()
{
	expression = "";
	value = 0.00;

	logfile_manager = NULL;
}

InfixSymbol::~InfixSymbol()
{
	//Do nothing
}

/////////////////////
// Data management //
/////////////////////

// Set InfixSymbol data
int InfixSymbol::SetExpression(string expression)
{
	this->expression = expression;

	return true;
}

int InfixSymbol::SetValue(complex<double> value)
{
	this->value = value;

	return true;
}

int InfixSymbol::SetLogFileManager(LogFileManager* logfile_manager)
{
	this->logfile_manager = logfile_manager;

	return true;
}

// Get InfixSymbol data
string InfixSymbol::GetExpression()
{
	return expression;
}

complex<double> InfixSymbol::GetValue()
{
	return value;
}

////////////////////////////
// Infix parser functions //
////////////////////////////

/////////////////////////
// Debugging functions //
/////////////////////////

int InfixSymbol::Print()
{
	printf("%s = %s\n", expression.c_str(), complex_to_str(value).c_str());

	return true;
}
