#include<iostream>
using namespace std;
int main()
{
 int g,b;
 cin>>g>>b;
 while(1)
 {    
      int max,min;
    if(g==-1 && b==-1)
             break;
    
    if(g==b)
    {
            if(g==0)
            cout<<"0"<<endl;
            else
            cout<<"1"<<endl;
             cin>>g>>b;
             continue;
            }
    else if(g==0 || b==0)
    {
         if(g!=0)
                 cout<<g<<endl;
         else
                 cout<<b<<endl;
                  cin>>g>>b;
                  continue;
         }
         
    else if(g==1 || b==1)
    {
         int ans;
         if(g!=1)
         {
                 if(g%2==0)
                           ans=g/2;
                 else
                           ans=g/2+1;
                 cout<<ans<<endl;
                 }
         if(b!=1)
         {
                 if(b%2==0)
                           ans=b/2;
                 else
                           ans=b/2+1;
                 cout<<ans<<endl;
         }
                  cin>>g>>b;
                  continue;
         }
         
    else if(g==b/2 || b==g/2)
    {
         cout<<"2"<<endl;
         cin>>g>>b;
         continue;
         }
   else if(g>b)
    {
           max=g;
           min=b;
           }
    else
    {
        max=b;
        min=g;
        }
    
    int value,carry,ans;
   
    min=min+1;
    carry=max%min;
    value=max/(min);
    if(carry>=1)
               value=value+1;
   /*
    if(carry==0)
                value=value-1;
   */
    /*
    if(max%2==0 && min%2==0){
   // min=min+1;
    carry=max%min;
    value=max/(min+1);
    ans=carry+value;
    //g>b?max=g:max=b;
    }
    else
    {
    min=min+1;
    carry=max%min;
    value=max/(min+1);
    ans=carry+value;
    //g>b?max=g:max=b;
    }
    */
    cout<<value<<endl;
    
    cin>>g>>b;
    
    }  
    return 0;
}
