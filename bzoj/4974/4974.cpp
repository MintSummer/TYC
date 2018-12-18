#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

namespace TYC
{
	const int N = 100010;
	int n, cnt, nxt[N], ans[N];
	bool vis[N][26];
	
	inline int read()
	{
		int x = 0, f = 0; char ch = getchar();
		while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		return f ? -x : x;
	}
	
	void work()
	{
		n = read();
		for (int i = 1; i <= n; i++)
			nxt[i] = i - read();
		ans[1] = 0;
		for (int i = 2; i <= n; i++)
			if (nxt[i]) ans[i] = ans[nxt[i]];
			else
			{
				for (int tmp = i - 1; tmp; tmp = nxt[tmp])
					vis[i][ans[tmp + 1]] = true;
				for (int j = 1; j < 26; j++)
					if (!vis[i][j]) {ans[i] = j;break;}
			}
		for (int i = 1; i <= n; i++)
			printf("%c", ans[i] + 'a');
	}
}

int main()
{
	TYC::work();
	return 0;
}
