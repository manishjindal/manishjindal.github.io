#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[100000]={0},max=0;
    for(int i=0;i<n;i++)
    {
            int fid,ffcount;
            cin>>fid>>ffcount;
            a[fid]=2;
            if(fid>max)
            max=fid;
            int ffid;
            for(int i=0;i<ffcount;i++)
            {
                    cin>>ffid;
                    if(a[ffid]!=2)
                    {
                         if(a[ffid]==0)
                          {
                           a[ffid]=1;
                                          
                                 if(ffid>max)
                                 max=ffid;  
                                 }
                                    
                      }
              }
    }    
    
    int count=0;
    for(int i=0;i<=max;i++)
    {
            if(a[i]==1)
            count++;
            
            }
            cout<<count;
          //  int p;
           // cin>>p;
    return 0;
    
}
