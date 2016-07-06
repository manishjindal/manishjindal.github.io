#include<iostream>
#include<stack>
using namespace std;
int main()
{
    int t;
    cin>>t;
    int j=1;
    while(t>0)
    {
    stack<char>mystack;
    char a[120000];
    cin>>a;
    int len=0;    
    while(a[len]!='\0')
        len++;
    int flag=0;
    for(int i=0;i<len;)
    {
            if(a[i]=='1' && a[i+1]=='0' && a[i+2]=='0')
                         i=i+3;
            else 
            {
            //     cout<<"i="<<i<<endl;
                 if(a[i]=='1'){
                   mystack.push(a[i]);i++;}
                 else
                 {
                     int a1,a2;
                     if(mystack.empty())
                         {
                             //           cout<<"i="<<i<<"--1--"<<endl;
                          flag=1;
                          break;
                          }
                     a1=mystack.top();
                     if(a1=='1'){
                     mystack.push(a[i]);i++;}
                     else
                     {
                         if(mystack.empty())
                         {
                           //                 cout<<"--2--"<<endl;
                          flag=1;
                          break;
                          }
                         
                         mystack.pop();
                         a2=mystack.top();
                         if(a2=='1'){
                         mystack.pop();i++;}
                         else{
                         //     cout<<"--3--"<<endl;
                         flag=1;
                         break;
                          }
                         
                       }
                     
                   }
                 
                 }
            
            
    }
    
    if(flag==1 || mystack.size()>0)
                cout<<"Case "<<j<<": "<<"no"<<endl;
   else 
    cout<<"Case "<<j<<": "<<"yes"<<endl;
               j++;
    t--;
    }
    return 0;
}

