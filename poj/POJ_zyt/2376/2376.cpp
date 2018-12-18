#include<iostream>
#include<algorithm>
using namespace std;
struct line
{
	int a;
	int b;
}cow[25010];
int n,t,ans,cnt;
bool cmp(const line &x,const line &y)
{
	return x.a<y.a;
}
int main(void)
{
	cin>>n>>t;
	for(int i=0;i<n;i++)
		cin>>cow[i].a>>cow[i].b;
	sort(cow,cow+n,cmp);
	int end=0,maxe=0;
	cnt=0;
	if(cow[0].a!=1)
	{
		cout<<-1;
		return 0;
	}
	while(cnt<n)
	{
		if(cow[cnt].a<=end+1&&cow[cnt].b>end)
		{
			maxe=max(maxe,cow[cnt].b);
		}
		else if(cow[cnt].a>end+1)
		{
			if(maxe>end)
			{
				end=maxe;
				ans++;
				cnt--;
			}
			else
			{
				cout<<-1;
				return 0;
			}
		}
		cnt++;
	}
	if(maxe>end)
	{
			end=maxe;
			ans++;
	}
	if(end<t)cout<<-1;
	else cout<<ans;
	return 0;
}
