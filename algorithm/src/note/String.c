// 交换两个字符！！这个只能交换两个字符！不能交换两个字符串！
// char a,b; swap(&a, &b);
void swap(char* a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

// 将字符串倒序翻转 如abcd变成dcba
// char a[] = "abcd"; revs(a);
void revs(char* str)
{
    int len = strlen(str);
    char *low = &str[0];
    char *high = &str[len - 1];
    while(low < high)
    {
        swap(low++, high--);
    }
}

// 将字符串l到r的部分反转，注意传入指针
// char a[] = "abcd"; rev(&a[1], &a[2]);
// 输出acbd
void rev(char * l, char * r)
{
    char tmp;
    while(r > l)
    {
        tmp = *l; *l = *r; *r = tmp;
        l++; r--;
    }
}

//计算str中有多少个字符ch
int numch(const char str[], char ch)
{
	char *p = strchr(str, ch);
	int cnt = 0;
	while(p) {
		++cnt;
		p = strchr(p + 1, ch);
	}
	return cnt;
}

//计算str中有多少个子串substr
int numstr(const char str[], char substr[])
{
	char *p = strstr(str, substr);
	int cnt = 0;
	while(p) {
		++cnt;
		p = strstr(p + 1, substr);
	}
	return cnt;
}

// 将字符串b拼接到a后面
strcat(a,b);

// 将字符串b拼接到a后面，且最多拼接n位
strncat(a,b,n);

// 将字符串b复制到a上，并覆盖a
// 如果b比a短，不保留a多出的位
strcpy(a,b);

// 将字符串b复制到a上，并覆盖a，且最多复制n位
// 当n小于等于b的长度时，如果b比a短，保留a多出的位
// 否则不保留
strncpy(a,b,n);

// 返回字符串a中第一次出现字符串b的位置对应的字符指针p，未出现返回NULL
// 如char a[] = "abcd", b[] = "bc";则strstr(a,b)返回值等价于&a[1]
strstr(a,b);

//比较字符串a和b的字典序
strcmp(a,b);

//比较字符串a和b的字典序，最多比较n位
strncmp(a,b,n);