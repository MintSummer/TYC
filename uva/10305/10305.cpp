#include<bits/stdc++.h>
using namespace std;
int n,m,Head[110],cnt,in[110],vis[110],dfn[110],top;
//vis[i]==0��δ���ʡ�vis[i]==1�Ѿ����ʹ��� 
//vis[i]==-1��ʾ���ڷ��ʵ�·������i����㣬���һ�û�еݹ�ص�i 
//ע�⣺һ��ͼ����л�����һ����������������ֻ�������޻�ͼ���������� 
//�л�������ǡ��� 

struct edge
{
	int to,next;
}E[10010];

void add(int u,int v)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
}

bool dfs(int u)
{
	vis[u]=-1;
	int v;
	for(int i=Head[u];i;i=E[i].next)
	{
		v=E[i].to;
		if(vis[v]==-1) return false;//���ڷ��ʵ�·������v��δ�ݹ��ȥ��˵���л� 
		if(!vis[v]&&!dfs(v)) return false;
  	}
  	vis[u]=1;
  	dfn[top--]=u;
  	return true;
}

bool huan()
{
	top=n;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		if(!vis[i]&&!dfs(i)) return false;
	return true; 
}

int main()
{
	while(scanf("%d%d",&n,&m)&&(n||m))//ֻ��n==0&&m==0ʱ�Ž��� 
	{
		cnt=0;
		memset(Head,0,sizeof(Head));
		int u,v;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&u,&v);
			add(u,v),in[v]++;
		}
		if(huan())
			for(int i=1;i<=n;i++) printf("%d ",dfn[i]);
		else printf("No");
		printf("\n");
	}
	return 0;
} 
