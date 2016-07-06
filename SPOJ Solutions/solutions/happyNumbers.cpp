#include<iostream>
using namespace std;
int a[1000000]={0};
int main()
{
    long long int n;
    cin>>n;
    long long sum=0,count=0;
    
    while(1)
    {
            sum=0;
            while(n!=0)
            {
                       int x;
                       x=n%10;
                       sum=sum+x*x;
                     //  cout<<"sum="<<sum<<" n="<<n<<endl;
                       n=n/10;
                       }
            count++;
            if(sum==1)
            {
                      cout<<count<<endl;
                      break;
                      }
            else
            {
                if(a[sum]==-1){
                cout<<"-1"<<endl;
                break;}
                else
                a[sum]=-1;
                n=sum;
                }
    }
    
    int t;
    cin>>t;
    return 0;
}
