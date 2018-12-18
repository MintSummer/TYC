#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N = 15010;

	int k, len, length, fail[N], last[N];
	char str[N], s[N];

	void KMP(const int start)
	{
		length = 0;
		for (int i = start; i <= len; i++) s[length++] = str[i];
		fail[0] = fail[1] = 0;
		for (int i = 1; i < length; i++)
		{
			int tmp = fail[i];
			while (tmp && s[tmp] != s[i])
			   tmp = fail[tmp];	
			fail[i + 1] = (s[tmp] == s[i]) ? tmp + 1: 0;
		}
	}
	
	int get_ans(const int start)
	{
		int ans = 0;
		memset(last, -1, sizeof(int[length + 1]));	
		for (int i = 1; i <= length; i++)
		{
			int f = fail[i];
			if (f && ~last[f]) last[i] = last[f];
			else if (i >= k) last[i] = i;
			if (~last[i] && (last[i] << 1) < i) ++ans;
		}
		return ans;
	}

	void work()
	{
		scanf("%s%d", str + 1, &k);
		len = strlen(str + 1);
		int ans = 0;
		for(int i = 1, t = len - (k << 1); i <= t; i++) 
			KMP(i), ans += get_ans(i);
		printf("%d\n", ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
