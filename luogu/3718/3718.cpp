#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=100010;
	int n,k;
	char a[N],c[2]={'N','F'};
	
	bool check(int mid)
	{
		int cnt=0,len=0;
		for(int l=0,r=0;r<n;r++)
        {
            if(a[l]==a[r]) len++;
            else l=r,len=1;
            if(mid<len) l=r+1,len=0,cnt++;
		}
		return cnt<=k;
	}
	
	void work()
	{
		scanf("%d%d%s",&n,&k,a);
		int num=0;
		for(int i=0;i<n;i++)
			if(a[i]==c[i%2]) num++;
		if(num<=k||n-num<=k) {printf("1\n");return;}
		int l=2,r=n/k+1,ans,mid;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(check(mid)) ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
