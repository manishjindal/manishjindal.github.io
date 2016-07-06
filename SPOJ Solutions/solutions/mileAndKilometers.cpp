#include<iostream>
using namespace std;
long long int a[72];
int main()
{
    a[0]=1;a[1]=1;
    for(int i=2;i<72;i++)
    a[i]=a[i-1]+a[i-2];
    
    //cout<<a[68]<<endl;
    
    int t;
    scanf("%d",&t);    
    while(t--)
    {
              long long int m,ans=0,sum=0;
              scanf("%lld",&m);
            
              
              for(int i=70;i>0;i--)
              {
                      while(sum+a[i]<=m)        
                      {
                          //cout<<"--"<<a[i]<<endl;                   
                          sum+=a[i];
                          ans+=a[i+1];
                                                                    
                      }
                      
              }
              //cout<<"sum="<<sum<<endl;
             cout<<ans<<endl;         
        }
    return 0;
}
