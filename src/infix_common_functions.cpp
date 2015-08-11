#include "infix_common_functions.h"

///////////////
// InfixSine //
///////////////

InfixSine::InfixSine()
{
	AppendFunctionIdentifier("sin");
	AppendFunctionIdentifier("Sin");
	AppendFunctionIdentifier("SIN");

	SetInputCount(1);
}

InfixSine::~InfixSine()
{
	// Do nothing
}

complex<double> InfixSine::Evaluate()
{
	if(CollectInputValuesFromChildNodes() == false)
		return 0.00;

	return sin(GetInputValue(0));
}

InfixFunctionNode* InfixSine::CreateNewInstance()
{
	return ((InfixFunctionNode*) new InfixSine);
}

/////////////////
// InfixCosine //
/////////////////

InfixCosine::InfixCosine()
{
	AppendFunctionIdentifier("cos");
	AppendFunctionIdentifier("Cos");
	AppendFunctionIdentifier("COS");

	SetInputCount(1);
}

InfixCosine::~InfixCosine()
{
	// Do nothing
}

complex<double> InfixCosine::Evaluate()
{
	if(CollectInputValuesFromChildNodes() == false)
		return 0.00;

	return cos(GetInputValue(0));
}

InfixFunctionNode* InfixCosine::CreateNewInstance()
{
	return ((InfixFunctionNode*) new InfixCosine);
}
