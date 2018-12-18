#include<bits/stdc++.h>
using namespace std;
const int MAXN=60010*2;
int n,m=26,a[MAXN],sa[MAXN],w[MAXN],x[MAXN],y[MAXN],rank[MAXN];

int read()
{
	char ch=getchar();
	while(ch<'A'||ch>'Z') ch=getchar();
	return ch-'A'+1;
}

bool cmp(int i,int j,int len)
{
	return y[i]==y[j]&&y[i+len]==y[j+len];
}

void get_sa()
{
	for(int i=1;i<=m;i++) w[i]=0;
	for(int i=1;i<=n;i++) w[x[i]=a[i]]++;
	for(int i=2;i<=m;i++) w[i]+=w[i-1];
	for(int i=n;i;i--) sa[w[x[i]]--]=i;
	
	for(int k=1,p=0;k<=n&&p<n;k<<=1,m=p,p=0)
	{
		for(int i=n;i>n-k;i--) y[++p]=i;
		for(int i=1;i<=n;i++) if(sa[i]>k) y[++p]=sa[i]-k;
		
		for(int i=1;i<=m;i++) w[i]=0;
		for(int i=1;i<=n;i++) w[x[y[i]]]++;
		for(int i=2;i<=m;i++) w[i]+=w[i-1];
		for(int i=n;i;i--) sa[w[x[y[i]]]--]=y[i];
		
		swap(x,y);//ÓÖÍüÁËÕâ¾ä 
		p=x[sa[1]]=1;
		for(int i=2;i<=n;i++)
			x[sa[i]]=cmp(sa[i-1],sa[i],k)?p:++p;
	}
	for(int i=1;i<=n;i++) rank[sa[i]]=i;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		a[i]=a[2*n-i+1]=read();
	n*=2;
	get_sa();
	n/=2;
	int lt=1,rt=n,cnt=0;
	while(lt<=rt)
	{
		if(rank[lt]<rank[2*n-rt+1]) 
			printf("%c",a[lt]-1+'A'),lt++;
		else 
			printf("%c",a[rt]-1+'A'),rt--;
		if(++cnt==80) printf("\n"),cnt=0;
	}
	return 0;
}
