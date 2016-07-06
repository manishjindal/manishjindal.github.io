#include<iostream>
using namespace std;

               int a[10000000]={0};
               int b[10000000]={0};
              
int main()
{
    //cout<<a[-11111];
    
    
    long long int t;
    cin>>t;
    while(t>0)
    {
              for(long long int i=0;i<=10000000;i++)
              {
                      a[i]=0;
                      b[i]=0;
                      }
              
              long long int n,sum=0;
              cin>>n;
              long long int num,max=0,min=0;
              for(long long int i=0;i<n;i++)
              {
                      cin>>num;
                      sum=sum+num;
                      if(sum<0)
                      {
                              long long int x=0,count=0;
                               x=sum;
                               while(x!=1)
                               {
                                          x++;
                                          count++;
                                          }
                                          if(count>min)
                                          min=count;
                               b[count]++;
                               }
                      
                      else{
                      a[sum]++;
                      if(max<sum)
                      max=sum;
                      }
                      }
    
                       long long int ans=0;
                             //  cout<<"max="<<max<<endl;              
                      for(long long int i=0;i<=max;i++){
                              if(a[i]>0)
                              {
                                        if(i==0)
                                        {
                                                
                                     //      cout<<"--1--a[i]="<<a[i]<<endl;
                                                for(long long int j=1;j<=a[i];j++)
                                                        ans=ans+j;                
                                                }
                                        else
                                        {
                                     //       cout<<"--2--a[i]="<<a[i]<<endl;
                                                for(long long int j=1;j<a[i];j++)
                                                        ans=ans+j;                
                                               
                                            
                                            }
                              }
                              }  
                      for(long long int i=1;i<=min ;i++){
                              if(b[i]>0)
                              {
                                                for(long long int j=1;j<b[i];j++)
                                                        ans=ans+j;                
                                               
                                            
                                            }
                              }
                              
                              //cout<<"a[o]="<<a[0]<<endl;
                                  cout<<ans<<endl;
              t--;
    }
    return 0;
}

