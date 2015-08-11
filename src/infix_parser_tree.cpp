#include "infix_parser_tree.h"

InfixParserTree::InfixParserTree()
{
	expression = "";
	tree_node_list.clear();

	function_manager = NULL;
	symbol_manager = NULL;

	logfile_manager = NULL;
}

InfixParserTree::~InfixParserTree()
{
	for(size_t i=0; i<tree_node_list.size(); i++)
	{
		InfixParserTreeNode* infix_parser_tree_node = tree_node_list[i];

		if(infix_parser_tree_node != NULL)
			delete infix_parser_tree_node;
	}
	tree_node_list.clear();
}

/////////////////////
// Data management //
/////////////////////

// Set InfixParserTree data
int InfixParserTree::SetExpression(string expression)
{
	this->expression = expression;

	return true;
}

int InfixParserTree::SetInfixFunctionManager(InfixFunctionManager* function_manager)
{
	this->function_manager = function_manager;

	return true;
}

int InfixParserTree::SetInfixSymbolManager(InfixSymbolManager* symbol_manager)
{
	this->symbol_manager = symbol_manager;

	return true;
}

int InfixParserTree::SetLogFileManager(LogFileManager* logfile_manager)
{
	this->logfile_manager = logfile_manager;

	return true;
}

// Get InfixParserTree data
size_t InfixParserTree::GetTreeNodeCount()
{
	return tree_node_list.size();
}

InfixParserTreeNode* InfixParserTree::GetTreeNode(size_t index)
{
	if(index >= tree_node_list.size())
		return NULL;

	return tree_node_list[index];
}

////////////////////////////
// Infix parser functions //
////////////////////////////

int InfixParserTree::RunParser()
{
	//Check if the parser has been run before
	if(tree_node_list.size() != 0)
		return true;

	if(InitializeParser() == false)
	{
		logfile_manager->WriteErrorMessage("InfixParserTree", "Could not initialize parser");
		return false;
	}

	int iteration_count = 0;
	int found_parseable_expression = true;

	while(found_parseable_expression && iteration_count < 1000)
	{
		found_parseable_expression = false;

		//Parse plus/minus
		if(ParseUntilDone(found_parseable_expression, &InfixParserTree::ParsePlusMinus) == false)
		{
			logfile_manager->WriteErrorMessage("InfixParserTree", "Could not do plus-minus parsing");
			return false;
		}

		//Parse times/divide
		if(ParseUntilDone(found_parseable_expression, &InfixParserTree::ParseTimesDivide) == false)
		{
			logfile_manager->WriteErrorMessage("InfixParserTree", "Could not do times-divide parsing");
			return false;
		}

		//Parse power
		if(ParseUntilDone(found_parseable_expression, &InfixParserTree::ParsePower) == false)
		{
			logfile_manager->WriteErrorMessage("InfixParserTree", "Could not do power parsing");
			return false;
		}

		//Parse parenthesis
		if(ParseUntilDone(found_parseable_expression, &InfixParserTree::ParseParenthesis) == false)
		{
			logfile_manager->WriteErrorMessage("InfixParserTree", "Could not do parenthesis parsing");
			return false;
		}

		//Parse functions
		if(ParseUntilDone(found_parseable_expression, &InfixParserTree::ParseFunction) == false)
		{
			logfile_manager->WriteErrorMessage("InfixParserTree", "Could not do function parsing");
			return false;
		}

		iteration_count++;
	}

	if(UpdateSymbolValues() == false)
	{
		logfile_manager->WriteErrorMessage("InfixParserTree", "Could not update symbol values");
		return false;
	}

	return true;
}

complex<double> InfixParserTree::Evaluate()
{
	return tree_node_list[0]->Evaluate();
}

/////////////////////////
// Debugging functions //
/////////////////////////

int InfixParserTree::Print()
{

	return true;
}

