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
	char buffer1[] = "define x (+ 3 0)";
 	char buffer[] = "* (+ (! x) 88) 8";
	Parser parser; 
	parser.Parse(buffer1);
	parser.Parse(buffer);
	return 0;
}