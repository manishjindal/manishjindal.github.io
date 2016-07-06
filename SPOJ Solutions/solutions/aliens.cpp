#include<iostream>
#include<queue>
#include<stdio.h>
using namespace std;
int main()
{
    
    long long int t;
scanf("%lld",&t);
while(t>0)    
{
              queue<long long int> q;
    long long int n,cost;
    long long int a[100001];
    scanf("%lld%lld",&n,&cost);
    for(long long int i=0;i<n;i++)
            scanf("%lld",&a[i]);
    
    //cout<<"--"<<endl;
    long long int global=0,local=0,sum=0,x1=0;        
    for(long long int i=0;i<n;i++)
    {
            long long int x=0;
            x=sum+a[i];
            q.push(a[i]);
            if(x<=cost)
            {
                      //cout<<"x="<<x<<endl;
                      x1=x;
                        
                        sum=sum+a[i];
                        local++;
                        if(local>global)
                        global=local;
            }
            else if(q.size()>0)
            {
                long long int item;
                item=q.front();
               
                q.pop();
                //sum=sum-item;
                sum=sum+a[i]-item;
                if(sum<x1)
                x1=sum;
                }
    }
   // if(sum<x1)
   // printf("%lld %lld\n",sum,global);
    //else
    printf("%lld %lld\n",x1,global);
    
 t--;   
}  
    return 0;
}


