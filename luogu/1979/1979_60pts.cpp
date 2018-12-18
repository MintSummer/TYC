#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    const int N=40;
    const int dx[5]={0,1,-1,0,0},dy[5]={0,0,0,1,-1};
    int n,m,question,Bx,By,Sx,Sy,Tx,Ty;
    bool G[N][N],vis[N][N][N][N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct stu
    {
        int bx,by,px,py,tim;
        stu(int x1,int y1,int x2,int y2,int t) :
            bx(x1),by(y1),px(x2),py(y2),tim(t) {}
    };
    queue<stu> q;

    int bfs()
    {
        while(!q.empty()) q.pop();
        vis[Bx][By][Sx][Sy]=1;
        q.push(stu(Bx,By,Sx,Sy,0));
        while(!q.empty())
        {
            stu now=q.front();q.pop();
            vis[now.bx][now.by][now.px][now.py]=1;
            if(now.px==Tx&&now.py==Ty) return now.tim;
            for(int i=1;i<=4;i++)
            {
                int x=now.bx+dx[i],y=now.by+dy[i],tx,ty;
                if(!G[x][y]) continue;
                if(x==now.px&&y==now.py) tx=now.bx,ty=now.by;
                else tx=now.px,ty=now.py;
                if(vis[x][y][tx][ty]) continue;
                q.push(stu(x,y,tx,ty,now.tim+1));
                if(tx==Tx&&ty==Ty) return now.tim+1;
            }
        }
        return -1;
    }

    void work()
    {
        n=read(),m=read(),question=read();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                G[i][j]=read();
        while(question--)
        {
            Bx=read(),By=read(),Sx=read(),Sy=read(),Tx=read(),Ty=read();
            memset(vis,false,sizeof(vis));
            printf("%d\n",bfs());
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}