#include <iostream>
#include <string>
using namespace std;

void isUnique(int *ptr,int size );
int main()
{
	int size=5;
	int arr[size]={3,2,5,2,1};
	int*ptr=arr;
	isUnique(ptr,size);


        return 0;
}

void isUnique(int *ptr,int size){
	int check=0;
	int a=1;
	for(int i=0,j;i<size;i++)
	{
		for(j=a;j<size;j++)
		{
			if(*(ptr+i)==*(ptr+j))
					check++;
		}
		a++;
	}
	if(check!=0)
		cout<<"array is not unique"<<endl;
	else
		cout<<"array is Unique"<<endl;
}

