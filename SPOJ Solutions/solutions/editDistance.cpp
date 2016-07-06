#include<iostream>
#include<string.h>
using namespace std;
 int d[2005][2005];
int min(int a,int b,int c)
{
    if(a<=b && a<=c)
    return a;
    if(b<=a && b<=c)
    return b;
    if(c<=a && c<=b)
    return c;

}
int edit(char s[], char t[])
 {  
              
              
   int row=strlen(s);
   int column=strlen(t);
   //cout<<"row="<<row<<endl;
   //cout<<"column="<<column<<endl; 
   
  
  
   for(int i=0;i<=row;i++)
     d[i][0] = i; // the distance of any first string to an empty second string
   for(int j=0;j<=column;j++)
     d[0][j] = j; // the distance of any second string to an empty first string
  
   for(int i=1;i<=row;i++)
     for (int j=1;j<=column;j++)
       if(s[i-1]==t[j-1])  
         d[i][j] =d[i-1][j-1];       // no operation required
       else
         d[i][j] = min(d[i-1][j],d[i][j-1],d[i-1][j-1])+1;
  /*
  for(int j=0;j<=row;j++){
     for (int i=0;i<=column;i++)
     cout<<d[j][i]<<" ";
     cout<<endl;}
     */
   return d[row][column];
}
int main()
{
 int t;
 scanf("%d",&t);
 while(t--)    
 {
    
    char s1[2005],s2[2005];
    scanf("%s%s",s1,s2);
    printf("%d\n",edit(s1,s2));
    
    
    }   
return 0;
}
