#include<iostream>
using namespace std;
int main()
{
    long long n;
    cin>>n;
    while(n!=-1)
    {
                long long a[10000];
              //  cout<<"n="<<n<<endl;
                long long sum=0,mod=0;
                for(int i=0;i<n;i++)
                {
                        cin>>a[i];
                        sum=sum+a[i];
                        }
                mod=sum/n;
        //        cout<<"mod="<<mod<<endl;
                int count=0,pos=0;
                for(int i=0;i<n;i++)
                {
                        if(mod-a[i]>0)
                        pos=pos+(mod-a[i]);
                        count=count+(mod-a[i]);
                        
                        }
      //            cout<<"count="<<count<<endl;
    //              cout<<"pos="<<pos<<endl;      
                        
                if(count!=0)
                cout<<"-1"<<endl;
                else
                cout<<pos<<endl;
                
                
                cin>>n;
    }
    return 0;
}
