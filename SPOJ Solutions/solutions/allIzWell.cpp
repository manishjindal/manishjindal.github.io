#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char str[109][109];
int visited[109][109];
int row,col,flag;

char result[11] = "ALLIZZWELL";


void dfs(int i,int j,int index)
{
    visited[i][j] = -1;

    if(index == 10 || flag == 1)
    {
        flag = 1;
        return;
    }

    if(i - 1 >= 0 && str[i-1][j] == result[index] && visited[i-1][j] != -1)
    {
        dfs(i-1,j,index+1);
        visited[i-1][j] = 0;
    }

    if(i + 1 < row && str[i+1][j] == result[index] && visited[i+1][j] != -1)
    {
        dfs(i+1,j,index+1);
        visited[i+1][j] = 0;
    }

    if(j - 1 >= 0 && str[i][j-1] == result[index] && visited[i][j-1] != -1)
    {
        dfs(i,j-1,index+1);
        visited[i][j-1] = 0;
    }

    if(j + 1 < col && str[i][j+1] == result[index] && visited[i][j+1] != -1)
    {
        dfs(i,j+1,index+1);
        visited[i][j+1] = 0;
    }

    if(i - 1 >= 0 && j - 1 >= 0 && str[i-1][j-1] == result[index] && visited[i-1][j-1] != -1)
    {
        dfs(i-1,j-1,index+1);
        visited[i-1][j-1] = 0;
    }

    if(i - 1 >= 0 && j + 1 < col && str[i-1][j+1] == result[index] && visited[i-1][j+1] != -1)
    {
        dfs(i-1,j+1,index+1);
        visited[i-1][j+1] = 0;
    }

    if(i + 1 < row && j - 1 >= 0 &&  str[i+1][j-1] == result[index] && visited[i+1][j-1] != -1)
    {
        dfs(i+1,j-1,index+1);
        visited[i+1][j-1] = 0;
    }

    if(i + 1 < row && j + 1 < col && str[i+1][j+1] == result[index] && visited[i+1][j+1] != -1)
    {
        dfs(i+1,j+1,index+1);
        visited[i+1][j+1] = 0;
    }
}


int calculate()
{
    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            flag = 0;
            if(str[i][j] == 'A')
                dfs(i,j,1);
            if(flag == 1)
                return 1;
            visited[i][j] = 0;
        }
    }
    return 0;

}



int main()
{
    int testCases ,i,j;
    
    scanf("%d",&testCases);

    while(testCases--)
    {
        memset(visited,0,sizeof(str));

        scanf("%d%d",&row,&col);



        for(i=0;i<row;i++)
        {
            
            scanf("%s",str[i]);
        }


        if(calculate())
            printf("YES\n");
        else
            printf("NO\n");
        getchar();
    }
    return 0;

}