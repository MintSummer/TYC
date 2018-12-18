#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    int n,tot,num[30],A[30],B[30],C[30],vis[30],list[30],used[30];
    char ch[30];

    inline int Mod(int x)
    {
        return x>=n?x-n:x;
    }

    bool check()
    {
        if(num[A[n]]+num[B[n]]>=n) return false;
        for(int i=1;i<=n;i++)
        {
            int a=num[A[i]],b=num[B[i]],c=num[C[i]];
            if(a==-1||b==-1||c==-1) continue;
            if(c!=Mod(a+b)&&c!=Mod(a+b+1)) return false;
        }
        return true;
    }

    bool judge()
    {
        int tmp=0;
        for(int i=1;i<=n;i++)
        {
            int now=Mod(num[A[i]]+num[B[i]]+tmp);
            if(now!=num[C[i]]) return false;
            tmp=(num[A[i]]+num[B[i]]+tmp)/n;
        }
        return true;
    }

    void print()
    {
        for(int i=0;i<n;i++) printf("%d ",num[i]);
        exit(0);
    }

    void dfs(int now)
    {
        if(!check()) return;
        if(now>n) 
        {
            if(judge()) print();
            return;
        }
        for(int i=n-1;i>=0;i--)
            if(!used[i])
            { 
                num[list[now]]=i;
                used[i]=1;
                dfs(now+1);
                num[list[now]]=-1;
                used[i]=0;
            } 
    }

    inline void inlist(int x)
    {
        if(!vis[x])
        {
            vis[x]=1;
            list[++tot]=x;
        }
    }

    void work()
    {
        scanf("%d",&n);
        scanf("%s",ch+1);
        for(int i=1;i<=n;i++) A[n-i+1]=ch[i]-'A';
        scanf("%s",ch+1);
        for(int i=1;i<=n;i++) B[n-i+1]=ch[i]-'A';
        scanf("%s",ch+1);
        for(int i=1;i<=n;i++) C[n-i+1]=ch[i]-'A';
        for(int i=1;i<=n;i++)
            inlist(A[i]),inlist(B[i]),inlist(C[i]);
        memset(num,-1,sizeof(int[n]));
        dfs(1);
    }
}

int main()
{
    TYC::work();
    return 0;
}