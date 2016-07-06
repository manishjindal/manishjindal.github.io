#include<iostream>
using namespace std;
int main()
{
    
    int a,b,c;
    cin>>a>>b>>c;
    while(1)
    {
            int d1,d2;
            int r1,r2;
            if(a==0 && b==0 && c==0)
                    break;
                    
            d1=b-a;
            d2=c-b;
                    
             r1=b/a;
             r2=c/b;
             
             if(d1==d2)
             {
                       int next;
                       next=c+d1;
                       cout<<"AP "<<next<<endl;
                       }
             
             else if(r1==r2)
             {
                       int next;
                       next=c*r1;
                       cout<<"GP "<<next<<endl;
                       }
              
               cin>>a>>b>>c;
    
    
    }
    return 0;
    
    }
