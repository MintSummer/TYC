#include<bits/stdc++.h>
using namespace std;
int n,m,cnt=0,Head[1010];
int fa[1010],vis[1010],d[1010];
struct edge
{
	int to,next;
}E[1010*1010];

void add(int u,int v)
{
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
	cnt++;
}

bool Path(int u)
{
	int v;
	for(int i=Head[u];i!=-1;i=E[i].next)
	  {
	  	v=E[i].to;
	  	if(vis[v]) continue;
	  	vis[v]=1;
	  	if(fa[v]==-1||Path(fa[v]))
	  	  {
	  	  	fa[v]=u;
	  	  	return true;
	  	  }
	  }
	return false;
}

void Hungary()
{
	memset(d,-1,sizeof(d));
	int ans=0;
	for(int i=0;i<m;i++)
	  {
	  	memset(vis,0,sizeof(vis));
	  	if(Path(i)) ans++;
	  	else break;
	  }
	printf("%d\n",ans);
	int q;
	for(int i=0;i<n;i++)
	  {
	  	q=fa[i];
	  	d[q]=i;
	  }
	for(int i=0;i<m;i++)
	  if(d[i]!=-1) printf("%d\n",d[i]);
	  else break;//因为必须按顺序做题，故无法匹配时就应退出 
}

int main()
{
	memset(Head,-1,sizeof(Head));
	memset(fa,-1,sizeof(fa));
	scanf("%d%d",&n,&m);
	int a,b;
	for(int i=0;i<m;i++)
	  {
	  	scanf("%d%d",&a,&b);
	  	add(i,a);
	  	add(i,b);
	  }
	Hungary();
	return 0;
}
