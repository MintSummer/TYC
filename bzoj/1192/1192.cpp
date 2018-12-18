#include<bits/stdc++.h>
using namespace std;
long long n,cnt=0;

bool cmp(int x,int y)
{
    return x<y;
}

int main()
{
    cin>>n;
    while(n>0)
    {
        ++cnt;
        n/=2;
    }
    cout<<cnt<<endl;
    return 0;
}