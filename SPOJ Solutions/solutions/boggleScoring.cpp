#include<iostream>
#include <map>
#include <stdio.h>
#include <string.h>
using namespace std;
char str[101][4000];
int main()
{
      map<string,int> mymap;
         map<string,int>::iterator it;
        //map<string,int> mymap;
         int a[101]={0};
     int n;
     scanf("%d",&n);
     getchar();
     
     for(int i=0;i<n;i++)
     gets(str[i]);
   
     for(int i=0;i<n;i++)
     {
      char *pch;
      int len=0,point=0;
      pch = strtok (str[i]," ");
      while (pch != NULL)
      {
        //printf ("%s\n",pch);
        len=strlen(pch);
        if(len<=4)
        point=1;
        if(len==5)
        point=2;
        if(len==6)
        point=3;
        if(len==7)
        point=5;
        if(len>7)
        point=11;
        //cout<<"points="<<point<<endl;
        it=mymap.find(pch);
        if(it!=mymap.end())
        {
      //  cout<<"already exist="<<pch<<" @"<<mymap.find(pch)->second<<endl;
         int sec;
         sec=mymap.find(pch)->second;
                     if(sec!=-1)
                    {
                    a[sec]=a[sec]-point;
                    it->second=-1;
                  //  cout<<"points="<<point<<" a[sec]="<<a[sec]<<endl;
                    }
        }
        else{
        
        mymap.insert(pair<string,int>(pch,i));
        a[i]+=point;
       // cout<<"inserting="<<pch<<" pos= "<<i<<" points="<<point<<" a[i]="<<a[i]<<endl;
        }
        pch = strtok (NULL, " ");
      }
           //  cout<<"a[i]="<<a[i]<<endl;
     }
    int max=a[0];
    for(int i=1;i<n;i++)
    {
            if(a[i]>max)
            max=a[i];
            }
    printf("%d",max);
    return 0;
}
