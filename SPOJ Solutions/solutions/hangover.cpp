#include<iostream>
using namespace std;
int main()
{
 float n;
 cin>>n ;
 while(n!=0.00)
 {
               int count=0;
               float j=2,sum=0;
              while(sum<n){
                       sum=sum+1/j;
                       j++;
                       count++;
                       }
               
               cout<<count<<" card(s)"<<endl;
               
               
               cin>>n;
               }   
    
    
    
    
    return 0;
}
