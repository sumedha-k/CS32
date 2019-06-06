#include <iostream>
#include <fstream>
#include <string>
#include "hash.h"
using namespace std;

bool getInt(istream& inf, int& n);
bool getCommand(istream& inf, char& cmd, int& length, int& offset);

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
	string sold(""), add(""), temp("");
	while (fold.peek() != EOF) // while not the end of the file
	{
		getline(fold, add);
		sold += add + '\n';
	}
	char cmd = '\0'; // just a random start char
	int length(0), offset(0);
	while (cmd != 'x') // while not at end of file
	{
		if (!getCommand(fdiff, cmd, length, offset)) // if command isn't valid
			return false;
		switch (cmd)
		{
		case 'A':
			for (int i = 0; i < length; i++) // get what needs to be added to the new file
			{
				char c;
				fdiff.get(c);
				fnew << c; // insert the chars into the file
			}
			break;
		case 'C':
			if (sold.size() < offset + length) // if the chars aren't possible to copy, the command is invalid
				return false;
			temp = sold.substr(offset, length); // insert substring into the new file
			fnew << temp;
			break;
		case '\r':
		case '\n':
			break;
		}
	}
	return true;
}

void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
	string sold("");
	string temp("");
	while (fold.peek() != EOF) // put old file into a string 
	{
		getline(fold, temp);
		sold += temp + '\n';
	}
	string smallestString;
	bool firstString = true;

	for (int checkSize = 6; checkSize < 40; checkSize++) // each iteration of this loop constructs a possible diff file
	{ // but uses different size string segments (6-40) to copy each iteration 
		if (!firstString)
		{
			fnew.clear();
			fnew.seekg(0);
		}
		string checkString = "";
		Hash h;
		// break up the old string into hash table
		const int n = checkSize; // MUST ATLEAST BE 4 otherwise the copy instruction is not worth it
		for (int i = 0; i < n; i++)
		{
			for (int offset = i; offset < sold.size(); offset += n)
				h.insert(sold.substr(offset, n), offset);
		}

		// break up and compare new string segments

		while (fnew.peek() != EOF)
		{
			string temp = "";
			int newOffset;
			Node*p;
			for (int i = 0; i < n && fnew.peek() != EOF; i++) // add n chars to temp
				temp += fnew.get();
			if (h.find(temp, newOffset, p))
			{
				int length = temp.size();
				bool match = true;
				while (match && p->next != nullptr) // if the segment is found
				{
					string comp = "";
					for (int i = 0; i < n && fnew.peek() != EOF; i++) // read in next three chars
						comp += fnew.get();
					int matchlength = 0;
					string check = p->next->data;
					for (int i = 0; i < comp.size() && i < check.size(); i++)
					{
						if (check[i] == comp[i]) // compare the next n chars from the new file to the old file
							matchlength++;
						else
						{
							match = false;
							break;
						}
					}
					length += matchlength;
					for (int i = 0; i < comp.size() - matchlength; i++)
						fnew.unget();
					p = p->next;
				}
				checkString += 'C'; // add command to the string
				checkString += to_string(length);
				checkString += ',';
				checkString += to_string(newOffset);
			}
			else // the the segment isn't found
			{
				for (int i = 0; i < temp.size() - 1; i++) // unget everything but first char of temp
					fnew.unget();
				temp = temp[0]; // set unmatching portion as first char of temp
				bool match = false;
				while (!match) // while nothing worth copying is found
				{
					string comp = "";
					for (int i = 0; i < n && fnew.peek() != EOF; i++)
						comp += fnew.get();
					if (comp.size() < 4) // end of file- not enough characters for it to be worth copying
					{
						temp += comp;
						break;
					}
					if (h.find(comp, newOffset, p)) 
					{
						for (int i = 0; i < comp.size(); i++) // unget all of the chars in comp
							fnew.unget();
						p->used = false;
						match = true; // finish add command and go to copy command
					}
					else // if the segment isn't found
					{
						temp += comp[0]; // add the first char of the string to the string that needs to be copied
						for (int i = 0; i < comp.size() - 1; i++)
							fnew.unget();
					}
				}
				checkString += 'A'; // add command to the string
				checkString += to_string(temp.size());
				checkString += ':';
				checkString += temp;
			}
		}
		if (firstString) // if this is the first iteration through the for loop, the diff file found is the smallest
		{
			smallestString = checkString;
			firstString = false;
		}
		else if (checkString.size() < smallestString.size()) // if the new diff file is smaller than the previously smallest 
			smallestString = checkString; 
	}
	for (int j = 0; j < smallestString.size(); j++) // put the smallest diff command sequence into the ostream
		fdiff << smallestString[j];
}

bool getInt(istream& inf, int& n)
{
	char ch;
	if (!inf.get(ch) || !isascii(ch) || !isdigit(ch))
		return false;
	inf.unget();
	inf >> n;
	return true;
}

bool getCommand(istream& inf, char& cmd, int& length, int& offset)
{
	if (!inf.get(cmd))
	{
		cmd = 'x';  // signals end of file
		return true;
	}
	char ch;
	switch (cmd)
	{
	case 'A':
		return getInt(inf, length) && inf.get(ch) && ch == ':';
	case 'C':
		return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);
	case '\r':
	case '\n':
		return true;
	}
	return false;
}