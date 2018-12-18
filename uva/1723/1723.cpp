#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN=6e4+10;
const int inf=0x3f3f3f3f;
int n,cnt,Head[MAXN],f[MAXN],vis[MAXN],mn,mx;

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

struct edge
{
    int to,next,w;
}E[MAXN*3];

void add(int u,int v,int w)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    E[cnt].w=w;
    Head[u]=cnt;
}

void init()
{
    cnt=0;
    mx=0,mn=inf;
    memset(f,0,sizeof(f));
    memset(vis,0,sizeof(vis));
    memset(Head,0,sizeof(Head));
}

void spfa()//最长路
{
    for(int i=mn;i<=mx;i++) f[i]=-inf;
    queue<int> q;
    q.push(mn);
    vis[mn]=1,f[mn]=0;
    while(!q.empty())
    {
		int u=q.front();q.pop();
		vis[u]=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(f[v]<f[u]+E[i].w)
			{
				f[v]=f[u]+E[i].w;
				if(!vis[v]) vis[v]=1,q.push(v);
			}
		}
    }
}

int main()
{
    int T;
    T=read();
    while(T--)
    {
		init();
		n=read();
		int lt,rt,c;
		for(int i=1;i<=n;i++)
		{
			lt=read(),rt=read(),c=read();
			mn=min(mn,lt-1),mx=max(mx,rt);
			add(lt-1,rt,c);//闭区间,其实应是sum[rt]-sum[lt-1]>=c(sum)表示个数
		}
		for(int i=mn;i<mx;i++)
		{
			add(i,i+1,0);//sum[i+1]-sum[i]>=0
			add(i+1,i,-1);//sum[i]-sum[i-1]>=-1
		}//将所有点都连起来，成为一个图
		spfa();
		printf("%d\n",f[mx]);
		if(T!=0) printf("\n");
    }
    return 0;
}
