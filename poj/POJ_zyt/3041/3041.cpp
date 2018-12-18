#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
bool map[510][510],c[510];
int b[510];
int n,k,ans;
bool path(int x)
{
	for(int i=1;i<=n;i++)
		if(map[x][i]&&!c[i])
		{
			c[i]=true;
			if(b[i]==-1||path(b[i]))
			{
				b[i]=x;
				return true;
			}
		}
	return false;
}
void hungary()
{
	memset(b,-1,sizeof(b));
	for(int i=1;i<=n;i++)
	{
		memset(c,0,sizeof(c));
		if(path(i))ans++;
	}
}
int main(void)
{
	cin>>n>>k;
	for(int i=0;i<k;i++)
	{
		int a,b;
		cin>>a>>b;
		map[a][b]=true;
	}
	hungary();
	cout<<ans;
	return 0;
} 
