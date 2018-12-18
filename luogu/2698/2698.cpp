#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int n,d;

int read()
{
	int x=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}

struct node
{
	int x,y;
	bool operator < (const node &d) const
	{
		return x<d.x;
	}
}a[MAXN],q[MAXN];

int main()
{
	n=read(),d=read();
	for(int i=1;i<=n;i++)
		a[i].x=read(),a[i].y=read();
	sort(a+1,a+1+n);
	int h=1,t=1,mn=0x3f3f3f3f;
	q[1]=a[1];
	for(int i=2;i<=n;i++)
	{
		while(t>=h&&q[t].y>a[i].y) t--;
		q[++t]=a[i];
		while(t>=h&&(q[t].y-q[h].y)>=d)
		{
			mn=min(mn,q[t].x-q[h].x);
			h++;
		}
 	}
 	if(mn==0x3f3f3f3f) printf("-1");
 	else printf("%d",mn);
 	return 0;
}
