#include"Opreator.h"

void main()
{
	char *str1 = "10011";
	char *str2 = "10011";
	Operation* A = new OperationMul(str1, str2);
	cout << A->GetResult()<<endl;
	cout << 10011 * 10011 << endl;
	system("pause");
}