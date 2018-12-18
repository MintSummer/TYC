#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100010;
int priority[100010];

namespace Tree
{
    int cnt;
	struct node
	{
		int ls,rs;
		ll size,sum;
	}tree[N*40];
    
    void insert(int &root,int l,int r,int num,int tag)
    {
        tree[++cnt]=tree[root];
		root=cnt;
        tree[root].size+=(ll)tag;
        tree[root].sum+=(ll)priority[num]*tag;
		if(l==r) return;
        int mid=(l+r)>>1;
        if(num<=mid)  insert(tree[root].ls,l,mid,num,tag);
        else insert(tree[root].rs,mid+1,r,num,tag);
    }

    ll query(int root,int l,int r,int k)
    {
        if(l==r) return tree[root].sum/tree[root].size*k;
        int res=tree[tree[root].ls].size,mid=(l+r)>>1;
        if(k<=res) return query(tree[root].ls,l,mid,k);
        else return tree[tree[root].ls].sum+query(tree[root].rs,mid+1,r,k-res);
    }
}

namespace TYC
{    
    int m,n,root[N];
    struct node
    {
        int pos,p,tag;
        bool operator < (const node &t) const
        {
            return (pos<t.pos)||(pos==t.pos&&p<t.p);
        }
    }a[N<<1];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    void work()
    {
        m=read(),n=read();
        for(int i=1;i<=m;i++) 
        {
            int s=read(),e=read(),p=read();
            priority[i]=p;
            a[(i<<1)-1]=(node){s,p,1};
            a[(i<<1)]=(node){e+1,p,-1};
        }
        sort(priority+1,priority+1+m);
        sort(a+1,a+1+(m<<1));
		root[0]=0;
        for(int i=1,j=1;i<=n;i++)
		{
			root[i]=root[i-1];
            for(;j<=(m<<1)&&a[j].pos==i;j++)
            {
                int th=lower_bound(priority+1,priority+1+n,a[j].p)-priority;
                Tree::insert(root[i],1,n,th,a[j].tag);
            }
		}
        ll ans=1;
        for(int kase=1;kase<=n;kase++)
        {
            int x=read(),a=read(),b=read(),c=read();
            int k=1+(a*ans+b)%c;
            if(k>=Tree::tree[root[x]].size) ans=Tree::tree[root[x]].sum;
            else ans=Tree::query(root[x],1,n,k);
            printf("%lld\n",ans);
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}