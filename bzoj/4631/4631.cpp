#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=1e5+10;

    int ans,interval[N],arr[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    inline void write(int x)
    {
        int len=0;
        static int bask[50];
        do bask[++len]=x%10,x/=10; while(x);
        for(;len;len--) putchar('0'+bask[len]);
        putchar('\n');
    }

    namespace Tree
    {
        struct node
        {
            int sum,flag;
            vector<int> list;
        }tree[N<<2]; 

        #define ls root<<1
        #define rs root<<1|1

        void build(const int root,const int l,const int r)
        {
            if(l==r) {tree[root].sum=arr[l];return;}
            int mid=(l+r)>>1;
            build(ls,l,mid),build(rs,mid+1,r);
        }

        void inter(const int root,const int l,const int r,const int s,const int e,int id)
        {
            if(s<=l&&r<=e) 
            {
                interval[id]++;
                tree[root].list.push_back(id);
                return;
            }
            int mid=(l+r)>>1;
            if(s<=mid) inter(ls,l,mid,s,e,id);
            if(e>mid) inter(rs,mid+1,r,s,e,id);
        }

        inline void update(const int root,const int tag=0)
        {
            if(!tag) tree[root].sum=tree[ls].sum+tree[rs].sum;
            if(!tree[root].sum&&!tree[root].flag)
            {
                tree[root].flag=1;
                for(int i=0,sz=tree[root].list.size();i<sz;i++)
                    if(!(--interval[tree[root].list[i]])) ans++;
            }
        }

        void init(const int root,const int l,const int r)
        {
            if(l==r) {update(root,1);return;}
            int mid=(l+r)>>1;
            init(ls,l,mid),init(rs,mid+1,r);
            update(root);
        }

        void modify(const int root,const int l,const int r,const int pos)
        {
            if(l==r)
            {
                tree[root].sum--;
                if(!tree[root].sum) 
                {
                    tree[root].flag=1;
                    for(int i=0,sz=tree[root].list.size();i<sz;i++)
                        if(!(--interval[tree[root].list[i]])) ans++;
                }
                return;
            }
            int mid=(l+r)>>1;
            if(pos<=mid) modify(ls,l,mid,pos);
            else modify(rs,mid+1,r,pos);
            update(root);
        }
    }

    void work()
    {
        int n=read(),m=read();
        for(int i=1;i<=n;i++) arr[i]=read();
        Tree::build(1,1,n);
        for(int i=1;i<=m;i++)
        {
            int l=read(),r=read();
            Tree::inter(1,1,n,l,r,i);
        }
        Tree::init(1,1,n);
        int q=read();
        while(q--)
        {
            int x=(read()+ans-1)%n+1;
            Tree::modify(1,1,n,x);
            write(ans);
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
