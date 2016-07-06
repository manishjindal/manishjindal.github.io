#include<iostream>
#include<queue>
#include<stdio.h>
long long int a[300001];
using namespace std;
int main()
{
    queue<long long int> myqueue;
    long long int n,m;
    scanf("%lld%lld",&n,&m);
    
    for(long long int i=0;i<n;i++)
    scanf("%lld",&a[i]);
    
    long long int sum=0,max=0;
    for(long long int i=0;i<n;i++)
    {
             myqueue.push(a[i]);
             long long int x=0;
             x=sum+a[i];
             if(x<=m)
             {
                       sum=sum+a[i];
                       if(sum>max)
                       max=sum;
                       }
             else if(myqueue.size()>0)
             {
                  while(x>m && myqueue.size()>0){
                  int item;
                  item=myqueue.front();
                  myqueue.pop();
                  sum=sum-item;
                  x=x-item;
                  }
                  if(x>max)
                  max=x;
                  sum=sum+a[i];
                  }
    }
    cout<<max<<endl;
  //  int p;
   // cin>>p;
    return 0;
}
