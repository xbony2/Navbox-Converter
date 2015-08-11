#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	string navbox;
	ifstream infile("navbox");
	infile >> navbox;
	cout << navbox << endl;
	infile.close();

	return 0;
}
