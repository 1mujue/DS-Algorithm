#include <stdio.h>
#include <math.h>
#define MIN(a,b) (a) > (b) ? (b) : (a)
#define MAX(a,b) (a) > (b) ? (a) : (b)
#define EPS 1e-6
double getDistance(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5)
{
    double a,b,c,d,e,f;
    double r2, temp, d2;
    double x,y;
    a = (double)x1 - x2;
    c = (double)x1 - x3;
    b = (double)y1 - y2;
    d = (double)y1 - y3;
    e = ((double)(x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2;
    f = ((double)(x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2;
    x = (e * d - f * b) / (a * d - b * c);// the x of the center of the circle
    y = (e * c - f * a) / (c * b - a * d);// the y of the center of the circle
    r2 = ((x - x1) * (x - x1) + (y - y1) * (y - y1) + (x - x2) * (x - x2) + (y - y2) * (y - y2) + (x - x3) * (x - x3) + (y - y3) * (y - y3)) / 3;
    temp = (y4 - y5) * x - (x4 - x5) * y + x4 * y5 - x5 * y4;
    d2 = temp * temp / ((double)(x4 - x5) * (x4 - x5) + (y4 - y5) * (y4 - y5));// the square of the distance from the center of the circle to the line
    if (d2 - r2 > EPS)
    {
        return (sqrt(d2) - sqrt(r2));
    }
    else
    {
        return 0.0;
    }
}

//针对三个基本计算几何的问题：1.向量p1在向量p2的顺时针侧还是逆时针侧？（同起点）
//2.经过向量p1到向量p2，中途需要左转还是右转？（向量p2的起点是向量p1的终点）
//3.两个向量线段p1，p2是否相交？
//因为计算精度问题，直接采用斜率计算，然后求交点的方法不准确！我们采用叉乘来判断。

typedef struct point
{
    double x;
    double y;
}P;

double getDirection(P a1, P a2,P k)//求向量a1 - k和a2 - k的叉积
{
    return (a1.x - k.x) * (a2.y - k.y) - (a1.y - k.y) * (a2.x - k.x);
}

int onSegement(P a1,P a2,P k)//求点k是否在线段a1-a2上
{
    double minx = MIN(a1.x,a2.x);
    double miny = MIN(a1.y,a2.y);
    double maxx = MAX(a1.x,a2.x);
    double maxy = MAX(a1.y,a2.y);
    if(minx <= k.x && k.x <= maxx && miny <= k.y && k.y <= maxy)
        return 1;
    else
        return 0;
}

int isClockWise(P a1,P a2,P k)//判断a2是否在a1的顺时针方向。注意此处传入的a1，a2是p1和p2的终点，k是它们的共同起点
{
    if(getDirection(a1,a2,k) < 0)
        return 1;
    else
        return 0;
}//判断左右转的方向也很简单，只需要将p1的起点与p2的终点连接，求得一个新的向量，然后再判断顺时针还是逆时针就可以了

int isSegmentIntersect(P a1,P a2,P b1,P b2)
{
    double d1 = getDirection(a1,a2,b1);
    double d2 = getDirection(a1,a2,b2);
    double d3 = getDirection(b1,b2,a1);
    double d4 = getDirection(b1,b2,a2);
    if((d1 > 0 && d2 < 0 || d1 < 0 && d2 > 0) && (d3 > 0 && d4 < 0 || d3 < 0 && d4 > 0))
        return 1;
    else if(fabs(d1) < EPS && onSegement(a1,a2,b1))
        return 1;
    else if(fabs(d2) < EPS && onSegement(a1,a2,b2))
        return 1;
    else if(fabs(d3) < EPS && onSegement(b1,b2,a1))
        return 1;
    else if(fabs(d4) < EPS && onSegement(b1,b2,a2))
        return 1;
    else
        return 0;
}


//precise version.
int VectorMult(long long x1,long long y1,long long x2,long long y2,long long x0,long long y0)
{
    long long dx1 = x1 - x0,dy1 = y1 - y0,dx2 = x2 - x0,dy2 = y2 - y0;
    if(dx1 * dy2 - dx2 * dy1 < 0)
        return -1;
    else if(dx1 * dy2 - dx2 * dy1 > 0)
        return 1;
    else
        return 0;
}
int Segment(long long x1,long long y1,long long x2,long long y2,long long x0,long long y0)
{
    if(x1 <= x0 && x0 <= x2 && y1 <= y0 && y0 <= y2 || x2 <= x0 && x0 <= x1 && y2 <= y0 && y0 <= y1)
        return 1;
    else
        return 0;
}
int Parallel(long long x1,long long y1,long long x2,long long y2,long long x3,long long y3,long long x4,long long y4)
{
    long long dx1 = x1 - x2,dy1 = y1 - y2,dx2 = x3 - x4,dy2 = y3 - y4;
    if(dx1 * dy2 == dx2 * dy1)
        return 1;
    else
        return 0;
}

double distance(long long x1,long long y1,long long x2,long long y2,long long x0,long long y0)
{
    long long dx1,dx2,dy1,dy2,dx3,dy3;
    dx1 = x1 - x0;
    dx2 = x2 - x0;
    dx3 = x2 - x1;
    dy1 = y1 - y0;
    dy2 = y2 - y0;
    dy3 = y2 - y1;

    double dis0;
    dis0 = fabs(-dx1 * dy3 + dy1 * dx3) / sqrt(dx3 * dx3 + dy3 * dy3);
    return dis0;
}