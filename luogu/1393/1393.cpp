#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    typedef long long ll;
    #define lowbit(x) x&(-x)
    const int N=200010;
    int n,m,arr[N],del[N],ans[N],c[N];

    struct ques
    {
        int tim,pos,val;
    }q[N];

    bool cmptim(const ques &a,const ques &b)
    {
        return a.tim<b.tim;
    }

    bool cmp1(const ques &a,const ques &b)
    {
        return a.pos<b.pos;
    }

    void add(int x,int val)
    {
        for(;x<=n;x+=lowbit(x)) c[x]+=val;
    }

    int query(int x)
    {
        int sum=0;
        for(;x;x-=lowbit(x)) sum+=c[x];
        return sum;
    }

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    void cdq(int l,int r)
    {
        if(l==r) return;
        int mid=(l+r)>>1;
        cdq(l,mid),cdq(mid+1,r);
        
        sort(q+l,q+mid+1,cmp1);
        sort(q+mid+1,q+r+1,cmp1);
        int i=l;
        for(int j=mid+1;j<=r;j++)
        {
            while(i<=mid&&q[i].pos<q[j].pos)
                add(q[i].val,1),i++;
            ans[q[j].tim]+=i-l-query(q[j].val);
        }
        for(i--;i>=l;i--) add(q[i].val,-1);
        i=mid;
        for(int j=r;j>mid;j--)
        {
            while(i>=l&&q[i].pos>q[j].pos)
                add(q[i].val,1),i--;
            ans[q[j].tim]+=query(q[j].val);
        }
        for(i++;i<=mid;i++) add(q[i].val,-1);
    }

    void work()
    {	
        n=read(),m=read();
		static int array[N];
        for(int i=1;i<=n;i++) arr[i]=array[i]=read();
		sort(array+1,array+1+n);
		int num=unique(array+1,array+1+n)-array-1;
		for(int i=1;i<=n;i++)
			arr[i]=lower_bound(array+1,array+1+num,arr[i])-array;
        int tot=0,tmp=n;
        for(int i=1;i<=m;i++)
        {
            int x=read();
            q[++tot]=(ques){tmp--,x,arr[x]};
            del[x]=1;
        }
        tmp=n-m;
        for(int i=1;i<=n;i++)
            if(!del[i]) q[++tot]=(ques){tmp--,i,arr[i]};
        sort(q+1,q+tot+1,cmptim);
        cdq(1,n);
        for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
        for(int i=n;i>=n-m;i--) printf("%d ",ans[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
