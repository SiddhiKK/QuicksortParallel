#include<iostream>
#include<omp.h>
using namespace std;
int n;
void quick(int[],int,int);
int part(int[],int,int);

void print(int *a, int n)
{
    int i = 0;
    while(i < n)
    {
        cout<<a[i]<<",";
        i++;
    }
}

int main()
{
	int a[50],i;
	int key,min,max,mid;
	omp_set_nested(1); 	    // inbuild function to start multiprocessing
	cout<<"\nEnter Number of Elements:";
	cin>>n;
	cout<<"Enter Elements: ";
	for(i=0;i<n;i++)
		cin>>a[i];
	cout<<"\nThe Entered Array={";
	for(i=0;i<n;i++)
		if((i+1)==n)
			cout<<a[i];
		else
			cout<<a[i]<<", ";
	cout<<"}\n";
	quick(a,0,n-1);
	cout<<"The Sorted Array={";
	for(i=0;i<n;i++)
		if((i+1)==(n))
			cout<<a[i];
		else
			cout<<a[i]<<", ";
	cout<<"}\n\n";
}

void quick(int a[50],int l,int h)
{
	int j,b[4];
	if(l<h)
	{
		b[0] = l;
		b[1]=part(a,l,h);
		print(a,n);
		b[2]=b[1]+1;
		b[3] = h;
		#pragma omp parallel for
		for(j = 0; j < 4; j=j+2)
		{			
			int tid = omp_get_thread_num();		
			cout<<"Thread No. "<<tid<<"\n";
			quick(a,b[j],b[j+1]);
		}
	}
}

int part(int a[50],int l,int h)
{
	int v,i,j,temp;
	v=a[l];
	i=l;
	j=h+1;
	do
	{
		do
		{
			i++;
		}while(a[i]<v && i<=h);
		do
		{
			j--;
		}while(v<a[j]);
		if(i<j)
		{
			temp=a[i];
			a[i]=a[j];
			a[j]=temp;
		}
	}while(i<j);
	a[l]=a[j];
	a[j]=v;
	return(j);
}

