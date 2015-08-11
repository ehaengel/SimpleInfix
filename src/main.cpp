#include <stdlib.h>
#include <stdio.h>

#include <string>
using namespace std;

// Logfile manager
#include "logfile_manager/logfile_manager.h"

// Simple Infix Parser
#include "infix_parser.h"

int main(int argc, char** argv)
{
	//Initialize infix parser
	LogFileManager* logfile_manager = new LogFileManager;
	logfile_manager->VerboseModeOn();

	InfixParser* infix_parser = new InfixParser;
	infix_parser->SetLogFileManager(logfile_manager);

	if(infix_parser->Initialize() == false)
	{
		logfile_manager->WriteErrorMessage("main", "Could not initialize infix parser");
		return 1;
	}

	//Run parser and respond to user input
	int done = false;
	char buffer[1000];
	while(!done)
	{
		fgets(buffer, 1000, stdin);

		if(strncmp(buffer, "help", 4) == 0)
		{
			printf("Command list:\n");
			printf("help -- print this help information\n");
			printf("graph -- print out a graph\n");
			printf("symbol -- print out symbol table\n");
			printf("set A B C -- set symbol A to have value B + iC\n");
			printf("quit -- quit this program\n");
			printf("All other inputs are interpretted as infix and will be parsed\n");
		}

		else if(strncmp(buffer, "graph", 5) == 0)
		{
			infix_parser->WriteDOTFile("data/output_graph.dot");
			printf("Wrote graphviz data to data/output_graph.dot\n");
		}

		else if(strncmp(buffer, "quit", 4) == 0)
			done = true;

		else if(strncmp(buffer, "symbol", 5) == 0)
		{
			InfixSymbolManager* infix_symbol_manager = infix_parser->GetSymbolManager();
			infix_symbol_manager->Print();
		}

		else if(strncmp(buffer, "set", 3) == 0)
		{
			char buffer2[1000];
			double real_part = 0.00;
			double imag_part = 0.00;

			sscanf(buffer, "set %s %lf %lf", buffer2, &real_part, &imag_part);

			InfixSymbolManager* infix_symbol_manager = infix_parser->GetSymbolManager();
			infix_symbol_manager->SetSymbolValue(buffer2, complex<double>(real_part, imag_part));
		}

		else
		{
			infix_parser->SetExpression(buffer);
			complex<double> result = infix_parser->Evaluate();

			printf("Result = %s\n", complex_to_str(result).c_str());
		}
	}

	delete infix_parser;
	return 0;
}
