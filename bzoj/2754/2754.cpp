#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=1e5+10;
    int n,m,tot,len[N],s[N],tim[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    namespace AC
    {
        int cnt=0,q[N<<3],fail[N],last[N],ans[N],same[N],vis[N];
		pair<int,int> end[N];
        map<int,int> son[N];
        map<int,int>::iterator it;

        inline void insert(int len,int id)
        {
            int now=0;
            for(int i=1;i<=len;i++)
            {
                int x=read();
                if(!son[now].count(x)) son[now][x]=++cnt;
                now=son[now][x];
            }
			if(end[now].second) same[id]=end[now].first;
			else end[now].first=id,same[id]=id;
			end[now].second++;
        }

        inline void get_fail()
        {
            int h=1,t=0;
            for(int i=0;i<=10000;i++)
                if(son[0].count(i)) q[++t]=son[0][i];
                else son[0][i]=0;
            while(h<=t)
            {
                int now=q[h++];
                for(it=son[now].begin();it!=son[now].end();it++)
                {
                    int p=it->second,tmp=fail[now];
                    while(tmp&&!son[tmp].count(it->first))
                        tmp=fail[tmp];
                    fail[p]=son[tmp][it->first];
                    last[p]=end[fail[p]].second?fail[p]:last[fail[p]];
                    q[++t]=p;
                }
            }
        }

        int search(int l,int r,int id)
        {
            int now=0,tot=0;
            for(int i=l;i<=r;i++)
            {
                int x=s[i];
                while(now&&!son[now].count(x))
                    now=fail[now];
                now=son[now][x];
				if(end[now].second&&vis[end[now].first]!=id) 
				{
					vis[end[now].first]=id;
					ans[end[now].first]++;
					tot+=end[now].second;
				}
                for(int j=last[now];j;j=last[j])
                    if(vis[end[j].first]!=id) 
                    {
                        vis[end[j].first]=id;
                        ans[end[j].first]++;
                        tot+=end[j].second;
                    }
            }
			return tot;
        }
    }

    void work()
    {
        n=read(),m=read();
        n<<=1;
        for(int i=1;i<=n;i++)
        {
            len[i]=read();
            for(int j=1;j<=len[i];j++)
                s[++tot]=read();
        }
        for(int i=1;i<=m;i++)
            AC::insert(read(),i);
        AC::get_fail();
        for(int i=1,l=1;i<=n;l+=len[i],i++)
            tim[(i+1)>>1]+=AC::search(l,l+len[i]-1,(i+1)>>1);
        for(int i=1;i<=m;i++)
            printf("%d\n",AC::ans[AC::same[i]]);
        for(int i=1;i<=(n>>1);i++)
            printf("%d ",tim[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