int InfixParserTree::WriteDOTFile(string filename)
{
	FILE* handle = fopen(filename.c_str(), "w");
	if(handle == NULL)
	{
		logfile_manager->WriteErrorMessage("InfixParserTree", "Could not open file for writing");
		return false;
	}

	fprintf(handle, "Graph G\n{\n");

	for(size_t i=0; i<tree_node_list.size(); i++)
	{
		InfixParserTreeNode* tree_node = tree_node_list[i];

		fprintf(handle, "\t%lu [label=\"%s\"]\n", (unsigned long) tree_node, tree_node->GetExpression().c_str());

		for(size_t j=0; j<tree_node->GetChildCount(); j++)
		{
			InfixParserTreeNode* child_node = tree_node->GetChild(j);

			fprintf(handle, "\t%lu -- %lu\n", (unsigned long) tree_node, (unsigned long) child_node);
		}
	}

	fprintf(handle, "}\n");

	fclose(handle);
	return true;
}

////////////////////////////
// Internal use functions //
////////////////////////////

int InfixParserTree::InitializeParser()
{
	InfixParserTreeNode* initial_tree_node = CreateNewNode(InfixParserTreeNode::IRREDUCIBLE_NODE, expression);
	if(initial_tree_node == NULL)
		return false;

	tree_node_list.push_back(initial_tree_node);

	return true;
}

int InfixParserTree::ParseUntilDone(int& found_parseable_expression, InfixParseRoutine parse_routine)
{
	int iteration_count = 0;
	int expression_parseable = true;

	while(expression_parseable && iteration_count<1000)
	{
		expression_parseable = false;

		for(size_t i=0; i<tree_node_list.size(); i++)
		{
			InfixParserTreeNode* tree_node = tree_node_list[i];
			if(tree_node->GetNodeType() != InfixParserTreeNode::IRREDUCIBLE_NODE)
				continue;

			if((this->*parse_routine)(tree_node, expression_parseable) == false)
				return false;

			if(expression_parseable)
			{
				delete tree_node;
				tree_node_list.erase(tree_node_list.begin() + i);

				found_parseable_expression = true;
				break;
			}
		}

		iteration_count++;
	}

	return true;
}

int InfixParserTree::ParsePlusMinus(InfixParserTreeNode* tree_node, int& expression_parseable)
{
	string cur_expression = tree_node->GetExpression();

	int operator_index = -1;

	int scope_level = 0;
	for(int i=0; i<cur_expression.length() && i<INFIX_PARSER_MAX_EXPR_LENGTH; i++)
	{
		if(cur_expression[i] == '(' || cur_expression[i] == '[')
			scope_level++;

		if(cur_expression[i] == ')' || cur_expression[i] == ']')
			scope_level--;

		if(scope_level == 0 && (cur_expression[i] == '+' || cur_expression[i] == '-'))
		{
			operator_index = i;
			break;
		}
	}
	if(operator_index == -1)
		return true;

	//Create a new operator node
	InfixParserTreeNode* plus_minus_node = CreateNewNode(InfixParserTreeNode::OPERATOR_NODE, cur_expression);
	if(plus_minus_node == NULL)
		return false;

	if(cur_expression[operator_index] == '+')
		((InfixOperatorNode*) plus_minus_node)->SetOperatorType(InfixOperatorNode::ADDITION_OPERATOR);

	else if(cur_expression[operator_index] == '-')
		((InfixOperatorNode*) plus_minus_node)->SetOperatorType(InfixOperatorNode::SUBTRACTION_OPERATOR);

	//Create children nodes
	string left_expression = cur_expression.substr(0, operator_index);
	string right_expression = cur_expression.substr(operator_index+1, cur_expression.length() - (operator_index + 1));
	//printf("left_expression = %s\n", left_expression.c_str());
	//printf("right_expression = %s\n", right_expression.c_str());

	InfixParserTreeNode* left_child = CreateNewNode(InfixParserTreeNode::IRREDUCIBLE_NODE, left_expression);
	InfixParserTreeNode* right_child = CreateNewNode(InfixParserTreeNode::IRREDUCIBLE_NODE, right_expression);

	if(left_child == NULL || right_child == NULL)
		return false;

	//Append children to operator node
	plus_minus_node->AppendChildNode(left_child);
	plus_minus_node->AppendChildNode(right_child);

	//Replace old tree node with new operator node
	size_t parent_child_index = tree_node->GetParentChildIndex();

	InfixParserTreeNode* parent_node = tree_node->GetParentNode();
	if(parent_node != NULL)
		parent_node->SetChildNode(parent_child_index, plus_minus_node);

	//Append all new nodes to tree node list
	tree_node_list.push_back(plus_minus_node);
	tree_node_list.push_back(left_child);
	tree_node_list.push_back(right_child);

	expression_parseable = true;
	return true;
}

