#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN=210;
int n,m,cnt,pos[MAXN],Head[MAXN*5],color[MAXN*5];

int read()
{
    int x=0,f=0;char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

void init()
{
    cnt=0;
    memset(pos,0,sizeof(pos));
    memset(Head,0,sizeof(Head));
    memset(color,-1,sizeof(color));
}
    
struct Before_Edge
{
    int u,v,tag;
}G[MAXN*5];

struct Now_Edge
{
    int to,next;
}E[MAXN*MAXN*2];

void add(int u,int v)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    Head[u]=cnt;
}

bool dfs(int u)//染色
{
    for(int i=Head[u];i;i=E[i].next)
    {
		int v=E[i].to;
		if(color[v]==-1) 
		{
			color[v]=color[u]^1;
			if(!dfs(v)) return false;
		}
		else if(color[v]==color[u]) return false;
    }
    return true;
}

int main()
{
    int T=read();
    while(T--)
    {
		init();
		n=read(),m=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			G[i]=(Before_Edge){u,v,0};
		}
		for(int i=1;i<=n;i++) pos[read()]=i;
		if(m>3*n-6) {printf("NO\n");continue;}
		//平面图定理:当 边数<=总点数 时，该图为平面图

		for(int i=1;i<=m;i++)
		{
			int u=G[i].u=pos[G[i].u],v=G[i].v=pos[G[i].v];
			if(u>v) swap(G[i].u,G[i].v);
			if((v-u==1)||(u==1&&v==n)) G[i].tag=1;
		}
		for(int i=1;i<=m;i++)
			if(!G[i].tag)
				for(int j=i+1;j<=m;j++)
					if(!G[j].tag)
					{
						int u1=G[i].u,v1=G[i].v;
						int u2=G[j].u,v2=G[j].v;
						if((u2>u1&&v2>v1&&v1>u2) || (u2<u1&&v2<v1&&v2>u1))
							add(i,j),add(j,i);
					}
	
		int flag=1;
		for(int i=1;i<=m;i++)
			if(color[i]==-1) 
			{
				color[i]=1;
				if(!dfs(i)) {flag=0;break;}
			}
		if(flag) printf("YES\n");
		else printf("NO\n");
    }
    return 0;
}
