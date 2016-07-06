#include <stdio.h>
#include <iostream>
#include <map>
#include <cmath>
#include <cstdlib>
using namespace std;
#define MOD 1000000007
long long a[1000009];
void pre()
{
 int i;
 a[2]=2;
 a[3]=6;
 for(i=4;i<=1000000;i++)
  a[i]=a[i-1] *(a[i-1]+1) % MOD;
}
int main()
{
 int t;
 pre();
 scanf("%d",&t);
 while(t--)
 {
  int n;
  scanf("%d",&n);
  printf("%lld\n",a[n]%MOD);
 }
 return 0;
}
