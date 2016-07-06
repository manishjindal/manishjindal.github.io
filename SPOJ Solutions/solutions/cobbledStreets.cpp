#include<iostream>
#include<limits.h>
#include<string.h>
#include<stdio.h>
using namespace std;
int a[1009][1009];
int p,n,m;
int minkey(int visited[],int cost[])
{
    
       int mini=INT_MAX,index;            
       for(int i=1;i<=n;i++)
       {
               if(visited[i]==0 && cost[i]<mini)
               {
                                mini=cost[i];
                                index=i;                 
               }
       }
       return index;
}
int main()
{
    
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(a,0,sizeof(a));      
        scanf("%d%d%d",&p,&n,&m);
        for(int i=0;i<m;i++)
        {
               int s,e,l;
               scanf("%d%d%d",&s,&e,&l);
               a[s][e]=l*p;   
               a[e][s]=l*p;         
        }
        /*
        for(int i=1;i<=n;i++)
        {
                        
                        for(int j=1;j<=n;j++)                          
                        cout<<a[i][j]<<" ";
                        cout<<endl;
        }
          */
          
            int cost[n+1],visited[n+1];
            for(int i=1;i<=n;i++)
            {
                    visited[i]=0;        
                    cost[i]=INT_MAX;
            }  
               cost[1]=0;
          
          for(int i=1;i<=n;i++)
          {
                  int u=minkey(visited,cost);
                  visited[u]=1;
                  for(int i=1;i<=n;i++)
                  {
                          if(a[u][i] && visited[i]==0 && a[u][i]<cost[i])
                                     cost[i]=a[u][i];           
                  }
       
          } 
          int ans=0;
          for(int i=1;i<=n;i++)
           ans+=cost[i];
          printf("%d\n",ans);
    }    
    return 0;
}
