#include "infix_symbol_manager.h"

InfixSymbolManager::InfixSymbolManager()
{
	infix_symbol_list.clear();

	logfile_manager = NULL;
}

InfixSymbolManager::~InfixSymbolManager()
{
	for(size_t i=0; i<infix_symbol_list.size(); i++)
	{
		InfixSymbol* infix_symbol = infix_symbol_list[i];

		if(infix_symbol != NULL)
			delete infix_symbol;
	}
	infix_symbol_list.clear();
}

/////////////////////
// Data management //
/////////////////////

// Set InfixSymbolManager data
int InfixSymbolManager::SetLogFileManager(LogFileManager* logfile_manager)
{
	this->logfile_manager = logfile_manager;

	return true;
}

// Get InfixSymbolManager data

////////////////////////////
// Infix parser functions //
////////////////////////////

int InfixSymbolManager::Initialize()
{
	CreateNewSymbol("i", complex<double>(0.00, 1.00));
	CreateNewSymbol("j", complex<double>(0.00, 1.00));
	CreateNewSymbol("pi", M_PI);
	CreateNewSymbol("e", M_E);

	return true;
}

int InfixSymbolManager::CreateNewSymbol(string expression, complex<double> value)
{
	InfixSymbol* new_infix_symbol = new InfixSymbol;

	new_infix_symbol->SetLogFileManager(logfile_manager);

	new_infix_symbol->SetExpression(expression);
	new_infix_symbol->SetValue(value);

	infix_symbol_list.push_back(new_infix_symbol);

	return true;
}

InfixSymbol* InfixSymbolManager::FindSymbol(string expression)
{
	for(size_t i=0; i<infix_symbol_list.size(); i++)
	{
		InfixSymbol* infix_symbol = infix_symbol_list[i];

		if(infix_symbol->GetExpression() == expression)
			return infix_symbol;
	}

	return NULL;
}

int InfixSymbolManager::SetSymbolValue(string expression, complex<double> value)
{
	InfixSymbol* infix_symbol = FindSymbol(expression);
	if(infix_symbol == NULL)
	{
		if(CreateNewSymbol(expression, value) == false)
			return false;
	}
	else
		infix_symbol->SetValue(value);

	return true;
}

/////////////////////////
// Debugging functions //
/////////////////////////

int InfixSymbolManager::Print()
{
	printf("Symbol list:\n");
	for(size_t i=0; i<infix_symbol_list.size(); i++)
		infix_symbol_list[i]->Print();

	return true;
}
