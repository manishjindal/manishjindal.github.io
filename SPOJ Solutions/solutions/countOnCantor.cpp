#include<iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t>0)
    {
              int n,count=0,flag=0;
              cin>>n;
         for(int i=1;i<100000000;i++)     
         {
                 int l,m;
                 if(i%2==0)
                 {
                          
                           m=i;
                           for(int j=1;j<=i;j++, m--){
                                   count++;
                                  
                                                       if(count==n){
                                                                   cout<<"TERM "<<n<<" IS "<<j<<"/"<<m<<endl;
                                                                   flag=1;
                                                                   break;
                                                                   }
                                       }
                 }
                 else
                 {
                     l=1;
                     for(int j=i;j>=1;j--,l++)
                     {
                             count++;
                             if(count==n)
                             {
                                         cout<<"TERM "<<n<<" IS "<<j<<"/"<<l<<endl;
                                         flag=1;
                                         break;
                                         }
                             
                      }
                             
                 }
                  if(flag==1)
                  break;  
                 
         }
    
    
    
     t--;
    }
    return 0;
}





