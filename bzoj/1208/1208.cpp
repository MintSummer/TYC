#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=80010;
const int P=1000000;
int q,n,son[MAXN][2];
ll val[MAXN],c[MAXN];

void rorate(int &a,int &b)
{
    int d=(b==son[a][1]);
    son[a][d]=son[b][d^1];
    son[b][d^1]=a;
    a=b;
}

void insert(int &o,ll x)
{
    if(!o) val[o]=x,c[o]=rand();
    else if(x<=val[o]) 
    {
	insert(son[o][0],x);
	if(c[o]<c[son[o][0]]) rorate(o,son[o][0])
    }
    else 
    {
	insert(son[o][1],x);
if(c[o]<c[son[o][1]]) rorate(o,son[o][1]);
    }
}

int main()
{
    scanf("%d",&q);
    int opt;
    ll x;
    while(q--)
    {
	scanf("%d%d",&opt,&x);
	if(opt==0) insert(++n,x);
    }
}
