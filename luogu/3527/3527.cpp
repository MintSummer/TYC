#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    #define lowbit(x) x&(-x)
    const int N=3e5+10;
    int n,m,k,ans[N];
    ll c[N],need[N];
    vector<int> station[N];

    inline int read()
    {
	    int x=0,f=0;char ch=getchar();
	    while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	    return f?-x:x;
    }

    struct ques
    {
    	int id,opt,l,r;
		ll k;
    }q[N*2],ql[N*2],qr[N*2];

    void add(int x,ll val)
    {
   		for(;x<=m;x+=lowbit(x)) c[x]+=val;
    }

    ll query(int x)
    {
	    ll sum=0;
	    for(;x;x-=lowbit(x)) sum+=c[x];
	    return sum;
    }

    void solve(int l,int r,int L,int R)
    {
	    if(l>r) return;
	    if(L==R) 
	    {
	        for(int i=l;i<=r;i++)
	        	if(q[i].opt==1) ans[q[i].id]=L;
	        return;
	    }
	    int Mid=(L+R)>>1,cntl=0,cntr=0;
	    for(int i=l;i<=r;i++)
	    {
	        if(q[i].opt==1)
	        {
		        ll sum=0;
		        int now=q[i].id;
		        for(int j=0;j<station[now].size();j++)
		        {
		            sum+=query(station[now][j]);
		            if(sum>=q[i].k) break;
		        }
		        if(sum>=q[i].k) ql[++cntl]=q[i];
		        else q[i].k-=sum,qr[++cntr]=q[i];
	        }
	        else 
	        {
		        if(q[i].id<=Mid)
		        {
		            if(q[i].opt==2) 
		           		add(q[i].l,q[i].k),add(q[i].r+1,-q[i].k);
		            else 
		            	add(1,q[i].k),add(q[i].r+1,-q[i].k),add(q[i].l,q[i].k);
		            ql[++cntl]=q[i];
		        }
		        else qr[++cntr]=q[i];
	        }
	    }
	    for(int i=l;i<=r;i++)
		    if(q[i].opt!=1&&q[i].id<=Mid)
		    {
		        if(q[i].opt==2)
		       		add(q[i].l,-q[i].k),add(q[i].r+1,q[i].k);
		        else 
		        	add(1,-q[i].k),add(q[i].r+1,q[i].k),add(q[i].l,-q[i].k);
		    }
	    for(int i=1;i<=cntl;i++) q[l+i-1]=ql[i];
	    for(int i=1;i<=cntr;i++) q[l+cntl+i-1]=qr[i];
	    if(cntl) solve(l,l+cntl-1,L,Mid);
	    if(cntr) solve(l+cntl,r,Mid+1,R);
    }

    void work()
    {
	    n=read(),m=read();
	    for(int i=1;i<=m;i++)
	        station[read()].push_back(i);
	    for(int i=1;i<=n;i++) need[i]=read();
	    k=read();
	    for(int i=1;i<=k;i++)
	    {
	        q[i].l=read();q[i].r=read();q[i].k=read();
	        if(q[i].r>=q[i].l) q[i].opt=2;else q[i].opt=3;
	        q[i].id=i;
	    }
	    for(int i=1;i<=n;i++)
	    {
	        q[i+k].k=need[i];q[i+k].opt=1;
	        q[i+k].id=i;
	    }
	    solve(1,n+k,1,k+1);
	    for(int i=1;i<=n;i++) 
	        if(ans[i]!=k+1) printf("%d\n",ans[i]);
	        else puts("NIE");
	}
}

int main()
{
    TYC::work();
    return 0;
}
