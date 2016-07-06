#include<iostream>
#include<math.h>
using namespace std;
long long m[8000][5];

long long p(int a, int b)
{
  if (b == 1 || a == 1||a==0)
    return 1;
  if (a < 0)
    return 0;

  if (m[a][b] != -1) return m[a][b];

  long long sum = 0;
  for (int i=1; i<=b; i++) {
    sum += p(a-i, i);
  }

  m[a][b] = sum;

  return sum;
}

int sq[300];
int search(int num)
{
    int l=0;
    int u=(int)ceil(sqrt(num));  
    //cout<<"num="<<num<<" l="<<l<<" u="<<u<<endl;  
    while(l<=u)
    {
        if(sq[l]+sq[u]==num)
              return 1;
        if(sq[l]+sq[u]<num)
        l++;
        else
        u--;          
              
    }
    return 0;
    
}

int main()
{
    int t;
    scanf("%d",&t);  
    int prime[8000]={0};
    int newprime[510];
     for(int i=2;i<8000;i++)
        {
            if(prime[i]==0){ 
            int j=2,k=0;
            while(j*i<8000)
            {
                     k=j*i;
                     if(prime[k]!=-1)
                     prime[k]=-1;
                     j++;
            }        
            }
        }    
  for(int i=1;i<300;i++)
  sq[i]=i*i;
  int k=0;
  for(int i=2;i<8000;i++)
  {
          if(prime[i]==0)
          {
              int re=search(i);
              if(re==1)
                 newprime[k++]=i;                       
                         
          }        
          
  }
  
     while(t--)
    {
               for (int i=0; i<8000; i++) {
    for (int j=0; j<5; j++) {
      m[i][j] = -1;
    }
  }
              int n,m1;
              scanf("%d%d",&n,&m1); 
              //memset(way,-1,sizeof(way));      
              printf("%lld\n",p(newprime[n-1],m1));        
    }
    return 0;
}
