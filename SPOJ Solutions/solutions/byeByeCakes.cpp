#include<iostream>
using namespace std;
int main()
{
    
    while(1)
    {
            int e,f,s,m,e1,f1,s1,m1;
            cin>>e>>f>>s>>m>>e1>>f1>>s1>>m1;
            if(e==-1 && f==-1 && s==-1 && m==-1 && e1==-1 && f1==-1 && s1==-1 && m1==-1)
                   break;
                   int max=0;
            
            if(e>=f && e>=s&& e>=m ){
                    if((e%e1)!=0)
                       max=(e/e1)+1;
                    else
                       max=e/e1;
                    }
            else if (f>=e && f>=s && f>=m )
                   {
                          if(f%f1!=0)
                               max=f/f1+1;
                            else
                               max=f/f1;
            
                          }
            else if (s>=m && s>=f && s>=e )
                    {
                           if(s%s1!=0)
                               max=s/s1+1;
                            else
                               max=s/s1;
                          
                          
                          }
            else 
                 {
                          if(m%m1!=0)
                               max=m/m1+1;
                            else
                               max=m/m1;
                          }
    
   // cout<<"max="<<max<<endl;
                          while(1)
                          {
                                  int diff1=0,diff2=0,diff3=0,diff4=0;
                                  diff1=e1*max-e;
                                 // cout<<"diff1"<<diff1<<endl;
                                  diff2=f1*max-f;
                                  
                                  //cout<<"diff2"<<diff2<<endl;
                                  diff3=s1*max-s;
                                  
                                 // cout<<"diff3"<<diff3<<endl;
                                  diff4=m1*max-m;
                                  
                           //       cout<<"diff4"<<diff4<<endl;
                                  if(diff1>=0 && diff2>=0 && diff3>=0 && diff4>=0)
                                  {
                                              cout<<diff1<<" "<<diff2<<" "<<diff3<<" "<<diff4<<endl;
                                              break;
                                              }
                                  max++;
                          }
    }
    return 0;
}
