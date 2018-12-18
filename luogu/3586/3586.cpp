#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    typedef pair<int,int> pa;
    const int N=1000010;

    int sz,id[N],val[N],num[N<<1],tmp[N<<1];
    pa modify[N],ques[N];
    ll sum[N<<1];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }
    
    #define lowbit(x) (x)&(-(x))

    inline void add(const int x,const int w)
    {
        if(!x) return;
        for(int i=x;i<=sz;i+=lowbit(i)) 
            num[i]+=w,sum[i]+=tmp[x]*w;
    }

    inline int query_num(const int x)
    {
        if(!x) return 0;
        int ans=0;
        for(int i=x;i;i-=lowbit(i)) ans+=num[i];
        return ans;
    }

    inline ll query_sum(const int x)
    {
        if(!x) return 0;
        ll ans=0;
        for(int i=x;i;i-=lowbit(i)) ans+=sum[i];
        return ans;
    }

    void work()
    {
        int n=read(),m=read(),tot=0;
        char ch;
        for(int i=1;i<=m;i++)
        {
            do ch=getchar(); while(!isalpha(ch));
            id[i]=(ch!='U');
            if(ch=='U') 
            {
                int pos=read(),a=read();
                tmp[++tot]=a;
                modify[i]=pa(pos,a);
            }
            else
            {
                int num=read(),w=read();
                ques[i]=pa(num,w);
            }
        }
        sort(tmp+1,tmp+1+tot);
        sz=unique(tmp+1,tmp+1+tot)-tmp-1;
        for(int i=1;i<=m;i++)
            if(!id[i])
            {
                int p=modify[i].first;
                add(val[p],-1);
                val[p]=lower_bound(tmp+1,tmp+1+sz,modify[i].second)-tmp;
                add(val[p],1);
            }
            else
            {
                int w=lower_bound(tmp+1,tmp+1+sz,ques[i].second)-tmp;
                while(w<sz&&tmp[w]<ques[i].second) w++;
                ques[i].first-=query_num(sz)-query_num(w-1);
                if(query_sum(w-1)>=(ll)ques[i].first*ques[i].second) puts("TAK");
                else puts("NIE");
            }
    }
}

int main()
{
    TYC::work();
    return 0;
}
