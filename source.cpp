#pragma once

#include "Building a lexical analyzer.h"
#include "Translation into a reverse Polish entry.h"
#include "Translation of the RPE into the output language.h"

int main(){
	bool ERROR = false;
	Conversion_to_lexemes(ERROR);
	Conversion_to_IPF(ERROR);
	Convert_to_Perl_code(ERROR);
	return 0;
}