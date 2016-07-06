#include<iostream>
using namespace std;
int main()
{
 int t;
 scanf("%d",&t);
    while(t--)    
    {
    
     int row,column;
     scanf("%d%d",&row,&column);
    int a[100][100],ans[100][100];
    for(int i=0;i<row;i++)
    for(int j=0;j<column;j++)
    scanf("%d",&a[i][j]);
    
    for(int j=0;j<column;j++)
    ans[0][j]=a[0][j];
    
      for(int i=1;i<row;i++)
      {
              for(int j=0;j<column;j++)
              {
                      
                      int up=0,left=0,right=0;
                      if(j==0)
                      {
                              up=ans[i-1][j];
                              right=ans[i-1][j+1];
                              if(up>=right)
                              ans[i][j]=a[i][j]+up;
                              else
                              ans[i][j]=a[i][j]+right;
                              
                      }
                      else if(j==column-1)
                      {
                                     
                              up=ans[i-1][j];
                              left=ans[i-1][j-1];
                               if(up>=left)
                              ans[i][j]=a[i][j]+up;
                              else
                              ans[i][j]=a[i][j]+left;      
                                     
                      }
                      else
                      {
                      
                              left=ans[i-1][j-1];
                              up=ans[i-1][j];
                              right=ans[i-1][j+1];    
                              if(up>=right && up>=left)
                              ans[i][j]=a[i][j]+up;
                              else if(right>=up && right >=left)
                              ans[i][j]=a[i][j]+right;
                              else
                              ans[i][j]=a[i][j]+left;
                          
                      }
                      
              }
      }
      
      int max=0;
      for(int j=0;j<column;j++)
      {
         if(ans[row-1][j]>max)
         max=ans[row-1][j];
       }
      
      printf("%d\n",max);
    }
    return 0;
}
