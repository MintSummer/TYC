#include<bits/stdc++.h>
using namespace std;
const int MAXN=6010;
int n,cnt,head,Head[MAXN],happy[MAXN],fa[MAXN];
int vis[MAXN],t,que[MAXN];//que得出一个从叶子到根的顺序
int dp[MAXN][2];//dp[i][0\1]分别表示i这个人是否参加的最大值

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

inline void add(int u,int v)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    Head[u]=cnt;
}

void bfs()//用bfs而不用dfs，防止爆栈
{
    queue<int> q;
    q.push(head);
    vis[head]=1;
    que[++t]=head;
    while(!q.empty())
    {
		int u=q.front();
		q.pop();
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]) continue;
			vis[v]=1;
			q.push(v);
			que[++t]=v;
		}
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) happy[i]=read();
    int u,v;
    for(int i=1;i<=n;i++)
    {
		v=read(),u=read();
		if(u==0&&v==0) break;
		fa[v]=u;
		add(u,v);
    }
    for(int i=1;i<=n;i++) 
		if(!fa[i]) head=i;
    bfs();
    for(int i=t;i;i--)//从叶子开始倒着推
    {
		int u=que[i];
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			dp[u][0]+=max(dp[v][0],dp[v][1]);
			dp[u][1]=max(dp[u][1],dp[u][1]+dp[v][0]);//小心，有负数,要取最大值
		}
		dp[u][1]+=happy[u];
    }
    printf("%d",max(dp[head][0],dp[head][1]));
    return 0;
}
