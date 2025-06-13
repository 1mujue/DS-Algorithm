#include <stdio.h>
#define VOLUME 1000007

// st[i] == 0 means i is a prime number.
// primes[i] is the i-th prime number.
int st[VOLUME],primes[VOLUME];
// cnt is the count of primes.
int cnt;

void Euler(int n)
{
    for(int i = 2;i <= n;i++)
    {
        if(st[i] == 0)
            primes[cnt++] = i;
        for(int j = 0; j < cnt && (long long)primes[j] * i <= n ;j++)
        {
            st[primes[j] * i] = 1;
            if(i % primes[j] == 0){
                // i % primes[j] == 0
                // so i must have been marked by primes[j] before.
                // and i * primes[j + 1], ..., i * primes[cnt - 1] 
                // must be marked by primes[j] as well.
                // so we can break here.
                break;
            }
        }
    }
}