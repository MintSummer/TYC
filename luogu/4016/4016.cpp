#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;

namespace TYC
{
    const int MAXN=110,inf=0x3f3f3f3f;
	typedef long long ll;
    int N;
	ll a[MAXN],c[MAXN];

    void work()
    {
		ios::sync_with_stdio(false);
		cin>>N;
		ll sum=0,ave;
		for(int i=1;i<=N;i++) 
			cin>>a[i],sum+=a[i];
		ave=sum/N;
		c[0]=0;
		for(int i=1;i<N;i++)
			c[i]=c[i-1]+a[i]-ave;
		sort(c,c+N);
		int x=c[N/2],ans=0;
		for(int i=0;i<N;i++)
			ans+=abs(x-c[i]);
		cout<<ans;
    }
}

int main()
{
    TYC::work();
    return 0;
}
