#include<stdio.h>

char str1[101],str2[101];

int main()
{
    int t,i,j,k;    char ch;

    scanf("%i%c",&t,&ch);

    while(t--)
    {
        gets(str1);
        gets(str2);

        int arr1[26]={0},arr2[26]={0},arr3[26]={0},flag = 0;

        i = -1;

        while(str1[++i] != 0)
        {
            if(str1[i] >= 'A' && str1[i] <= 'Z')
                arr1[str1[i] - 65]++;

            else if(str1[i] >= 'a' && str1[i] <= 'z')
                arr1[str1[i] - 97]++;
        }

        i = -1;

        while(str2[++i] != 0)
        {
            if(str2[i] >= 'A' && str2[i] <= 'Z')
                arr2[str2[i] - 65]++;

            else if(str2[i] >= 'a' && str2[i] <= 'z')
                arr2[str2[i] - 97]++;
        }

        for(i=0;    i<26;   i++)
        {
            if(!flag)
            {
                if(arr1[i] > arr2[i])
                {
                    flag = 1;
                    arr3[i] = arr1[i] - arr2[i];
                }
                else if(arr1[i] < arr2[i])
                {
                    flag = 2;
                    arr3[i] = arr2[i] - arr1[i];
                }
            }

            else if(flag == 1)
            {
                if(arr2[i] > arr1[i])
                {
                    flag = 3;
                    break;
                }
                else
                    arr3[i] = arr1[i] - arr2[i];
            }

            else
            {
                if(arr2[i] < arr1[i])
                {
                    flag = 3;
                    break;
                }
                else
                    arr3[i] = arr2[i] - arr1[i];
            }

        }

        if(flag == 1 || flag == 2)
        {
            int count=0,hold;

            for(i=0;    i<26;   i++)
                if(arr3[i]%2)
                {
                    count++;
                    hold = i;
                    arr3[i] -= 1;
                }

            if(count > 1)
                flag = 3;

            else
            {
                for(i=0;    i<26;   i++)
                {
                    for(j=0;    j<arr3[i]/2;   j++)
                        printf("%c",i+97);
                }

                if(count == 1)
                    printf("%c",hold+97);

                for(i=25;  i>=0;    i--)
                {
                    for(j=0;    j<arr3[i]/2;   j++)
                        printf("%c",i+97);
                }

                printf("\n");
            }
        }

        if(!flag)
            printf("YES\n");
        else if(flag == 3)
            printf("NO LUCK\n");

    }

    return 0;
}

