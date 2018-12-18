#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

namespace TYC
{
    namespace IO
    {
        inline int read()
        {
            int x=0,f=0;char ch=getchar();
            while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
            while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
            return f?-x:x;
        }

        inline void write(int x)
        {
            if(x<0) putchar('-'),x=-x;
            if(!x) putchar('0');
            else
            {
                int len=0;
                static int bask[20];
                while(x) bask[++len]=x%10,x/=10;
                for(;len;len--) putchar('0'+bask[len]);
            }
            putchar('\n');
        }
    }

    using IO::read;
    using IO::write;

    int n,m,ques;

    namespace Subtask1
    {
        const int N=210;
        int a[N][N],sum[N][N][1010],num[N][N][1010];

        void work()
        {
            for(int i=1;i<=n;i++)
                for(int j=1;j<=m;j++)
                    a[i][j]=read();
            for(int i=1;i<=n;i++)
                for(int j=1;j<=m;j++)
                    for(int k=a[i][j];k;k--)
                    {
                        sum[i][j][k]+=a[i][j];
                        num[i][j][k]++;
                    }
            for(int i=1;i<=n;i++)
                for(int j=1;j<=m;j++)
                    for(int k=1;k<=1000;k++)
                    {
                        sum[i][j][k]+=sum[i-1][j][k]+sum[i][j-1][k]-sum[i-1][j-1][k];
                        num[i][j][k]+=num[i-1][j][k]+num[i][j-1][k]-num[i-1][j-1][k];
                    }
            while(ques--)
            {
                int x1=read()-1,y1=read()-1,x2=read(),y2=read(),height=read();
                int l=1,r=1000,mid,ans=-1,last,tot;
                while(l<=r)
                {
                    mid=(l+r)>>1;
                    int tmp=sum[x2][y2][mid]-sum[x1][y2][mid]-sum[x2][y1][mid]+sum[x1][y1][mid];
                    if(tmp>=height) 
                    {
                        ans=num[x2][y2][mid]-num[x1][y2][mid]-num[x2][y1][mid]+num[x1][y1][mid];
                        tot=tmp,last=mid;
                        l=mid+1;
                    }
                    else r=mid-1;
                }
                if(ans==-1) puts("Poor QLW");
                else 
                {   
                    for(;tot-last>=height;last++)
                    {
                        int tim=num[x2][y2][last]-num[x1][y2][last]-num[x2][y1][last]+num[x1][y1][last];
                        while(tim&&tot-last>=height) 
                            ans--,tot-=last,tim--;
                    }
                    write(ans);
                }
            }
        }
    }

    namespace Subtask2
    {
        const int N=500010;
        int root[N];

        namespace Tree
        {
            const int M=N*12;
            int cnt,sum[M],ls[M],rs[M],num[M];

            void insert(int &root,int last,int l,int r,int pos)
            {
                root=++cnt;
                sum[root]=sum[last]+pos;
                num[root]=num[last]+1;
                ls[root]=ls[last],rs[root]=rs[last];
                if(l==r) return;
                int mid=(l+r)>>1;
                if(pos<=mid) insert(ls[root],ls[last],l,mid,pos);
                else insert(rs[root],rs[last],mid+1,r,pos);
            }

            int query(int x,int y,int l,int r,int k)
            {
                if(l==r) return k/l+(k%l!=0);
                int mid=(l+r)>>1,ans=num[y]-num[x];
                if(sum[rs[y]]-sum[rs[x]]>=k) 
                    return query(rs[x],rs[y],mid+1,r,k);
                else 
                {
                    k-=sum[rs[y]]-sum[rs[x]];
                    return num[rs[y]]-num[rs[x]]+query(ls[x],ls[y],l,mid,k);
                }
            }
        }

        void work()
        {
            swap(n,m);
            for(int i=1;i<=n;i++)
            {
                int val=read();
                Tree::insert(root[i],root[i-1],1,1000,val);
            }
            int l,r,height;
            while(ques--)
            {
                read(),l=read(),read(),r=read(),height=read();
                if(Tree::sum[root[r]]-Tree::sum[root[l-1]]<height) 
                    puts("Poor QLW");
                else 
                    write(Tree::query(root[l-1],root[r],1,1000,height)); 
            }
        }
    }

    void work()
    {
        n=read(),m=read(),ques=read();
        if(n==1) Subtask2::work();
        else Subtask1::work();
    }
}

int main()
{
    TYC::work();
    return 0;
}