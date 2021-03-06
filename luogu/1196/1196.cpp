#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<iostream>
using namespace std;

namespace TYC
{
    const int MAXN=30010;
    int T,fa[MAXN],before[MAXN],sum[MAXN];

    inline int read()
    {
		int x=0;char ch=getchar();
		while(!isdigit(ch)) ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return x;
    }

    int find(int x)
    {
		if(x==fa[x]) return x;
		int f=find(fa[x]);
		before[x]+=before[fa[x]];
		return fa[x]=f;
    }

    void work()
    {
		for(int i=1;i<=30000;i++) 
			fa[i]=i,sum[i]=1,before[i]=0;
		T=read();
		char ch[5];
		int x,y;
		while(T--)
		{
			scanf("%s%d%d",ch,&x,&y);
			if(ch[0]=='M')
			{
				int fx=find(x),fy=find(y);
				fa[fx]=fy;
				before[fx]=sum[fy];
				sum[fy]+=sum[fx];
			}
			else
			{
				int fx=find(x),fy=find(y);
				if(fx!=fy) printf("-1\n");
				else printf("%d\n",abs(before[x]-before[y])-1);
			}
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
