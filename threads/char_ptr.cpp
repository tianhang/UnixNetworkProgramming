#include<iostream>
using namespace std;

int main()
{
	char *p;
	char arr[] = "hello,world!";
	p = arr;
	int n = sizeof(arr);
	cout<<"sizeof:"<<n<<endl;
	cout<<"sizeof:"<<sizeof(arr)<<endl;
	while(n--)
	{
		cout<<*p++<<endl;
	}
	return 0;
}
