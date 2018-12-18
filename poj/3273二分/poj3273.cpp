#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
int n,m,l=0x3f3f3f3f,r,mid,cnt,sum,ans;
int a[1000010];

bool check(int e)
{
	cnt=1,sum=0;
	for(int i=1;i<=n;i++)
	  {
	  	if(a[i]>e) return false;
	  	if(sum+a[i]>mid)
	  	  {
			cnt++;
	  	  	sum=0;
	  	  }
	  	sum+=a[i];
	  }
	if(cnt>m) return false;
	else return true;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	  {
	  	scanf("%d",&a[i]);
	  	r+=a[i];
	  	l=min(l,a[i]);
	  }
	while(l<=r)
	  {
	  	mid=(l+r)/2;
	  	if(check(mid)) ans=mid,r=mid-1;
	  	else l=mid+1;
	  }
	cout<<ans;
	return 0;
}