#include <stdio.h>
#include <stdlib.h>

#include "pre/PreMSS.h"
#include "tools/Number.h"

void PreMSSEntryPoint(int argc, char *argv[])
{

	printf("start MSSS test.\n");

	int nn;
	scanf("%d", &nn);
	int *arr = (int *)malloc(sizeof(int) * nn);

	for (int i = 0; i < nn; ++i)
	{
		scanf("%d", arr + i);
	}

	int ans = PreMSSSolution(arr, 0, nn);
	printf("The max sum of sub sequence is: %d\n", ans);

	free(arr);

	printf("end MSSS test.\n");
}

int PreMSSSolution(int *arr, int begin, int end)
{
	int ans1 = PreMSSDivideAndConquer(arr, begin, end);
	int ans2 = PreMSSLinear(arr, begin, end);
	if(ans1 == ans2){
		return ans1;
	}
	return -1;
}

// The max sum of a sequence can ONLY be found in three parts:
// The former half, the latter half, and across the two parts.
// Therefore, we caculate the former half part and the latter half part
// recursively, and caculate the crossing part individually.
// The time complexity is O(NlogN)
int PreMSSDivideAndConquer(int* arr, int begin, int end){
	if (begin != end - 1)
	{
		int mid = begin + (end - begin) / 2;

		int ans1 = PreMSSDivideAndConquer(arr, begin, mid);
		int ans2 = PreMSSDivideAndConquer(arr, mid, end);
		int ans3 = 0, subans1 = 0, subans2 = 0, tmp;

		tmp = 0;
		for (int i = mid - 1; i >= begin; --i)
		{
			tmp += arr[i];
			if (tmp > subans1) { subans1 = tmp; }
		}

		tmp = 0;
		for (int i = mid; i < end; ++i)
		{
			tmp += arr[i];
			if (tmp > subans2) { subans2 = tmp; }
		}

		ans3 = subans1 + subans2;
		return MAX(MAX(ans1, ans2), ans3);
	}
	else
	{
		return arr[begin];
	}
}

//
int PreMSSLinear(int* arr, int begin, int end){
	int ans = 0;
	int tmp = 0;

	for(int i = begin; i < end; ++i){
		tmp += arr[i];
        if(tmp < 0){
			tmp = 0;
		}
		if(tmp > ans){
			ans = tmp;
		}
	}
	
	return ans;
}