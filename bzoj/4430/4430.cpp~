//开LL……
#include<bits/stdc++.h>
using namespace std;
const int MAXN=200010;
typedef long long ll;
int n,a[MAXN],b[MAXN],c[MAXN];
int id[MAXN],cc[MAXN];

inline void insert(int num,int val)
{
    for(int i=num;i<=n;i+=i&(-i)) cc[i]+=val;
}

inline ll ask(int num)
{
    ll ans=0;
    for(int i=num;i;i-=i&(-i)) ans+=cc[i];
    return ans;
}

inline ll solve(int *x,int *y)
{
    ll ans=0;
    for(int i=1;i<=n;i++) id[x[i]]=i,cc[i]=0;
    for(int i=n;i;i--)
    {
	ans+=ask(id[y[i]]);
	insert(id[y[i]],1);
    }
    return ans;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);

    ll ans=(ll)(n-1)*n;//不强制转化成ll害死人……
    ans-=solve(a,b)+solve(a,c)+solve(b,c);
    printf("%lld\n",ans>>1);
    return 0;
}
