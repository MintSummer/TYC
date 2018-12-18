//µ¥¹þÏ£ AÁË
#include <map>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const ll seed = 233, p = 1e9 + 7;
	const int N = 4e6+10;
	int TotalS, TotalT, n, m, ans;
	ll Pow[N], Hash[N];
	string str[40010];
	map<ll, int> times;

	inline void init(int len)
	{
		Pow[0] = 1;
		for (int i = 1; i <= len; i++)
			Pow[i] = Pow[i - 1] * seed % p;
	}

	inline ll hash(string &s, int l, int r)
	{
		ll ans = s[l];
		for (int i = l + 1; i < r; i++)
			ans = (ans * seed + s[i]) % p;
		return ans;
	}

	inline void get_hash(string &s, int len)
	{
		Hash[0] = s[0];
		for (int i = 1; i < len; i++)
			Hash[i] = (Hash[i - 1] * seed + s[i]) % p;
		for (int i = len, lim = (len << 1); i < lim; i++)
			Hash[i] = (Hash[i - 1] * seed + s[i - len]) % p;
	}

	inline ll hash_init(string &s, int l, int r)
	{
		int len = r - l + 1;
		if (!l)	return Hash[r];
		else return (Hash[r] - Hash[l - 1] * Pow[len] % p + p) % p;
	}

	inline void match(string &s, int len, ll to, int matchlen)
	{
		for (int i = 0; i < len; i++)
			if (hash_init(s, i, i + matchlen - 1) == to)
			{
				int start = i + matchlen;
				ans += times[hash_init(s, start, start + (len - matchlen) - 1)];
			}
	}

	void work()
	{
		ios::sync_with_stdio(false);
		cin.tie(0);
		cin >> TotalS >> TotalT >> n >> m;
		if ((n + m) & 1) {puts("0"); return;}
		int len = (n + m) / 2;
		init(len);
		for (int i = 1; i <= TotalS; i++) cin >> str[i];
		string x;
		for (int i = 1; i <= TotalT; i++)
		{
			cin >> x;
			times[hash(x, 0, x.size())]++;
		}
		for (int i = 1;i <= TotalS; i++)
		{
			get_hash(str[i], len);
			match(str[i], len, hash(str[i], len, n), n - len);
		}
		cout << ans << "\n";
	}
}

int main()
{
	TYC::work();
	return 0;
}
