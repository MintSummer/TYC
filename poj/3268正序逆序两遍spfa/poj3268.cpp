//用floyd过不去1000的O(n3) 
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<string>
using namespace std;
struct edge
{
	int to,next,w;
}e1[100010],e2[100010];
//由于是单向边，故我们设定从i到j为去，从j到i为回，进行两次spfa单源最短路径，统一起点

int n,m,x,ans=0,cnt1=0,cnt2=0,head1[1010],head2[1010];
int f1[1010],f2[1010],vis[1010];
queue<int> q1,q2;

void add1(int u,int v,int w)
{
	cnt1++;
	e1[cnt1].to=v;
	e1[cnt1].next=head1[u];
	e1[cnt1].w=w;
	head1[u]=cnt1;
}

void add2(int u,int v,int w)
{
	cnt2++;
	e2[cnt2].to=v;
	e2[cnt2].next=head2[u];
	e2[cnt2].w=w;
	head2[u]=cnt2;
}

void spfa1(int s)
{
	int h,t;
	q1.push(s);
	vis[s]=1;
	f1[s]=0;
	while(!q1.empty())
	  {
	  	h=q1.front();
	  	q1.pop();
	  	vis[h]=0;
	  	for(int i=head1[h];i!=0;i=e1[i].next)
	  	  {
	  	  	t=e1[i].to;
	  	  	if(f1[t]>f1[h]+e1[i].w)
	  	  	  {
	  	  	  	f1[t]=f1[h]+e1[i].w;
	  	  	  	if(vis[t]==0)
	  	  	  	  {
	  	  	  	  	vis[t]=1;
	  	  	  	  	q1.push(t);
	  	  	  	  }
	  	  	  }
	  	  }
	  }
}

void spfa2(int s)
{
	int h,t;
	q2.push(s);
	vis[s]=1;
	f2[s]=0;
	while(!q2.empty())
	  {
	  	h=q2.front();
	  	q2.pop();
	  	vis[h]=0;
	  	for(int i=head2[h];i!=0;i=e2[i].next)
	  	  {
	  	  	t=e2[i].to;
	  	  	if(f2[t]>f2[h]+e2[i].w)
	  	  	  {
	  	  	  	f2[t]=f2[h]+e2[i].w;
	  	  	  	if(vis[t]==0)
	  	  	  	  {
	  	  	  	  	vis[t]=1;
	  	  	  	  	q2.push(t);
	  	  	  	  }
	  	  	  }
	  	  }
	  }
}

int main()
{
	scanf("%d%d%d",&n,&m,&x);
	memset(f1,0x3f3f3f3f,sizeof(f1));
	memset(f2,0x3f3f3f3f,sizeof(f2));
	memset(vis,0,sizeof(vis));
	int a,b,l;
	for(int i=1;i<=m;i++)
	  {
	  	scanf("%d%d%d",&a,&b,&l);
	  	add1(a,b,l);
	  	add2(b,a,l);
	  } 
	spfa1(x);
	memset(vis,0,sizeof(vis));
	spfa2(x);
	for(int i=1;i<=n;i++)
	  ans=max(ans,f1[i]+f2[i]);
	printf("%d",ans);
	return 0;
}