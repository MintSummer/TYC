#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=510;
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void work()
	{
		int T=read();
		static int fa[N],son[N],vis[N];
		static queue<int> q;
		while(T--)
		{
			int n=read(),k=read();
			memset(son,0,sizeof(int[n+1]));
			memset(vis,0,sizeof(int[n+1]));
			for(int i=2;i<=n;i++) 
				fa[i]=read(),son[fa[i]]++;
			while(!q.empty()) q.pop();
			for(int i=1;i<=n;i++)
				if(!son[i]) q.push(i);
			int flag=1;
			while(!q.empty())
			{
				int u=q.front(),f=fa[u];q.pop();
				if(!f||vis[f]) {flag=0;break;}
				vis[u]=1,vis[f]=1;
				son[fa[f]]--;
				if(!son[fa[f]]) q.push(fa[f]);
			}	
			if(flag&&k>=n/2-1) puts("Bob");
			else puts("Alice");
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
