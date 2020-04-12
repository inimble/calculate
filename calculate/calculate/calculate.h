#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<stack>
#include<time.h>

struct result
{
	int real;
	int up;
	int down;
};

void rof(struct result* result);
void creat(int num, int range);
void calculate(std::stack<int>* eq, char sym, struct result* result);
void verify();
