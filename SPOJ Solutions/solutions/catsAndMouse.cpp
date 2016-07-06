#include <iostream>
#include <cmath>

using namespace std;

int main(){
 int m, n, t, x1, x2, x3, y1, y2, y3;
 cin>>n>>m>>t;
 while(t--){
  cin>>x1>>y1>>x2>>y2>>x3>>y3;
  int d1,d2,d3,d4;
  if(y1>y2)
  d1=y1-y2;
  else
  d1=y2-y1;
  if(y1>y3)
  d2=y1-y3;
  else
  d2=y3-y1;
if(x1>x2)
  d3=x1-x2;
  else
  d3=x2-x1;
  if(x1>x3)
  d4=x1-x3;
  else
  d4=x3-x1;
  if((x1<x2+d1 && x1<x3+d2) || (m-x1<m-x2+d1 && m-x1<m-x3+d2))
   cout<<"YES"<<endl;
  else if((y1<y2+d3 && y1<y3+d4) || (n-y1<n-y2+d3 && n-y1<n-y3+d4))
   cout<<"YES"<<endl;
  else
   cout<<"NO"<<endl;
 }
 return 0;
}
