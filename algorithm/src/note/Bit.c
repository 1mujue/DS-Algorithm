////////////////////////////////////////////////////////
// makeBitOp(3, 6) => 00001111000
int makeBitOp(int low, int high)
{
    return ((1 << (high - low + 1)) - 1) << low;
}

int clearZero(int num, int low, int high)
{
    return num & (~makeBitOp(low, high));
}

int setOne(int num, int low, int high)
{
    return num | makeBitOp(low, high);
}

int flip(int num, int low, int high)
{
    return num ^ makeBitOp(low, high);
}

////////////////////////////////////////////////////////
//大小端转换 如十六进制0x12345678转换为0x78563412
unsigned int rev(unsigned int v)
{
    unsigned int rv;
    unsigned int c[4];
    c[0] = (v >> 24) & 0xFF;
    c[1] = (v >> 16) & 0xFF;
    c[1] <<= 8;
    c[2] = (v >> 8) & 0xFF;
    c[2] <<= 16;
    c[3] = v & 0xFF;
    c[3] <<= 24;

    rv = c[0] | c[1] | c[2] | c[3];
    return rv;
}
//补码逆置 如十六进制0x12345678转换为0x87654321
unsigned int inv(unsigned int v)
{
    unsigned int rv = 0;
    int i;
    for(i = 0; i < 16; ++i)
    {
        rv |= (v & (1 << i)) << (31 - 2 * i);
        rv |= (v & (1 << (31 - i))) >> (31 - 2 * i);
    }
    return rv;
}
