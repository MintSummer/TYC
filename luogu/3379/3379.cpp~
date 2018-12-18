#include<bits/stdc++.h>
using namespace std;
const int MAXN=500010;
int n,m,s,cnt,len;
int Head[MAXN],oula[MAXN*2],fir[MAXN],dep[MAXN],fa[MAXN*2][25],log_2[MAXN*2];

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

void dfs(int u,int f)
{
	int v;
	oula[++len]=u;
	fir[u]=len;
	dep[u]=dep[f]+1;
	for(int i=Head[u];i;i=E[i].next)
	{
		v=E[i].to;
		if(v==f) continue;
		dfs(v,u);
		oula[++len]=u;
	}
}

void init()
{
	log_2[1]=0;
	for(int i=2;i<=len;i++)
		log_2[i]=log_2[i>>1]+1;
	for(int i=1;i<=len;i++) fa[i][0]=oula[i];
	for(int i=1;i<=20;i++)
		for(int j=1;j<=len-(1<<(i-1))+1;j++)
			if(dep[fa[j][i-1]]>dep[fa[j+(1<<(i-1))][i-1]])
				fa[j][i]=fa[j][i-1];
			else fa[j][i]=fa[j+(1<<(i-1))][i-1];
	
}

int getans(int u,int v)
{
	int lt=fir[u],rt=fir[v];
	if(lt>rt) swap(lt,rt);
	int k=log_2[rt-lt+1];
	if(dep[fa[lt][k]]<dep[fa[rt-(1<<k)+1][k]])
		return fa[lt][k];
	else return fa[rt-(1<<k)+1][k];
}

int main()
{
	scanf("%d%d%d",&n,&m,&s);
	int u,v;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs(s,0);
	init();
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		printf("%d\n",getans(u,v));
	}
	return 0;
}
