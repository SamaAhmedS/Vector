#include<iostream>
#include<regex>
#include"MyVector.cpp"
using namespace std;

int main() {
	int arr[] = { 1,9,0,6,7 };
	MyVector<int> v1(arr, 5), v2(6);
	cout <<"Frist Vector\n" << v1<<"\nSize of v1= "<<v1.size()<<" capacity of V1 = "<<
		v1.Capacity()<< "\n\nSecond Vector\n" << v2 << "\nSize of v2= " << v2.size() << " capacity of V2 = " <<
			v2.Capacity();

	v1.push_back(8);
	cout << "\n\nv1 after pushing 8\n" << v1 << "\nSize of v1= " << v1.size() << " capacity of V1 = " <<
		v1.Capacity();

	v2.push_back(78);
	cout << "\n\nv2 after pushing 78\n" << v2 << "\nSize of v2= " << v2.size() << " capacity of V2 = " <<
		v2.Capacity();
	MyVector<int> v3 = v1;
	cout<<"\n\nV3 which is equal to v2 is\n" << v3 << "\nSize of v3= " << v3.size() << " capacity of V3 = " <<
		v3.Capacity();
}
