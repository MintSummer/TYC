#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int p=1e9+7;
    const int N=1205;
    const int S=1505;

    int m,cnt,son[S][10],end[S],fail[S],arr[N],dp[2][2][S];
    string Limit,str;

    void insert(const string &str)
    {
        int len=str.size(),now=0;
        for(int i=0;i<len;i++)
        {
            int c=str[i]-'0';
            if(!son[now][c]) son[now][c]=++cnt;
            now=son[now][c];
        }
        end[now]=1;
    }

    void get_fail()
    {
        static queue<int> q;
        for(int i=0;i<10;i++)
            if(son[0][i]) q.push(son[0][i]);
        while(!q.empty())
        {
            int now=q.front(),f=fail[now];
            q.pop();
            end[now]|=end[f];
            for(int i=0;i<10;i++)
                if(son[now][i])
                {
                    fail[son[now][i]]=son[f][i];
                    q.push(son[now][i]);
                }
                else son[now][i]=son[f][i];
        }
    }

    inline void Mod(int &x) {x=(x>=p?x-p:x);}
    
    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>Limit>>m;
        for(int i=1;i<=m;i++)
            cin>>str,insert(str);
        get_fail();
        int len=Limit.size(),now=0;
        for(int i=0;i<len;i++)
            arr[i+1]=Limit[i]-'0';
		for(int i=1;i<arr[1];i++)
			dp[now][0][son[0][i]]++;
		dp[now][1][son[0][arr[1]]]++;
        for(int i=2;i<=len;i++)
        {
			now^=1;
            memset(dp[now],0,sizeof(dp[now]));
			for(int i=1;i<10;i++) 
				dp[now][0][son[0][i]]++;
            for(int k=0;k<=cnt;k++) 
            {
				if(end[k]) continue;
				int val=dp[now^1][0][k],t=arr[i];		
				if(val) for(int j=0;j<10;j++) 
                	if(!end[son[k][j]])
                        Mod(dp[now][0][son[k][j]]+=val);
				val=dp[now^1][1][k];
				if(val) for(int j=0;j<t;j++) 
                    if(!end[son[k][j]])
                        Mod(dp[now][0][son[k][j]]+=val);
               	if(val&&!end[son[k][t]])
                    Mod(dp[now][1][son[k][t]]+=val);
            }
        }
        int ans=0;
        for(int i=0;i<=cnt;i++)
            if(!end[i])
               Mod(ans+=dp[now][0][i]),Mod(ans+=dp[now][1][i]);
        printf("%d\n",ans);
    }
}

int main()
{
	TYC::work();
	return 0;
}
