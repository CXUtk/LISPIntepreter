#include "Parser.h"
#include <stdio.h>
#include <string.h>
static int maxTest = 0;
static int succeedTest = 0;

void testfor(const std::string& code, const std::string& ans){
	const char * buffer = code.c_str();
	maxTest++;
	Parser parser;
	parser.Parse(buffer);
	if (parser.checkSucceed(ans)) {
		succeedTest++;
	}
}

void test() {
	testfor("* 3 3", "9");
	testfor("+ (* 3 3) 1", "10");
	testfor("if (< 1 2) (+ 9 9) (- 9 9)", "18");
	//testfor("f 9", "729");

	printf("Test Report: %d / %d\n", succeedTest, maxTest);
}

int main(int argc, char ** argv) {
	//printf("%s\n", ">>>");
	//char buffer[1024];
	//fgets(buffer, 1024, stdin);
 	char buffer[] = "if (< 1 2) (+ 9 9) (- 9 9)";
	//char buffer[] = "define (f x) (* x x x)";
	//char buffer1[] = "f 9";
	Parser parser;
	parser.Parse(buffer);
	//parser.Parse(buffer1);
	// test();
	getchar();
	return 0;
}