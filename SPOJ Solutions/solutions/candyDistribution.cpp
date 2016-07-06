#include<iostream>
#include<string.h>
using namespace std;
long long int tmp[100005];
void merge(long long int arr[],long long int min,long long int mid,long long int max)
{
  
  //memset(tmp,0,sizeof(long long int)*max);
  long long int i,j,k,m; 
  j=min;
  m=mid+1;
  for(i=min; j<=mid && m<=max ; i++)
  {
     if(arr[j]<=arr[m])
     {
         tmp[i]=arr[j];
         j++;
     }
     else
     {
         tmp[i]=arr[m];
         m++;
     }
  }
  if(j>mid)
  {
     for(k=m; k<=max; k++)
     {
         tmp[i]=arr[k];
         i++;
     }
  }
  else
  {
     for(k=j; k<=mid; k++)
     {
        tmp[i]=arr[k];
        i++;
     }
  }
  for(k=min; k<=max; k++)
     arr[k]=tmp[k];
}

void part(long long int arr[],long long int min,long long int max)
{
   //  cout<<"--inside--"<<endl;
 long long int mid;
 if(min<max)
 {
   mid=(min+max)/2;
   part(arr,min,mid);
   part(arr,mid+1,max);
   merge(arr,min,mid,max);
 }
}

int main()
{
    long long int n;
    scanf("%lld",&n);
    while(1)    
    {
             if(n==0)
             break;
             long long int c[100005],p[100005];
         //       cout<<"--1--"<<endl;  
             for(long long int i=0;i<n;i++)
                      scanf("%lld",&c[i]);
          //   cout<<"--2--"<<endl;  
             for(long long int i=0;i<n;i++)
                      scanf("%lld",&p[i]);
            //         cout<<"--3--"<<endl;   
                
             part(c,0,n-1);
           //  cout<<"--4--"<<endl;   
             part(p,0,n-1);
             
           // cout<<"--5--"<<endl;    
             long long int sum=0,j=n-1;
             
             for(long long int i=0;i<n;i++)
             {
                      sum=sum+(c[j]*p[i]);
                      j--;
                      
                      }
                
                printf("%lld\n",sum);
                scanf("%lld",&n);
    }
    return 0;
}
