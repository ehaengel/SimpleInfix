#include "infix_function_manager.h"

InfixFunctionManager::InfixFunctionManager()
{
	function_instance_list.clear();
	logfile_manager = NULL;

}

InfixFunctionManager::~InfixFunctionManager()
{
	for(size_t i=0; i<function_instance_list.size(); i++)
	{
		InfixFunctionNode* function_node = function_instance_list[i];

		if(function_node != NULL)
			delete function_node;
	}
	function_instance_list.clear();
}

/////////////////////
// Data management //
/////////////////////

// Set InfixFunctionManager data
int InfixFunctionManager::AppendFunctionInstance(InfixFunctionNode* function_instance)
{
	function_instance_list.push_back(function_instance);

	return true;
}

int InfixFunctionManager::SetLogFileManager(LogFileManager* logfile_manager)
{
	this->logfile_manager = logfile_manager;

	return true;
}

// Get InfixFunctionManager data
size_t InfixFunctionManager::GetFunctionInstanceCount()
{
	return function_instance_list.size();
}

InfixFunctionNode* InfixFunctionManager::GetFunctionInstance(size_t index)
{
	if(index >= function_instance_list.size())
		return NULL;

	return function_instance_list[index];
}

////////////////////////////
// Infix parser functions //
////////////////////////////

int InfixFunctionManager::Initialize()
{
	if(LoadCommonFunctions() == false)
	{
		logfile_manager->WriteErrorMessage("InfixFunctionManager", "Could not load common functions");
		return false;
	}

	return true;
}

/////////////////////////
// Debugging functions //
/////////////////////////

int InfixFunctionManager::Print()
{
	for(size_t i=0; i<function_instance_list.size(); i++)
	{
		InfixFunctionNode* function_instance = function_instance_list[i];

		function_instance->Print();
		printf("\n");
	}

	return true;
}

////////////////////////////
// Internal use functions //
////////////////////////////

int InfixFunctionManager::LoadCommonFunctions()
{
	AppendFunctionInstance((InfixFunctionNode*) new InfixSine);
	AppendFunctionInstance((InfixFunctionNode*) new InfixCosine);

	for(size_t i=0; i<function_instance_list.size(); i++)
	{
		InfixFunctionNode* function_instance = function_instance_list[i];
		((InfixParserTreeNode*) function_instance)->SetLogFileManager(logfile_manager);
	}

	return true;
}
