#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,ans=1e14;
int mx,prime[30]={0,2,3,5,7,11,13,17,19,23,29,31,37,39,41,43,47};
//对于N<=2000000000,最多为12个质数连乘

//now为当前是第几个质数,num为当前的数,tot为当前数的因数个数;
//mi为上一个质因数对当前幂次的限制
//显然，质因数越大，它的幂次就应越小
void dfs(int now,ll num,int tot,int mi)
{
    if(now==13)
    {
		if(tot>mx||(tot==mx&&ans>num))
			ans=num,mx=tot;
		return;
    }
    ll sum=1;
    for(int i=0;i<=mi;i++)
    {
		dfs(now+1,num*sum,tot*(i+1),i);
		sum*=prime[now];
		if(num*sum>n) break;
    }
}

int main()
{
    cin>>n;
    dfs(1,1LL,1,30);
    cout<<ans;
    return 0;
}
