#include<iostream>
#include<string.h>
using namespace std;
long long int a[100009],dp[100009];
long long  int n;
long long int max(long long int l,long long int m,long long int n)
{
    if(l>=m && l>=n )
    return l;
    if(m>=l && m>=n)
    return m;
    if(n>=l && n>=m)
     return n;
}
long long int find(long long int i)
{
    if(i>=n)
    return 0;
    
    if(dp[i]!=-1)
    return dp[i];
    
   dp[i]=max((a[i]+find(i+2)),(a[i]+a[i+1]+find(i+4)),(a[i]+a[i+1]+a[i+2]+find(i+6)));
   return dp[i];
}
int main()
{
    int t;
    scanf("%d",&t);    
    while(t--)
    {
             
              scanf("%lld",&n);
              memset(a,0,sizeof(a));
              for(long long int i=0;i<n;i++)
              {
                    scanf("%lld",&a[i]);  
              }
              memset(dp,-1,sizeof(dp));
             
            printf("%lld\n",find(0));
    }
    return 0;
}

