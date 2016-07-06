#include<iostream>
using namespace std;
long long int gcd(long long int a,long long int b)
{
return b == 0 ? a : a > b ? gcd(b, a%b) : gcd(a, b%a);
}
int main()
{
    int t;
    scanf("%d",&t);    
    while(t--)
    {
              long long int m,x,y,gcd1;
              scanf("%lld%lld",&x,&y);
               if(x>y)
                     gcd1=gcd(x,y);
                else
                     gcd1=gcd(y,x);
            
                
                
                printf("%lld %lld\n",y/gcd1,x/gcd1);
    
    
    
    }
    return 0;
}