int InfixParserTree::ParseTimesDivide(InfixParserTreeNode* tree_node, int& expression_parseable)
{
	string cur_expression = tree_node->GetExpression();

	int operator_index = -1;

	int scope_level=0;
	for(int i=0; i<cur_expression.length() && i<INFIX_PARSER_MAX_EXPR_LENGTH; i++)
	{
		if(cur_expression[i] == '(' || cur_expression[i] == '[')
			scope_level++;

		if(cur_expression[i] == ')' || cur_expression[i] == ']')
			scope_level--;

		if(scope_level == 0 && (cur_expression[i] == '*' || cur_expression[i] == '/'))
		{
			operator_index = i;
			break;
		}
	}
	if(operator_index == -1)
		return true;

	//Create a new operator node
	InfixParserTreeNode* plus_minus_node = CreateNewNode(InfixParserTreeNode::OPERATOR_NODE, cur_expression);
	if(plus_minus_node == NULL)
		return false;

	if(cur_expression[operator_index] == '*')
		((InfixOperatorNode*) plus_minus_node)->SetOperatorType(InfixOperatorNode::MULTIPLICATION_OPERATOR);

	else if(cur_expression[operator_index] == '/')
		((InfixOperatorNode*) plus_minus_node)->SetOperatorType(InfixOperatorNode::DIVISION_OPERATOR);

	//Create children nodes
	string left_expression = cur_expression.substr(0, operator_index);
	string right_expression = cur_expression.substr(operator_index+1, cur_expression.length() - (operator_index + 1));
	//printf("left_expression = %s\n", left_expression.c_str());
	//printf("right_expression = %s\n", right_expression.c_str());

	InfixParserTreeNode* left_child = CreateNewNode(InfixParserTreeNode::IRREDUCIBLE_NODE, left_expression);
	InfixParserTreeNode* right_child = CreateNewNode(InfixParserTreeNode::IRREDUCIBLE_NODE, right_expression);

	if(left_child == NULL || right_child == NULL)
		return false;

	//Append children to operator node
	plus_minus_node->AppendChildNode(left_child);
	plus_minus_node->AppendChildNode(right_child);

	//Replace old tree node with new operator node
	size_t parent_child_index = tree_node->GetParentChildIndex();

	InfixParserTreeNode* parent_node = tree_node->GetParentNode();
	if(parent_node != NULL)
		parent_node->SetChildNode(parent_child_index, plus_minus_node);

	//Append all new nodes to tree node list
	tree_node_list.push_back(plus_minus_node);
	tree_node_list.push_back(left_child);
	tree_node_list.push_back(right_child);

	expression_parseable = true;
	return true;
}

int InfixParserTree::ParsePower(InfixParserTreeNode* tree_node, int& expression_parseable)
{
	string cur_expression = tree_node->GetExpression();

	int operator_index = -1;

	int scope_level = 0;
	for(int i=0; i<cur_expression.length() && i<INFIX_PARSER_MAX_EXPR_LENGTH; i++)
	{
		if(cur_expression[i] == '(' || cur_expression[i] == '[')
			scope_level++;

		if(cur_expression[i] == ')' || cur_expression[i] == ']')
			scope_level--;

		if(scope_level == 0 && cur_expression[i] == '^')
		{
			operator_index = i;
			break;
		}
	}
	if(operator_index == -1)
		return true;

	//Create a new operator node
	InfixParserTreeNode* power_node = CreateNewNode(InfixParserTreeNode::OPERATOR_NODE, cur_expression);
	if(power_node == NULL)
		return false;

	((InfixOperatorNode*) power_node)->SetOperatorType(InfixOperatorNode::POWER_OPERATOR);

	//Create children nodes
	string left_expression = cur_expression.substr(0, operator_index);
	string right_expression = cur_expression.substr(operator_index+1, cur_expression.length() - (operator_index + 1));
	//printf("left_expression = %s\n", left_expression.c_str());
	//printf("right_expression = %s\n", right_expression.c_str());

	InfixParserTreeNode* left_child = CreateNewNode(InfixParserTreeNode::IRREDUCIBLE_NODE, left_expression);
	InfixParserTreeNode* right_child = CreateNewNode(InfixParserTreeNode::IRREDUCIBLE_NODE, right_expression);

	if(left_child == NULL || right_child == NULL)
		return false;

	//Append children to operator node
	power_node->AppendChildNode(left_child);
	power_node->AppendChildNode(right_child);

	//Replace old tree node with new operator node
	size_t parent_child_index = tree_node->GetParentChildIndex();

	InfixParserTreeNode* parent_node = tree_node->GetParentNode();
	if(parent_node != NULL)
		parent_node->SetChildNode(parent_child_index, power_node);

	//Append all new nodes to tree node list
	tree_node_list.push_back(power_node);
	tree_node_list.push_back(left_child);
	tree_node_list.push_back(right_child);

	expression_parseable = true;
	return true;
}

