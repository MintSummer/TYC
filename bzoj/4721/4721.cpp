#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<queue>
#include<stack>
using namespace std;
#define MAXN 7000010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
int q[3][MAXN],hd[3],tl[3];
int n,m,u,v,t,Q;
int main(){
	int i;
	scanf("%d%d%d%d%d%d",&n,&m,&Q,&u,&v,&t);
	for(i=1;i<=n;i++){
		scanf("%d",&q[0][tl[0]++]);
	}
	sort(q[0],q[0]+tl[0]);
	for(i=0;i<tl[0]/2;i++){
		swap(q[0][i],q[0][tl[0]-i-1]);
	}
	for(i=1;i<=m;i++){
		int nw;
		if(hd[0]<tl[0]&&(q[0][hd[0]]>=q[1][hd[1]]||hd[1]>=tl[1])&&(q[0][hd[0]]>=q[2][hd[2]]||hd[2]>=tl[2])){
			nw=q[0][hd[0]++];
		}else if(hd[1]<tl[1]&&(q[1][hd[1]]>=q[0][hd[0]]||hd[0]>=tl[0])&&(q[1][hd[1]]>=q[2][hd[2]]||hd[2]>=tl[2])){
			nw=q[1][hd[1]++];
		}else{
			nw=q[2][hd[2]++];
		}
		nw+=(i-1)*Q;
		if(i%t==0){
			printf(i+t>m?"%d":"%d ",nw);
		}
		int nw1=(ll)nw*u/v;
		int nw2=nw-nw1;
		q[1][tl[1]++]=nw1-i*Q;
		q[2][tl[2]++]=nw2-i*Q;
	}
	printf("\n");
	for(i=1;i<=n+m;i++){
		int nw;
		if(hd[0]<tl[0]&&(q[0][hd[0]]>=q[1][hd[1]]||hd[1]>=tl[1])&&(q[0][hd[0]]>=q[2][hd[2]]||hd[2]>=tl[2])){
			nw=q[0][hd[0]++];
		}else if(hd[1]<tl[1]&&(q[1][hd[1]]>=q[0][hd[0]]||hd[0]>=tl[0])&&(q[1][hd[1]]>=q[2][hd[2]]||hd[2]>=tl[2])){
			nw=q[1][hd[1]++];
		}else{
			nw=q[2][hd[2]++];
		}
		nw+=m*Q;
		if(i%t==0){
			printf(i+t>n+m?"%d":"%d ",nw);
		}
	}
	return 0;
}
