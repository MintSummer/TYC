#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int n,m,fa[MAXN],mark[MAXN];

int find(int a)
{
	return fa[a]==a?a:fa[a]=find(fa[a]);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i;
	int a,b,FA,FB;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		FA=find(a),FB=find(b);
		if(FA==FB) mark[FA]=1;
		else
		{
			fa[FA]=FB;
			mark[FB]=mark[FA]|mark[FB];
		}
	}
	for(int i=1;i<=n;i++) 
		if(!mark[find(i)]) {printf("NIE");return 0;}
	printf("TAK");
	return 0;
}

