#include "Parser.h"
#include <stdio.h>
#include <string.h>

void test() {

}

int main(int argc, char ** argv) {
	//printf("%s\n", ">>>");
	//char buffer[1024];
	//fgets(buffer, 1024, stdin);
	char buffer1[] = "define x 3";
 	char buffer[] = "(* (+ 2 (* 4 6)) (+ 3 5 7))";
	Parser parser;
	parser.Parse(buffer);
	getchar();
	return 0;
}