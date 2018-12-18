#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1000010;
ll dp[MAXN][2],ans;
int n,cnt=1,Head[MAXN],force[MAXN],vis[MAXN],lt,rt,duan;

int read()
{
    int x=0,f=0;char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

struct edge
{
    int to,next;
}E[MAXN*2];

void add(int u,int v)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    Head[u]=cnt;
}

void find_circle(int u,int pre)
{
    vis[u]=1;
    for(int i=Head[u];i;i=E[i].next)
	{
		int v=E[i].to;
		if((i^1)==pre) continue;
		if(vis[v]) 
		{
			lt=u,rt=v;
			duan=i;
			continue;
		}
		else find_circle(v,i);
    }
}

void dfs(int u,int pre)
{
    dp[u][0]=0,dp[u][1]=force[u];
    int v;
    for(int i=Head[u];i;i=E[i].next)
    {
		v=E[i].to;
		if(i==duan||(i^1)==duan||(i^1)==pre) continue;
		dfs(v,i);
		dp[u][0]+=max(dp[v][1],dp[v][0]);
		dp[u][1]+=dp[v][0];
    }
}

int main()
{
    n=read();
    int v;
    for(int i=1;i<=n;i++)
    {
		force[i]=read(),v=read();
		add(v,i),add(i,v);
    }
    for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			find_circle(i,-2);
			dfs(lt,-1);
			ll tmp=dp[lt][0];
			dfs(rt,-1);
			tmp=max(tmp,dp[rt][0]);
			ans+=tmp;
		}
    printf("%lld",ans);
    return 0;
}
