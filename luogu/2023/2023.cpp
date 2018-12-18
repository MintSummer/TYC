#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=100010;
    int n,m,p,a[MAXN];

    struct node
    {
		int l,r;
		ll sum,tagc,tagj;
		void Tril(ll c,ll j)
		{
			tagc=tagc*c%p; 
			tagj=((tagj*c%p)+j)%p;
			sum=((sum*c)+j*(r-l+1))%p;
		} 
    }tree[MAXN*4];

    void update(int root)
    {
		tree[root].sum=(tree[root*2].sum+tree[root*2+1].sum)%p;
    }

    void build(int root,int lt,int rt)
    {
		tree[root].l=lt,tree[root].r=rt;
		tree[root].tagc=1,tree[root].tagj=0;
		if(lt==rt)
		{
			tree[root].sum=a[lt]%p;
			return;
		}
		int mid=(lt+rt)>>1;
		build(root*2,lt,mid),build(root*2+1,mid+1,rt);
		update(root);
    }
    
    void pushdown(int root)
    {
		int tagc=tree[root].tagc,tagj=tree[root].tagj;
		if(tagc==1&&tagj==0) return;
		if(tree[root].l==tree[root].r) return;
		tree[root*2].Tril(tagc,tagj);
		tree[root*2+1].Tril(tagc,tagj);
		tree[root].tagc=1,tree[root].tagj=0;
    }

    void mul(int root,int s,int e,ll val)
    {
		int lt=tree[root].l,rt=tree[root].r;
		if(s<=lt&&rt<=e)
		{
			tree[root].tagc=(tree[root].tagc*val)%p;
			tree[root].tagj=(tree[root].tagj*val)%p;
			tree[root].sum=(tree[root].sum*val)%p;
			return;
		}
		pushdown(root);
		int mid=(lt+rt)>>1;
		if(e<=mid) mul(root*2,s,e,val);
		else if(s>mid) mul(root*2+1,s,e,val);
		else mul(root*2,s,mid,val),mul(root*2+1,mid+1,e,val);
		update(root);
    }

    void add(int root,int s,int e,ll val)
    {
		int lt=tree[root].l,rt=tree[root].r;
		if(s<=lt&&rt<=e)
		{
			tree[root].tagj=(tree[root].tagj+val)%p;
			tree[root].sum=(tree[root].sum+val*(rt-lt+1)%p)%p;
			return;
		}
		pushdown(root);
		int mid=(lt+rt)>>1;
		if(e<=mid) add(root*2,s,e,val);
		else if(s>mid) add(root*2+1,s,e,val);
		else add(root*2,s,mid,val),add(root*2+1,mid+1,e,val);
		update(root);
    }

    ll query(int root,int s,int e)
    {
		int lt=tree[root].l,rt=tree[root].r;
		if(s<=lt&&rt<=e) return tree[root].sum%p;
		pushdown(root);
		int mid=(lt+rt)>>1;
		if(e<=mid) return query(root*2,s,e);
		else if(s>mid) return query(root*2+1,s,e);
		else return (query(root*2,s,mid)+query(root*2+1,mid+1,e))%p;
    }

    void work()
    {
		ios::sync_with_stdio(false);
		cin>>n>>p;
		for(int i=1;i<=n;i++) cin>>a[i];
		cin>>m;
		build(1,1,n);
		int opt,l,r;ll k;
		while(m--)
		{
			cin>>opt>>l>>r;
			if(l>r) swap(l,r);
			if(opt==1) cin>>k,mul(1,l,r,k);
			else if(opt==2) cin>>k,add(1,l,r,k);
			else printf("%lld\n",query(1,l,r));
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
