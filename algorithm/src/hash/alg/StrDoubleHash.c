#include <stdio.h>
#include <string.h>
#define VOLUME 400007

const int base = 97;
const int _base = 137;
#define MOD 998244353
#define _MOD 10000007
#define ll long long

ll add(ll a, ll b, ll mod);
ll sub(ll a, ll b, ll mod);
ll mul(ll a, ll b, ll mod);
ll Hash(int a, int b);
ll _Hash(int a, int b);

ll hash[VOLUME];
ll rec[VOLUME];
ll _rec[VOLUME];
ll _hash[VOLUME];
char str[VOLUME];

int main()
{
	int q;
	int a, b, x, y;
	scanf(" %s", str);
	int len = strlen(str);
	int m;
	for (int i = 0; i < len; i++)
	{
		str[i + len] = str[i];
	}
	m = len;
	len *= 2;
	rec[0] = _rec[0] = 1;
	for (int i = 1; i <= len; i++)
	{
		rec[i] = mul(rec[i - 1], base, MOD);
		_rec[i] = mul(_rec[i - 1], _base, _MOD);
	}
	for (int i = 1; i <= len; i++)
	{
		hash[i] = add(mul(hash[i - 1], base, MOD), str[i - 1] - 'a' + 1,MOD);
		_hash[i] = add(mul(_hash[i - 1], _base, _MOD),str[i - 1] - 'a' + 1,_MOD);
	}

	scanf("%d", &q);
	while(q--)
	{
		scanf("%d%d%d%d",&a,&b,&x,&y);
		if(a > b)
			b += m;
		if(x > y)
			y += m;
		ll r1,_r1,r2,_r2;
		r1 = Hash(a, b);
		r2 = Hash(x, y);
		_r1 = _Hash(a, b);
		_r2 = _Hash(x, y);
		if(r1 == r2 && _r1 == _r2)
			printf("owo\n");
		else
			printf("qwq\n");
	}
	return 0;
}

ll add(ll a, ll b, ll mod)
{
	ll res = (a % mod + b % mod) % mod;
	return res;
}
ll sub(ll a, ll b, ll mod)
{
	ll res = ((a % mod + (mod - b) % mod) + mod) % mod;
	return res;
}
ll mul(ll a, ll b, ll mod)
{
	ll res = ((a % mod) * (b % mod)) % mod;
	return res;
}
ll Hash(int a, int b)
{
	ll res = sub(hash[b], mul(hash[a - 1], rec[b - a + 1],MOD),MOD);
	return res;
}
ll _Hash(int a, int b)
{
	ll res = sub(_hash[b], mul(_hash[a - 1], _rec[b - a + 1],_MOD),_MOD);
	return res;
}