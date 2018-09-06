#include "Parser.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {
	printf("%s\n", ">>>");
	char buffer[1024];
	fgets(buffer, 1024, stdin);
	Parser parser;
	parser.Parse(buffer);
	getchar();
	return 0;
}