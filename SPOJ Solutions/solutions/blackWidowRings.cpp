#include<iostream>
#include<vector>
#include<algorithm>
struct bridge 
{
  int p;
  int q;
};

using namespace std;
bool check(struct bridge s1, struct bridge s2)
 {
  return (s1.p<s2.p||(s1.p==s2.p&&s1.q<s2.q));
}

int main()
{
int t;
cin>>t;
while(t>0)
{
  
//  int b2[1010]={0};
int n,a1,b1;
              scanf("%d",&n);
  struct bridge a[1500],b[1500];
  for(int i=0;i<n;i++)
  {
    cin>>a1>>b1;
    
      a[i].p=a1; a[i].q=i;
      b[i].p=b1; b[i].q=i;
  }

    sort(a,a+n,check);    sort(b,b+n,check);  
    
     
             if(a[n-1].p>b[n-1].p)
             {
                           
                              printf("%d\n",a[n-1].q+1);
                              
                              }
             else
             {
                 if(a[n-1].q==b[n-1].q)
                 {
                                     if(a[n-1].p>b[n-2].p)
                                      printf("%d\n",a[n-1].q+1);
                              
                                     else
                                     printf("-1\n");
                                     }
                 else
                
                                     printf("-1\n");
                 
                 }
                           

t--;}
return 0;}
