/*
CS-132
Professor Mckay
Project-3
16/12/2021*/

#include<iostream>
#include"BST.h"
#include<fstream>
#include<sstream>
#include"wordinfo.h"

using namespace std;

void reduceString(string&);//function to remove all non-alphabetic chars 
void getfileinfo(ifstream&);//gets the file name 

int main()
{


	BST<wordinfo> Concordance[26];//BST to contain words in alphabetical order (a-z)
	ifstream fin;
	string line;//variable that takes in entire line
	string word;// to read each individual word from the line, stingstream more specifically
	int linecount = 0;// to keep track of line number


	getfileinfo(fin);//call function to open file

	/*end program if file is not found*/
	if (!fin) {
		cout << "Unable to locate file\n";
		return -1;
	}
	/*it can process very large txt files but takes a while*/
	cout << "Processing txt file, please wait\n";
	cout << '\n';


	/*read in entire  line till the end of file */
	while (getline(fin, line)) {

		/*if the line read in is empty, increment the linecount and continue to read in the next line*/
		if (line.empty()) {
			linecount++;
			continue; // continue to read in the next line as there is nothing to process on an emmpty string
		}
		/* if not empty, still increment line count as a line has been read in */
		linecount++;

		/* put the entire line in a stringstream for reading in each individual word on the line from the stream */
		stringstream wordstream(line);

		/*read in each individual word from the stream until end and process each word  */
		while (wordstream >> word)
		{
			/*	get rid of all the non alphabetic characters, if string gets reduced to empty, continue to read in next word from the stream*/
			reduceString(word);

			if (word.empty()) {
				continue;
			}

			else {
				//the ascii value of the very first character of the string subtracted by ascii value of a gives the correct spot(a-z)-'a'
				
				int pos = word[0] - 'a';

				//construct struct with the required information
				wordinfo temp(word, linecount);

				//simply insert it at the valid position
				Concordance[pos].insert(temp);
				//(if item aldready exists in the tree, the insert function and BinNode class has been modified for that instance)


			}

		}
	}
	bool Exit = false; //for search menu condition
	while (!Exit) {
		char  decision;// users decision to continue
		cout << '\n';
		cout << "Enter a word you would like to search for in the BST\n";
		cout << '\n';
		cin >> word;
		cout << '\n';
		//reduce the word after user enters it
		reduceString(word);

		//if word is empty after reduceString,the word is invalid, return to the very top of condition and read in word again
		if (word.empty()) {
			cout << "Please enter a valid word\n";
			continue;
		}
		int pos = word[0] - 'a'; //the correct spot in the bst array
		wordinfo temp(word, -1);

		//if search returns true, print the information of the word  user entered ,else print message
		if (Concordance[pos].search(temp)) {
			cout << "The item was found, here are the information:\n";
			Concordance[pos].printInfo(temp);
		}
		else
			cout << "Item does not exist in the tree\n";
		cout << '\n';
		cout << "Enter y or Y to continue or N or n to exit\n";
		cin >> decision;

		if (decision == 'n' || decision == 'N') {
			Exit = true;
		}
	}

	cout << '\n';
	/*print out text concordance */
	cout << "Here is the text concordance:\n";
	cout << '\n';
	for (int i = 0; i < 26; i++) {

		Concordance[i].inorder(cout);
	}
}



void reduceString(string& s) {
	//traverse through the string and check for each character 
	for (int i = 0; i < s.size(); i++) {

		//if the character does not fall within the range of alpabets 
		if (s[i] < 'A' || s[i] > 'Z' &&
			s[i] < 'a' || s[i] > 'z')
		{
			/*erase the char if it does not fall under range  */
			s.erase(i, 1);
			i--; //decrement i as a char has been reduced from the string
		}
	}
	/* if string is not empty after removing all non alphabetical characters, convert them to all lower;*/
	if (!s.empty()) {
		for (int i = 0; i < s.size(); i++) {
			s[i] = tolower(s[i]);
		}
	}
}


void getfileinfo(ifstream& fin)
{
	/*gets filename and attempts to open it*/
	string filename;
	cout << "Enter the name of the txt file\n";
	cin >> filename;


	fin.open(filename);

}

