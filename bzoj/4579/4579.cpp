//˫�����飺 bzoj1015 �����ս 
#include<bits/stdc++.h>
using namespace std;
const int MAXN=200010;
int n,m,cnt=0,Head[MAXN];
int tim[MAXN],vis[MAXN],fa[MAXN];
int ans[MAXN];

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

int find(int a)
{
	return a==fa[a]?a:fa[a]=find(fa[a]);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i;
	int u,v;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++) scanf("%d",&tim[i]);
	int fu,fv,tot=0;//tot��ʾ��ͨ����� 
	for(int j=n;j>=1;j--)//���򲢲鼯 
	{
		u=tim[j];
		vis[u]=1;
		tot++;//ÿ�ָ�һ���㣬��ͨ�����++ 
		for(int i=Head[u];i;i=E[i].next)
		{
			v=E[i].to;
			if(!vis[v]) continue;
			fu=find(u),fv=find(v);
			if(fu!=fv) fa[fv]=fu,tot--;//ÿ��ͨһ������ͨ�����-- 
		}
		ans[j]=(tot==1);//tot==1ʱ��ʾ��ʱֻ��һ����ͨ�飨��ȫ����ͨ�� 
	}
	for(int i=1;i<=n;i++)
		if(ans[i]) printf("YES\n");
		else printf("NO\n");
	return 0;
}
