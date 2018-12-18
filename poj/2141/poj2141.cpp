#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
 char key[27],message[81];
 gets(key);gets(message);
 int len=strlen(message);
 for(int i=0;i<len;i++)
 {
  if(message[i]!=' ')//if (isalpha(message[i]))
  {
     if(message[i]>='a')
     {
      
      message[i]=key[message[i]-'a'];
      
     }
     else 
     {
      
      message[i]=key[message[i]-'A']-32;
      //message[i] = toupper(key[message[i] - 'A']);
      
     }
     
  }
  
  
 }
 puts(message);
 return 0;
 
 
}