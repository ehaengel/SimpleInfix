#include "infix_operator_node.h"

InfixOperatorNode::InfixOperatorNode()
{
	node_type = InfixParserTreeNode::OPERATOR_NODE;
	operator_type = InfixOperatorNode::NO_OPERATION;
}

InfixOperatorNode::~InfixOperatorNode()
{
	//Do nothing
}

/////////////////////
// Data management //
/////////////////////

// Set InfixOperatorNode data
int InfixOperatorNode::SetOperatorType(int operator_type)
{
	this->operator_type = operator_type;

	return true;
}

// Get InfixOperatorNode data
int InfixOperatorNode::GetOperatorType()
{
	return operator_type;
}

////////////////////////////
// Infix parser functions //
////////////////////////////

complex<double> InfixOperatorNode::Evaluate()
{
	complex<double> result = 0.00;

	if(child_node_list.size() == 2)
	{
		complex<double> left_operand = child_node_list[0]->Evaluate();
		complex<double> right_operand = child_node_list[1]->Evaluate();

		if(operator_type == InfixOperatorNode::ADDITION_OPERATOR)
			result = left_operand + right_operand;

		else if(operator_type == InfixOperatorNode::SUBTRACTION_OPERATOR)
			result = left_operand - right_operand;

		else if(operator_type == InfixOperatorNode::MULTIPLICATION_OPERATOR)
			result = left_operand * right_operand;

		else if(operator_type == InfixOperatorNode::DIVISION_OPERATOR)
			result = left_operand / right_operand;

		else if(operator_type == InfixOperatorNode::POWER_OPERATOR)
			result = pow(left_operand, right_operand);
	}

	else if(child_node_list.size() == 1)
	{
		if(operator_type == InfixOperatorNode::PARENTHESIS_OPERATOR)
			result = child_node_list[0]->Evaluate();
	}

	else
	{
		logfile_manager->WriteErrorMessage("InfixOperatorNode", "Operator node does not have exactly 2 children nodes");
		return 0.00;
	}


	return result;
}

/////////////////////////
// Debugging functions //
/////////////////////////

int InfixOperatorNode::Print()
{

	return true;
}
