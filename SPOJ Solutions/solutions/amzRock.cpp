#include<iostream>
using namespace std;
int a[10000000];
int main()
{
    a[0]=0;
    a[1]=2;
    a[2]=3;
    for(int i=3;i<=1000000;i++)
    a[i]=a[i-1]+a[i-2];
    //cout<<a[100000]<<endl; 
    int t;
    scanf("%d",&t);    
    while(t--)
    {
              int n;
              scanf("%d",&n);
              printf("%d\n",a[n]);
    }
    return 0;
}
