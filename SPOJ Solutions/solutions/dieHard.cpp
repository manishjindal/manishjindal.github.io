#include<iostream>
using namespace std;
int main()
{
    int t;
    scanf("%d",&t);    
    while(t--)
    {
              int h,a;
              scanf("%d%d",&h,&a);
              
              int ha=3,aa=2,hw=-5,aw=-10,hf=-20,af=5;
              int count=0;
              int flag=0;
              while(1)
              {
                      
                      if(h<=0 || a<=0)
                           break;
                         
                    
                     if(flag==1)
                    count++;
                     
                    
                      h+=ha;
                      a+=aa;
                      count++;
                  
                //  cout<<"h="<<h<<" a="<<a<<endl;
                      if(a>10)
                      {
                           h+=hw;
                           a+=aw;    
                      }
                      else
                      {
                          h+=hf;
                          a+=af;
                      }
                      
                      flag=1;
                //  cout<<"h="<<h<<" a="<<a<<endl;
              }
                printf("%d\n",count);        
    }
    return 0;
}
