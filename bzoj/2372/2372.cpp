#include<bits/stdc++.h>
using namespace std;
int n,m,s,a[100010],b[25010],t[30],fail[25010],tot,ans[100010];

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

struct num
{
    int l1,l2;
    num(int l1=0,int l2=0):l1(l1),l2(l2){}
    bool operator != (const num &d) const
    {
		return l1!=d.l1||l2!=d.l2;
    }
}c[25010];

int lowbit(int x) {return x&(-x);}

void insert(int x,int val)
{
    for(;x<=s;x+=lowbit(x)) t[x]+=val;
}

int get_ans(int x)
{
    int ans=0;
    for(;x;x-=lowbit(x)) ans+=t[x];
    return ans;
}

num get_pair(int x)
{
    return num(get_ans(x-1),get_ans(x));
}

void get_fail()
{
    for(int i=1;i<=s;i++) t[i]=0;
    int tmp=0;
    fail[1]=0;
    for(int i=1;i<m;i++)
    {
		insert(b[i],1);
		while(tmp&&get_pair(b[i+1])!=c[tmp+1]) 
		{
			for(int k=i-tmp+1;k<=i-fail[tmp];k++) insert(b[k],-1);
			tmp=fail[tmp];
		}
		if(c[tmp+1]!=get_pair(b[i+1])) insert(b[i],-1);
		fail[i+1]=++tmp;
    }
}

void search()
{
    for(int i=1;i<=s;i++) t[i]=0;
    int tmp=0;
    for(int i=0;i<n;i++)
    {
		while(tmp&&c[tmp+1]!=get_pair(a[i+1])) 
		{
			for(int k=i-tmp+1;k<=i-fail[tmp];k++) insert(a[k],-1);
			tmp=fail[tmp];
		}
		tmp++;
		if(tmp==m) ans[++tot]=i-tmp+2;
		insert(a[i+1],1);
    }
}

int main()
{
    n=read(),m=read(),s=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=m;i++) b[i]=read();
    for(int i=1;i<=s;i++) t[i]=0;
    for(int i=1;i<=m;i++)
    {
		c[i]=get_pair(b[i]);
		insert(b[i],1);
    }
    c[m+1]=num(-1,-1);
    
    get_fail();
    search();
    printf("%d\n",tot);
    for(int i=1;i<=tot;i++) printf("%d\n",ans[i]);
    return 0;
}
