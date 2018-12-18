#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    int n,m;

    inline int ra()
    {
        return rand()%n;
    }

    void work()
    {
        srand(time(NULL));
        n=rand()%5+1,m=rand()%10+1;
        cout<<n<<" "<<m<<" "<<rand()%10+1<<" "<<ra()<<" "<<ra()<<"\n";
        for(int i=1;i<=m;i++)
            cout<<ra()<<" "<<ra()<<" "<<"\n";
    }
}

int main()
{
    TYC::work();
    return 0;
}