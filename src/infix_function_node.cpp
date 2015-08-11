#include "infix_function_node.h"

InfixFunctionNode::InfixFunctionNode()
{
	node_type = InfixFunctionNode::FUNCTION_NODE;

	function_identifier_list.clear();
	input_value_list.clear();
}

InfixFunctionNode::~InfixFunctionNode()
{
	// Do nothing
}

/////////////////////
// Data management //
/////////////////////

// Set InfixFunctionNode data
int InfixFunctionNode::AppendFunctionIdentifier(string function_identifier)
{
	function_identifier_list.push_back(function_identifier);

	return true;
}

int InfixFunctionNode::SetInputCount(size_t input_count)
{
	input_value_list.clear();
	input_value_list.resize(input_count, 0.00);

	return true;
}

// Get InfixFunctionNode data
size_t InfixFunctionNode::GetFunctionIdentifierCount()
{
	return function_identifier_list.size();
}

string InfixFunctionNode::GetFunctionIdentifier(size_t index)
{
	if(index <= function_identifier_list.size())
		return function_identifier_list[index];

	return "";
}

size_t InfixFunctionNode::GetInputCount()
{
	return input_value_list.size();
}

complex<double> InfixFunctionNode::GetInputValue(size_t index)
{
	if(index >= input_value_list.size())
		return 0.00;

	return input_value_list[index];
}

////////////////////////////
// Infix parser functions //
////////////////////////////

complex<double> InfixFunctionNode::Evaluate()
{
	if(CollectInputValuesFromChildNodes() == false)
	{
		logfile_manager->WriteErrorMessage("InfixFunctionNode", "Could not evaluate child nodes");
		return 0.00;
	}

	return 0.00;
}

InfixFunctionNode* InfixFunctionNode::CreateNewInstance()
{
	return (new InfixFunctionNode);
}

/////////////////////////
// Debugging functions //
/////////////////////////

int InfixFunctionNode::Print()
{
	for(size_t i=0; i<function_identifier_list.size(); i++)
		printf("%s\n", function_identifier_list[i].c_str());

	return true;
}

////////////////////////////
// Internal use functions //
////////////////////////////

int InfixFunctionNode::CollectInputValuesFromChildNodes()
{
	for(size_t i=0; i<child_node_list.size() && i<input_value_list.size(); i++)
	{
		InfixParserTreeNode* child_node = child_node_list[i];
		input_value_list[i] = child_node->Evaluate();
	}

	return true;
}
