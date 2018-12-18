#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1010;
int T,to[MAXN],st[MAXN],cnt,num,Head[MAXN],dp[MAXN];
ll n,h,r,x[MAXN],y[MAXN],z[MAXN];

struct edge
{
	int to,next;
}E[MAXN*MAXN];

inline void add(int u,int v)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
}

inline long long read()
{
	long long x=0;
	int f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') {f|=(ch=='-');ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+(ch-'0');ch=getchar();}
	return f==0?x:-x; 
}

inline ll dis(int i,int j)
{
	return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])+(z[i]-z[j])*(z[i]-z[j]);
}

int dfs(int u)
{
	if(~dp[u]) return dp[u];
	if(to[u]) return dp[u]=1;
	dp[u]=0;
	for(int i=Head[u];i;i=E[i].next)
	{
		dp[u]|=dfs(E[i].to);
		if(dp[u]) return 1;
	}
	return dp[u];
}

int main()
{
	T=read();
	for(int tim=1;tim<=T;tim++)
	{
		n=read(),h=read(),r=read();
		cnt=num=0;
		memset(Head,0,sizeof(Head));
		memset(to,0,sizeof(to));
		memset(dp,-1,sizeof(dp));
		
		for(int i=1;i<=n;i++)
		{
			x[i]=read(),y[i]=read(),z[i]=read();
			if(z[i]<=r) st[++num]=i;
			if(z[i]+r>=h) to[i]=1;
		}
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				if(i!=j&&dis(i,j)<=4*r*r) add(i,j),add(j,i);
				
		int flag=0;
		for(int i=1;i<=num;i++)
			if(dfs(st[i])) {flag=1;break;}
			
		if(flag) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
} 
