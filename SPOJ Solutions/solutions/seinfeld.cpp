#include<iostream>
#include<vector>
#include<stdio.h>
using namespace std;
int main()
{
  static int k=1;
  int i=0,l=0,move=0;
  long int open=0,close=0;
  vector<string>str;
  string str1;
  char c;
  cin>>str1;
  str.push_back(str1);
  c=str[l][0];
  while(c!='-')
  {   
    
      open=0;close=0;move=0;
      for(int j=0;j<(str[i].size());j++)
      {
        if(str[i][j]=='{')
          open++;
        else
          close++;
        if(str[i][j]=='\n')
          {
            move=0;
            break;
          }
        if((open>0)&&(close>0)&&(open==close))
        {
          open--;
          close--;
          continue;       
                  
        }
        
          
      
        if((close>0)&&(open==0))
        { move++;
          close--;
          open++;
          //cout<<"close="<<close<<endl;
          //cout<<"open="<<open<<endl;
          //cout<<"move="<<move<<endl;
        
          continue;
        }
        if((close>0)&&(open!=0)&&(open>close))
        {
          open--;
          close--;
          //move++;
          //  cout<<"close="<<close<<endl;
          //cout<<"open="<<open<<endl;
          //cout<<"move="<<move<<endl;
        
          continue;
        }
        
        if((close>0)&&(open!=0))
        {
          open--;
          close--;
          move++;
          //  cout<<"close="<<close<<endl;
          //cout<<"open="<<open<<endl;
          //cout<<"move="<<move<<endl;
        
          continue;
        }
        if((close==0)&&(open!=0))
        {
          //move++;
          
          //  cout<<"close="<<close<<endl;
          //cout<<"open="<<open<<endl;
          //cout<<"move="<<move<<endl;
        
          continue;
        }
      
      }
        move=move+(open/2);
        cout<<k++<<". "<<move<<endl;
    
    i++;
    l++;
    cin>>str1;  
    str.push_back(str1);
    c=str[l][0];
  } 
return 0;
}
