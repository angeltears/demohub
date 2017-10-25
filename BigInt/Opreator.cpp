#include"Opreator.h"

Operation::Operation(const char *str1, const char *str2) :num1(str1), num2(str2){}
Operation::~Operation(){}
Bigint& Operation::GetResult()
{
	return Bigint("0");
}

OperationAdd::OperationAdd(const char *str1, const char *str2) :Operation(str1, str2) {}
Bigint& OperationAdd::GetResult()
{
	int carrynum = 0;
	result.num = new char[(result.length = num1.length > num2.length ? num1.length + 1 : num2.length + 1)+1];
	int length = result.length - 1;
	int temp = 0;
	for (int i = num1.length -1, j = num2.length -1; length >= 0;)
	{
		if(i >= 0 && j >= 0)
		{ 
			temp = num1.num[i--] + num2.num[j--] + carrynum - 2 * '0';
			result.num[length--] = temp % 10 + '0';
			carrynum = temp / 10;
		}
		else if (i >= 0)
		{
			temp = num1.num[i--] + carrynum - '0';
			result.num[length--] = temp % 10 + '0';
			carrynum = temp / 10;
		}
		else if (j >= 0)
		{
			temp = num2.num[j--] + carrynum - '0';
			result.num[length--] = temp % 10 + '0';
			carrynum = temp / 10;
		}
		else if (carrynum != 0)
		{
			result.num[length--] = carrynum + '0';
		}
		else
		{
			for (int k = 0; k < result.length - 1; k++)
			{
				result.num[k] = result.num[k + 1];
			}
			result.length--;
			length--;
		}
	}
	result.num[result.length] = '\0'; 
	return result;
}



OperationSub::OperationSub(const char *str1, const char *str2):Operation(str1,str2){}
Bigint& OperationSub::GetResult()
{
	int borrownum = 0;
	result = new char[(result.length = num1.length > num2.length ? num1.length + 1 : num2.length + 1) + 1];
	int length = result.length - 1;
	int temp = 0;
	if (num1.length > num2.length || (num1.length == num2.length &&strcmp(num1.num, num2.num) >= 0))
	{
		for (int i = num1.length - 1, j = num2.length - 1; length >= 0;)
		{
			if (i >= 0 && j >= 0)
			{
				temp = num1.num[i--] - num2.num[j--] - borrownum;
				if (temp < 0)
				{
					temp = temp + 10;
					borrownum = 1;
				}
				else
				{
					borrownum = 0;
				}
				result.num[length--] = temp + '0';
			}
			else if (i >= 0)
			{
				temp = num1.num[i--] - borrownum - '0';
				if (temp < 0)
				{
					temp = temp + 10;
					borrownum = 1;
				}
				else
				{
					borrownum = 0;
				}
				result.num[length--] = temp + '0';
			}
			else 
			{
				for (int k = 0; k < result.length - 1; k++)
				{
					result.num[k] = result.num[k + 1];
				}
				result.length--;
				length--;
			}
		}
		result.num[result.length] = '\0';
		return result;
	}
	else
	{
		result.num[0] = '-';
		for (int  j= num1.length - 1, i = num2.length - 1; length >= 0;)
		{
			if (i >= 0 && j >= 0)
			{
				temp = num2.num[i--] - num1.num[j--] - borrownum;
				if (temp < 0)
				{
					temp = temp + 10;
					borrownum = 1;
				}
				else
				{
					borrownum = 0;
				}
				result.num[length--] = temp + '0';
			}
			else if (i >= 0)
			{
				temp = num2.num[i--] - borrownum - '0';
				if (temp < 0)
				{
					temp = temp + 10;
					borrownum = 1;
				}
				else
				{
					borrownum = 0;
				}
				result.num[length--] = temp + '0';
			}
			else if (length >= 1)
			{
				for (int k = 1; k < result.length - 1; k++)
				{
					result.num[k] = result.num[k + 1];
				}
				result.length--;
				length--;
			}
			else
			{
				length--;
			}
		}
		result.num[result.length] = '\0';
		return result;
	}
}


OperationMul::OperationMul(const char *str1, const char *str2) :Operation(str1, str2) {}

Bigint& OperationMul::GetResult()
{
	const int wid = num1.length / 4 + 1 + 1;
	const int len = num2.length / 4 + 1 + 1;
	long int **arrresult = new long int *[wid];
	for (int i = 0; i < wid; i++)
	{
		*(arrresult + i) = new long int[len];
	}
	for (int i = 0; i < wid - 1; i++)
	{
		arrresult[i][0] = Toint(num1.num +(i * 4 > 0 ? i * 4  : 0));
	}
	for (int i = 0; i < len - 1; i++)
	{
		arrresult[wid - 1][i + 1] = Toint(num2.num + (i * 4 > 0 ? i * 4 : 0));
	}
	for (int i = 0; i < wid - 1; i++)
	{
		for (int j = 1; j < len; j++)
		{
			arrresult[i][j] = arrresult[i][0] * arrresult[wid - 1][j];
		}
	}
	int k = 0;
	long int *resultnum = new long int[wid + len - 3]{0};
	for (int i = 0; i < wid - 1; i++)
	{
		for (int j = 1; j < len; j++)
		{
			resultnum[i + j - 1] +=  arrresult[i][j];
		}
	}
	for(int i = 0; i < wid + len - 3; i++)
		std::cout << resultnum[i] << endl;
	Tostring(resultnum, wid + len - 3);
	for (int i = 0; i < wid; i++)
	{
		delete[] *(arrresult + i);
	}
	delete[] arrresult;
	return result;
}

int  OperationMul::Toint(char *start)
{
	long int desc = 0;
	int i = 0;
	while (*start != '\0' && i <= 3)
	{
		desc = desc * 10;
		desc += *start - '0';
		i++;
		start++;
	}
	return desc;

}

void OperationMul::Tostring(long int *src,int length)
{
	result.num = new char[length * 4 + 1]{'0'};
	result.length = 0;
	int carry = 0;
	int temp = 0;
	char* ptr = result.num;
	for (int i = 0; i < length * 4 + 1; i++)
		result.num[i] = '0';
	for (int i = 0; i < length; i++)
	{
		if (src[i] == 0)
		{
			ptr = ptr + 1;
			result.length++;
		}
		else
		{
			int num = 10000000;
			int step = 0;
			while (num)
			{
				if (src[i] % num * 10 / num != 0)
					break;
				num = num / 10;
			}
			while (num != 1 && src[i] != 0)
			{
				*ptr += src[i] % num * 10 / num;
				num = num / 10;
				src[i] = src[i] % num;
				ptr++;
				step++;
				result.length++;
			}
			ptr = ptr - step + 4;	
		}
	}
	result.length = result.length - length;
	ptr = result.num;
	while (*ptr == '0')
	{
		for (int i = 0; i < result.length - 1; i++)
		{
			result.num[i] = result.num[i + 1];
		}
		result.length--;
	}
	for (int i = result.length -1; i >= 0; i--)
	{
		temp = result.num[i] - '0';
		result.num[i] = temp % 10 + '0' + carry;
		carry = temp / 10;
	}
	result.num[result.length] = '\0';
}