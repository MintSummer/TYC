#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=410;
    int n,plane;
    double G[N][N];
    typedef pair<double,int> pa;
    priority_queue<pa,vector<pa>,greater<pa> > q;

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct City
    {
        int x[5],y[5];
    }city[N];

    inline int sqr(int x)
    {
        return x*x;
    }

    inline double dis(int x1,int y1,int x2,int y2)
    {
        return sqrt((double)sqr(x1-x2)+sqr(y1-y2));
    }

    inline int sqrdis(int x1,int y1,int x2,int y2)
    {
        return sqr(x1-x2)+sqr(y1-y2);
    }

    inline void get(City &now)
    {
		double ab=sqrdis(now.x[1],now.y[1],now.x[2],now.y[2]);
		double ac=sqrdis(now.x[1],now.y[1],now.x[3],now.y[3]);
		double bc=sqrdis(now.x[2],now.y[2],now.x[3],now.y[3]);
		int x,y;
		if(ab+ac==bc) 
            x=now.x[3]+now.x[2]-now.x[1],y=now.y[3]+now.y[2]-now.y[1];
        else if(ab+bc==ac) 
            x=now.x[1]+now.x[3]-now.x[2],y=now.y[1]+now.y[3]-now.y[2];
        else 
            x=now.x[1]+now.x[2]-now.x[3],y=now.y[1]+now.y[2]-now.y[3];
        now.x[4]=x,now.y[4]=y;
    }

    inline void connect(City now,int cost,int id)
    {
        for(int i=1;i<=4;i++)
            for(int j=i+1;j<=4;j++)
                G[id+i][id+j]=G[id+j][id+i]=dis(now.x[i],now.y[i],now.x[j],now.y[j])*cost;
    }

    inline void connect(City A,City B,int a,int b)
    {
        for(int i=1;i<=4;i++)
            for(int j=1;j<=4;j++)
                G[a+i][b+j]=G[b+j][a+i]=dis(A.x[i],A.y[i],B.x[j],B.y[j])*plane;
    }

    void work()
    {
        int T=read();
        while(T--)
        {
			memset(G,127,sizeof(G));
            n=read(),plane=read();
            int a=read(),b=read();
			if(a==b) {printf("0.0\n");return;}
            for(int i=1;i<=n;i++)
            {
                city[i].x[1]=read(),city[i].y[1]=read();
                city[i].x[2]=read(),city[i].y[2]=read();
                city[i].x[3]=read(),city[i].y[3]=read();
                get(city[i]);
                connect(city[i],read(),((i-1)<<2));
            }
            for(int i=1;i<=n;i++)
                for(int j=i+1;j<=n;j++)
                    connect(city[i],city[j],(i-1)<<2,(j-1)<<2);
			int tot=n*4;
            for(int k=1;k<=tot;k++)
				for(int i=1;i<=tot;i++)
					for(int j=1;j<=tot;j++)
						G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
			double mn=1e18;
			for(int i=((a-1)<<2)+1;i<(a<<2);i++)
				for(int j=((b-1)<<2)+1;j<(b<<2);j++)
					mn=min(mn,G[i][j]);
            printf("%.1lf",mn);
        }
    }
}

int main()
{
    TYC::work();
    return  0;
}