//�Ҿ�����һ������Ŀǰ���������ѵ�һ������ö���⣬�����벻���ò��ð�����Ц
//��л����CSDN����⣨û����Ҿ����ˣ� 
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
/*
��Ϊ������б�ȫ�����ϣ���ô���������߶��ɴ����Ŀ��˵������������� 
�����������һ�����ڶϿ��ıߣ���ôֻ��ö��ÿ���Ͽ��ı߾����� 
��ʱͼ���һ��������� 
*/
int n,p,ans=0x3f3f3f3f;
int f[10010];
//f[i]��ʾ��i��ʼһֱ��f[i]���Ѿ��������ˣ�ȫ����¼��Ϊ˳��ʱ�ɴ� ��f[i]��ָ��Ϊһ���㣬������һ������ 
struct qujian
{
	int x,y;
}cow[10010];

bool cmp(qujian a,qujian b)
{
	if(a.x==b.x) return a.y<b.y;
	else return a.x<b.x;
}

int main()
{
	scanf("%d%d",&n,&p);
	int x,y;
	for(int i=1;i<=p;i++)
	  {
	  	scanf("%d%d",&x,&y);
	  	if(x>y) swap(x,y);//��֤x<=y 
	  	cow[i].x=x,cow[i].y=y;
	  }
	  
	sort(cow+1,cow+1+p,cmp);//��ǰ�Ÿ�����һ�º���Ҫ 
	
	for(int d=1;d<=n;d++)//�ϵ�Ϊd,������d=1ʱ1��2֮�䲻������ 
	  {
	  	memset(f,0,sizeof(f));//�ϵ㲻ͬ�����ܴﵽ��f[i]ֵҲ��ͬ 
	  	for(int i=1;i<=p;i++)
	  	  {
	  	  	if(d<cow[i].x||d>=cow[i].y)//�ϵ㲻��x,y֮�� 
	  	  	  f[cow[i].x]=max(f[cow[i].x],cow[i].y); 
				  //��x��ʼ����Ҫôԭ�������Ե���y��Ҫô�ͻ�Ҫ�䳤 
	  	  	else//�м�Ͽ���ֻ���������� 
	  	  	  {
	  	  	  	//����η�Ϊ�������֣�һ��Ϊ1��x,��һ��Ϊy��1 
	  	  	  	f[1]=max(f[1],cow[i].x);//���´�1��ʼ����Զ�ĵ� 
	  	  	  	f[cow[i].y]=n+1; //n+1��ʵ��Ϊʵ���ϵĵ�1������Ϊ��Ϊ�˱�ʾһ�ξ��루û�и��������ʽ�1��n+1��ʾ 
	  	  	  }
	  	  }
	  	int to=0,sum=0;//to��ʾ��ʱ�ܹ��������Զ�ĵ� 
	  	for(int i=1;i<=n;i++)
	  	  {
	  	  	if(f[i]==0) continue;//��i��ʼ�޷������κ� 
	  	  	if(f[i]>to)//�Ѿ��ɴ�Ĳ����ٿ��� 
	  	  	  {
	  	  	  	sum+=f[i]-max(i,to);//ѡȡi��to�нϴ�ģ�ʹ����f[i]��ͨ
				//��Ϊ���to>i����i��t���ⲿ��һ���Ѿ��������ˣ�����i>toʱ����˵��i��t���û��Ҫ����
				to=f[i];//��ʱ�ܵ������Զ�ĵ����Ϊf[i] 
	  	  	  }
	  	  }
	  	ans=min(ans,sum);
	  }
	printf("%d",ans);
	return 0;
}
