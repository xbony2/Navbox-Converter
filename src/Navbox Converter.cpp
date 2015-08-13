#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// For {{NI}}/{{L}}
struct NavboxThing {
	enum Type {ITEM, LINK};
	Type type;
	string mod;
	string name;
	string link;
	string displayName;
};

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
				if(viter2->type == viter2->ITEM){
					mod = viter2->mod;
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
				wikitext =+ "|group" + to_string(num) + "=" + viter->name + "\n";
			vector<NavboxThing>::iterator viter2 = viter->contents.begin();
			bool firstTime = true;
			bool lastTime = false;
			while(viter2 != viter->contents.end()){
				if(firstTime){
					if(viter2->type == viter2->LINK)
						wikitext += "|list" + to_string(num) + "={{L|" + viter2->link + "|" + viter2->displayName + "}}{{,}}<!--";
					else
						wikitext += "|list" + to_string(num) + "={{NI|mod=" + viter2->mod + "|" + viter2->name + + "|" + viter2->link + "|" + viter2->displayName + "}}{{,}}<!--";
					firstTime = false;
				}else if(lastTime){
					if(viter2->type == viter2->LINK)
						wikitext += "        -->{{L|" + viter2->link + "|" + viter2->displayName + "}}";
					else
						wikitext += "        -->{{NI|mod=" + viter2->mod + "|" + viter2->name + + "|" + viter2->link + "|" + viter2->displayName + "}}";
				}else{
					if(viter2->type == viter2->LINK)
						wikitext += "        -->{{L|" + viter2->link + "|" + viter2->displayName + "}}{{,}}<!--";
					else
						wikitext += "        -->{{NI|mod=" + viter2->mod + "|" + viter2->name + + "|" + viter2->link + "|" + viter2->displayName + "}}{{,}}<!--";
					if(viter2 - 1 == viter->contents.end())
						lastTime = true;
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
	vector<int> v = { 34,23 };
	Navbox navbox = new Navbox("{{L|Santa's Toys}}", "Navbox Santa's Toys", new vector<Group>{
		{"Items", new vector<NavboxThing>{{NavboxThing::ITEM, "STS", "Match"}, {NavboxThing::ITEM, "STS", "Ender Blaster"}, {NavboxThing::ITEM, "STS", "Nether Blaster"}}},
		{"Blocks", new vector<NavboxThing>{{NavboxThing::ITEM, "STS", "Block of Damn Giving"}, {NavboxThing::ITEM, "V", "Glowstone", "Heavy Light"}, {NavboxThing::ITEM, "STS", "Spiced Sand"}}}});

	string navboxS = navbox.toWikitext();
	/*ifstream infile("navbox");

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

	infile.close();*/

	cout << navbox << endl;

	return 0;
}
