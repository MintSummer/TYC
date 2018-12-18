#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=1010;
    int n,tot,cnt,top1,top2,vis[N],a[N],Head[N],mn[N],col[N],stack1[N],stack2[N]; 
    char ans[100010]; 

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct edge
    {
        int to,next;
    }E[N*N];

    inline void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
    }

    bool bfs(int s)
    {
        queue<int> q;
        q.push(s);
        col[s]=0;
        while(!q.empty())
        {
            int u=q.front();q.pop();
            vis[u]=1;
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(~col[v]&&col[u]==col[v]) return false;
                else if(col[v]==-1)
                    col[v]=col[u]^1,q.push(v);
            }
        }
        return true;
    }

    void work()
    {
        n=read();
        for(int i=1;i<=n;i++) a[i]=read();
        mn[n+1]=0x3f3f3f3f;
        for(int i=n;i;i--)
        {
            mn[i]=min(mn[i+1],a[i]);
            for(int j=i+1;j<n;j++)
                if(a[i]<a[j]&&a[i]>mn[j+1])
                    add(i,j),add(j,i);
        }
        memset(col,-1,sizeof(col));
        for(int i=1;i<=n;i++) if(!vis[i]) 
            if(!bfs(i)) {puts("0");return;}
        int num=0;
        for(int i=1;i<=n;i++)
        {
            if(!col[i]) 
            {
                while(top1&&stack1[top1]<a[i]) 
                    printf("b "),top1--,num++;
                printf("a "),stack1[++top1]=a[i];
            }
            else
            {
                while(top1&&stack1[top1]==num+1) 
                    printf("b "),top1--,num++;
                while(top2&&stack2[top2]<a[i]) 
                    printf("d "),top2--,num++;
                printf("c "),stack2[++top2]=a[i];
            }
        }
        while(num!=n)
        {
            num++;
            if(stack1[top1]==num) 
                printf("b "),top1--;
            else printf("d "),top2--;
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}