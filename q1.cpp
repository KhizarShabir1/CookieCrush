#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

const int n = 3, m= 5;
int dif=0,sum;

void calculateDistance(int data[][m], int disances[][n])
{
	//Start your code here//

	for(int i=0;i<n;i++)
	{


		for(int j=0;j<n;j++)
		{
				dif=0;

			for(int k=0;k<m;k++)
			{
				sum=data[i][k]-data[j][k];
				dif+=pow((sum),2);
			}
			disances[i][j]=dif;
		}

	}




	//End your code here//
}

int main()
{
	// Do not modify below this block //
	int arr[n][m] = {0};
	int dis[n][n] = {0};
	for (int i =0; i <n ; i++)
	{
		for (int j=0; j< m ; j++)
		{
			arr[i][j] = rand() % m;
		}
	}

	cout << "Generated Data \n";
	for (int i =0; i <n ; i++)
	{
		for (int j=0; j< m ; j++)
		{
			cout<<arr[i][j]<<" ";
		}
		cout <<endl;
	}

	calculateDistance(arr, dis);

	cout << "\nCalculated Distance \n";

	for (int i =0; i <n ; i++)
	{
		for (int j=0; j< n ; j++)
		{
			cout<<dis[i][j]<<" ";
		}
		cout <<endl;
	}

	// Do not modify below this block //
}


