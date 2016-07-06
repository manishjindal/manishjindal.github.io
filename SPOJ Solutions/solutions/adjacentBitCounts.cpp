#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#define inf 1000000000
#define MAXN 100

using namespace std;

int dp[MAXN][MAXN][2];
int n, k;

int adjbc(int z = 0, int b = 0, int poz = 0) {
    
    if (poz == n) return b == k;
    
    if (b > k) return 0;
    
    /*
    int &ref = dp[poz][b][z];
    
    if (ref != -1) return ref;
    
    //ref = 0;
    ref = adjbc(0, b, poz+1)+adjbc(1, b+z, poz+1);
    
    return ref;
    */
    //int &ref = ;
    
    if (dp[poz][b][z] != -1) return dp[poz][b][z];
    
    return dp[poz][b][z]= adjbc(0, b, poz+1)+adjbc(1, b+z, poz+1);
}

int main()
{
    int t;
    
    scanf("%d", &t);
    
    for (int qwertz = 1; qwertz <= t; ++qwertz) {
        memset(dp, -1, sizeof dp);
        int x;
        scanf("%d%d%d", &x, &n, &k);
        
        printf("%d %d\n", qwertz, adjbc());
    }
    
    return 0;
}
