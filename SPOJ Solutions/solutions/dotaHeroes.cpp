#include<iostream>
using namespace std;
void merge(int arr[],int min,int mid,int max)
{
  int tmp[550];
 // int tmpi[5500];
  int i,j,k,m; 
  j=min;
  m=mid+1;
  for(i=min; j<=mid && m<=max ; i++)
  {
     if(arr[j]<=arr[m])
     {
         tmp[i]=arr[j];
       //  tmpi[i]=j;
         j++;
     }
     else
     {
         tmp[i]=arr[m];
      //   tmpi[i]=m;
         m++;
     }
  }
  if(j>mid)
  {
     for(k=m; k<=max; k++)
     {
         tmp[i]=arr[k];
     //    tmpi[i]=k;
         i++;
     }
  }
  else
  {
     for(k=j; k<=mid; k++)
     {
        tmp[i]=arr[k];
    //    tmpi[i]=k;
        i++;
     }
  }
  for(k=min; k<=max; k++){
     arr[k]=tmp[k];
  //   arri[k]=tmpi[k];
     }
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
    scanf("%d",&t);
    while(t>0)
    {
               int a[550];
              int n,m,d;
              scanf("%d%d%d",&n,&m,&d);
              
              for(int i=0;i<n;i++)
              scanf("%d",&a[i]);
     
              part(a,0,n-1);
    
              long long int total=m*d;
              int i=n-1,flag=1;
              while(i>=0)
              {
                              if(total==0)
                             {
                                 flag=0;
                                 break;
                                 }
                            else if(a[i]<=d && total>=d)
                             {
                                          flag=1;break;
                                          }
                             else
                             {

                                 a[i]=a[i]-d;
                                 total=total-d;
                                 if(a[i]<=d)
                                   i--;
                                 
                                 }
                             
              }
              
              if(total==0)
               printf("YES\n");
               else
               printf("NO\n");
    
    
    t--;
    
    }
    return 0;
    }
