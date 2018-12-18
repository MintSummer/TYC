#include <bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N = 17, MX = (1 << 13) + 100, Q = 110;
	int n, m, q, edge[N][N], a[Q], b[Q], lca[Q], bin[N], from[N], to[N];
	ll dp[N][MX];
	
	bool intree(int tree, int node)
	{
		return tree & bin[node];
	}
	
	ll dfs(int root, int tree)
	{
		ll &ans = dp[root][tree];
		if (~ans) return ans;
		ans = 0;
		int sub = tree ^ bin[root];
		int x = 1;
		for (; x <= n; x++)
			if (intree(sub, x)) break;
		for (int Subtree = sub; Subtree; Subtree = (Subtree - 1) & sub)
		{
			if (!intree(Subtree, x)) continue; // �޶������С�ĵ�Ϊ����㣬�����б������
			
			bool flag = false;
			for (int i = 1; i <= m; i++)
				if (from[i] != root && to[i] != root &&
				    intree(Subtree, from[i]) != intree(Subtree, to[i]))
					{flag = true; break;} // i��j �����ߵ�����ͬһ��������
			if (flag) continue;
			
			for (int i = 1; i <= q; i++)
			{
				if (lca[i] == root && intree(Subtree, a[i]) && intree(Subtree, b[i]))
					{flag = true; break;} // LCA Ϊ���� �������㶼��������
				if (intree(Subtree, lca[i]) && (!intree(Subtree, a[i]) || !intree(Subtree, b[i])))
					{flag = true; break;} // LCA �������У����������е㲻��������
			
			}
			if (flag) continue;
			
			int num = 0, son;
			for (int i = 1; i <= n; i++) 
				if (intree(Subtree, i) && edge[root][i])
					num++, son = i; // son ��Ϊ�������ĸ�
			if (num > 1) continue; // �����������ж������
			
			if (!num) // û�����Ƶı�
			{
				for (int i = 1; i <= n; i++)
					if (intree(Subtree, i))
						ans += dfs(i, Subtree) * dfs(root, tree ^ Subtree);
			}
			else
				ans += dfs(son, Subtree) * dfs(root, tree ^ Subtree); // ��Ҫ���� root ���������������
		}
		return ans;
	}
	
	void work()
	{
		ios::sync_with_stdio(false);
		cin.tie(0);
		cin >> n >> m >> q;
		int u, v;
		for (int i = 1; i <= m; i++)
		{
			cin >> u >> v;
			edge[u][v] = edge[v][u] = 1;
			from[i] = u, to[i] = v;
		}
		for (int i = 1; i <= q; i++)
			cin >> a[i] >> b[i] >> lca[i];
		bin[1] = 1;
		for (int i = 2; i <= n; i++)
			bin[i] = bin[i - 1] << 1;
		memset(dp, -1, sizeof(dp));
		for (int i = 1; i <= n; i++)
			dp[i][bin[i]] = 1;
		cout << dfs(1, (1 << n) - 1);
	}
}

int main()
{
	TYC::work();
	return 0;
}

