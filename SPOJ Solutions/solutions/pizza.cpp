#include<iostream>
using namespace std;
int main()
{
    
    int n,q=0,h=0,t=0;
    cin>>n;
    int count=0;
   // float item;
   // cout<<"n="<<n;
                                            for(int i=0;i<n;i++)
                                            {
                                                    char s[5];
                                                  //  cout<<"---"<<endl;
                                                    cin>>s;
                                                    
                                                    if(s[2]=='4' && s[0]=='3')
                                                    t++;
                                                    if(s[2]=='2')
                                                    h++;
                                                    if(s[0]=='1' && s[2]=='4')
                                                    q++;
                                                    
                                            }     
            if(t==q){
            count=count+t;
            q=0;
            }
            else if(q<t){
            count=count+t;
            q=0;
            }
            else if(q>t)
            {
                 count=count+t;
                 q=q-t;
                 }
            
            if(h%2==0)
            {
                      count=count+h/2;
                      if(q>0)
                      {
                             if(q%4==0)
                             count=count+q/4;
                             else
                             count=count+q/4+1;
                      }
            }
            else
            {
                count=count+h/2+1;
                q=q-2;
                if(q>0)
                      {
                             if(q%4==0)
                             count=count+q/4;
                             else
                             count=count+q/4+1;
                      }
                
                
                
                }
            
            cout<<count+1<<endl;
            int c;
            cin>>c;
           
    return 0;
    }
