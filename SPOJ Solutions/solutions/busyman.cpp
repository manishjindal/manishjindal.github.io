#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
struct node 
{
       int a,b;
       };
int check(struct node s1,struct node s2)
{
   return (s1.b<s2.b||(s1.b==s2.b&&s1.a<s2.a));
    
}
int main()
{
    
    int t;
    scanf("%d",&t);
    while(t--)
    {
         struct node point[100009];     
         int n;
         scanf("%d",&n);     
         for(int i=0;i<n;i++)
         scanf("%d%d",&point[i].a,&point[i].b);        
         sort(point,point+n,check);
         int maxi=1;
         int preb=point[0].b;
         for(int i=1;i<n;i++)
         {
                 if(point[i].a>=preb)
                 {
                   preb=point[i].b; 
                   maxi++;
                 }
         }
          printf("%d\n",maxi);
         
    }
    return 0;
}
