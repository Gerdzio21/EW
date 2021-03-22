#include <iostream>
#include <fstream>
#include <string>
#include "HTMLcreator.h"
#include "FilesStructure.h"
using namespace std;

void findTextFile(Elem* head, string& p) {
	while (head) {
		//cout << head->data << " " <<head->name << " " << head->type <<'\n';
		if (head->type == ".txt") {
			//cout << head->data << "!";
			p = head->data;
			break;
		}
		head = head->next;
	}
}

void createHTML(Elem* head, std::string htmlTemplate, std::string folder) {
	ofstream html; //plik html, do ktorego zapisujemy nasza strone
	string siteName = head->name;
	siteName += ".html";
	siteName = folder + siteName;
	html.open(siteName.c_str());
	addContent(head, html, htmlTemplate, folder);

	html.close();
	/*std::cout << htmlFileName.c_str();*/
	//std::cout << "Done!\a";
}

void addContent(Elem* head, ofstream& html, std::string htmlTemplate, std::string folder)
{

	//tekst
	html << "<div class=\"tekst\">\n";

	string line;
	fstream text;
	string p = "NULL";
	findTextFile(head->firstChild, p);
	if (p != "NULL") {
		//cout << p << endl;
		text.open(p.c_str());
		while (getline(text, line)) {
			//cout << line << endl;
			html << line;
		}
		text.close();
	}

	//while (!text.eof()) { //nie dzia³a³o :O
	//	cout << p;
	//	getchar();
	//	getline(text, line);
	//	//cout << line;
	//	html << line;
	//}

	html << "\n</div>\n";
	//tekst

	html << "\n<ul>\n";
	Elem* tmp = head->firstChild;
	while (tmp) {
		if (tmp->type != ".txt") {
			html << "<li>";
			html << "<a href = \"" << tmp->name + ".html" << "\" >";
			html << tmp->name << "</a>\n</li>\n";
			createHTML(tmp, htmlTemplate, folder);
		}
		tmp = tmp->next;
	}
	html << "\n</ul>\n";
}

