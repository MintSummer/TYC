#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;

namespace Treap
{
    int val[N],son[N][2],num[N],tagm[N],tagn[N],key[N];
    #define ls son[root][0]
    #define rs son[root][1]

    void pushdown(int root)
    {
		if(!root) return;
		if(tagm[root])
		{
			int t=tagm[root];
			val[ls]+=t,val[rs]+=t;
			tagm[ls]+=t,tagm[rs]+=t;
			tagm[root]=0;
		}
		if(tagn[root])
		{
			int t=tagn[root];
			num[ls]+=t,num[rs]+=t;
			tagn[ls]+=t,tagn[rs]+=t;
			tagn[root]=0;
		}
    }

    void split(int root,int v,int &l,int &r)
    {
		if(!root) {l=r=0;return;}
		pushdown(root);
		if(val[root]<v)
			l=root,split(son[l][1],v,son[l][1],r);
		else 
			r=root,split(son[r][0],v,l,son[r][0]);
    }

    int merge(int x,int y)
    {
		if(!x||!y) return x+y;
		if(key[x]<key[y])
		{
			pushdown(x);
			son[x][1]=merge(son[x][1],y);
			return x;
		}
		else 
		{
			pushdown(y);
			son[y][0]=merge(x,son[y][0]);
			return y;
		}
    }

    int insert(int root,int now)
    {
		int l=0,r=0;
		split(root,val[now],l,r);
		return merge(merge(l,now),r);
    }

    int dfs(int now,int root)
    {
		if(!now) return root;
		pushdown(now);
		root=dfs(son[now][0],root);
		root=dfs(son[now][1],root);
		son[now][0]=son[now][1]=0;
		return insert(root,now);
    }

    void down(int root)
    {
		if(!root) return;
		pushdown(root);
		down(ls),down(rs);
    }
}

namespace TYC
{
using namespace Treap;
    int n,m,root;

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct node
    {
		int c,q;
		bool operator < (const node &x) const
		{
			return (q>x.q)||(q==x.q&&c<x.c);
		}
    }a[N];

    void work()
    {
		srand(20030902);
		n=read();
		for(int i=1;i<=n;i++)
			a[i].c=read(),a[i].q=read();
		sort(a+1,a+1+n);
		m=read();
		for(int i=1;i<=m;i++)
		{
			val[i]=read();
			key[i]=rand();
			root=insert(root,i);
		}
		for(int i=1;i<=n;i++)
		{
			int c=a[i].c;
			int l=0,r=0,L=0,R=0;
			split(root,c,l,r);
			val[r]-=c;
			tagm[r]-=c;
			num[r]++;
			tagn[r]++;
			split(r,c-1,L,R);//分出L为钱用完的人
			l=dfs(L,l);
			root=merge(l,R);//l为买不起i的人,R为买完i还有钱的人
		}
		down(root);
		for(int i=1;i<=m;i++) printf("%d ",num[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
