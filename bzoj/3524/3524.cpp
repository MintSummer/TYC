#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

namespace TYC
{
    const int N=500010;
    int n,m,root[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    namespace Tree
    {
        const int M=N*40;
        int cnt=0,sum[M],ls[M],rs[M];

        void insert(int &root,int last,int l,int r,int val)
        {
            root=++cnt;
            ls[root]=ls[last],rs[root]=rs[last];
            sum[root]=sum[last]+1;
            if(l==r) return;
            int mid=(l+r)>>1;
            if(val<=mid) insert(ls[root],ls[last],l,mid,val);
            else insert(rs[root],rs[last],mid+1,r,val);
        }

        int query(int L,int R,int l,int r,int num)
        {
            if(l==r) return l;
            int mid=(l+r)>>1;
            if(sum[ls[R]]-sum[ls[L]]>num) 
                return query(ls[L],ls[R],l,mid,num);
            else if(sum[rs[R]]-sum[rs[L]]>num)
                return query(rs[L],rs[R],mid+1,r,num);
            else return 0;
        }
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=n;i++)
            Tree::insert(root[i],root[i-1],1,n,read());
        while(m--)
        {
            int l=read(),r=read();
            printf("%d\n",Tree::query(root[l-1],root[r],1,n,(r-l+1)/2));
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}