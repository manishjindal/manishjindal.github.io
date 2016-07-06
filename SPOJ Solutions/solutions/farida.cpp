#include<iostream>
using namespace std;
long long int monester[10010]={0};

int main()
{
long long int t;
cin>>t;
int p=1;
while(p<=t)
{
long long int max[10010]={0};
long long int num,j1=0,j2=0,sum1=0,sum2=0;
cin>>num;
  for(long long int i=0;i<num;i++)
    cin>>monester[i]; 
  
    max[0]=monester[0];
    max[1]=monester[1];
    long long int ans;
    //max=max[0]>max[1]?max[0]:max[1]
  for(long long int i=0;i<num-2;i++)
  {
    j1=i+2;
    j2=i+3;
    sum1=max[i]+monester[j1];
    sum2=max[i]+monester[j2];
    if(sum1>max[j1])
      max[j1]=sum1;
    if(sum2>max[j2])
      max[j2]=sum2;
    
  }
  ans=max[0];
  
  for(long long int i=1;i<num;i++)
  {
    if(ans<max[i])
    ans=max[i];
  } 
    cout<<"Case "<<p<<": "<<ans<<endl;
p++;
}
return 0;
}
