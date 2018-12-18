#include<bits/stdc++.h>
using namespace std;
const double eps=1e-14;
const int dx[5]={0,1,0,-1,0},dy[5]={0,0,1,0,-1};
int n;
double x,y,ans=1e70;

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

struct node
{
    int x,y,w;
}a[10010];

double dis(double x1,double y1,int x2,int y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

double get_sum(double nx,double ny)
{
    double sum=0;
    for(int i=1;i<=n;i++)
        sum+=dis(nx,ny,a[i].x,a[i].y)*a[i].w;
    return sum;
}

void search()
{
    double xx=x,yy=y;
    double T=1926;
    while(T>eps)
    {
        double nx=x+(rand()*2-RAND_MAX)*T,ny=y+(rand()*2-RAND_MAX)*T;
		double tmp=get_sum(nx,ny);
		double delta=tmp-ans;
        if(delta<eps) 
            ans=tmp,x=nx,y=ny,xx=nx,yy=ny;
		else if(rand()<exp(-delta/T)*RAND_MAX)
	    	xx=nx,yy=ny;
        T*=0.98;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        a[i].x=read(),a[i].y=read(),a[i].w=read();
        x+=a[i].x,y+=a[i].y;
    }
    for(int i=1;i<=2;i++) search();
    printf("%.3lf %.3lf",x,y);
    return 0;
}
