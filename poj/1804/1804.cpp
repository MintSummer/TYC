#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int MAXN=1010;
int T,n,a[MAXN],tmp[MAXN],ans;

void HEBING(int lt,int rt)
{
	int mid=(lt+rt)>>1;
	int k=lt,i=lt,j=mid+1;
	while(i<=mid&&j<=rt)
	{
		if(a[i]>a[j])
		{
			tmp[k++]=a[j];
			j++;
			ans+=mid-i+1;
		}
		else
		{
			tmp[k++]=a[i];
			i++;
		}
	}
	while(i<=mid) tmp[k++]=a[i],i++;
	while(j<=rt) tmp[k++]=a[j],j++;
	for(i=lt;i<=rt;i++) a[i]=tmp[i];
}

void Merge_sort(int l,int r)
{
	if(l<r)
	{
		int mid=(l+r)>>1;
		Merge_sort(l,mid);
		Merge_sort(mid+1,r);
		HEBING(l,r);
	}
}


int main()
{
	scanf("%d",&T);
	for(int cnt=1;cnt<=T;cnt++)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		ans=0;
		Merge_sort(1,n);
		printf("Scenario #%d:\n%d\n\n",cnt,ans);
	}
}
