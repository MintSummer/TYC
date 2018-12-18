#include<cstdio>
#include<iostream>
using namespace std;
typedef long long LL;
LL xx,yy,m,n,len;

long long exgcd(LL a,LL b,LL &x,LL &y)
{
	if(b==0) 
	{
		x=1,y=0;
		return a;
	}
	LL ans=exgcd(b,a%b,x,y);
	int tmp=x;
	x=y;
	y=tmp-a/b*y;
	return ans;
}

int main()
{
	cin>>xx>>yy>>m>>n>>len;
	LL a=xx-yy,b=n-m,x,y,ans;
	if(b<0) a=-a,b=-b;
	ans=exgcd(b,len,x,y);
	if(a%ans) cout<<"Impossible";
	else cout<<((x*(a/ans))%(len/ans)+(len/ans))%(len/ans);
	return 0;
}
