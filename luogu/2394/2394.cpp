#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;

int main()
{
    double x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    if(ch=='.')
    {
		double f=0.1;
		ch=getchar();
		for(int i=1;(ch>='0'&&ch<='9')&&i<=10;i++)
			x+=f*(ch-'0'),ch=getchar(),f/=10;
    }
    printf("%.8Lf",(long double)x/23.0);
    return 0;
}
