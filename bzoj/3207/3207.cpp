//玄学调参
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
const int N=200010,seed=107;
const ull inf=0xffffffffffffffff;//18446744073709551615UL

namespace Tree
{   
    int cnt,son[N*40][2],val[N*40];

    void insert(int &root,int last,ull v)
    {
		root=++cnt;
		int tmp=root;//因为这里root传的是引用,不能被while修改
		val[root]=val[last]+1;
		ull l=0,r=inf,mid;
		int d;
		while(l<r)
		{
			mid=l/2+r/2;//不能用(l+r)>>1 l+r会炸
			if((l&1)&&(r&1)) mid++;
			if(v<=mid) d=0,r=mid-1;
			else d=1,l=mid+1;
			son[root][d]=++cnt;
			son[root][d^1]=son[last][d^1];
			root=son[root][d];
			last=son[last][d];
			val[root]=val[last]+1;
		}
		root=tmp;	
    }

    int query(int x,int y,ull v)
    {
		ull l=0,r=inf,mid;
		int d;
		while(l<r)
		{
			mid=l/2+r/2;
			if((l&1)&&(r&1)) mid++;
			if(v<=mid) d=0,r=mid-1;
			else d=1,l=mid+1;
		   	x=son[x][d],y=son[y][d]; 
		}
		return (val[y]-val[x])!=0;
    }
}

namespace TYC
{
    using namespace Tree;
    int n,m,k,a[N],b[N],ro[N];
    ull h[N];

    void work()
    {
		ios::sync_with_stdio(false);
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++) 
		{
			int x;
			cin>>x;
			h[i]=h[i-1]*seed+x;
		}
		ull M=1;
		for(int i=1;i<=k;i++) M*=seed;
		for(int i=k;i<=n;i++) 
			insert(ro[i],ro[i-1],h[i]-h[i-k]*M);
		while(m--)
		{
			int x,y;
			cin>>x>>y;
			ull now=0;
			for(int i=1;i<=k;i++) 
			{
				int x;
				cin>>x;
				now=now*seed+x;
			}
			if(query(ro[x+k-2],ro[y],now)) puts("No");
			else puts("Yes");
		}
    }
}

int main()
{
    //freopen("3207.in","r",stdin);
    TYC::work();
    return 0;
}
