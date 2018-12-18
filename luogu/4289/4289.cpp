#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int S,T,vis[65536],to[6][6],h,t;
int dx[5]={0,1,0,-1,0},dy[5]={0,0,1,0,-1};

struct node
{
    int a[6][6],now;
}q[100010];

int hash(int a[6][6])
{
    int s=0,k=1;
    for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			s+=k*a[i][j],k<<=1;
    return s;
}

void bfs()
{
    while(h<t)
    {
		h++;
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
				if(q[h].a[i][j])
					for(int k=1;k<=4;k++)
					{
						int x=i+dx[k],y=j+dy[k];
						if(q[h].a[x][y]||x<1||y<1||x>4||y>4) continue;
						swap(q[h].a[i][j],q[h].a[x][y]);
						int d=hash(q[h].a);
						if(!vis[d])
						{
							if(d==T) {printf("%d",q[h].now+1);return;}
							vis[d]=1;
							t++;
							memcpy(q[t].a,q[h].a,sizeof(q[t].a));
							q[t].now=q[h].now+1;
						}
						swap(q[h].a[i][j],q[h].a[x][y]);
					}
    }
}

int main()
{
    h=0,t=1;
    char ch[6];
    for(int i=1;i<=4;i++)
    {
		scanf("%s",ch);
		for(int j=0;j<4;j++)
			q[t].a[i][j+1]=ch[j]-'0';
    }
    for(int i=1;i<=4;i++)
    {
		scanf("%s",ch);
		for(int j=0;j<4;j++)
			to[i][j+1]=ch[j]-'0';
    }
    S=hash(q[t].a);
    vis[S]=1;
    T=hash(to);
    if(S==T) printf("0");
    else bfs();
    return 0;
}
