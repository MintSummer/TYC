#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

namespace TYC
{
    const int N=12*50+10,M=(1<<12)+100;
    const int inf=0x3f3f3f3f;
    int n,ans=inf,dp[N][M],nxt[N][M];

    namespace AC
    {
        int cnt,son[N][26],q[N*10],fail[N],end[N];

        inline void insert(char *ch,int id)
        {
            int len=strlen(ch+1),now=0;
            for(int i=1;i<=len;i++)
            {
                int c=ch[i]-'A';
                if(!son[now][c]) son[now][c]=++cnt;
                now=son[now][c];
            }
            end[now]|=(1<<(id-1));
        }

        void get_fail()
        {
            int h=1,t=0;
            for(int i=0;i<26;i++)
                if(son[0][i]) q[++t]=son[0][i];
            while(h<=t)
            {
                int now=q[h++],x;
                for(int i=0;i<26;i++)
                    if(x=son[now][i])
                    {
                        fail[x]=son[fail[now]][i];
                        q[++t]=x;
                    }
                    else son[now][i]=son[fail[now]][i];
            }
            for(int i=1;i<=cnt;i++)
            {
                int tmp=fail[i];
                while(tmp)
                    end[i]|=end[tmp],tmp=fail[tmp];
            }
        }
    }
    using namespace AC;

    struct node
    {
        int now,s;
    };

    void get_ans()
    {
        static queue<node> q;
        dp[0][0]=0;
        q.push((node){0,0});
        while(!q.empty())
        {
            int now=q.front().now,s=q.front().s;
            q.pop();
            for(int i=0;i<26;i++)
                if(son[now][i])
                {
                    int x=son[now][i],t=s|end[x];
                    if(dp[x][t]>dp[now][s]+1)
                    {
                        dp[x][t]=dp[now][s]+1;
                        q.push((node){x,t});
                    }
                }
        }
    }

    int dfs(int now,int s)
    {
        if(s==(1<<n)-1) return dp[now][s];
        int x;
        for(int i=0;i<26;i++)
            if((x=son[now][i])&&dp[now][s]+1==dp[x][s|end[x]])
                if(dfs(x,s|end[x])==ans) {nxt[now][s]=i;return ans;}
        return -1;
    } 

    void work()
    {
        scanf("%d",&n);
        char ch[60];
        for(int i=1;i<=n;i++)
        {
            scanf("%s",ch+1);
            insert(ch,i);
        }
        get_fail();
        memset(dp,inf,sizeof(dp));
        get_ans();
        for(int i=1;i<=cnt;i++)
            ans=min(ans,dp[i][(1<<n)-1]);
        dfs(0,0);
        int now=0,s=0;
        while(dp[now][s]!=ans)
        {
            putchar(nxt[now][s]+'A');
            int t=son[now][nxt[now][s]];
            s|=end[t];
            now=t;
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}