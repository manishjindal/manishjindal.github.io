#include<iostream>
#include<string.h>
using namespace std;
long long int cnt[1000009]={0};
int main()
{
    int t;
    scanf("%d",&t);    
    while(t--)
    {
              long long int n,k,zero=0,one=0,res=0;
              scanf("%lld%lld",&n,&k);
              char a[1000009];
              memset(cnt,0,sizeof(cnt));
              scanf("%s",a);
              cnt[0]++;
              for(long long int i=0;i<n;i++)
              {
                     
                     if (a[i] == '1') 
                     one++;
                       if (one >= k) 
                       {
                        res += cnt [one - k];
                        }
                        cnt [one]++;
                      
              }
             // cout<<"one="<<one<<endl;
             // cout<<"zero="<<zero<<endl;
              
                  cout<<res<<endl;
            //  cout<<"1"<<endl;
        }
    return 0;
}
