#include "hash.h"
#include "node.h"
#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew);
void createDiff(istream& fold, istream& fnew, ostream& fdiff);

int main()
{
	/*Hash h;
	h.insert("aaaaaa", 0);
	h.insert("bbbbbb", 9);
	h.insert("cccccc", 10);
	int offset;
	Node* p;
	assert(h.find("aaaaaa", offset, p));
	assert( offset == 0 && p->next->data == "bbbbbb" && p->next->next->data == "cccccc");
	cout << "all tests passed" << endl;*/

	ofstream diff("wardiff.txt");
	ifstream old1("warandpeace1.txt");
	ifstream newf("warandpeace2.txt");

	createDiff(old1, newf, diff);

	ofstream diff2("greendiff.txt");
	ifstream old2("greeneggs1.txt");
	ifstream newf2("greeneggs2.txt");

	createDiff(old2, newf2, diff2);

	ofstream diff3("strangediff.txt");
	ifstream old3("strange1.txt");
	ifstream newf3("strange2.txt");

	createDiff(old3, newf3, diff3);

	ofstream diff4("smalldiff.txt");
	ifstream old4("smallmart1.txt");
	ifstream newf4("smallmart2.txt");

	createDiff(old4, newf4, diff4);

	/*ifstream old1("warandpeace1.txt");
	ifstream old2("greeneggs1.txt");
	ifstream old3("strange1.txt");
	ifstream old4("smallmart1.txt");

	ifstream diff1("wardiff.txt");
	ifstream diff2("greendiff.txt");
	ifstream diff3("strangediff.txt");
	ifstream diff4("smalldiff.txt");
	ofstream change1("warnew.txt");
	ofstream change2("greennew.txt");
	ofstream change3("strangenew.txt");
	ofstream change4("smallnew.txt");

	applyDiff(old1, diff1, change1);
	applyDiff(old2, diff2, change2);
	applyDiff(old3, diff3, change3);
	applyDiff(old4, diff4, change4);*/

	/*ifstream old("old.txt");
	ifstream eggs("greeneggs1.txt");
	ofstream change("new.txt");*/
	/*ifstream old2("greeneggs1.txt");

	applyDiff(old2, diff2, change);*/

	cout << "everything's fine" << endl;
	return 0;

}