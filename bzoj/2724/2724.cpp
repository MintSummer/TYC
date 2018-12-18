#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=4e4+10,M=5e4+10;
    int n,m,block,belong[N],end[1010],col[N],cnt[N],f[1010][1010];
    vector<int> appear[M];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    inline void init(int id,int start)
    {
        memset(cnt,0,sizeof(cnt));
        int mx=0,num;
        for(int i=start;i<=n;i++)
        {
            cnt[col[i]]++;
            if(cnt[col[i]]>mx) 
                mx=cnt[col[i]],num=col[i];
            else if(cnt[col[i]]==mx&&col[i]<num)
                num=col[i];
            f[id][belong[i]]=num;
        }
    }

    int get_num(int l,int r,int x)
    {
        return upper_bound(appear[x].begin(),appear[x].end(),r)-
               lower_bound(appear[x].begin(),appear[x].end(),l);
    }

    int query(int l,int r)
    {
        int ans=f[belong[l]+1][belong[r]-1];
        int mx=get_num(l,r,ans);
        for(int i=l;i<=min(end[belong[l]],r);i++)
        {
            int num=get_num(l,r,col[i]);
            if(num>mx) mx=num,ans=col[i];
            else if(num==mx&&col[i]<ans) ans=col[i];
        }
        if(belong[l]==belong[r]) return ans;
        for(int i=max(l,end[belong[r]-1]+1);i<=r;i++)
        {
            int num=get_num(l,r,col[i]);
            if(num>mx) mx=num,ans=col[i];
            else if(num==mx&&col[i]<ans) ans=col[i];
        }
        return ans;
    }

    void work()
    {
        n=read(),m=read();
        static int tmp[N];
        for(int i=1;i<=n;i++) 
            col[i]=tmp[i]=read();
        sort(tmp+1,tmp+1+n);
        int size=unique(tmp+1,tmp+1+n)-tmp-1;
        for(int i=1;i<=n;i++)
        {
            col[i]=lower_bound(tmp+1,tmp+1+size,col[i])-tmp;
            appear[col[i]].push_back(i);
        }
        
        block=sqrt(n/log2(n));
        for(int i=1;i<=n;i++) belong[i]=(i-1)/block+1;
        for(int i=1;i<=belong[n];i++) end[i]=end[i-1]+block;
        for(int i=1;i<=belong[n];i++) init(i,end[i-1]+1);

        int ans=0;
        while(m--)
        {
            int l=read(),r=read();
            l=(l+ans-1)%n+1,r=(r+ans-1)%n+1;
            if(l>r) swap(l,r);
            printf("%d\n",ans=tmp[query(l,r)]);
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}