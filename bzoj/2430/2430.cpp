#include<bits/stdc++.h>
using namespace std;
int n,m,ans=0,tim[3];
struct cut
{
	int val,id;
}a[20010];

bool cmp(cut p,cut q)
{
	return p.val>q.val;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++) 
		scanf("%d",&a[i].val),a[i].id=0;
	for(int i=1;i<m;i++) 
		scanf("%d",&a[i+n-1].val),a[i+n-1].id=1;
	sort(a+1,a+m+n,cmp);
	tim[0]=tim[1]=1;
	for(int i=1;i<m+n-1;i++)
	{
		ans+=tim[a[i].id^1]*a[i].val;
		tim[a[i].id]++;
	}
	printf("%d",ans);
	return 0;
} 
