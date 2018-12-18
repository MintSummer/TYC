#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
int n,m,cnt,a[MAXN],ro[MAXN];

int read()
{
    int x=0,f=0;char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

struct Tree
{
    int ls[MAXN*20],rs[MAXN*20],val[MAXN*20];
    void build(int &root,int lt,int rt)
    {
		root=cnt++;
		if(lt==rt) {val[root]=a[lt];return;}
		int mid=(lt+rt)>>1;
		build(ls[root],lt,mid);
		build(rs[root],mid+1,rt);
    }
    void change(int &root,int last,int lt,int rt,int x,int v)
    {
		root=++cnt;
		ls[root]=ls[last],rs[root]=rs[last];
		if(lt==rt) {val[root]=v;return;}
		int mid=(lt+rt)>>1;
		if(x<=mid) change(ls[root],ls[last],lt,mid,x,v);
		else change(rs[root],rs[last],mid+1,rt,x,v);
    }
    int ask(int root,int lt,int rt,int x)
    {
		if(lt==rt) return val[root];
		int mid=(lt+rt)>>1;
		if(x<=mid) return ask(ls[root],lt,mid,x);
		else return ask(rs[root],mid+1,rt,x);
    }
}tree;

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    tree.build(ro[0],1,n);
    int opt,v,loca,val;
    for(int i=1;i<=m;i++)
    {
		v=read(),opt=read(),loca=read();
		if(opt==1)
		{
			val=read();
			tree.change(ro[i],ro[v],1,n,loca,val);
		}
		else 
		{
			printf("%d\n",tree.ask(ro[v],1,n,loca));
			ro[i]=ro[v];
		}
    }
}
