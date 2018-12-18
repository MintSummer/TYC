#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int MAXN=10010;
int n,m,cnt,ans,head[MAXN],cou[MAXN];
int t,q,vis[MAXN],dfn[MAXN],low[MAXN],csize[MAXN],belong[MAXN],st[MAXN],top,dfs;
struct edge
{
	int to,next;
}E[50010];

void init()
{
	q=cnt=ans=dfs=top=0;
	memset(vis,0,sizeof(vis));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(csize,0,sizeof(csize));
	memset(belong,0,sizeof(belong));
	memset(st,0,sizeof(st));
	memset(cou,0,sizeof(cou));
}

void add(int u,int v)
{
	E[++cnt].to=v;
	E[cnt].next=head[u];
	head[u]=cnt;
}

void Tarjan(int x)
{
	st[++top]=x;
	dfn[x]=low[x]=++dfs;
	for(int i=head[x];i;i=E[i].next)
	  {
	  	t=E[i].to;
	  	if(vis[t]) continue;
	  	if(dfn[t])
	  	  low[x]=min(low[x],dfn[t]);
	  	else
	  	  {
	  	  	Tarjan(t);
	  	  	low[x]=min(low[x],low[t]);
	  	  }
	  }
	if(low[x]==dfn[x])
	  {
	  	q++;
	  	do
		  {
		  	t=st[top--];
			vis[t]=1;
		  	belong[t]=q;
		  	csize[q]++;
	  	  }
	  	while(t!=x);
	  }
}

int main()
{
	//while(){
	scanf("%d%d",&n,&m);
    init();
	int a,b;
	for(int i=1;i<=m;i++)
	  {
	  	scanf("%d%d",&a,&b);
	  	add(a,b);
	  }
	for(int i=1;i<=n;i++)
	  if(!vis[i]) Tarjan(i);
	//����Ϊbelong 
	for(int i=1;i<=n;i++)
	  {
	  	a=belong[i];
	  	for(int j=head[i];j;j=E[j].next)
	  	  {
	  	  	b=belong[E[j].to];
	  	  	if(a!=b)//��ͬһǿ��ͨ������������������ǿ��ͨ 
	  	  	cou[a]++;//ǿ��ͨbelong[i]��������
	  	  } 
	  }
	//����ĳǿ��ͨ��������Ϊ0����˵����ǿ��ͨ�����е�ţ��ӭ
	//��ΪΪ����ͼ��������ţ��Ľ��һͷţ������һͷţҲ��Ľ��ͷţ���򹹳�ǿ��ͨ 
    //����������ͼ����һ�����ϳ���Ϊ0��ǿ��ͨ���������ͼ�ͻ��ɷ���ͨͼ�������ڱ�����ţ����Ľ��ţ 
	int panduan=0;
	for(int i=1;i<=q;i++)
	  if(cou[i]==0) panduan++,ans=csize[i];
	if(panduan==1) printf("%d",ans);
	else printf("0");//}
	return 0;
}

