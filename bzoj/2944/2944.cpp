#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll Ca[25];//Catalan

void dfs(ll n,int k,int now)
//当处理的为左子树时now为0，表示从0开始，而处理右子树时，需要加上左子树和根的节点数
{
    int lt=0,rt=k-1;
    while(n)
    {
	if(n>Ca[lt]*Ca[rt])
	{
	    n-=Ca[lt]*Ca[rt];
	    lt++,rt--;
	}//lt、rt分别会得出来左右子树的节点数
	else break;
    }
    printf("%c",(char)(lt+now+'a'));//确定当前节点
    if(lt>0)//左子树
	dfs(ceil((double)n/Ca[rt]),lt,now);
    if(rt>0)//右子树
    {
	int x=n%Ca[rt];
	dfs(x?x:Ca[rt],rt,lt+now+1);
    }
}

int main()
{
    ll n;int k;
    scanf("%lld%d",&n,&k);
    Ca[0]=1;
    for(int i=1;i<=k;i++) 
	Ca[i]=Ca[i-1]*(4*i-2)/(i+1);
    dfs(n,k,0);
    return 0;
}