int InfixParserTree::ParseParenthesis(InfixParserTreeNode* tree_node, int& expression_parseable)
{
	string cur_expression = tree_node->GetExpression();
	if(cur_expression.length() <= 2)
		return true;

	int len = cur_expression.length();
	int found_open_parenthesis = (cur_expression[0] == '(' || cur_expression[0] == '[');
	int found_close_parenthesis = false; //(cur_expression[len-1] == ')' || cur_expression[len-1] == ']');

	int scope_level = 1;
	for(int i=1; i<cur_expression.length(); i++)
	{
		if(cur_expression[i] == '(' || cur_expression[i] == '[')
			scope_level++;

		else if(cur_expression[i] == ')' || cur_expression[i] == ']')
			scope_level--;

		if(scope_level == 0)
		{
			if(i == cur_expression.length() - 1)
				found_close_parenthesis = true;

			break;
		}
	}

	if(!found_open_parenthesis || !found_close_parenthesis)
		return true;

	//Create a new operator node
	InfixParserTreeNode* parenthesis_node = CreateNewNode(InfixParserTreeNode::OPERATOR_NODE, cur_expression);
	if(parenthesis_node == NULL)
		return false;

	((InfixOperatorNode*) parenthesis_node)->SetOperatorType(InfixOperatorNode::PARENTHESIS_OPERATOR);

	//Create children node
	InfixParserTreeNode* child_node = CreateNewNode(InfixParserTreeNode::IRREDUCIBLE_NODE, cur_expression.substr(1, len-2));

	if(child_node == NULL)
		return false;

	//Append children to operator node
	parenthesis_node->AppendChildNode(child_node);

	//Replace old tree node with new operator node
	size_t parent_child_index = tree_node->GetParentChildIndex();

	InfixParserTreeNode* parent_node = tree_node->GetParentNode();
	if(parent_node != NULL)
		parent_node->SetChildNode(parent_child_index, parenthesis_node);

	//Append all new nodes to tree node list
	tree_node_list.push_back(parenthesis_node);
	tree_node_list.push_back(child_node);

	expression_parseable = true;
	return true;
}

