#include "infix_parser_tree_node.h"

InfixParserTreeNode::InfixParserTreeNode()
{
	expression = "";

	node_type = InfixParserTreeNode::IRREDUCIBLE_NODE;
	node_value = 0.00;

	parent_child_index = 0;
	parent_node = NULL;

	child_node_list.clear();

	logfile_manager = NULL;
}

InfixParserTreeNode::~InfixParserTreeNode()
{
	//Do nothing
}

/////////////////////
// Data management //
/////////////////////

// Set InfixParserTreeNode data
int InfixParserTreeNode::SetExpression(string expression)
{
	this->expression = expression;

	if(CleanExpression() == false)
		return false;

	return true;
}

int InfixParserTreeNode::SetNodeValue(complex<double> node_value)
{
	this->node_value = node_value;

	return true;
}

int InfixParserTreeNode::AppendChildNode(InfixParserTreeNode* child_node)
{
	child_node_list.push_back(child_node);
	child_node->SetParentNode(this, child_node_list.size()-1);

	return true;
}

int InfixParserTreeNode::SetChildNode(size_t index, InfixParserTreeNode* child_node)
{
	child_node_list[index] = child_node;
	child_node->SetParentNode(this, index);

	return true;
}

int InfixParserTreeNode::SetParentNode(InfixParserTreeNode* parent_node, size_t parent_child_index)
{
	this->parent_node = parent_node;
	this->parent_child_index = parent_child_index;

	return true;
}

int InfixParserTreeNode::SetLogFileManager(LogFileManager* logfile_manager)
{
	this->logfile_manager = logfile_manager;

	return true;
}

// Get InfixParserTreeNode data
int InfixParserTreeNode::GetNodeType()
{
	return node_type;
}

string InfixParserTreeNode::GetExpression()
{
	return expression;
}

size_t InfixParserTreeNode::GetChildCount()
{
	return child_node_list.size();
}

InfixParserTreeNode* InfixParserTreeNode::GetChild(size_t index)
{
	if(index >= child_node_list.size())
		return NULL;

	return child_node_list[index];
}

InfixParserTreeNode* InfixParserTreeNode::GetParentNode()
{
	return parent_node;
}

size_t InfixParserTreeNode::GetParentChildIndex()
{
	return parent_child_index;
}

////////////////////////////
// Infix parser functions //
////////////////////////////

complex<double> InfixParserTreeNode::Evaluate()
{
	if(TestIsNumeric())
	{
		double result = 0.00;
		sscanf(expression.c_str(), "%lf", &result);

		node_value = result;
	}

	return node_value;
}

int InfixParserTreeNode::TestIsNumeric()
{
	if(expression.length() == 0 || isdigit(expression[0]) == false)
		return false;

	return true;
}

/////////////////////////
// Debugging functions //
/////////////////////////

int InfixParserTreeNode::Print()
{

	return true;
}

////////////////////////////
// Internal use functions //
////////////////////////////

int InfixParserTreeNode::CleanExpression()
{
	int start_index = 0;
	int stop_index = expression.length();

	for(int i=0; i<expression.length() && i<INFIX_PARSER_MAX_EXPR_LENGTH; i++)
	{
		if(expression[i] != ' ' && expression[i] != '\n')
		{
			start_index=i;
			break;
		}

		else if(i == expression.length()-1 || i == INFIX_PARSER_MAX_EXPR_LENGTH-1)
			start_index = expression.length()-1;
	}

	for(int i=expression.length()-1; i>=0; i--)
	{
		if(expression[i] != ' ' && expression[i] != '\n')
		{
			stop_index = i+1;
			break;
		}

		else if(i == 0)
			stop_index = 0;
	}

	expression = expression.substr(start_index, stop_index);

	return true;
}
