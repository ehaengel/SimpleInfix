#include <stdlib.h>
#include <stdio.h>

#include <complex>
using namespace std;

#ifndef SIMPLE_INFIX_PARSER_UTILITY_H
#define SIMPLE_INFIX_PARSER_UTILITY_H

#ifndef INFIX_PARSER_MAX_EXPR_LENGTH
#define INFIX_PARSER_MAX_EXPR_LENGTH 1000
#endif

#ifndef EPS
#define EPS 1e-8
#endif

string complex_to_str(complex<double> z);

#endif
