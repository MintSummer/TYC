#include<bits/stdc++.h>
using namespace std;
const int MAXN=10010;
int n,m,cnt,a[MAXN],f[MAXN],d[MAXN];

int read()
{
    int x=0,f=0;char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

int find(int x)
{
    int lt=1,rt=cnt,mid,ans=0;
    while(lt<=rt)
    {
		mid=(lt+rt)>>1;
		if(d[mid]>x) ans=mid,lt=mid+1;
		else rt=mid-1;
    }
    return ans;
}

void init()
{
    for(int i=n;i;i--)
    {
		f[i]=find(a[i])+1;
		cnt=max(cnt,f[i]);
		d[f[i]]=a[i];
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    init();
    m=read();
    int len;
    for(int i=1;i<=n;i++) cout<<f[i]<<' ';puts("");
    for(int i=1;i<=cnt;i++) cout<<d[i]<<' ';puts("");
    while(m--)
    {
		len=read();
		if(len>cnt) {printf("Impossible\n");continue;}
		int last=0;
		for(int i=1;i<=n&&len;i++)//话说它居然要的是下标最小……
			if(f[i]>=len&&last<a[i])
			{
				last=a[i];
				printf("%d ",a[i]);
				len--;
			}
		printf("\n");
    }
    return 0;
}
