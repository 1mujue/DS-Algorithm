#include <stdio.h>
#include <limits.h>
// Problem: we need to calculate the maximum sum of a subarray.
// Algorithm: if the sum of the previous elements is greater than or equal to 0, 
// then adding the current element will definitely be BETTER than just the current element;
// If the sum of the previous elements is less than 0, then it is definitely better to JUST HAVE the current element.
int main()
{
    int n;
    scanf("%d",&n);
    int temp;
    int sum = 0;
    int ans = INT_MIN;
    for(int i = 0;i < n;i++)
    {
        scanf("%d",&temp);
        if(sum < 0) sum = 0;
        sum += temp;
        ans = fmax(sum, ans);
    }
    printf("%d",ans);
    return 0;
}