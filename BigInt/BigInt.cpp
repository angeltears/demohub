#include"BigInt.h"
#include<string.h>
#include<assert.h>
Bigint::Bigint(const char *p)
{
	if (p == NULL)
		return;
	length = strlen(p);
	num = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		num[i] = p[i];
	}
	num[length] = '\0';
}
Bigint::Bigint(int n)
{	
	num = new char[n + 1];
	num[n] = '/0';
	length = n;
}
Bigint::Bigint(Bigint &T)
{
	if (this == &T)
		return;
	length = T.length;
	num = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		num[i] = T.num[i];
	}
	num[length] = '\0';
}
int Bigint::getlength()
{
	return length;
}
Bigint::~Bigint()
{
	if (num != NULL)
	{
		delete[]num;
		num = NULL;
	}
	length = 0;
}

ostream & operator<<(ostream & out, Bigint &T)
{
	out << T.num;
	return out;
}