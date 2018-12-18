#include<bits/stdc++.h>
using namespace std;
const int MAXN=200000*2+10;
const int inf=1001;
int la,lb,n,m=inf+1;
int a[MAXN],x[MAXN],y[MAXN],sa[MAXN],w[MAXN],rank[MAXN];

int read()
{
	int x=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}

bool cmp(int i,int j,int len)
{
	return y[i]==y[j]&&y[i+len]==y[j+len];
}

void get_sa()
{
	for(int i=0;i<=m;i++) w[i]=0;
	for(int i=1;i<=n;i++) w[x[i]=a[i]]++;
	for(int i=1;i<=m;i++) w[i]+=w[i-1];
	for(int i=n;i;i--) sa[w[x[i]]--]=i;
	for(int k=1,p=0;k<=n;k<<=1,m=p,p=0)
	{
		for(int i=n;i>n-k;i--) y[++p]=i;
		for(int i=1;i<=n;i++) if(sa[i]>k) y[++p]=sa[i]-k;
		for(int i=0;i<=m;i++) w[i]=0;
		for(int i=1;i<=n;i++) w[x[y[i]]]++;
		for(int i=1;i<=m;i++) w[i]+=w[i-1];
		for(int i=n;i;i--) sa[w[x[y[i]]]--]=y[i];
		swap(x,y);
		p=x[sa[1]]=1;
		for(int i=2;i<=n;i++)
			x[sa[i]]=cmp(sa[i-1],sa[i],k)?p:++p;
		if(p>=n) break;
	}
	for(int i=1;i<=n;i++) rank[sa[i]]=i;
}

int main()
{
	la=read();
	for(int i=1;i<=la;i++) a[++n]=read();
	a[++n]=inf;
	lb=read();
	for(int i=1;i<=lb;i++) a[++n]=read();
	a[++n]=inf;
	get_sa();
	int nowa=1,nowb=la+2;
	for(int tot=1;tot<=la+lb;tot++)
		if(rank[nowa]<rank[nowb]) printf("%d ",a[nowa++]);
		else printf("%d ",a[nowb++]);
	return 0;
}
