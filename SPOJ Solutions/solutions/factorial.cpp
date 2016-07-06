#include<iostream>
using namespace std;
int main()
{
  int num;
  cin>>num;
  while(num){
    int input;
    cin>>input;
    int sum=0;
    while(input){
      sum+=input/5;
      input=input/5;
    }
    cout<<sum<<endl;
    num--;
  }
  return 0;
}