#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<string>
#include<algorithm>
#include<set>
using namespace std;
typedef long long ll;
int T,n,a[25];
ll k;

void getnxt()
{
    ll x=k*k;
    int len=0;
    while(x) a[++len]=x%10,x/=10;
    k=0;
    for(int i=len;i>len-n;i--) k=k*10+a[i];
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>T;
    while(T--)
    {
	cin>>n>>k;
	ll ans=k;
	set<ll> s;
	while(!s.count(k))
	{
	    s.insert(k);
	    if(k>ans) ans=k;
	    getnxt();
	}
	cout<<ans<<endl;
    }
}
