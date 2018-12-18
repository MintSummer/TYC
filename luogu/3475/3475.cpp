#include<bits/stdc++.h>
using namespace std;
 
namespace TYC
{
    const int N=30,MX=(1<<13)+5;
 
    int n,m,ans=0x3f3f3f3f,s,G[N],bin[N],cnt[MX];
 
    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }
	
	inline int count(int x)
	{
		return cnt[x>>13]+cnt[x&((1<<13)-1)];
	}

	void dfs(int last,int A,int B,int num,int edge)
	{
		if(num==(n>>1))
		{
			if(edge<ans)
			   ans=edge,s=((A&bin[1])?A:B);
			return; 
		}
		for(int i=last+1;i<=n;i++)
			if(B&bin[i]) 
				dfs(i,A|bin[i],B^bin[i],num+1,edge-count(G[i]&A)+count(G[i]&B));
	}
 
    void work()
    {
        n=read(),m=read();
		bin[1]=1;
		for(int i=2;i<=n;i++) bin[i]=bin[i-1]<<1;
		for(int i=1;i<(1<<13);i++) cnt[i]=cnt[i>>1]+(i&1);
        for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			G[u]|=bin[v],G[v]|=bin[u];
		}
		int tot=(1<<(n+1))-1;
        dfs(0,0,tot,0,0);
		for(int i=1;i<=26;i++)
			if(s&bin[i]) printf("%d ",i);
    }
}
 
int main()
{
    TYC::work();
    return 0;
}

