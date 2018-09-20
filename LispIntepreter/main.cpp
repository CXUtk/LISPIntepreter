#include "Parser.h"
#include <stdio.h>
#include <string.h>

void test() {
    char buffer[] = "* 3 3";
    Parser parser;
    parser.Parse(buffer);
}

int main(int argc, char ** argv) {
	//printf("%s\n", ">>>");
	//char buffer[1024];
	//fgets(buffer, 1024, stdin);
 	char buffer[] = "+ (/ 10 2) 8";
	
	Parser parser;
	parser.Parse(buffer);
	getchar();
	return 0;
}