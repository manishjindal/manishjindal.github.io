#include<iostream>
using namespace std;
#include<stdio.h>
void merge(int [],int ,int ,int );
void part(int [],int ,int );

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


void merge(int arr[],int min,int mid,int max)
{
  int tmp[20001];
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
int main()
{
    
    int t;
    cin>>t;
    while(t>0)
    {
        int n,k;
        cin>>n>>k;
        int a[20001];
        for(int i=0;i<n;i++)
                cin>>a[i];
         part(a,0,n-1); 
         
         int start,end,min=1000000000;
         start=0;
         end=k-1;
       //  cout<<"a[start]="<<a[start]<<endl;
        // cout<<"a[end]="<<a[end]<<endl;
         
         while(end<n)
         {
                   int out=a[end]-a[start];
                   //cout<<"out="<<out<<endl;
                   if(min>out)
                              min=out;
                              start++;
                              end++;
                   }
         cout<<min<<endl;
         t--;
         }
 return 0;
}





