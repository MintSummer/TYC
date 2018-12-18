#include<bits/stdc++.h>
using namespace std;

int n,m,ans,tyc;
int G[50][50],belong[50],from[1010],to[1010];

int main()
{
	freopen("1130.in","r",stdin);
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i=1;i<=m;i++)
		scanf("%d%d",&from[i],&to[i]);

	freopen("ans.out","r",stdin);
	for(int i=1;i<=(n>>1);i++)
		scanf("%d",&u),belong[u]=1;
	for(int i=1;i<=m;i++)
		if(belong[from[i]]!=belong[to[i]]) ans++;

	freopen("1130.out","r",stdin);
	memset(belong,0,sizeof(belong));
	for(int i=1;i<=(n>>1);i++)
		scanf("%d",&u),belong[u]=1;
	for(int i=1;i<=m;i++)
		if(belong[from[i]]!=belong[to[i]]) tyc++;
	if(ans!=tyc) return 1;
	else return 0;
}
