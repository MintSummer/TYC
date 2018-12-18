//from:崩溃的TYC
//离散化+并查集

//vjudge上第一名是一个写的很可爱的离散化代码
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000020;
int t,n;
int a[MAXN],b[MAXN],opt[MAXN],fa[MAXN*2],mp[MAXN*2];

bool cmp(int p,int q)
{
	return p<q;
}

int find(int a)
{
	return fa[a]==a?a:fa[a]=find(fa[a]);
}

int search(int num)
{
	int l=0,r=2*n+1,mid;
	while(l+1<r)
	{
		mid=(l+r)>>1;
		if(num<mp[mid]) r=mid;
		else l=mid;
	}
	while(mp[l-1]==mp[l]) l--;
	return l;
}

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int fx,fy,flag=0,x,y;
		scanf("%d",&n);
		mp[0]=-1;
		for(int i=1;i<=n*2;i++) fa[i]=i;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d%d",&a[i],&b[i],&opt[i]);
			mp[(i<<1)-1]=a[i],mp[i<<1]=b[i];
		}
		sort(mp+1,mp+1+n*2,cmp);
		for(int i=1;i<=n;i++)
			if(opt[i])
			{
				x=search(a[i]),y=search(b[i]);
				fx=find(x),fy=find(y);
				if(fx!=fy) fa[fx]=fy;
			}
		for(int i=1;i<=n;i++)
			if(opt[i]==0)
			{
				x=search(a[i]),y=search(b[i]);
				fx=find(x),fy=find(y);
				if(fx==fy) {flag=1;break;}
			}
		flag==0?printf("YES\n"):printf("NO\n");
	}
	return 0;
}
