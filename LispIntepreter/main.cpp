#include "Parser.h"
#include <stdio.h>
#include <string.h>

void test() {

}

int main(int argc, char ** argv) {
	//printf("%s\n", ">>>");
	//char buffer[1024];
	//fgets(buffer, 1024, stdin);
	char buffer1[] = "define x (+ 3 0)";
 	char buffer[] = "^ x 3";
	Parser parser; 
	parser.Parse(buffer1);
	parser.Parse(buffer);
	getchar();
	return 0;
}