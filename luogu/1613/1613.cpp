#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int N=60;
    int n,m,dis[N][N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct Matrix
    {
        bool G[N][N];
        Matrix() {memset(G,false,sizeof(G));}
        Matrix operator * (const Matrix &t) const
        {
            Matrix ans;
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    for(int k=1;k<=n;k++)
                        ans.G[i][j]|=G[i][k]&t.G[k][j];
            return ans;
        }
    }M[70];

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read();
            M[0].G[u][v]=true;
        }
        memset(dis,0x3f3f3f3f,sizeof(dis));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(M[0].G[i][j]) dis[i][j]=1;
        int tim;
        for(tim=1;tim<=63;tim++)
        {
            M[tim]=M[tim-1]*M[tim-1];
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    if(M[tim].G[i][j]) dis[i][j]=1;
        }
        for(int i=1;i<=n;i++) dis[i][i]=0;
        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
        printf("%d\n",dis[1][n]);
    }
}

int main()
{
    TYC::work();
    return 0;
}