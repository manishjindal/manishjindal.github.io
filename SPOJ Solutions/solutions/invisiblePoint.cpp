#include<iostream>
using namespace std;
int main()
{
    int t;
    scanf("%d",&t);    
    while(t>0)
    {
              int n;
              scanf("%d",&n);
              int count=3;
              if(n%2!=0)
              n=n+1;
              while(n>4)
              {
                         n=n/2;
                         if(n%2!=0)
                         n=n+1;
                         count++;
                         }
                         
              printf("%d\n",count);
              t--;
    }
    return 0;
}



