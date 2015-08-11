#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
	string navbox [1000000];
	ifstream infile("navbox");
	int count;

	infile >> count;
	for(int i = 0; i < count; i++){
		infile >> navbox[i];
		cout << navbox[i] << endl;
	}

	//cout << navbox << endl;
	infile.close();

	return 0;
}
