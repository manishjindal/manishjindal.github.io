#include<iostream>
using namespace std;
int main()
{
        
    while(1)
    {
              int n;
              scanf("%d",&n);
              if(n==0)
              break;
              
              double pi=3.1415926;
              pi=2*pi;
               
               n=n*n;
               double ans;
               ans=n/pi;
               printf("%.2lf\n",ans);
        }
    return 0;
}
