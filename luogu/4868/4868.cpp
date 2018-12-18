#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=100010;
int n,m;
ll sum[MAXN],s[MAXN],a[MAXN];

int lowbit(int x) {return x&(-x);}
 
void insert(ll c[],int x,ll val)
{
    for(;x<=n;x+=lowbit(x)) c[x]+=val;
}
 
ll ask(ll c[],int x)
{
    ll ans=0;
    for(;x;x-=lowbit(x)) ans+=c[x];
    return ans;
}
 
ll SS(int x)
{
    return ask(sum,x)*x-ask(s,x);
}
 
int main()
{
    scanf("%d%d",&n,&m);
    char ch[10];
    int x,val;
    for(int i=1;i<=n;i++) 
    {
        scanf("%lld",&a[i]);
        insert(sum,i,a[i]);
        insert(s,i,(i-1)*a[i]);
    }
    while(m--)
    {
        scanf("%s",ch);
        if(ch[0]=='Q') 
            {scanf("%d",&x);printf("%lld\n",SS(x));}
        else
        {
            scanf("%d%d",&x,&val);
            ll d=val-a[x];a[x]=val;
            insert(sum,x,d),insert(s,x,(ll)d*(x-1));
        }
    }
    return 0;
}
