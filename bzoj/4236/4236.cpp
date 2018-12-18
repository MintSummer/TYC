#include<bits/stdc++.h>
using namespace std;
const int MAXN=200010;

struct node
{
    int x,y,id;
    bool operator < (const node &d) const
    {
	if(x!=d.x) return x<d.x;
	else if(y!=d.y) return y<d.y;
	else return id<d.id;
    }
}a[MAXN];

int main()
{
    int n;char ch;
    scanf("%d",&n);
    ch=getchar();
    while(ch<'A'||ch>'Z') ch=getchar();
    for(int i=1;i<=n;i++)
    {
	a[i].x=a[i-1].x,a[i].y=a[i-1].y;
	if(ch=='J') a[i].x++;
	else if(ch=='O') a[i].x--,a[i].y++;
	else a[i].y--;
	a[i].id=i;
	if(i<n) ch=getchar();
    }
    sort(a,a+1+n);
	//有可能有x、y均为0的情况，此时是可以选的，表示从第一个一直到这一个（不从0开始会WA）
    int ans=0,now=a[0].id;
    for(int i=1;i<=n;i++)
    {
	if(a[i].x==a[i-1].x&&a[i].y==a[i-1].y) 
	    ans=max(ans,a[i].id-now);
	else now=a[i].id;
    }
    printf("%d",ans);
    return 0;
}
