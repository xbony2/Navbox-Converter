#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(){
	vector<string> navbox;
	ifstream infile("navbox");
	string item;

	while(true){
		infile >> item;
		if(infile.eof())
			break;

		cout << item << endl;
	}

	//cout << navbox << endl;
	infile.close();

	return 0;
}
