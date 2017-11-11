#pragma once
using namespace std;
#include<string>
class Classify {
private:
	static const int NAME_SIZE = 20;
public:
	int id;
	char name[NAME_SIZE];
	int getId() {
		return id;
	}
	void setId(int id) {
		this->id = id;
	}
	char* getName() {
		return name;
	}
	void setName(char* name) {
		for (int i = 0; i < strlen(name); i++)
			this->name[i] = name[i];
		this->name[strlen(name)] = '\0';
	}
	string getElemType(string Elem) {
		if (Elem == "id") return typeid(id).name();
		else if (Elem == "name") return typeid(name).name();
		else {
			throw "Field  Not Found!";
		}
	}
	int getIntElemByName(string Elem) {
		if (Elem == "id") return id;
		else {
			throw "Field  Not Found!";
		}
	}
	float getFloatElemByName(string Elem) {
		return 1;
	}
	char* getCharElemByName(string Elem) {
		if (Elem == "name") return  name;
		else {
			throw "Field  Not Found!";
		}
	}
};
