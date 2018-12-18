#include<bits/stdc++.h>
using namespace std;
const int MAXN=200010*2;
int n,m,cnt=0,k,Head[MAXN],get[MAXN];
int vis[MAXN],des[MAXN],fa[MAXN],ans[MAXN];

struct edge
{
	int from,to,next;
}E[MAXN];

void add(int u,int v)
{
	cnt++;
	E[cnt].from=u;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
}

int find(int a)
{
	return fa[a]==a?a:fa[a]=find(fa[a]);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) fa[i]=i;
	int a,b;
	for(int i=0;i<m;i++)
	  {
	  	scanf("%d%d",&a,&b);
	  	add(a,b);
	  	add(b,a);
	  }
	scanf("%d",&k);
	for(int i=0;i<k;i++)
	  scanf("%d",&des[k-i]),vis[des[k-i]]=1;
	int u,v,fu,fv;
	int tot=n-k;
	for(int i=1;i<=cnt;i++)
	  {
	  	u=E[i].from,v=E[i].to;
	  	fu=find(u),fv=find(v);
	  	if(!vis[u]&&!vis[v]&&fu!=fv)
	  	  fa[fu]=fv,tot--;
	  }
	ans[1]=tot;
	for(int i=1;i<=k;i++)
	  {
		u=des[i],vis[u]=0;
		tot++;
		for(int j=Head[u];j;j=E[j].next)
		  {
		  	v=E[j].to;
		  	if(vis[v]) continue;
		  	fu=find(u),fv=find(v);
		  	if(fu!=fv) fa[fu]=fv,tot--;
		  }
		ans[i+1]=tot;
	  }
	for(int i=k+1;i>0;i--)
	  printf("%d\n",ans[i]);
	return 0;
}
