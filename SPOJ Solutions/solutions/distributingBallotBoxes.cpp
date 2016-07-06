#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string.h>
using namespace std;
int a[5000009];
int n,m,ans=6000000;
int f(int mid)
{
    int c=0,temp;
    for(int i=n-1;i>=0;i--)
    {
            temp=a[i]-mid;
            while(1)
            {
                     c+=1;
                    if((temp)<=0)
                    break;
                   temp=temp-mid;
                    
            }
            if(c>m)
            return 2;
           
    }

    //cout<<"mid="<<mid<<" c="<<c<<" ans="<<ans<<endl;
    if(c<=m)
    {
        if(ans>mid)
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
    int l=0,u=a[n-1];
    int mid;
    
   while(l<u)
   { 
          mid=(l+u)/2;
       //   cout<<"mid="<<mid<<endl;
        if(f(mid)==1)
        {
             u=mid;     
            // f(l); 
        //    cout<<"--1--"<<"l="<<l<<endl; 
            
        //    cout<<"--1--"<<"u="<<u<<endl;
             
        }
        else if(f(mid)==2)
        {
             l=mid+1;
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
   while(1)
   {
             
              scanf("%d%d",&n,&m);
               if(n==-1 && m==-1)
              break;
              for(long long int i=0;i<n;i++)
              {
                    scanf("%d",&a[i]);  
              }
              ans=6000000;
                  sort(a,a+n);
                  binary();   
              printf("%d\n",ans);
              getchar();
   }
    return 0;
}
