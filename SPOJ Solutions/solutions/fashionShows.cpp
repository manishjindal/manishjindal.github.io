#include<iostream>
using namespace std;

void merge(int arr[],int min,int mid,int max)
{
  int tmp[1000];
  int i,j,k,m; 
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


void part(int arr[],int min,int max)
{
 int mid;
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
    
    int t;
    cin>>t;
    while(t>0)
    {
              int n;
              cin>>n;
              int m[1000],f[1000];
              for(int i=0;i<n;i++)
                      cin>>m[i];
                      part(m,0,n-1);
              for(int i=0;i<n;i++)
                      cin>>f[i];
                      part(f,0,n-1);
    
    int sum=0;                  
               for(int i=0;i<n;i++)
               {
                       sum=sum+m[i]*f[i];
                      
                      }
                      cout<<sum<<endl;
    
    
     t--;
    }
    return 0;
}
