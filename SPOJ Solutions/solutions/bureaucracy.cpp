#include<iostream>
using namespace std;
 char str[100005][100];
int main()
{
    int t;
    cin>>t;
    getchar();
    while(t>0)
    {    
         int a[100005]={0};
         
         int n,p;
         cin>>n;
         getchar();
                
         for(int i=1;i<=n;i++)
                 gets(str[i]);
               
         for(int i=n;i>0;i--)
         {
                 //cout<<"--"<<endl;
         
                 if(str[i][0]=='d')
                   a[i]++;
                 else
                 {
                     int x=0,j=7;
                     //cout<<str[i][j]<<"--2--";
                     while(str[i][j]!='\0' && str[i][j]!=' '){
                    x=x*10;
                     x=x+str[i][j]-'0';
                     j++;
                     }
                   // cout<<"x="<<x<<endl;
               //      cout<<"i="<<i<<endl;
               
                     if(a[i]>=0)
                     a[x]--;
                     a[i]++;
                     
                     }
                 
                // cout<<"i="<<i<<endl;
                 //int p;
          //       cin>>p;
                 
                 }
                 int count=0;
         for(int i=1;i<=n;i++)
         {
                 if(a[i]>0)
                 count++;
                 //cout<<i<<" ";
          }
          if(count==0){
          cout<<count<<endl;
          t--;
          continue;
          }
          cout<<count<<endl;
         for(int i=1;i<=n;i++)
         {
                 if(a[i]>0)
                 
                 cout<<i<<" ";
          }
           
          cout<<endl;
         t--;
    }
    return 0;
}
