#include<bits/stdc++.h>
using namespace std;
map<string,int> id;
const int MAXN=4010*2;
int n,m,cnt,num,top,tot,Head[MAXN],st[MAXN];
int dfn[MAXN],low[MAXN],belong[MAXN],size[MAXN],vis[MAXN];

struct edge
{
    int to,next;
}E[20010+MAXN];

void add(int u,int v)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    Head[u]=cnt;
}

void Tarjan(int u)
{
    dfn[u]=low[u]=++num;
    st[++top]=u;
    vis[u]=1;
    int v;
    for(int i=Head[u];i;i=E[i].next)
    {
	v=E[i].to;
	if(!dfn[v])
	    Tarjan(v),low[u]=min(low[u],low[v]);
	else if(vis[v]) low[u]=min(low[u],dfn[v]);
    }

    if(dfn[u]==low[u])
    {

	int x;
	tot++;
	do
	{
	    x=st[top--];
	    vis[x]=0;
	    size[tot]++;
	    belong[x]=tot;
	}
	while(x!=u);
    }
}

int main()
{
    scanf("%d",&n);
    char a[15],b[15];
    for(int i=1;i<=n;i++)
    {
	scanf("%s%s",a,b);;
	id[a]=i,id[b]=i+n;
	add(i,i+n);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
	scanf("%s%s",a,b);
	add(id[b],id[a]);
    }

    for(int i=1;i<=2*n;i++)
	if(!dfn[i]) Tarjan(i);

    for(int i=1;i<=n;i++)
	if(belong[i]!=belong[i+n]) printf("Safe\n");
	else printf("Unsafe\n");
    return 0;
}
