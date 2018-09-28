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
 	char buffer[] = "define (funcName y) (y 9)";
	char buffer1[] = "define (pow2 x) (* x x)";
	char buffer2[] = "funcName funcName";
	Parser parser;
	parser.Parse(buffer);
	parser.Parse(buffer1);
	parser.Parse(buffer2);
	getchar();
	return 0;
}