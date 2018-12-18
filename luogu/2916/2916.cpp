#include<bits/stdc++.h>
using namespace std;
int n,p,cnt=0;
int c[10010],fa[10010];
struct edge
{
	int s,t,w;
}E[100010*2];

void add(int u,int v,int w)
{
	cnt++;
	E[cnt].s=u;
	E[cnt].t=v;
	E[cnt].w=w;
}

bool cmp(edge a,edge b)
{
	return a.w<b.w;
}

int find(int a)
{
	return a==fa[a]?a:fa[a]=find(fa[a]);
}

int kruskal()
{
	int ans=0;
	for(int i=1;i<=cnt;i++)
	  {
	  	int a=E[i].s,b=E[i].t;
	  	int FA=find(a),FB=find(b);
	  	if(FA!=FB)
	  	  {
	  	  	fa[FA]=FB;
	  	  	ans+=E[i].w;
	  	  }
	  }
	return ans;
}

int main()
{
	scanf("%d%d",&n,&p);
	int mn=0x3f3f3f3f;
	for(int i=1;i<=n;i++) 
	  {
	  	scanf("%d",&c[i]),fa[i]=i;
	  	if(mn>c[i]) mn=c[i];//��С����Ϊ��㣬�����һ�� 
	  }
	int s,e,len;
	for(int i=1;i<=p;i++)
	  {
	  	scanf("%d%d%d",&s,&e,&len);
	  	add(s,e,len*2+c[s]+c[e]);
	  	//���ص�·��Ҫ��һ�飬len*2������յ������һ��c[s]+c[e] 
	  }
	sort(E+1,E+1+cnt,cmp);
	printf("%d",kruskal()+mn);
	return 0;
} 
