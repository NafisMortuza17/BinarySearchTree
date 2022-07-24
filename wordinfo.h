#pragma once
#include<iostream>
using namespace std;

//struct that holds the relavent information for a word and sent to the BST array
struct  wordinfo
{
	string word;// word itself
	int line;// line of first apperance

	//constructors 
	wordinfo(string w, int l) : word(w), line(l) {};
	wordinfo() :line(0) {};
};
// operator overloading

//comparison operators 
inline bool operator < (wordinfo obj1, wordinfo obj2) {
	return obj1.word < obj2.word;
}

inline bool operator > (wordinfo obj1, wordinfo obj2) {
	return obj1.word > obj2.word;
}
//ostream operator to print the struct 
inline ostream& operator << (ostream& out, wordinfo obj)
{
	out << "Word:" << obj.word << endl;
	out << "First Apperance: Line:" << obj.line << endl;

	return out;
}

