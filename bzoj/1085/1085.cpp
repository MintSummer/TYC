#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int dx[]={0,1,1,-1,-1,2,2,-2,-2};
    const int dy[]={0,2,-2,2,-2,1,-1,1,-1};
    const int goal[7][7]={
        {0,0,0,0,0,0},
        {0,1,1,1,1,1},
        {0,0,1,1,1,1},
        {0,0,0,2,1,1},
        {0,0,0,0,0,1},
        {0,0,0,0,0,0}
    };

    int G[8][8];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    inline int calc()
    {
        int num=0;
        for(int i=1;i<=5;i++)
            for(int j=1;j<=5;j++)
                num+=(G[i][j]!=goal[i][j]);
        return num;
    }

    bool Astar(int dep,int x,int y,int maxdep)
    {
        if(dep==maxdep) return !calc();	
        for(int i=1;i<=8;i++)
        {
            int nx=x+dx[i],ny=y+dy[i];
            if(nx<1||nx>5||ny<1||ny>5) continue;
            swap(G[x][y],G[nx][ny]);
            if(calc()+dep<=maxdep)
                if(Astar(dep+1,nx,ny,maxdep)) return true;
            swap(G[x][y],G[nx][ny]);
        }
        return false;
    }

    void work()
    {
        int T=read();
        while(T--)
        {
            char ch;
            int bx,by,ans=-1;
            for(int i=1;i<=5;i++)
                for(int j=1;j<=5;j++)
                {
                    do ch=getchar(); while(ch!='0'&&ch!='1'&&ch!='*');
                    if(ch=='*') G[i][j]=2,bx=i,by=j;
                    else G[i][j]=ch-'0';
                }
            if(!calc()) {puts("0");continue;}
            for(int maxdep=1;maxdep<=15;maxdep++)
                if(Astar(0,bx,by,maxdep)) 
                    {ans=maxdep;break;}
            printf("%d\n",ans);
        }
    }
}

int main()
{
	TYC::work();
	return 0;
}
