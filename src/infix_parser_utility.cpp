#include "infix_parser_utility.h"

string complex_to_str(complex<double> z) {
	char buffer[1000];
	buffer[0] = '\0';

	if(abs(z) < EPS)
		sprintf(buffer, "%.5f", 0.0);

	else {
		//Real part
		if(fabs(real(z)) > EPS)
			sprintf(buffer, "%.5f", real(z));

		//Imaginary part
		if(fabs(imag(z)) > EPS) {
			if(fabs(real(z)) > EPS && imag(z) < 0.0)
				sprintf(buffer, "%s-", buffer);

			else if(fabs(real(z)) > EPS && imag(z) > 0.0)
				sprintf(buffer, "%s+", buffer);

			else if(fabs(real(z)) < EPS && imag(z) < 0.0)
				sprintf(buffer, "%s-", buffer);

			sprintf(buffer, "%s%.5fi", buffer, fabs(imag(z)));
		}
	}

	return string(buffer);
}
