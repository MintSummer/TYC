//啦啦啦～树形背包dp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int MAXN=3010;
int n,m,cnt,Head[MAXN],money[MAXN],dp[MAXN][MAXN],val[MAXN],tmp[MAXN];
//dp[i][j]表示在以i为根的子树中，满足j的用户的最大利润

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

struct edge
{
    int to,next,w;
}E[MAXN*MAXN];

void add(int u,int v,int w)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    E[cnt].w=w;
    Head[u]=cnt;
}

int dfs(int u)
{
    if(u>n-m)//u为用户
		{dp[u][1]=money[u];return 1;}
    int v,tot=0;//tot表示u能连到的用户数
    for(int i=Head[u];i;i=E[i].next)
    {
		v=E[i].to;
		int t=dfs(v);
		for(int j=0;j<=tot;j++) tmp[j]=dp[u][j];
		//在背包中，dp[u][j]的值可能会改变，必须要先记下来
		for(int j=0;j<=tot;j++)//枚举需要u连j个用户
			for(int k=0;k<=t;k++)//枚举需要v连k个用户
				dp[u][j+k]=max(dp[u][j+k],tmp[j]+dp[v][k]-E[i].w);
		tot+=t;
    }
    return tot;
}

int main()
{
    n=read(),m=read();
    for(int u=1;u<=n-m;u++)
    {
		int x=read();
		for(int i=1;i<=x;i++)
		{
			int v=read(),w=read();
			add(u,v,w);
		}
    }
    for(int i=n-m+1;i<=n;i++) money[i]=read();
    memset(dp,-inf,sizeof(dp));//有负数
    for(int i=1;i<=n;i++) dp[i][0]=0;
    dfs(1);
    int ans;
    for(int i=m;i>=0;i--)
		if(dp[1][i]>=0) {ans=i;break;}
    printf("%d",ans);
    return 0;
}
