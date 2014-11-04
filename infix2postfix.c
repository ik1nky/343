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
	char *postfix = malloc(50 *sizeof(char));

	stackInit(&ops);
	char * token;
	/*tokenize it*/
	token = strtok(infixStr," ");
	postfix[0] = '\0';
	while (token != NULL){
		char *str = malloc(10 * sizeof(char));
		sprintf(str, "%s", token);

		/*#skip operand, we can use last case as an else*/
		if (isLeftParen(str)){
			stackPush(&ops, str);
		}else if (isOperand(str)){
		}else if (isOperator(str)){
			//printf("op! %s\n", str);
			//pop stack items with higher or equal input presedence than the input
			while (!stackIsEmpty(&ops) && inputPrecedence(token) <= stackPrecedence(stackPeek(&ops))){
				sprintf(postfix, "%s %s", postfix, stackPop(&ops));
			}
			stackPush(&ops, str);
		}else if(isRightParen(str)){
			while (!stackIsEmpty(&ops) && *stackPeek(&ops) != '('){
				sprintf(postfix, "%s %s", postfix, stackPop(&ops));
			}
			//removes the last paren
			stackPop(&ops);
		}else{
			//it's a number
			sprintf(postfix, "%s %d", postfix, atoi(str));
		}

		token = strtok(NULL," ");
	}
	while (!stackIsEmpty(&ops)){
		sprintf(postfix, "%s %s", postfix, stackPop(&ops));
	}
	return postfix;
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
	if (*str == '('){
		return true;
	}
	return false;
}

/* function that returns true if the string is a right parenthesis */
bool isRightParen(char *str)
{
	if (*str == ')'){
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
		/* value of '(' */
		default:
			return -1;
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
	stack s;
	stackInit(&s);
  char *token = malloc(20 * sizeof(char));
	token = strtok(postfixStr, " ");
	while (token != NULL){
		if (isOperator(token)){
			int y = atoi(stackPop(&s));
			int x = atoi(stackPop(&s));
			int out = applyOperator(x, y, token);
			char *str = malloc(10 * sizeof(char));
			str[0] = '\0';
			sprintf(str, "%i", out);
			stackPush(&s, str);
		}else{
			stackPush(&s, token);
		}


		token = strtok(NULL, " ");
	}
	return atoi(stackPop(&s));
}

/* apply operator to num1 and num2 and return the result */
int applyOperator(int num1, int num2, char *opr)
{
	int i = 0;
	switch (*opr){
		case '+':
			i=num1+num2;
			return i;
		case '-':
			i=num1-num2;
			return i;
		case '*':
			i=num1*num2;
			return i;
		case '/':
			i=num1/num2;
			return i;
		case '%':
			i=num1 % num2;
			return i;
		case '^':
			i = (int) (pow(num1, num2));
			return i;
	}
	return 0;
}
