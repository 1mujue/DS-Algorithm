// problem link: https://leetcode.cn/problems/total-characters-in-string-after-transformations-ii/description/
#define LEN 26
#define MOD 1000000007
#define ll long long

// let's define f[i][j], which is after i time transformation, the number of
// alpha 'a' + j. Clearly, j is in [0, 25]. then, f[i + 1][j] =
// \Sigma{k=0}^{25}(f[i][k] * flag[k][j]). If (j + 25 - k) % 25 <= nums[k], then
// flag[k][j] here is 1, otherwise it is 0. Obviously, flag[k][j] is
// determinated by nums and will never change!! We can use fast pow of matrix
// multiplying to handle the problem.

typedef struct Matrix
{
    int row;
    int col;
    ll **mat;
} Mat;

void initMat(Mat *m)
{
    m->mat = (ll **)malloc(sizeof(ll *) * m->row);
    for (int i = 0; i < m->row; i++)
    {
        m->mat[i] = (ll *)calloc(m->col, sizeof(ll));
    }
}

void freeMat(Mat *obj)
{
    for (int i = 0; i < obj->row; i++)
    {
        free(obj->mat[i]);
    }
    free(obj->mat);
}

void printMat(Mat *obj)
{
    for (int i = 0; i < obj->row; i++)
    {
        for (int j = 0; j < obj->col; j++)
        {
            printf("%lld ", obj->mat[i][j]);
        }
        printf("\n");
    }
}

Mat multMat(Mat a, Mat b)
{
    Mat ret;
    ret.row = a.row;
    ret.col = b.col;
    initMat(&ret);

    for (int i = 0; i < a.row; i++)
    {
        for (int j = 0; j < b.col; j++)
        {
            for (int k = 0; k < a.col; k++)
            {
                ret.mat[i][j] =
                    (ret.mat[i][j] + a.mat[i][k] * b.mat[k][j] % MOD) % MOD;
            }
        }
    }
    return ret;
}
Mat fastpowMat(Mat ori, int index)
{
    Mat ans;
    ans.row = ori.row, ans.col = ori.col;
    initMat(&ans);

    for (int i = 0; i < ans.row; i++)
    {
        ans.mat[i][i] = 1;
    }

    Mat base;
    base.row = ori.row;
    base.col = ori.col;
    initMat(&base);

    for (int i = 0; i < base.row; i++)
    {
        for (int j = 0; j < base.col; j++)
        {
            base.mat[i][j] = ori.mat[i][j];
        }
    }

    while (index)
    {

        if (index & 1)
        {
            Mat orians = ans;
            ans = multMat(ans, base);
            freeMat(&orians);
        }
        Mat oribase = base;
        base = multMat(base, base);
        freeMat(&oribase);
        index >>= 1;
    }
    return ans;
}

int lengthAfterTransformations(char *s, int t, int *nums, int numsSize)
{
    Mat trans;
    trans.row = trans.col = LEN;
    initMat(&trans);

    for (int i = 0; i < 26; i++)
    {
        for (int j = 1; j <= nums[i]; j++)
        {
            int ind = (i + j) % LEN;
            trans.mat[i][ind]++;
        }
    }

    Mat vec;
    vec.row = 1;
    vec.col = LEN;
    initMat(&vec);

    int slen = strlen(s);
    for (int i = 0; i < slen; i++)
    {
        vec.mat[0][s[i] - 'a']++;
    }

    Mat fp = fastpowMat(trans, t);
    Mat ans = multMat(vec, fp);

    int ret = 0;
    for (int i = 0; i < 26; i++)
    {
        ret = (ret + ans.mat[0][i]) % MOD;
    }
    return ret;
}