#include<iostream>
using namespace std;
int main()
{
    
    long long int t;
    cin>>t;
 while(t>0)
 {
           getchar();
           long long int n,sum=0;
           cin>>n;
           for(int i=0;i<n;i++)
           {
                   long long int item;
                   cin>>item;
                   sum=(sum+item)%n;
                   }
           if(sum%n==0)
           cout<<"YES"<<endl;
           else
           cout<<"NO"<<endl;
           t--;
 }
return 0;
}
