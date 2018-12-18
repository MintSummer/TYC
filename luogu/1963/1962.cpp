#include<bits/stdc++.h>
using namespace std;
const int MAXN=20010;
int n,ans,vis[MAXN],fa[MAXN],tmp[MAXN];
vector<int> E[MAXN];

void add(int u,int v)
{
    E[u].push_back(v),E[v].push_back(u);
}

bool Path(int u,int tim)
{
    int s=E[u].size();
    for(int i=0;i<s;i++)
    {
		int v=E[u][i];
		if(vis[v]==tim) continue;
		vis[v]=tim;
		if(fa[v]==-1||Path(fa[v],tim)) 
		{
			fa[v]=u;
			return true;
		}
    }
    return false;
}

void Hungary()
{
    memset(fa,-1,sizeof(fa));
    for(int i=n-1;i>=0;i--)//用字典序小的挤掉大的
		if(Path(i,i+1)) ans++;
}

int main()
{
    scanf("%d",&n);
    int d;
    for(int i=0;i<n;i++)
    {
		scanf("%d",&d);
		add(i,(i+d)%n+n);
		add(i,(i-d+n)%n+n);
    }
    for(int i=0;i<2*n;i++)
		sort(E[i].begin(),E[i].end());
    Hungary();
    if(ans!=n) {printf("No Answer");return 0;}
    for(int i=0;i<n;i++)
		tmp[fa[i+n]]=i;
    for(int i=0;i<n;i++)
    {
		printf("%d",tmp[i]);
		if(i!=n-1) printf(" ");
    }
    return 0;
}
