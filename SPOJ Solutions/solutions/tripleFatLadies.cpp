#include<iostream>
using namespace std;
int main()
{
    
    int t;
    cin>>t;
    while(t>0)
    {
              long long n;
              cin>>n;
              long long sum=1;
              if(n==1)
              {
                      cout<<"192"<<endl;
                      t--;
                      continue;
                      }
              
              for(long long i=2;i<=n/2;i++)
              {
                     sum=sum+5;
                       }
              if(n%2==0)
              {
                        sum=sum+3;
                        cout<<sum<<"42"<<endl;
                        }
              else{
                   sum=sum+5;
              cout<<sum<<"92"<<endl;
              }
                  t--; 
              }
    return 0;
    
    
    }
