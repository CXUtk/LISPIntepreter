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
 	char buffer[] = "define (x y) (+ y 1)";
	char buffer1[] = "+ x 6";
	Parser parser;
	parser.Parse(buffer);
	parser.Parse(buffer1);
	getchar();
	return 0;
}