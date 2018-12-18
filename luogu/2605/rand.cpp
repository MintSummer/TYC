#include<bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    srand(time(NULL));
    int n=rand()%5+1,k=rand()%3+1;
    cout<<n<<" "<<k<<"\n";
    int last=0;
    for(int i=1;i<n;i++)
        cout<<(last=last+rand()%5+1)<<" ";
    cout<<"\n";
    for(int i=1;i<=n;i++)
        cout<<rand()%5+1<<" ";
    cout<<"\n";
    for(int i=1;i<=n;i++)
        cout<<rand()%5+1<<" ";
    cout<<"\n";
    for(int i=1;i<=n;i++)
        cout<<rand()%5+1<<" ";
    cout<<"\n";
}