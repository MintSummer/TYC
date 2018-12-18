#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,a[100010],sum;

bool check(int x)
{
    ll d=sum-a[x];
    int lt=x+1,rt=n,mid,ans=-1;
    while(lt<=rt)
    {
		mid=(lt+rt)>>1;
		if(a[mid]<=d) ans=mid,lt=mid+1;
		else rt=mid-1;
    }
    if(ans!=-1&&a[ans]+a[x]==sum) 
    {
		printf("%lld %lld",a[x],a[ans]);
		return true;
    }
    return false;
}

int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
	scanf("%lld",&a[i]);
    scanf("%lld",&sum);
    sort(a+1,a+1+n);
	bool flag=false;
    for(int i=1;i<n;i++) 
	{
		flag=check(i);
		if(flag) return 0;
	}
	printf("No");
    return 0;
}
