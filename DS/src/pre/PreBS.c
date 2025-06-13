#include "pre/PreBS.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int CmpDemo(const void* e1, const void* e2)
{
    int a1 = *(int*)e1;
    int a2 = *(int*)e2;
    if(a1 < a2)
        return -1;
    else if(a1 > a2)
        return 1;
    else
        return 0;
}

// We presume that the data type is int.
void PreBSEntryPoint(int argc, char* argv[])
{
    printf("start binary search test.\n");

    int nn;
    int dst;
    int *array = NULL;
    scanf("%d", &nn);
    array = (int*)malloc(sizeof(int) * nn);
    for(int i = 0;i < nn;++i)
        scanf("%d", &array[i]);
    scanf("%d", &dst);

    int index = PreBinarySearch(array, &dst, sizeof(int), 0, nn, CmpDemo);
    printf("The index of %d is %d\n", dst, index);

    free(array);
    printf("end binary search test.\n");
}

int PreBinarySearch(const void* arr, void* dst, int size, int begin, int end, Compare cmp)
{
    if(begin < end)
    {
        int low = begin, high = end;
        int mid;
        while(low < high)
        {
            mid = low + (high - low) / 2;
            void* tmp = (void*)((uint64_t)arr + size * mid);
            int res = cmp(tmp, dst);
            if(res < 0)
                low = mid + 1;
            else if(res > 0)
                high = mid;
            else if(res == 0)
                return mid;
        }
    }
    return -1;
}