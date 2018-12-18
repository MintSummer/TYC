#include<bits/stdc++.h>
using namespace std;
const int MAXN=(1e6+10)*2;
char ch[MAXN];
int n,m=100,a[MAXN],w[MAXN],sa[MAXN],x[MAXN],y[MAXN];

int Get(char c)
{
    if (c>='0'&&c<='9') return c-'0';
    if (c>='A'&&c<='Z') return c-'A'+10;
    if (c>='a'&&c<='z') return c-'a'+36;
    return c;
}

bool cmp(int a,int b,int len)
{
    return y[a]==y[b]&&y[a+len]==y[b+len];
}

void get_sa()
{
    for(int i=0;i<=m;i++) w[i]=0;
    for(int i=1;i<=n;i++) w[x[i]=a[i]]++;
    for(int i=1;i<=m;i++) w[i]+=w[i-1];
    for(int i=n;i;i--) sa[w[x[i]]--]=i;

    for(int k=1;k<=n;k<<=1)
    {
	int p=0;
	for(int i=n-k+1;i<=n;i++) y[++p]=i;
	for(int i=1;i<=n;i++) if(sa[i]>k) y[++p]=sa[i]-k;

	for(int i=0;i<=m;i++) w[i]=0;
	for(int i=1;i<=n;i++) w[x[y[i]]]++;
	for(int i=1;i<=m;i++) w[i]+=w[i-1];
	for(int i=n;i;i--) sa[w[x[y[i]]]--]=y[i];

	swap(x,y);
	p=1,x[sa[1]]=1;
	for(int i=2;i<=n;i++) 
	    x[sa[i]]=cmp(sa[i-1],sa[i],k)?p:++p;
	if(p>=n) break;
	m=p;
    }
}

int main()
{
    scanf("%s",ch);
    n=strlen(ch);
    for(int i=0;i<n;i++) a[i+1]=Get(ch[i]);
    get_sa();
    for(int i=1;i<=n;i++) printf("%d ",sa[i]);
    return 0;
}
