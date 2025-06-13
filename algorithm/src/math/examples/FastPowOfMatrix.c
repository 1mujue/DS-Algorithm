#include <stdio.h>
#define Range 200
const int MOD = 1e9 + 7;
typedef struct Matrix
{
    long long matrix[Range][Range];
} M;

M matrixPow(M matrix, int index, int range);
M matrixMul(M matrix1, M matrix2, int range);

int main()
{
    int T, n;
    M Matrix;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                scanf("%lld", &Matrix.matrix[i][j]);
        }
        Matrix = matrixPow(Matrix, n, n);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                printf("%lld ", Matrix.matrix[i][j]);
            printf("\n");
        }
    }
    return 0;
}

M matrixPow(M matrix, int index, int range)
{
    M res;
    for (int i = 1; i <= range; i++)
    {
        for (int j = 1; j <= range; j++)
        {
            if (i == j)
                res.matrix[i][j] = 1;
            else
                res.matrix[i][j] = 0;
        }
    }
    while (index)
    {
        if (index % 2 == 1)
            res = matrixMul(res, matrix, range);
        matrix = matrixMul(matrix, matrix, range);
        index /= 2;
    }
    return res;
}
M matrixMul(M matrix1, M matrix2, int range)
{
    M res;
    for (int i = 1; i <= range; i++)
    {
        for (int j = 1; j <= range; j++)
            res.matrix[i][j] = 0;
    }
    for (int i = 1; i <= range; i++)
    {
        for (int j = 1; j <= range; j++)
        {
            for (int k = 1; k <= range; k++)
            {
                res.matrix[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
                res.matrix[i][j] %= MOD;
            }
        }
    }
    return res;
}