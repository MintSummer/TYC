#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=500010;
char ch[MAXN];
int n,m=26,a[MAXN],sa[MAXN],x[MAXN],y[MAXN],w[MAXN],rank[MAXN],height[MAXN];
int st[MAXN],top;
ll f[MAXN];

bool cmp(int i,int j,int len)
{
    return i+len<=n&&j+len<=n&&y[i]==y[j]&&y[i+len]==y[j+len];
}

void get_sa()
{
    for(int i=1;i<=m;i++) w[i]=0;
    for(int i=1;i<=n;i++) w[x[i]=a[i]]++;
    for(int i=2;i<=m;i++) w[i]+=w[i-1];
    for(int i=n;i;i--) sa[w[x[i]]--]=i;
    for(int k=1,p=0;k<=n;k<<=1,m=p,p=0)
    {
		for(int i=n-k+1;i<=n;i++) y[++p]=i;
		for(int i=1;i<=n;i++) if(sa[i]>k) y[++p]=sa[i]-k;
		for(int i=1;i<=m;i++) w[i]=0;
		for(int i=1;i<=n;i++) w[x[y[i]]]++;
		for(int i=2;i<=m;i++) w[i]+=w[i-1];
		for(int i=n;i;i--) sa[w[x[y[i]]]--]=y[i];
		swap(x,y);
		p=x[sa[1]]=1;
		for(int i=2;i<=n;i++)
			x[sa[i]]=cmp(sa[i-1],sa[i],k)?p:++p;
		if(p>=n) return;
    }
}

void get_height()
{
    for(int i=1;i<=n;i++) rank[sa[i]]=i;
    int i,j,k=0;
    for(i=1;i<=n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];a[i+k]==a[j+k];k++);
}

/*
对于每一个height[i],若height[i-1]<=height[i]，那么height[i-1]能取到的值height[i]都能取到；若height[i-1]>height[i]，这部分的LCP长度就是height[i]。
用一个栈维护前面距i最近且小于等于height[i]的元素，记为p，则转移方程为：f[i]=f[p]+(i-p)*height[i];
*/

ll lcp()
{
    int pos=0;
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
		int p=pos;
		while(top&&height[st[top]]>height[i]) top--;
		if(top) p=st[top];
		f[i]=f[p]+(i-p)*height[i];
		if(!height[i]) pos=i;//当height[i]为0时说明从i开始后面所有的取i前的部分均为0,不用再往前考虑了
		st[++top]=i;
    }
    for(int i=1;i<=n;i++) ans+=f[i];
    return ans;
}

int main()
{
    scanf("%s",ch);
    n=strlen(ch);
    for(int i=1;i<=n;i++) a[i]=ch[i-1]-'a'+1;
    get_sa();
    get_height();
    ll ans=(ll)(1+n)*n/2*(n-1);//叫你不加LL
    printf("%lld\n",ans-2*lcp());
    return 0;
}
