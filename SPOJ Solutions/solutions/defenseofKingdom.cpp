#include<stdio.h>
void mergesort(int A[],int low,int mid,int high,int N)
{
 int i,j,k,l,m,temp[N];
 i=low;
 l=low;
 m=mid+1;
 while(i<=mid && m<=high)
 {
  if(A[i]<=A[m])
   temp[l++]=A[i++];
  else
   temp[l++]=A[m++];
 }
 while(i<=mid)
  temp[l++]=A[i++];
 while(m<=high)
  temp[l++]=A[m++];
 for(i=low;i<=high;i++)
  A[i]=temp[i];
}
void partition(int A[],int LB,int UB,int N)
{
 int mid;
 if(LB<UB)
 {
  mid=(LB+UB)/2;
  partition(A,LB,mid,N);
  partition(A,mid+1,UB,N);
  mergesort(A,LB,mid,UB,N);
 }
}
int main()
{
 int t;
 scanf("%d",&t);
 while(t--)
 {
  int W,H,N,i,temp_x,temp_y;
  scanf("%d%d%d",&W,&H,&N);
  int X[N+1],Y[N+1];
  for(i=0;i<N;i++)
   scanf("%d%d",&X[i],&Y[i]);
  partition(X,0,N-1,N);
  partition(Y,0,N-1,N);
  X[N]=W+1;
  Y[N]=H+1;
  long long max_x,max_y;
  max_x=X[0];
  max_y=Y[0];
  for(i=1;i<=N;i++)
  {
   temp_x=X[i]-X[i-1];
   temp_y=Y[i]-Y[i-1];
   if(max_x<temp_x)
    max_x=temp_x;
   if(max_y<temp_y)
    max_y=temp_y;
  }

  printf("%lld\n", (max_y - 1) * (max_x - 1));
 }
 return 0;
}