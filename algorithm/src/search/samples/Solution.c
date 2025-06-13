#include <stdio.h>
#include <math.h>
#define EPS 1e-7

// problem: given a, b, c, d (double), calculate the zero point of 
// a * x^3 + b * x^2 + c * x^1 + d. It is guaranteed that the 3 zero points
// would be in the range of [-100, 100], and the distance between each point
// is not smaller than 1.

// 秦九韶
double getVal(double a, double b, double c, double d, double x){
    return (((a * x) + b) * x + c) * x + d;
}

// we will NOT calculate the right boundary.
// Note that the function is consecutive, it lval * rval >= 0, then there is NO zero point in 
// [left, right) !
double solute(int* flag, double a, double b, double c, double d, double left, double right){
    double lval = getVal(a, b, c, d, left), rval = getVal(a, b, c, d, right);
    if(!lval) {
        *flag = 1;
        return left;
    }
    if(lval * rval >= 0) {
        *flag = 0;
        return -1000;
    }
    double mid;
    while(right - left > EPS){
        mid = (right + left) / 2;
        double mval = getVal(a, b, c, d, mid);
        if(getVal(a, b, c, d, mid) * getVal(a, b, c, d, right) <= 0){
            left = mid;
        }
        else{
            right = mid;
        }
    }
    *flag = 1;
    return mid;
}

int main(){
    double a, b, c, d;
    scanf("%lf%lf%lf%lf", &a, &b, &c, &d); 

    double ans[3];
    int ind = 0;
    for(int x = -100; x < 100; x++){
        int flag = 0;
        double t = solute(&flag, a, b, c, d, x, x + 1.0);
        if(flag) ans[ind++] = t;
    }
    if(ind != 3) printf("Error");
    for(int i = 0; i < ind; i++){
        printf("%.2f ", ans[i]);
    }
    return 0;
}