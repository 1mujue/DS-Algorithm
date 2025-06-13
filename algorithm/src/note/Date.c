////////////////////////////////////////////////////////////////////
// 判断是否是闰年 是返回1 不是返回0
int isLeap(int year)
{
    return (year % 4 == 0) && // 逢四则闰
           (year % 100 != 0) || // 百年不闰
           (year % 400 == 0); // 四百再闰
}

////////////////////////////////////////////////////////////////////
// 返回某年某月有多少天
int getDaysOfMonth(int year, int month)
{
    int days = 0;
    switch(month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        days = 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;
        break;
    case 2:
        days = isLeap(year) ? 29 : 28;
        break;
    }
    return days;
}

int getDaysOfMonth(int year, int month)
{
    int days[2][13]= {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                      {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
    int leap = isLeap(year);
    return days[leap][month];
}

////////////////////////////////////////////////////////////////////
#define YEAR(d) ((d) / 10000)
#define MONTH(d) (((d) / 100) % 100)
#define DAY(d) ((d) % 100)
#define LONGDAY(y, m, d) ((y) * 10000 + (m) * 100 + (d))

/////////////////////////////////////////////////////////////////////
//计算某年某月某日的下一天，注意会修改输入的year, month, day的值
int nextDay(int *year, int *month, int *day)
{
    int days = getDaysOfMonth(*year, *month);
    if(*day < days)
    {
        (*day)++;
    }
    else
    {
        *day = 1;
        if(*month < 12)
        {
            (*month)++;
        }
        else
        {
            (*month) = 1;
            (*year)++;
        }
    }
    return LONGDAY(*year, *month, *day);
}
//计算>=d的第一个能够表示为合法日期的8位数
int nextDate(int d)
{
    int year = YEAR(d), month = MONTH(d), day = DAY(d);
    if(month == 0)
    {
        return LONGDAY(year, 1, 1);
    }
    else if(month > 12)
    {
        return LONGDAY(year + 1, 1, 1);
    }
    else
    {
        if(day == 0)
            return LONGDAY(year, month, 1);
        else if(day <= getDaysOfMonth(year, month))
            return LONGDAY(year, month, day);
        else
        {
            return (month < 12) ? LONGDAY(year, month + 1, 1) : LONGDAY(year + 1, 1, 1);
        }
    }
}
