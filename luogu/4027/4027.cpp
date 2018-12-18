#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long double ld;
    const int N=100010;
	const ld eps=1e-6;

    int n;
    ld start,a[N],b[N],rate[N],f[N];

    inline double read()
    {
        double x=0;int f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        if(ch=='.')
        {
            double t=0.1;ch=getchar();
            while(isdigit(ch)) x+=(ch-'0')*t,t*=0.1,ch=getchar();
        }
        return f?-x:x;        
    }

	struct node
	{
		ld k,x,y;
		int id;
		void update()
		{
			f[id]=max(f[id],f[id-1]);
			y=f[id]/(b[id]+a[id]*rate[id]);
			x=y*rate[id];
		}
	}arr[N];

	bool cmpk(const node &p,const node &q)
	{
		return p.k>q.k;
	}

	inline ld K(int p,int q)
	{
		if(fabs(arr[p].x-arr[q].x)<eps) return -1e20;
		else return (ld)(arr[q].y-arr[p].y)/(arr[q].x-arr[p].x);
	}

	inline ld B(int from,int to)
	{
		return a[to]*arr[from].x+b[to]*arr[from].y;
	}

	void CDQ(int l,int r)
	{
		if(l==r) {arr[l].update();return;} 
		int mid=(l+r)>>1,tmp1=l-1,tmp2=mid;
		static node t[N];
		for(int i=l;i<=r;i++)
			if(arr[i].id<=mid) t[++tmp1]=arr[i];
			else t[++tmp2]=arr[i];	
		for(int i=l;i<=r;i++) arr[i]=t[i];
		CDQ(l,mid);
		static int sta[N];
		int top=0,num=l;
		for(int i=l;i<=mid;i++)
		{
			while(top>1&&K(sta[top-1],sta[top])<K(sta[top],i)+eps) top--;
			sta[++top]=i;
		}
		int i,j=1;
		for(i=mid+1;i<=r;i++)
		{
			int x=arr[i].id;
			while(j<top&&B(sta[j+1],x)-B(sta[j],x)>eps) j++;
			f[x]=max(f[x],B(sta[j],x));
		}
		CDQ(mid+1,r);
		i=l,j=mid+1;
		while(i<=mid&&j<=r)
			if(arr[i].x<arr[j].x||(arr[i].x==arr[j].x&&arr[i].y>arr[j].y)) 
				t[num++]=arr[i++];
			else t[num++]=arr[j++];
		while(i<=mid) t[num++]=arr[i++];
		while(j<=r) t[num++]=arr[j++];
		for(i=l;i<=r;i++) arr[i]=t[i];
	}

    void work()
    {
        n=read(),start=read();
        for(int i=1;i<=n;i++) 
		{
            a[i]=read(),b[i]=read(),rate[i]=read();
			arr[i].k=-a[i]/b[i];
			arr[i].id=i;
		}
		sort(arr+1,arr+1+n,cmpk);
		f[1]=start;
		CDQ(1,n);
		printf("%.3f",(double)f[n]);
    }    
}

int main()
{
    TYC::work();
    return 0;
}
