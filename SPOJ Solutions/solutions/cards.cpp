#include<iostream>
using namespace std;
long long  a[1000001];
int main()
{
    a[1]=2;
    for(long long i=2;i<1000001;i++)
    {
             a[i]=(a[i-1]+2*i+(i-1))%1000007;
             
             }          
    
    
    int t;
    cin>>t;
    while(t>0)
    {
              long long n;
              cin>>n;
              cout<<a[n]<<endl;
              t--;
    }    
    return 0;
}
