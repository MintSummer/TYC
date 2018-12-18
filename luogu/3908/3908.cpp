#include<bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    long long n,ans;
    cin>>n;
    switch(n%4)
    {
        case 0: ans=n;break;
        case 1: ans=1;break;
        case 2: ans=n+1;break;
        case 3: ans=0;
    }
    cout<<ans<<"\n";
    return 0;
}