int InfixParserTree::ParseFunction(InfixParserTreeNode* tree_node, int& expression_parseable)
{
	string cur_expression = tree_node->GetExpression();

	int found_matching_function = false;

	string matching_function_identifier = "";
	InfixFunctionNode* matching_function_instance = NULL;

	for(size_t i=0; i<function_manager->GetFunctionInstanceCount(); i++)
	{
		InfixFunctionNode* function_instance = function_manager->GetFunctionInstance(i);

		for(size_t j=0; j<function_instance->GetFunctionIdentifierCount(); j++)
		{
			string function_identifier = function_instance->GetFunctionIdentifier(j);

			string cur_expression_substr = cur_expression.substr(0, function_identifier.length());
			if(cur_expression_substr == function_identifier)
			{
				found_matching_function = true;

				matching_function_identifier = function_identifier;
				matching_function_instance = function_instance;

				break;
			}
		}
		if(found_matching_function)
			break;
	}
	if(found_matching_function == false)
		return true;

	//Check for open/close parenthesis
	int identifier_length = matching_function_identifier.length();
	if(cur_expression.length() <  identifier_length + 3)
		return true;

	int expr_length = cur_expression.length();
	int found_open_parenthesis = (cur_expression[identifier_length] == '(' || cur_expression[identifier_length] == '[');
	int found_close_parenthesis = (cur_expression[expr_length-1] == ')' || cur_expression[expr_length-1] == ']');

	if(!found_open_parenthesis || !found_close_parenthesis)
		return true;

	//Find delimiters
	vector<size_t> delimiter_location_list;
	delimiter_location_list.push_back(identifier_length);

	int scope_level = 0;
	for(size_t i=identifier_length+1; i<cur_expression.length()-1; i++)
	{
		if(cur_expression[i] == '(' || cur_expression[i] == '[')
			scope_level++;

		if(cur_expression[i] == ')' || cur_expression[i] == ']')
			scope_level--;

		if(scope_level == 0 && cur_expression[i] == ',')
			delimiter_location_list.push_back(i);
	}
	delimiter_location_list.push_back(cur_expression.length()-1);

	if(delimiter_location_list.size() != matching_function_instance->GetInputCount()+1)
		return true;

	//for(size_t i=0; i<delimiter_location_list.size()-1; i++)
	//	printf("%s\n", cur_expression.substr(delimiter_location_list[i]+1, delimiter_location_list[i+1] - (delimiter_location_list[i]+1)).c_str());
	//printf("\n");

	//Create a new function node
	InfixParserTreeNode* function_node = (InfixParserTreeNode*) matching_function_instance->CreateNewInstance();
	if(function_node == NULL)
		return false;

	function_node->SetExpression(cur_expression);
	function_node->SetLogFileManager(logfile_manager);

	//Create children nodes
	for(size_t i=0; i<delimiter_location_list.size()-1; i++)
	{
		int substr_length = delimiter_location_list[i+1] - (delimiter_location_list[i]+1);
		string substr = cur_expression.substr(delimiter_location_list[i]+1, substr_length);

		InfixParserTreeNode* child_node = CreateNewNode(InfixParserTreeNode::IRREDUCIBLE_NODE, substr);

		if(child_node == NULL)
			return false;

		function_node->AppendChildNode(child_node);
	}

	//Replace old tree node with new operator node
	size_t parent_child_index = tree_node->GetParentChildIndex();

	InfixParserTreeNode* parent_node = tree_node->GetParentNode();
	if(parent_node != NULL)
		parent_node->SetChildNode(parent_child_index, function_node);

	//Append all new nodes to tree node list
	tree_node_list.push_back(function_node);

	for(size_t i=0; i<function_node->GetChildCount(); i++)
		tree_node_list.push_back(function_node->GetChild(i));

	expression_parseable = true;

	return true;
}

InfixParserTreeNode* InfixParserTree::CreateNewNode(int node_type, string node_expr)
{
	InfixParserTreeNode* infix_parser_tree_node = NULL;

	if(node_type == InfixParserTreeNode::IRREDUCIBLE_NODE)
		infix_parser_tree_node = new InfixParserTreeNode;

	else if(node_type == InfixParserTreeNode::OPERATOR_NODE)
		infix_parser_tree_node = (InfixParserTreeNode*) (new InfixOperatorNode);

	infix_parser_tree_node->SetExpression(node_expr);
	infix_parser_tree_node->SetLogFileManager(logfile_manager);

	return infix_parser_tree_node;
}

int InfixParserTree::UpdateSymbolValues()
{
	for(size_t i=0; i<tree_node_list.size(); i++)
	{
		InfixParserTreeNode* tree_node = tree_node_list[i];
		if(tree_node->GetNodeType() != InfixParserTreeNode::IRREDUCIBLE_NODE || tree_node->TestIsNumeric() || tree_node->GetExpression().length() == 0)
			continue;

		InfixSymbol* infix_symbol = symbol_manager->FindSymbol(tree_node->GetExpression());
		if(infix_symbol != NULL)
			tree_node->SetNodeValue(infix_symbol->GetValue());

		else
		{
			if(symbol_manager->CreateNewSymbol(tree_node->GetExpression(), 0.00) == false)
			{
				logfile_manager->WriteErrorMessage("InfixParserTree", "Could not create new symbol for irreducible expression");
				return false;
			}
		}
	}

	return true;
}
