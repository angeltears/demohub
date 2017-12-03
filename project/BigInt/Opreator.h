#include"BigInt.h"
class Operation
{
public:
	Operation(const char *str1, const char *str2);
	~Operation();
	virtual Bigint& GetResult();
	Bigint num1;
	Bigint num2;
	Bigint result;
	char ch;
};


class OperationAdd : public Operation
{
public:	
	OperationAdd(const char *str1, const char *str2);
	virtual Bigint& GetResult();
};


class OperationDiv : public Operation
{
public:
	virtual Bigint& GetResult();
};


class OperationSub : public Operation
{
public:
	OperationSub(const char *str1, const char *str2);
	virtual Bigint& GetResult();
};



class OperationMul : public Operation
{
public:
	OperationMul(const char *str1, const char *str2);
	virtual Bigint& GetResult();
private:
	int Toint(char *start);
	void Tostring(long int *src,int length);
};