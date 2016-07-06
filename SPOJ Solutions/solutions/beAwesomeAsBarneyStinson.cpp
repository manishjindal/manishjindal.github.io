#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
int m,n,a[105][105],dp[105][105];
int ways(int index,int gift)
{
  if(gift > 0 && index > m )
    return  0 ;
  if(gift==0 && index==m)
    return 1;

  if(dp[index][gift] != -1 )
    return dp[index][gift] ;
  
  int res=0;

  for(int i=a[index][0];i<=a[index][1];i++)
  {
    if(gift-i>=0)
    {
      res+=ways(index+1,gift-i);
    }
  }
  
  return dp[index][gift]=res;
}
int main()
{
  
  while(1)
  {
    
    scanf("%d%d",&m,&n);
    if(m==0 && n==0)
      break;
    
    for(int i=0;i<m;i++)
    {
      scanf("%d",&a[i][0]);
      scanf("%d",&a[i][1]);
    }
    memset(dp,-1,sizeof(dp));
    cout<<ways(0,n);
  }
  return 0;
}