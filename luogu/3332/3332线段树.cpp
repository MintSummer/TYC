//Time:3964ms
#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    #define int long long
    const int MAXN=50010;
    int ans[MAXN],ques[MAXN];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    struct question
    {
		int opt,l,r,id;
		int val;
    }a[MAXN],ql[MAXN],qr[MAXN];

    struct node
    {
		int l,r,sum,tag;
    }tree[MAXN*4];

    void build(int root,int lt,int rt)
    {
		tree[root].l=lt,tree[root].r=rt;
		if(lt==rt) return;
		int mid=(lt+rt)>>1;
		build(root*2,lt,mid),build(root*2+1,mid+1,rt);
    }

    void pushdown(int root)
    {
		int tag=tree[root].tag;
		if(!tag) return;
		int lt=tree[root].l,rt=tree[root].r,mid=(lt+rt)>>1;
		node &int=tree[root*2],&rr=tree[root*2+1];
		int.tag+=tag,rr.tag+=tag;
		int.sum+=tag*(mid-lt+1),rr.sum+=tag*(rt-mid);
		tree[root].tag=0;
    }

    void add(int root,int s,int e,int val)
    {
		int lt=tree[root].l,rt=tree[root].r;
		if(s<=lt&&rt<=e)
		{
			tree[root].sum+=(rt-lt+1)*val;
			tree[root].tag+=val;
			return;
		}
		pushdown(root);
		int mid=(lt+rt)>>1;
		if(e<=mid) add(root*2,s,e,val);
		else if(s>mid) add(root*2+1,s,e,val);
		else add(root*2,s,mid,val),add(root*2+1,mid+1,e,val);
		tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
    }

    int query(int root,int s,int e)
    {
		int lt=tree[root].l,rt=tree[root].r;
		if(s<=lt&&rt<=e) return tree[root].sum;
		pushdown(root);
		int mid=(lt+rt)>>1;
		if(e<=mid) return query(root*2,s,e);
		else if(s>mid) return query(root*2+1,s,e);
		else return query(root*2,s,mid)+query(root*2+1,mid+1,e);
    }

    void solve(int l,int r,int L,int R)//lr是询问,LR是值
    {
		if(l>r) return;
		if(L==R) 
		{
			for(int i=l;i<=r;i++)
				if(a[i].opt==2) ans[a[i].id]=L;
			return;
		}
		int Mid=(L+R)>>1;
		int lt=0,rt=0;
		for(int i=l;i<=r;i++)
		{
			if(a[i].opt==1)
			{
				if(a[i].val<=Mid) ql[++lt]=a[i];
				else qr[++rt]=a[i],add(1,a[i].l,a[i].r,1);
			}
			else
			{
				int num=query(1,a[i].l,a[i].r);
				if(a[i].val<=num) qr[++rt]=a[i];
				else a[i].val-=num,ql[++lt]=a[i];
			}
		}
		for(int i=l;i<=r;i++)
			if(a[i].opt==1&&a[i].val>Mid) add(1,a[i].l,a[i].r,-1);
		for(int i=1;i<=lt;i++) a[l+i-1]=ql[i];
		for(int i=1;i<=rt;i++) a[l+lt+i-1]=qr[i];
		solve(l,l+lt-1,L,Mid);
		solve(l+lt,r,Mid+1,R);
    }

    void work()
    {
		int n=read(),m=read();	
		build(1,1,n);
		for(int i=1;i<=m;i++)
		{
			int opt=read(),l=read(),r=read();
			int val=read();
			a[i]=(question){opt,l,r,i,val};
			ques[i]=(opt==2);
		}
		solve(1,m,-n,n);
		for(int i=1;i<=m;i++) 
			if(ques[i]) printf("%lld\n",ans[i]);
    }
}

signed main()
{
    TYC::work();
    return 0;
}
