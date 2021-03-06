//应该是正解吧...但它WA了
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

namespace TYC
{
    const int N=1010;
    int n,worm[N],succ[N],fail[N],leaf[N],son[N][N],cnt[N];

    void init()
    {		
    	memset(fail,0,sizeof(fail));
		memset(succ,0,sizeof(succ));
		memset(leaf,0,sizeof(leaf));
		memset(worm,0,sizeof(worm));
		memset(cnt,0,sizeof(cnt));
    }

    bool cmp(int a,int b)
    {
		return (fail[a]+2)*leaf[b]<(fail[b]+2)*leaf[a];//不要除,会有精度问题
    }

    void dfs(int u)
    {
		if(!cnt[u]) {leaf[u]=1;return;}
		for(int i=1;i<=cnt[u];i++)
		{
			int v=son[u][i];
			dfs(v);
			if(worm[v]) fail[v]=0;
			fail[u]+=fail[v]+2;
			leaf[u]+=leaf[v];
		}
		sort(son[u]+1,son[u]+1+cnt[u],cmp);
		int sum=0;//sum记录访问过的子节点的失败次数之和
		for(int i=1;i<=cnt[u];i++)
		{
			int v=son[u][i];
			succ[u]+=(sum+1)*leaf[v]+succ[v];
			sum+=fail[v]+2;
		}
    }

    void work()
    {
		while(scanf("%d",&n)&&n)
		{
			init();
			int x;char ch[3];
			for(int i=1;i<=n;i++)
			{
				scanf("%d%s",&x,ch);
				if(x!=-1) son[x][++cnt[x]]=i;
				if(ch[0]=='Y') worm[i]=1;
			}
			dfs(1);
			double ans=(double)succ[1]/leaf[1];
			printf("%.4lf\n",ans);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
