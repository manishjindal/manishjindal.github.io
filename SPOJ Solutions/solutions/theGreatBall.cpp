#include<iostream>
using namespace std;

void merge(int arr[],int min,int mid,int max)
{
  int tmp[110];
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



int BS(int a[], int l, int r, int key)
{
    int mid;
    
    while(l<r)
    {
              mid=(l+r)/2;
              if(a[mid]==key)          
              return (mid+1);
              else
              if(a[mid]>key)
              r=mid-1;
              else
              l=mid+1;
    }
    if(key<a[l])
    return l;
    else
    return l+1;
    
}

int main()
{
    int t;
    scanf("%d",&t);    
    while(t--)
    {
              int n;
              int a[110];
              int b[110];
              scanf("%d",&n);
              for(int i=0;i<n;i++)
              {
                    scanf("%d%d",&a[i],&b[i]);  
              }
              part(a,0,n-1);
              part(b,0,n-1);
              
              
                            int max=0,local=0;
              for(int i=0;i<n;i++)
              {
                      int index=BS(a,0,n-1,b[i]);
                      
                      local=(index)-i;
                     // cout<<"index="<<index<<" local="<<local<<endl;
                      if(max<local)
                      max=local;
              }
              printf("%d\n",max);
        }     
    return 0;
}
