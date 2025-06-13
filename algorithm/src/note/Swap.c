void swap(char* a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap(int* a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap(double* a, double *b)
{
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap(float* a, float *b)
{
	float tmp = *a;
	*a = *b;
	*b = tmp;
}

#define MaxLen 10005
//交换两个存储字符串的数组a[MaxLen]和b[MaxLen]中的内容：swap(a, b);
void swap(char a[], char b[])
{
	char t[MaxLen];
	strcpy(t, a);
	strcpy(a, b);
	strcpy(b, t);
}

//交换char*指针p和指针q指向的字符串：swap(&p, &q);
//不能直接对字符数组操作！！！必须对指针赋值字符数组才行！
//比如char a[] = "abcd", b[] = "dddd"; char *p = a, *q = b; swap(&p, &q);才可以！！！
void swap(char** a, char **b)
{
	char *tmp = *a;
	*a = *b;
	*b = tmp;
}
