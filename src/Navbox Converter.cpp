#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(){
	vector<string> navbox;
	ifstream infile("navbox");

	if(!infile){
		cout << "Um... something broke." << endl;
		return 0;
	}

	while(1){
		char buf[1000000];
		infile.getline(&(buf[0]), 1000000, '\n');
		navbox.push_back(string(buf));
		if(infile.eof())
			break;
	}

	vector<string>::iterator viter = navbox.begin();

	while(viter != navbox.end()){
		cout << *viter << endl;
		viter++;
	}

	//cout << navbox << endl;
	infile.close();

	return 0;
}
