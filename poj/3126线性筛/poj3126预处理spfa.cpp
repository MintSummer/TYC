#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

const int maxn=10010;
int head[maxn],isp[maxn],pri[maxn],vis[maxn],d[maxn],t,x,y,cnt,c;
queue<int >q;

struct ed{
	int next ,to;	
}e[4000000];

void add(int a,int b){
	e[++c].next=head[a];
	e[c].to=b;
	head[a]=c;	
}

void init(){
	int q;
	isp[1]=1;
	for(int i=2;i<10000;i++){
		if(!isp[i]){
			pri[++cnt]=i;
			if(i==1009)
				q=cnt;
		}
			for(int j=1;j<=cnt&&i*pri[j]<10000;j++){
				int tt=i*pri[j];
				isp[tt]=1;
				if(!i%pri[j])
					break;
			}		
	}
	for(int i=q;i<=cnt;i++){
		for(int j=10;j<=10000;j*=10)
			for(int k=pri[i]%j/(j/10);k<=9;k++){
				int tt=pri[i]-pri[i]%j+pri[i]%(j/10)+k*j/10;	
				if(tt>1000&&!isp[tt]&&tt!=pri[i]){
					add(pri[i],tt);
					add(tt,pri[i]);	
				}
			}	
	}

}

void spfa(int s)
{
	while(!q.empty())
		q.pop();
	q.push(s);
	d[s]=0;
	while(!q.empty())
	{
		int h=q.front() ;
		q.pop() ;
		vis[h]=0;
		for(int i=head[h];i;i=e[i].next )
		{
			int tt=e[i].to;
			if(d[h]+1<d[tt]){
				d[tt]=d[h]+1;
			if(!vis[tt])
			{
				q.push(tt);
				vis[tt]=true;
			}
			}
			
		}
	} 
	
}


int main(){
	
	init();
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		memset(vis,0,sizeof(vis));
		memset(d,0x3f3f3f3f,sizeof(d));
		scanf("%d%d",&x,&y);
		spfa(x);
		if(d[y]<0x3f3f3f3f)
			printf("%d\n",d[y]);
		else
			printf("Impossible\n");
	}
	
	return 0;	
}
