#include<iostream>
using namespace std;
int main()
{
int t;
cin>>t;
while(t>0)
{
int m,n,revm=0,revn=0,revans=0;

cin>>m>>n;
//cout<<m<<n;
int a;
while(m%10==0)
{
  m=m/10;
}
while(n%10==0)
{
  n=n/10;
}

//cout<<m;
//cout<<n;

while(m!=0)
{
  a=m%10;
  revm=a+revm*10;
  m=m/10;

}
//cout<<revm;
a=0;
while(n!=0)
{
  a=n%10;
  revn=a+revn*10;
  n=n/10;

}
//cout<<revn;

int ans=revn+revm;
a=0;
while(ans!=0)
{
  a=ans%10;
  revans=a+revans*10;
  ans=ans/10;

}

while(revans%10==0)
{
  revans=revans/10;
}

cout<<revans<<endl;
t--;
}
return 0;
}