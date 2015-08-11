#include "infix_parser.h"

InfixParser::InfixParser()
{
	expression = "";

	infix_parser_tree = NULL;

	infix_symbol_manager = NULL;
	infix_function_manager = NULL;

	logfile_manager = NULL;
}

InfixParser::~InfixParser()
{
	FreeData();
}

/////////////////////
// Data management //
/////////////////////

// Set InfixParser data
int InfixParser::SetExpression(string expression)
{
	if(FreeParserData() == false)
	{
		logfile_manager->WriteErrorMessage("InfixParser", "Could not free parser data");
		return 0.00;
	}

	this->expression = expression;

	if(Initialize() == false)
	{
		logfile_manager->WriteErrorMessage("InfixParser", "Could not Initialize during SetExpression");
		return false;
	}

	return true;
}

int InfixParser::SetLogFileManager(LogFileManager* logfile_manager)
{
	this->logfile_manager = logfile_manager;

	return true;
}

// Get InfixParser data
InfixSymbolManager* InfixParser::GetSymbolManager()
{
	return infix_symbol_manager;
}

////////////////////////////
// Infix parser functions //
////////////////////////////

int InfixParser::Initialize()
{
	//Initialize symbol manager
	if(infix_symbol_manager == NULL)
	{
		infix_symbol_manager = new InfixSymbolManager;
		infix_symbol_manager->SetLogFileManager(logfile_manager);

		if(infix_symbol_manager->Initialize() == false)
		{
			logfile_manager->WriteErrorMessage("InfixParser", "Could not initialize infix symbol manager");
			return false;
		}
	}

	//Initialize function manager
	if(infix_function_manager == NULL)
	{
		infix_function_manager = new InfixFunctionManager;
		infix_function_manager->SetLogFileManager(logfile_manager);

		if(infix_function_manager->Initialize() == false)
		{
			logfile_manager->WriteErrorMessage("InfixParser", "Could not initialize infix function manager");
			return false;
		}
	}

	//Initialize infix parser tree and run parser
	if(infix_parser_tree == NULL)
	{
		infix_parser_tree = new InfixParserTree;

		infix_parser_tree->SetLogFileManager(logfile_manager);
		infix_parser_tree->SetInfixFunctionManager(infix_function_manager);
		infix_parser_tree->SetInfixSymbolManager(infix_symbol_manager);

		infix_parser_tree->SetExpression(expression);

		/*if(infix_parser_tree->RunParser() == false)
		{
			logfile_manager->WriteErrorMessage("InfixParser", "Could not run parser");
			return false;
		}*/
	}

	return true;
}

complex<double> InfixParser::Evaluate()
{
	if(infix_parser_tree->RunParser() == false)
	{
		logfile_manager->WriteErrorMessage("InfixParser", "Could not run parser");
		return 0.00;
	}

	return infix_parser_tree->Evaluate();
}

/////////////////////////
// Debugging functions //
/////////////////////////

int InfixParser::Print()
{

	return true;
}

int InfixParser::WriteDOTFile(string filename)
{
	if(infix_parser_tree->WriteDOTFile(filename) == false)
		return false;

	return true;
}

////////////////////////////
// Internal use functions //
////////////////////////////

//Initialization and Memory management
int InfixParser::FreeData()
{
	if(infix_parser_tree != NULL)
	{
		delete infix_parser_tree;
		infix_parser_tree = NULL;
	}

	if(infix_symbol_manager != NULL)
	{
		delete infix_symbol_manager;
		infix_symbol_manager = NULL;
	}

	if(infix_function_manager != NULL)
	{
		delete infix_function_manager;
		infix_function_manager = NULL;
	}

	return true;
}

int InfixParser::FreeParserData()
{
	if(infix_parser_tree != NULL)
	{
		delete infix_parser_tree;
		infix_parser_tree = NULL;
	}

	return true;
}
