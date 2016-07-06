#include<iostream>



using namespace std;


void merge(int a[], int low, int mid, int high,int arr[])
{
    int b[10001],c[10001];
    int i = low, j = mid + 1, k = 0,temp;
  
    while (i <= mid && j <= high) {
        if (a[i] < a[j])
        {   b[k] = a[i];
        c[k]=arr[i];
        k++;
        i++;
    }
    else if(a[i]==a[j])
    {
        if(arr[i] > arr[j])
        {
            temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
        c[k]=arr[i];
        i++;
        k++;
    }
        else
        {    b[k] = a[j];
         c[k++] = arr[j++];
    }
    }
    while (i <= mid)
    {    b[k] = a[i];
     c[k++] = arr[i++];
    }
  
    while (j <= high)
    {    b[k] = a[j];
     c[k++] = arr[j++];
    }
  
    k--;
    while (k >= 0) {
        a[low + k] = b[k];
    arr[low + k] = c[k];
        k--;
    }
}
  
void mergesort(int a[], int low, int high,int b[])
{
    if (low < high) {
        int m = (high + low)/2;
        mergesort(a, low, m,b);
        mergesort(a, m + 1, high,b);
        merge(a, low, m, high,b);
    }
}
//int inc[10001];
/*int getindex(int inc[] , int l ,int r ,int key)
{
    
    int no;
    while(r - l > 1)
    {
        no=l+(r-l)/2;
        if( inc[no] >= key )
            r=no;
        else
            l=no;
    }
    return r;
}
int longest(int arr[] , int no)
{   
    int i, len;
    int inc[10001];
    for(i=0;i<no;i++)
        inc[i]=0;
    inc[0]=arr[0];
    len=1;
    for(i=1;i<no;i++)
    {
        if(inc[0] > arr[i] )
            inc[0]=arr[i];
        else if(inc[len-1] < arr[i] )
        {   inc[len] = arr[i];
            len++;
        }
        else
        {
            inc[getindex(inc, -1 , len-1 , arr[i] )]=arr[i];
        }
    }
    return len;
} 
            
*/
int main()
{
    int T,no,a[10001],b[10001],i,max,lis[10001],j,temp;
    cin >> T;
    while(T>0)
    {
        T--;
        cin >> no;
        for(i=0;i<no;i++)
            cin >> a[i];
        for(i=0;i<no;i++)
        {   cin >> b[i];
        }
    //  mergesort(a,0,no-1,b);
    //  len=longest(b,no);
        for(i=0 ; i< no; i++)
        {
            for(j=i+1 ; j<no ; j++)
            {
                if(a[i] > a[j])
                {
                    temp=a[i];
                    a[i]=a[j];
                    a[j]=temp;
                    temp=b[i];
                    b[i]=b[j];
                    b[j]=temp;
                }
                else if(a[i]==a[j])
                {
                    if(b[i] > b[j] )
                    {
                        temp=b[i];
                        b[i]=b[j];
                        b[j]=temp;
                    }
                }
            }
        }

    //  for(i=0;i<no;i++)
    //      cout << b[i] << "\t";
    //  cout << endl;
        lis[0]=1;
        max=1;
        for(i=1;i<no;i++)
        {
        
            lis[i]=1;
            for(j=i-1;j>=0;j--)
            {
                if(b[j]<=b[i])
                {
                    if(lis[j]+1>lis[i])
                    {
                        lis[i]=lis[j]+1;
                    }
                }
                if(lis[i]>max)
                {
                    max=lis[i]; 
                }
                
            }
        }       
    //  printf("%d\n",max);
        cout << max << endl;
    }
    return 0;
}       

