#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=150010;
ll n;

struct building
{
    ll t1,t2;
}a[MAXN];

priority_queue<ll> q;
//优先队列记录现在可以修的建筑所需要的修筑时间

ll read()
{
    ll x=0;int f=0;char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

bool cmp(building x,building y)
{
    return x.t2<y.t2;
}

int main()
{
    n=read();
    for(ll i=1;i<=n;i++)
		a[i].t1=read(),a[i].t2=read();
    sort(a+1,a+1+n,cmp);
    ll now=0,ans=0;
    for(ll i=1;i<=n;i++)
    {
		if(a[i].t1+now<=a[i].t2)
		{
			now+=a[i].t1,ans++;
			q.push(a[i].t1);
		}
		//如果能修现在的就直接修
		else
		{
			//如果不能修，若当前建筑需要的花费时间比堆顶小，那么修堆顶的那个还不如修当前的这个
			//毕竟赚到的都是一个建筑……
			if(a[i].t1<q.top())
			{
				now=now-q.top()+a[i].t1;
				q.pop(),q.push(a[i].t1);
			}
		}
    }
    printf("%lld",ans);
    return 0;
}
