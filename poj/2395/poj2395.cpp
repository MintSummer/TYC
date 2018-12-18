#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<string>
using namespace std;
int n,m,cnt=0,ans=0,c=0;
int fa[2010];
struct edge
{
	int f,e,len;
}G[10010];

bool cmp(edge a,edge b)
{
	return a.len<b.len;
}

int find(int a)
{
	return fa[a]==a?a:fa[a]=find(fa[a]);
}

void kruskal()
{
	int a,b,FA,FB;
	for(int i=1;i<=m;i++)
	  {
	  	a=G[i].f,b=G[i].e;
	  	FA=find(a),FB=find(b);
	  	if(FA!=FB)
	  	  {
	  	  	fa[FA]=FB;
	  	  	ans=max(ans,G[i].len);
	  	  }
	  }
	printf("%d",ans);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i;
	int a,b,l;
	for(int i=1;i<=m;i++)
	  {
	  	scanf("%d%d%d",&a,&b,&l);
	  	cnt++;
	  	G[cnt].f=a,G[cnt].e=b,G[cnt].len=l;
	  }
	sort(G+1,G+1+m,cmp);
	kruskal();
	return 0;
}