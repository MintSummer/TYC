#include<cstdio>
#include<algorithm>
#include<iostream>
#include<string>
using namespace std;
int n,m,lt[100010],rt[100010];
int c[100010],cnt;
bool apple[100010];
struct edge
{
	int to;
	int next;
}e[200010];
int head[100010],ccnt;
void add(int a,int b)
{
	e[++ccnt]=(edge){b,head[a]};
	head[a]=ccnt;
}
void dfs(int u,int fa)
{
	lt[u]=++cnt;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==fa)continue;
		dfs(v,u);
	}
	rt[u]=cnt;
}
void change(int i,int x)
{
	while(i<=n)
	{
		c[i]+=x;
		i+=(i&(-i));
	}
}
int sum(int a)
{
	int ans=0;
	while(a>0)
	{
		ans+=c[a];
		a-=(a&(-a));
	}
	return ans;
}
int main(void)
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)apple[i]=true,change(i,1);
	scanf("%d",&m);
	while(m--)
	{
		char s[50];
		int a;
		scanf("%s%d",s,&a);
		char c=s[0];
		if(c=='Q')
			printf("%d\n",sum(rt[a])-sum(lt[a]-1));
		else
			if(apple[a])
				apple[a]=false,change(lt[a],-1);
			else
				apple[a]=true,change(lt[a],1);
	}
	return 0;
}
