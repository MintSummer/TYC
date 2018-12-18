#include<iostream>
#include<queue>
using namespace std;
bool vis[100010];
struct note
{
	int a;
	int t;
};
int main(void)
{
	int n,k;
	queue<note>q;
	cin>>n>>k;
	q.push({n,0});
	vis[n]=true;
	while(1)
	{
		int a=q.front().a;
		int t=q.front().t;
		q.pop(); 
		if(a==k)
		{
			cout<<t;
			return 0;
		}
		if(a+1<=100000&&!vis[a+1])q.push({a+1,t+1}),vis[a+1]=true;
		if(a-1>=0&&!vis[a-1])q.push({a-1,t+1}),vis[a-1]=true;
		if(a*2<=100000&&!vis[a*2])q.push({a*2,t+1}),vis[a*2]=true;
	}
} 
