#include<iostream>
using namespace std;
int main()
{
    
  
    int t;
    scanf("%d",&t);
    for(int i=0;i<t;i++)
    {
        int num;
        scanf("%d",&num);    
        if(num%2!=0)
            printf("%d\n",num);
        else
        {
            int copy,bits=1;    
            copy=num;
            
            while(1)
            {
                    if(copy==1 || copy==0)
                    break;
             copy=copy/2;              
                 bits++;         
            }
            //cout<<"bits="<<bits<<endl;
            int a[100000],item;
            for(int i=0;i<bits;i++)
            {
                   a[i]=num&1;
                   
                    num=num>>1;
            }
            int sum=0,j=0;
            for(int i=bits-1;i>=0;i--)
            {
                //    cout<<a[i];
                    int multi=1,k=j;
                    while(k!=0)
                    {
                           multi=multi*2;              
                             k--;  
                    }
                //   cout<<"i="<<i<<" multi="<<multi<<endl;
                    sum+=a[i]*multi;
               //     cout<<"sum="<<sum<<endl;
            j++;
            }
            printf("%d\n",sum);
        }
    }
    return 0;
}
