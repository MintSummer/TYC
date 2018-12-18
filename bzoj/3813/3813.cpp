#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int p=19961993,N=100000;
    const int prime[70]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,
    73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,
    181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281};
    ll bin[70],inv[300];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    void init()
    {
		bin[0]=1LL;
		for(int i=1;i<60;i++) bin[i]=bin[i-1]<<1;
		inv[1]=1;
		for(int i=2;i<=281;i++) inv[i]=(ll)(p-p/i)*inv[p%i]%p;
    }

    struct node
    {
		ll mul,now;
    }tree[N*4+100];

    void update(int root)
    {
		tree[root].mul=tree[root*2].mul*tree[root*2+1].mul%p;
		tree[root].now=tree[root*2].now|tree[root*2+1].now;
    }

    void build(int root,int l,int r)
    {
		if(l==r) 
		{
			tree[root].mul=3;
			tree[root].now|=bin[1];
			return;
		}
		int mid=(l+r)>>1;
		build(root*2,l,mid),build(root*2+1,mid+1,r);
		update(root);
    }

    void change(int root,int l,int r,int pos,int val)
    {
		if(l==pos&&pos==r)
		{
			tree[root].mul=val%p;
			ll tmp=0;
			for(int i=0;i<60;i++)
			if(val%prime[i]==0) tmp|=bin[i];
			tree[root].now=tmp;
			return;
		}
		int mid=(l+r)>>1;
		if(pos<=mid) change(root*2,l,mid,pos,val);
		else if(pos>mid) change(root*2+1,mid+1,r,pos,val);
		update(root);
    }

    node query(int root,int l,int r,int s,int e)
    {
		if(s<=l&&r<=e) return tree[root];
		int mid=(l+r)>>1;
		if(e<=mid) return query(root*2,l,mid,s,e);
		else if(s>mid) return query(root*2+1,mid+1,r,s,e);
		else 
		{
			node ll=query(root*2,l,mid,s,mid),rr=query(root*2+1,mid+1,r,mid+1,e);
			node ans;
			ans.mul=ll.mul*rr.mul%p;
			ans.now=ll.now|rr.now;
			return ans;
		}
    }

    void work()
    {
		init();
		build(1,1,N);
		int kase=read();
		while(kase--)
		{
			int opt=read(),x=read(),y=read();
			if(opt) change(1,1,N,x,y);
			else 
			{
				node tmp=query(1,1,N,x,y);
				ll ans=tmp.mul;
				for(int i=0;i<60;i++)
					if(tmp.now&bin[i]) 
						ans=ans*(prime[i]-1)*inv[prime[i]]%p;
				printf("%lld\n",ans);
			}
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
