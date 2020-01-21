#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

const int n = 5, m= 5;

void drop(int data[][m])
{
	//Start your code here//
	int temp=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(data[i][j]<0)

				data[i][j]=0;

		}
	}
	for(int i=0;i<n;i++)
	{

		for(int j=0;j<n;j++)
		{
			temp=0;
			if(data[j][i]==0 && (j-1)>=0)
			{
				temp=data[j][i];
				data[j][i]=data[j-1][i];
				data[j-1][i]=temp;
			}

		}
	}






	//End your code here//
}

int main()
{
	// Do not modify below this block //
	int arr[n][m] = {0};
	srand(0);
	for (int i =0; i <n ; i++)
	{
		for (int j=0; j< m ; j++)
		{
			arr[i][j] = rand() % 10 - 5;
		}
	}

	cout << "Generated Data \n";
	for (int i =0; i <n ; i++)
	{
		for (int j=0; j< m ; j++)
		{
			if (arr[i][j] >= 0)
				cout<<" ";
			cout<<arr[i][j]<<" ";
		}
		cout << endl;
	}

	drop(arr);

	cout << "\nAfter -ve removal \n";
	for (int i =0; i <n ; i++)
	{
		for (int j=0; j< m ; j++)
		{
			if (arr[i][j] >= 0)
				cout<<" ";
			cout<<arr[i][j]<<" ";
		}
		cout <<endl;
	}

	// Do not modify below this block //
}

