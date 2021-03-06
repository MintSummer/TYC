#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;
int n,m,s,hurt,r,t,cnt,G[15][15];
bool cake,vis[15][15];
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};

struct Tower
{
    int x,y;
}tow[110];

struct Ant
{
    int level,blood,x,y,tim,lx,ly,born_hp;
    bool cake,live;
}ant[15];

struct point
{
    int x,y;
};

struct Line 
{
    point a,b;
}line;

bool cmp(Ant a,Ant b)
{
    return a.tim>b.tim;
}

void add_ant(int d)
{
    ant[d].x=ant[d].y=ant[d].lx=ant[d].ly=0;
    vis[0][0]=1;
    int k=cnt/6+1;
    ant[d].level=k;
    ant[d].blood=ant[d].born_hp=int(4*pow(1.1,k));
    ant[d].tim=0,ant[d].live=true;
    cnt++;
}

void add_information()
{
    for(int i=1;i<=6;i++) if(ant[i].live)
    {
        int x=ant[i].x,y=ant[i].y;
        if(ant[i].cake) G[x][y]+=5;
        else G[x][y]+=2;
    }
}

bool check_direction(int x,int y,int lx,int ly)
{
    if(vis[x][y]||x>n||x<0||y>m||y<0) return false;
    if(x==lx&&y==ly) return false;
    return true;
}

void move(int d,int dir)
{
    int x=ant[d].x,y=ant[d].y;
    if(dir==-1) {ant[d].lx=x,ant[d].ly=y;return;}
    int xx=x+dx[dir],yy=y+dy[dir];
    vis[x][y]=0,vis[xx][yy]=1;
    ant[d].lx=x,ant[d].ly=y;
    ant[d].x=xx,ant[d].y=yy;
}

void turn_direction(int d,int dir)
{
    int x=ant[d].x,y=ant[d].y,lx=ant[d].lx,ly=ant[d].ly;
    for(int i=(dir-1+4)%4;;i=(i-1+4)%4)
    {
	int xx=x+dx[i],yy=y+dy[i];
	if(check_direction(xx,yy,lx,ly)) {move(d,i);return;}
    }
}

void get_direction(int d)
{
    int x=ant[d].x,y=ant[d].y,lx=ant[d].lx,ly=ant[d].ly;
    int mx=-0x3f3f3f3f,dir=-1,xx,yy;
    for(int i=0;i<4;i++)
    {
        xx=x+dx[i],yy=y+dy[i];
        if(check_direction(xx,yy,lx,ly)&&G[xx][yy]>mx) mx=G[xx][yy];
    }
    for(int i=0;i<4;i++) 
    {
	xx=x+dx[i],yy=y+dy[i];
        if((check_direction(xx,yy,lx,ly))&&(G[xx][yy]==mx)) 
	    {dir=i;break;}
    }
    if((ant[d].tim+1)%5!=0||dir==-1) move(d,dir);
    else turn_direction(d,dir);
}

void check_cake()
{	
    for(int i=1;i<=6;i++) if(ant[i].live)
	if(ant[i].x==n&&ant[i].y==m)
	{
	    ant[i].cake=true;
	    cake=true;
	    ant[i].blood=min(ant[i].blood+ant[i].born_hp/2,ant[i].born_hp);
	}
}

int dis(int x1,int y1,int x2,int y2)
{
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

point sub(point a,point b) 
{
    point tmp;
    tmp.x=a.x-b.x,tmp.y=a.y-b.y;
    return tmp;
}

int cmul(point a,point b)
{
    return a.x*b.y-a.y*b.x;
}

int turn(point a,point b,point c)
{
    return cmul(sub(b,a),sub(c,a));
}

bool check_cross(int x,int y)
{
    if((x==line.a.x&&y==line.a.y) || (x==line.b.x&&y==line.b.y)) return true;
    double diss=(double)sqrt((double)dis(line.a.x,line.a.y,line.b.x,line.b.y));
    int lx=min(line.a.x,line.b.x),rx=max(line.a.x,line.b.x);
    int ly=min(line.a.y,line.b.y),ry=max(line.a.y,line.b.y);
    if(x<lx||x>rx||y<ly||y>ry) return false;

    point c;
    c.x=x,c.y=y;
    if(fabs(turn(line.a,line.b,c))/diss<=0.5) return true;
    return false;
}

void attack(int k)
{
    int diss,enemy=0,mndis=0x3f3f3f3f;
    for(int i=1;i<=6;i++) if(ant[i].live)
    {
	diss=dis(tow[k].x,tow[k].y,ant[i].x,ant[i].y);
	if(diss<=r*r)
	{
	    if(ant[i].cake) enemy=i;
	    else if(!ant[enemy].cake&&diss<mndis) mndis=diss,enemy=i;
	}
    }
    if(enemy==0) return;

    line.a.x=ant[enemy].x,line.a.y=ant[enemy].y;
    line.b.x=tow[k].x,line.b.y=tow[k].y;
    for(int i=1;i<=6;i++) if(ant[i].live)
	if(check_cross(ant[i].x,ant[i].y)) ant[i].blood-=hurt;
}

void check_die(int d) 
{
    if(ant[d].blood>=0) return;
    if(ant[d].cake) cake=ant[d].cake=false;
    vis[ant[d].x][ant[d].y]=0;
    ant[d].live=false;
} 

bool check_gameover()
{
    if(cake==false) return false;
    for(int i=1;i<=6;i++) if(ant[i].live)
	if(ant[i].cake&&ant[i].x==0&&ant[i].y==0) return true;
    return false;
}

void reduce_information()
{
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
            if(G[i][j]>0) G[i][j]--;
}

void add_age()
{
   for(int i=1;i<=6;i++) if(ant[i].live)
	ant[i].tim++;
}

bool judge()
{
    if(!vis[0][0])
	for(int i=1;i<=6;i++)
	    if(!ant[i].live) {add_ant(i);break;}
    sort(ant+1,ant+7,cmp);
    add_information();
    for(int i=1;i<=6;i++) if(ant[i].live) 
	get_direction(i);
    if(!cake) check_cake();
    for(int i=1;i<=s;i++) attack(i);
    for(int i=1;i<=6;i++) if(ant[i].live) 
	check_die(i);
    if(check_gameover()) return true;
    reduce_information();
    add_age();
    return false;
}

void print()
{
    int alive=0;
    sort(ant+1,ant+7,cmp);
    for(int i=1;i<=6;i++) if(ant[i].live) alive++;
    printf("%d\n",alive);
    for(int i=1;i<=6;i++)
	if(ant[i].live)
	    printf("%d %d %d %d %d\n",ant[i].tim,ant[i].level,ant[i].blood,ant[i].x,ant[i].y);
}

int main()
{
    freopen("2586.in","r",stdin);
    freopen("TYC.out","w",stdout);
    scanf("%d%d",&n,&m);
    scanf("%d%d%d",&s,&hurt,&r);
    for(int i=1;i<=s;i++)
    {
        scanf("%d%d",&tow[i].x,&tow[i].y);
        vis[tow[i].x][tow[i].y]=1;
    }
    scanf("%d",&t);
    
    for(int i=1;i<=t;i++)
        if(judge())
        {
            printf("Game over after %d seconds\n",i);
            print();
            return 0;
        }
    printf("The game is going on\n");
    print();
    return 0;
} 
