#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;

namespace TYC
{
    const int MAXN=100010;
    typedef long long ll;
    int n,k,cnt;
    ll hei,sum,tmp;
    
    struct node
    {
		ll w,h;
		bool operator < (const node &a) const
		{
			return (w>a.w)||(w==a.w&&h>a.h);
		}
    };
    priority_queue<node> q;
    void work()
    {
		ios::sync_with_stdio(false);
		cin>>n>>k;
		ll w;
		for(int i=1;i<=n;i++) 
			cin>>w,q.push((node){w,1});
		if((n-1)%(k-1)!=0)  cnt=k-1-(n-1)%(k-1);
		for(int i=1;i<=cnt;i++) q.push((node){0,1});
		cnt+=n;
		while(cnt>1)
		{
			tmp=hei=0;
			for(int i=1;i<=k;i++)
			{
				tmp+=q.top().w;
				hei=max(hei,q.top().h);
				q.pop();
			}
			sum+=tmp;
			q.push((node){tmp,hei+1});
			cnt-=k-1;
		}
		cout<<sum<<endl<<q.top().h-1;
    }
}

int main()
{
    TYC::work();
    return 0;
}
