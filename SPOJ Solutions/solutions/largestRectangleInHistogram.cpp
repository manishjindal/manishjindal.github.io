#include<iostream>
#include<stack>
using namespace std;
long long int getMaxArea(long long int hist[],long long  int n)
{
    
    stack<long long int> s;
 
    long long int max_area = 0; // Initalize max area
    long long int tp;  // To store top of stack
   long long  int area_with_top; // To store area with top bar as the smallest bar
 
    // Run through all bars of given histogram
    long long int i = 0;
    while (i < n)
    {
        // If this bar is higher than the bar on top stack, push it to stack
        if (s.empty() || hist[s.top()] <= hist[i])
            s.push(i++);
        else
        {
            tp = s.top();  // store the top index
            s.pop();  // pop the top
 
            // Calculate the area with hist[tp] stack as smallest bar
            area_with_top = hist[tp] * (s.empty() ? i : i - s.top() - 1);
 
            // update max area, if needed
            if (max_area < area_with_top)
                max_area = area_with_top;
        }
    }
 
    // Now pop the remaining bars from stack and calculate area with every
    // popped bar as the smallest bar
    while (s.empty() == false)
    {
        tp = s.top();
        s.pop();
        area_with_top = hist[tp] * (s.empty() ? i : i - s.top() - 1);
 
        if (max_area < area_with_top)
            max_area = area_with_top;
    }
 
    return max_area;
}
 
// Driver program to test above function
int main()
{
    long long int n;
    cin>>n;
    while(n!=0)
    {
     long long int hist[100001];
          for(long long int i=0;i<n;i++)
                  cin>>hist[i];
    cout<<getMaxArea(hist, n)<<endl; 
    cin>>n;
    }
    return 0;
}
