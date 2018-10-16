#include "Parser.h"
#include "Lexical.h"
#include "Semantic.h"
#include <stdio.h>
#include <string.h>

// ������

/*
	��ֵ˳�� ��׺ (+ 2 2) -> 2 + 2
	���ʽ��ֵ��Ӧ���� ( expr ( <expr> ) ) -> (expr value)
	������������define ( <������> <arg1> <arg2> ... ) ( <��������> )
	�������ù���( <����>  <arg1> <arg2> ... )
*/

static int maxTest = 0;
static int succeedTest = 0;

void testfor(const std::string& code, const std::string& ans) {
	const char * buffer = code.c_str();
	maxTest++;
	try {
		Parser parser;
		parser.Parse(buffer);
		if (parser.checkSucceed(ans)) {
			succeedTest++;
		}
	}
	catch (ParseException &ex) {
		fprintf(stderr, "%s\n", ex.what());
	}
}

void test() {
	testfor("* 3 3", "9");
	testfor("+ (* 3 3) 1", "10");
	testfor("- 10 (* 3 3) 1", "0");
	testfor("/ (* 12 6) 0", "Error");
	testfor("define (f x y z) (* x y z)", "None");
	testfor("f 1 2 3", "6");
	testfor("define (g x y) (define (h z) (+ z y x))", "None");
	testfor("((g 10 10) 3)", "23");
	testfor("if (< 1 2) (+ 9 9) (- 9 9)", "18");
	//testfor("f 9", "729");

	printf("Test Report: %d / %d (%.2f %%)\n", succeedTest, maxTest, succeedTest * 100.0 / maxTest);
}

int main(int argc, char ** argv) {
	//printf("%s\n", ">>>");
	//char buffer[1024];
	//fgets(buffer, 1024, stdin);
	char buffer[] = "( define (f x) ( if (= x 0) (1) ( * (f (- x 1)) x) ) )";
	// char buffer[] = "(- 10 (* 3 3) 1)";
	char buffer1[] = "(f 2)";


	Lexical lex;
	lex.Parse(buffer);
	lex.Display();

	printf("\n");

	Semantic sem;
	sem.Analyze(lex);
	sem.Display();
	Parser parser;
	parser.Parse(buffer1);
	//test();
	getchar();
	return 0;
}