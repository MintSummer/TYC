//推荐博客https://cnyali-lk.com/HNOI2013-%E6%95%B0%E5%88%97/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,m,p; 

ll qpow(ll x,ll tim)
{
    ll ans=1;
    while(tim)
    {
	if(tim&1) ans=ans*x%p;
	x=x*x%p;
	tim>>=1;
    }
    return ans;
}

int main()
{
    cin>>n>>k>>m>>p;
    k--;
    n%=p;//n太大了……
    ll ans=n*qpow(m,k)%p-qpow(m,k-1)*k%p*(m*(m+1)/2%p)%p;
    cout<<(ans+p)%p;
    return 0;
}
