#include<iostream>
using namespace std;
int main()
{
int a[101][200];
 
for(int i=0;i<101;i++)
{
        for(int j=0;j<200;j++)
                a[i][j]=-1;
        
}

a[1][0]=1;  
for(int i=2;i<101;i++)
{
        int j=0;
        int sum=0,carry=0;
        while(a[i-1][j]!=-1)
        {
                         //   cout<<"i="<<i<<"j="<<j<<endl<<a[i-1][j]*i<<"++"<<carry<<endl;
                sum=carry+a[i-1][j]*i;
                a[i][j]=sum%10;
                carry=sum/10;
               // cout<<"sum="<<sum<<"carry="<<carry<<endl;
                j++;
         }
         if(carry>0)
         {
                    while(carry>10)
                    {
                                   a[i][j++]=carry%10;
                                   carry=carry/10;
                                   }
         
                    a[i][j]=carry;        
                    
         }           
}
    
    int t;
    cin>>t;
    while(t>0)
    {
              int n;
              cin>>n;
            int j=0;
            while(a[n][j]!=-1)  
            {
               j++;
    
            }
            for(int k=j-1;k>=0;k--)
                    cout<<a[n][k];
                    cout<<endl;
              t--;
    }
    /*
    for(int i=1;i<101;i++)
    {
            int j=0;
            while(a[i][j]!=-1)
            {
                            cout<<a[i][j];
                            j++;
                            }
            cout<<endl;
            }
                int p;
    cin>>p;
    */
    return 0;
}
