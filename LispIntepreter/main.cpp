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
 	char buffer[] = "define (funcName y x) (define (y) (+ 3 x))";
	char buffer1[] = "funcName abc 100";
    char buffer2[] = "abc";
	Parser parser;
	parser.Parse(buffer);
	parser.Parse(buffer1);
    parser.Parse(buffer2);
	getchar();
	return 0;
}