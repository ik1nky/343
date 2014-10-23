#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "stack.h"
#include "infix2postfix.h"

/*http://www.youtube.com/watch?v=vq-nUF0G4fI*/
/* function to convert an infix to postfix */
/*    ((A+B))*C-D)*E -> AB+C*D-E*     */

stack ops;

char *infixToPostfix(char *infixStr)
{
	stackInit(&ops);
	char * token;
	/*tokenize it*/
	token = strtok(infixStr," ");

	while (token != NULL){
		char *str = malloc(10 * sizeof(char));
		sprintf(str, "%s", token);

		/*#skip operand, we can use last case as an else*/
		if (isLeftParen(token)){
			printf("is left paren\n");
			stackPush(&ops, str);
		}else if (isOperand(token)){
			printf("is an operand\n");
		}else if (isOperator(token)){
			printf("is an operator\n");
		}else if(isRightParen(token)){
			printf("is a right paren\n");
		}else{
			//it's a number
			//num = atoi(token);
			sprintf(str, "%d", atoi(token));
			printf("%i\n", atoi(token));
		}

		//sprintf(str, "%c", num);
		//stackPush(&ops, str);

		//printf("%s", token);
		token = strtok(NULL," ");
	}

	return NULL;
}

/* function that returns true if the string is an operator */
bool isOperator(char *str)
{
	if (*str == '*' || *str == '/' || *str == '%' || *str == '^' || *str == '+' || *str == '-'){
		return true;
	}
	return false;
}

/* function that returns true if the string is an operand/integer */
bool isOperand(char *str)
{
	return false;
}

/* function that returns true if the string is a left parenthesis */
bool isLeftParen(char *str)
{
	if (*str == ')'){
		return true;
	}
	return false;
}

/* function that returns true if the string is a right parenthesis */
bool isRightParen(char *str)
{
	if (*str == '('){
		return true;
	}
	return false;
}

/* function that returns the stack precedence of given operator */
int stackPrecedence(char *str)
{
	switch (*str){
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return 2;
		case '/':
			return 2;
		case '%':
			return 2;
		case '^':
			return 3;
		default:
			return 1;
	}
}

/* function that returns the input precedence of given operator */
int inputPrecedence(char *str)
{
	switch (*str){
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return 2;
		case '/':
			return 2;
		case '%':
			return 2;
		case '^':
			return 4;
		default:
			/* value of '(' */
			return 5;
	}
}

/* function that evaluates a postfix expression and returns the result */
int evaluatePostfix(char *postfixStr)
{
	return 69;
}

/* apply operator to num1 and num2 and return the result */
int applyOperator(int num1, int num2, char *opr)
{
	return 0;
}
