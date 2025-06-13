#define LEN 100002
// problem link: https://leetcode.cn/problems/largest-rectangle-in-histogram/description/

// the key of this problem: for each column(height is h), find the FIRST shorter column both in
// LEFT and RIGHT. Beacause they are restriction. If we want our rectangle's
// height is h, we must make sure all columns' heights are greater or equal to h.
// Monotonic Stack can solve the problem. If it is an increasing stack(from bottom to top),
// then, for column in stack[i](the index of it), the first shorter column is in stack[i - 1].
// If we have to pop the stack, it means we find the first shorter column for stack[i].
// Then, we can calculate the area of rectangle with height h and width (i - stack[i - 1] - 1).

// Here, since each operation we will pop the top element of stack, so i is top - 1.

// However, if the array is [2, 4, 6, 8], then we CAN'T find the first right shorter column for 8.
// Moreover, we can't find the first left shorter column for 2.
// So, we add two SENTINELS to the array, which are 0, and the array is [0, 2, 4, 6, 8, 0].
int largestRectangleArea(int *heights, int heightsSize)
{

    int h[LEN];
    h[0] = h[heightsSize + 1] = 0;
    for (int i = 0; i < heightsSize; i++)
        h[i + 1] = heights[i];

    int stack[LEN];
    int top = 0;

    int ans = 0;

    for (int i = 0; i < heightsSize + 2; i++)
    {
        while (top && h[i] < h[stack[top - 1]])
        {
            ans = fmax(ans, (i - stack[top - 2] - 1) * h[stack[top - 1]]);
            top--;
        }
        stack[top++] = i;
    }
    return ans;
}