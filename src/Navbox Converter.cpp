#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct NavboxThing {
	string link;
	string displayName;
};

// For {{NI}}
struct NavboxItem : NavboxThing {
	string mod;
	string name;
};

// For {{L}}
struct Link : NavboxThing {};

// {{Navbox}} group[1-20] parameters
struct Group {
	string name;
	vector<NavboxThing> contents;
};

class Navbox {
private:
	string title;
	string name;
	string mod;
	vector<Group> contents;
public:
	Navbox(string title, string name, vector<Group> contents) : title(title), name(name), contents(contents){
		vector<Group>::iterator viter = contents.begin();
		bool foundMod;

		while(viter != contents.end() && !foundMod){
			vector<NavboxThing>::iterator viter2 = viter->contents.begin();
			while(viter2 != viter->contents.end() && !foundMod){
				NavboxItem item = (NavboxItem) viter2;
				if(item.mod != ""){//TODO: Internet is down, I'm not sure how to do a null check
					mod = item.mod;
					foundMod = true;
				}
				viter2++;
			}
			viter++;
		}

		if(mod == ""){
			cout << "Error: mod wasn't found. Now it's all broken." << endl;
		}
	}

	Navbox(string title, string name, string mod, vector<Group> contents) : title(title), name(name), mod(mod), contents(contents){}

	string toWikitext(){
		string wikitext = "{{Navbox\n";
		wikitext =+ "|title=" + title + "\n";
		wikitext =+ "|name=" + name + "\n";
		vector<Group>::iterator viter = contents.begin();
		int num = 1;
		while(viter != contents.end()){
			if(viter->name != "")
				wikitext =+ "|group" + num + "=" + viter->name + "\n";
			vector<NavboxThing>::iterator viter2 = viter->contents.begin();
			bool firstTime = true;
			while(viter2 != viter->contents.end()){
				if(firstTime){
					NavboxItem item = (NavboxItem) viter2;
					if(item.mod != ""){//If true, this assumes it is a link.
						Link link = (Link) viter2;
						wikitext += "|list" + num + "={{L|" + link.link + "|" + link.displayName + "}}{{,}}<!--";
					}else{
						wikitext += "|list" + num + "={{NI|mod=" + item.mod + "|" + item.name + + "|" + item.link + "|" + item.displayName + "}}{{,}}<!--";
					}
				}
				viter2++;
			}

			num++;
			viter++;
		}

		wikitext =+ "}}<noinclude>{{Navbox Applied Energistics/doc|the items in the " + title + " mod}}</noinclude>\n";

		return wikitext;
	}

	string toLua(){
		return ""; //TODO
	}

};

int main(){
	string navbox;
	ifstream infile("navbox");

	if(!infile){
		cout << "Um... something broke." << endl;
		return 0;
	}

	while(1){
		char buf[1000000];
		infile.getline(&(buf[0]), 1000000, '\n');
		navbox += string(buf) + "\n";
		if(infile.eof())
			break;
	}

	cout << navbox << endl;

	infile.close();

	return 0;
}
