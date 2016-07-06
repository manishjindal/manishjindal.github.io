#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string.h>
using namespace std;
int a[1000009];
long long int n,m,ans=0;
long long int f(long long int mid)
{
    long long int c=0;
    for(long long int i=n-1;i>=0;i--)
    {
            if((a[i]-mid)>=0)
            c+=(a[i]-mid);
            else
            break;
    }

   // cout<<"mid="<<mid<<" c="<<c<<endl;
    if(c>=m)
    {
        if(ans<mid)
        {
                   ans=mid;
                 //  cout<<"ans="<<ans<<endl;
                   }
                   
        return 1;        
    }
    return 2;
}
void binary()
{
    long long int l=0,u=a[n-1];
    long long int mid;
    
   while(l<u)
   { 
          mid=(l+u)/2;
       //   cout<<"mid="<<mid<<endl;
        if(f(mid)==1)
        {
             l=mid+1;     
            // f(l); 
        //    cout<<"--1--"<<"l="<<l<<endl; 
            
        //    cout<<"--1--"<<"u="<<u<<endl;
             
        }
        else if(f(mid)==2)
        {
             u=mid;
            // f(u);
         //   cout<<"--2--"<<"l="<<l<<endl; 
          //  cout<<"--2--"<<"u="<<u<<endl;
                  
        }
   }
}
int main()
{
   // int t;
//    scanf("%d",&t);    
  //  while(t--)
   // {
              
              scanf("%lld%lld",&n,&m);
              for(long long int i=0;i<n;i++)
              {
                    scanf("%d",&a[i]);  
              }
                  sort(a,a+n);
                  binary();   
              printf("%lld\n",ans);
     //   }
    return 0;
}
