#pragma once
#include<iostream>
using namespace std;

class Bigint 
{
public:
	Bigint() {}
	Bigint(const char *);
	Bigint(int);
	Bigint(Bigint &);
	int getlength();
	~Bigint();
	char *num;
	int length;
	friend ostream & operator<<(ostream &, Bigint &);
};

ostream & operator<<(ostream &, Bigint &);