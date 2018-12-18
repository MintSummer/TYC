#include<iostream>
#include<algorithm>
using namespace std;
int r[1010];
int n,t;
int main(void)
{
	cin>>n>>t;
	for(int i=1;i<=n;i++)
		cin>>r[i];
	while(t--)
	{
		int maxid=0,maxr=-1;
		for(int i=1;i<=n;i++)
			if(maxr<r[i])maxr=r[i],maxid=i;
		cout<<maxid<<endl;
		int a=r[maxid]/(n-1),b=r[maxid]%(n-1);
		for(int i=1;i<=n;i++)
			if(i==maxid)r[i]=0;
			else r[i]+=a;
		for(int i=1;i<=b;i++)
			if(i==maxid)b++;
			else r[i]++;
	}
	return 0;
}
