#include<iostream>
using namespace std;
int a[1000009];
int main()
{
    int t;
    scanf("%d",&t);    
    while(t--)
    {
              char st[1000009];
              scanf("%s",st);
              int i=0;
              while(st[i]!='.' && st[i]!='\0')
              i++;
              if(st[i]=='.')
              i++;
              int num=0,j=1;
              while(st[i]!='\0')
              {
                 // cout<<"i="<<i<<endl;              
                  num=num*10;
                  j*=10;
                  num+=(st[i]-'0');
                  i++; 
                                             
              }
              if(num==0)
              printf("1\n"); 
              else
              {
                  int l=1;
                  int x=num;
                 // cout<<"num="<<num<<" j="<<j<<endl;
                  while(1)
                  {
                         if(x%j==0)    
                            break; 
                         x=num*l;                   
                         l++;      
                  }
                  
                  printf("%d\n",l-1);
              }       
        }
    return 0;
}
