#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdio>
int n,d,t;
int top,len,a[200001],num[200001];
int main()
{
    int x;char ch[1];
    scanf("%d%d",&n,&d);
    while(n--)
    {
              scanf("%s%d",ch,&x);
              if(ch[0]=='A')
              {
                      x=(x+t)%d;
                      num[++len]=x;
                      while(top&&num[a[top]]<=x)top--;
                      a[++top]=len;      
                      }
              else{
                  int y=lower_bound(a+1,a+top+1,len-x+1)-a;
                  t=num[a[y]];
                  printf("%d\n",t=num[a[y]]);
              }
          }
    return 0;
}
