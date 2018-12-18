#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
int n;
long long ans;
priority_queue<long long,vector<long long>,greater<long long> > q;
int main(void)
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int a;
		scanf("%d",&a);
		q.push(a);
	}
	while(q.size()>1)
	{
		long long a=q.top(),b;
		q.pop();
		b=q.top();
		q.pop();
		ans+=a+b;
		q.push(a+b);
	}
	printf("%lld",ans);
	return 0;
}
