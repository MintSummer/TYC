#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef pair<int,int> pa;
    const int N=55;
    const int M=4005;
    const int MX=500000;
    const int inf=0x3f3f3f3f;

    int tot,n,m,a[M],b[M],c[M],w[M],money[M];
    int f[N][N][M],cnt[N][M];
    pa from[N][N][M];
    
    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    void get_money(const int l,const int r,const int val)
    {
		if(l>r) return;
		int v=from[l][r][val].second;
        int pos=from[l][r][v].first;
		if(!v||!pos) return;
        money[pos]=w[v];
        if(l!=r) get_money(l,pos-1,v),get_money(pos+1,r,v);
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=m;i++) 
            a[i]=read(),b[i]=read(),w[i]=c[i]=read();
        sort(w+1,w+1+m);
        tot=unique(w+1,w+1+m)-w-1;
        for(int i=1;i<=m;i++) 
            c[i]=lower_bound(w+1,w+1+tot,c[i])-w;
        for(int l=n;l;l--)
            for(int r=l;r<=n;r++)
            {
                for(int k=l;k<=r;k++)
				   	memset(cnt[k],0,sizeof(int[tot+1]));
                for(int k=1;k<=m;k++)
                    if(l<=a[k]&&b[k]<=r)
                        for(int p=a[k];p<=b[k];p++)
                            cnt[p][c[k]]++;
                for(int k=l;k<=r;k++)
                    for(int x=tot-1;x;x--) cnt[k][x]+=cnt[k][x+1];
                for(int k=tot;k;k--)
                {
                    int mx=0;
                    for(int p=l;p<=r;p++)
                    {
                        int t=f[l][p-1][k]+f[p+1][r][k]+cnt[p][k]*w[k];
                        if(t>mx) mx=t,from[l][r][k].first=p;
                    }
                    if(mx>=f[l][r][k+1]) f[l][r][k]=mx,from[l][r][k].second=k;
                    else f[l][r][k]=f[l][r][k+1],from[l][r][k].second=from[l][r][k+1].second;
                }
            }
        for(int i=1;i<=n;i++) money[i]=MX;
        get_money(1,n,1);
        printf("%d\n",f[1][n][1]);
        for(int i=1;i<=n;i++) printf("%d ",money[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
