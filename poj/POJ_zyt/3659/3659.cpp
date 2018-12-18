#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct edge
{
	int to;
	int next;
} e[20010];
int head[10010],n,cnt,num[10010],fa[10010],ans;
bool vis[10010],s[10010],set[10010];
void add(int x,int y)
{
	e[cnt].to=y;
	e[cnt].next=head[x];
	head[x]=cnt;
	cnt++;
}
void dfs(int x)
{
	num[cnt++]=x;
	for(int i=head[x];i!=-1;i=e[i].next)
	{
		if(vis[e[i].to])continue;
		vis[e[i].to]=true;
		fa[e[i].to]=x;
		dfs(e[i].to);
	}
}
int main(void)
{
	memset(head,-1,sizeof(head));
	scanf("%d",&n);
	for(int i=0;i<n-1;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	cnt=0;
	dfs(1);
	for(int i=cnt-1;i>=0;i--)
	{
		int v=num[i];
		if(!s[v])
		{
			if(!set[fa[v]])
			{
				set[fa[v]]=true;
				ans++;
			}
			s[v]=true;
			s[fa[v]]=true;
			s[fa[fa[v]]]=true;
		}
	}
	printf("%d",ans);
	return 0;
}
