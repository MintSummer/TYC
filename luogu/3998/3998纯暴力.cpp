//说实话，这道题在洛谷上这种纯暴力能水80分 
#include<bits/stdc++.h>
using namespace std;
const int MAXN=200010;
int n,m,cnt=0,Head[MAXN];
int ans[MAXN];

struct edge
{
	int to,next;
}E[500010*2];

void add(int u,int v)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	Head[u]=cnt;
}

void del(int a,int b)
{
	int be;
	for(int i=Head[a];i;i=E[i].next)
	{
		if(E[i].to==b&&i==Head[a]) {Head[a]=E[i].next;return;}
		if(E[i].to==b) {E[be].next=E[i].next;return;}
		be=i;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	int x,y;
	char ch[5];
	while(m--)
	{
		scanf("%s",ch);
		if(ch[0]=='!') 
		{
			scanf("%d",&x);
			for(int i=Head[x];i;i=E[i].next) ans[E[i].to]++;
		}
		else if(ch[0]=='+')
		{
			scanf("%d%d",&x,&y);
			add(x,y),add(y,x);
		}
		else 
		{
			scanf("%d%d",&x,&y);
			del(x,y),del(y,x);
		}
	}
	for(int i=1;i<n;i++) printf("%d ",ans[i]);
	printf("%d",ans[n]);
	return 0;
}
