#include<bits/stdc++.h>
using namespace std;
const int MAXN=2*1e5+10;
int n,m,tot,cnt,a[MAXN],v[MAXN],ro[MAXN];

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){f|=(ch=='-');ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return f?-x:x;
}

struct Tree
{
    int ls[MAXN*20],rs[MAXN*20],val[MAXN*20];

    void build(int &root,int lt,int rt)
    {
		root=cnt++;val[root]=0;
		if(lt==rt) return;
		int mid=(lt+rt)>>1;
		build(ls[root],lt,mid);
		build(rs[root],mid+1,rt);
    }
    
    void insert(int &root,int &last,int lt,int rt,int v)
    {
		root=cnt++;val[root]=val[last]+1;
		ls[root]=ls[last],rs[root]=rs[last];
		if(lt==rt) return;
		int mid=(lt+rt)>>1;
		if(v<=mid) insert(ls[root],ls[last],lt,mid,v);
		else insert(rs[root],rs[last],mid+1,rt,v);
    }

    int ask(int x,int y,int lt,int rt,int k)
    {
		int t=val[ls[y]]-val[ls[x]];
		if(lt==rt) return lt;
		int mid=(lt+rt)>>1;
		if(k<=t) return ask(ls[x],ls[y],lt,mid,k);
		else return ask(rs[x],rs[y],mid+1,rt,k-t);
    }
}tree;

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read(),v[i]=a[i];

    sort(v+1,v+1+n);
    tot=unique(v+1,v+1+n)-v-1;

    tree.build(ro[0],1,tot);
    int t;
    for(int i=1;i<=n;i++)
    {
		t=lower_bound(v+1,v+1+tot,a[i])-v;
		tree.insert(ro[i],ro[i-1],1,tot,t);
    }

    int x,y,k;
    for(int i=1;i<=m;i++)
    {
		x=read(),y=read(),k=read();
		printf("%d\n",v[tree.ask(ro[x-1],ro[y],1,tot,k)]);
    }
    return 0;
}
