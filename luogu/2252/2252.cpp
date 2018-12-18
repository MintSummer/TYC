#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    int a,b;
    void work()
    {
        scanf("%d%d",&a,&b);
        int tmp=abs(a-b)*(1+sqrt(5))/2;
        if(tmp==a||tmp==b) puts("0");
        else puts("1");
    }
}

int main()
{
    TYC::work();
    return 0;
}
