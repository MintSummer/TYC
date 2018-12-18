#include<cstdio>
#include<algorithm>
using namespace std;
const int eps=1e6;

int main()
{
    long double sum=0,x;
    while(~scanf("%Lf",&x)) sum+=x*eps;
    printf("%.5LF",sum/eps);
    return 0;
}
