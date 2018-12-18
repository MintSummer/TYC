#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
int n,len[20010];

int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		for(int i=1;i<=n;i++)
			scanf("%d",&len[i]);
		long long sum=0;
		priority_queue< int,vector<int>, greater<int> > q;
		for(int i=1;i<=n;i++) q.push(len[i]);
		while(q.size()>1)
		{
			int a=q.top();q.pop();
			int b=q.top();q.pop();
			sum+=(a+b);
			q.push(a+b);
		}
		printf("%lld\n",sum);
	}
	return 0;
} 
