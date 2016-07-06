#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
int tmp[1100000];
 
 int fib[1100001];
void merge(int arr[],int min,int mid,int max)
{
  
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
    
    fib[1]=0;
    fib[2]=1;
    int a=0,b=1,c;
    for(int i=3;i<1100001;i++)
    {
            c=(a+b)%100000;
            fib[i]=c;
            a=b;
            b=c;
    }
    
    int t,turn=1;
    scanf("%d",&t);
    while(t--)
    {
          int a,b,count=0,k=0;
         
          scanf("%d%d",&a,&b);
          printf("Case %d:",turn);
          int p=a+b;
        //  cout<<"p="<<p<<endl;
        int *res=new int[b+1];
          for(int i=a;i<=p;i++)
          {
                 // cout<<"i="<<i<<endl;
                  res[k]=fib[i];
                  k++;
                  
                  } 
                //  cout<<"fib[100]="<<fib[100]<<endl;
                 // cout<<"fib[101]="<<fib[101]<<endl;  
                    partial_sort(res, res+100, res+b+1);
                    //printf("Case %i:", i+1);
                    int lim=min(100, b+1);
                    for(int j=0; j<lim; j++)
                    {
                    printf(" %i", res[j]);
                    }
                    printf("\n");
    turn++;
    }
    return 0;
}
