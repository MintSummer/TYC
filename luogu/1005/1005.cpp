#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef __int128 bll;
    const int N=90;
    int n,m,a[N],num[N<<2];
   	bll dp[N][N],mi[N];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void write(bll x)
	{
		int len=0;
		if(!x) putchar('0');
		while(x) num[++len]=(x%10),x/=10;
		while(len) 
			putchar(num[len--]+'0');
	}

    bll dfs(int l,int r)
    {
        bll &ans=dp[l][r];
        if(~ans) return ans;
		int now=m-(r-l);
        if(l==r) return ans=a[l]*mi[now];
        ans=max(a[l]*mi[now]+dfs(l+1,r),a[r]*mi[now]+dfs(l,r-1));
		return ans;
    }

    void work()
    {
		ios::sync_with_stdio(false);
		cin.tie(0);
		n=read(),m=read();
		mi[0]=1;
		for(int i=1;i<=m;i++) mi[i]=mi[i-1]*2;
		bll ans=0;
        for(int i=1;i<=n;i++)
		{
            for(int j=1;j<=m;j++) a[j]=read();
			memset(dp,-1,sizeof(dp));
			ans+=dfs(1,m);
		}
		write(ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
