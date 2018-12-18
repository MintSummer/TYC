#include<bits/stdc++.h>
using namespace std;

int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

const int MAXN=20010;
int n,m,d[MAXN],p[MAXN];

int main()
{
	while(1)
	{
		n=read(),m=read();
		if(n==0&&m==0) break;
		for(int i=1;i<=n;i++) d[i]=read();
		for(int i=1;i<=m;i++) p[i]=read();
		sort(d+1,d+1+n);
		sort(p+1,p+1+m);
		int ans=0,flag=1;
		for(int x=1,y=1;x<=n;x++)
		{
			while(y<=m&&d[x]>p[y]) y++;
			if(y>m) {flag=0;break;}
			ans+=p[y];
			y++;
		}
		if(flag) printf("%d\n",ans);
		else printf("Loowater is doomed!\n");
	}
	return 0;
}
