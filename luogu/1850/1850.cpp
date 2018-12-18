#include<bits/stdc++.h>
using namespace std;
const int MAXN=2010;
int n,m,v,e,c[MAXN],d[MAXN];
double k[MAXN],dp[MAXN][MAXN][2],G[310][310];

int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return x;
}

double fread()
{
    double x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    if(ch=='.')
    {
    double t=0.1;
    ch=getchar();
    while(ch>='0'&&ch<='9') {x=x+(ch-'0')*t;t/=10;ch=getchar();}
    }
    return x;
}

void flyod()
{
    for(int k=1;k<=v;k++)
    for(int i=1;i<=v;i++)
        for(int j=1;j<i;j++)
        if(G[i][j]>G[i][k]+G[k][j])
            G[i][j]=G[i][k]+G[k][j],G[j][i]=G[i][j];

}

int main()
{
    n=read(),m=read(),v=read(),e=read();
    for(int i=1;i<=n;i++) c[i]=read();
    for(int i=1;i<=n;i++) d[i]=read();
    for(int i=1;i<=n;i++) k[i]=fread();

    for(int i=1;i<=v;i++) 
		for(int j=1;j<i;j++) 
			G[i][j]=G[j][i]=0x3f3f3f3f;//强烈建议double不要用memset 
    int u,v;
	double w;
    for(int i=1;i<=e;i++)
    {
		u=read(),v=read(),w=fread();
    	G[u][v]=G[v][u]=min(G[u][v],w);
    }
    flyod();

    for(int i=1;i<=n;i++)
    	for(int j=0;j<=m;j++)
    		for(int k=0;k<2;k++)
    			dp[i][j][k]=0x3f3f3f3f;
    dp[1][0][0]=0.0,dp[1][1][1]=0.0;
    for(int i=2;i<=n;i++)
    for(int j=0;j<=min(m,i);j++)
    {
        dp[i][j][0]=min(
            dp[i-1][j][0]+G[c[i-1]][c[i]],
            dp[i-1][j][1]+k[i-1]*G[d[i-1]][c[i]]
            +(1.0-k[i-1])*G[c[i-1]][c[i]]);
        if(j>=1)
        dp[i][j][1]=min(
            dp[i-1][j-1][0]+k[i]*G[c[i-1]][d[i]]
            +(1.0-k[i])*G[c[i-1]][c[i]],
            dp[i-1][j-1][1]+k[i-1]*k[i]*G[d[i-1]][d[i]]
            +k[i-1]*(1.0-k[i])*G[d[i-1]][c[i]]
            +(1.0-k[i-1])*k[i]*G[c[i-1]][d[i]]
            +(1.0-k[i-1])*(1.0-k[i])*G[c[i-1]][c[i]]);
    }
    double ans=0x3f3f3f3f;
    for(int i=0;i<=m;i++)
    	for(int j=0;j<2;j++)
    		ans=min(ans,dp[n][i][j]);
    printf("%.2lf",ans);
    return 0;
}
