#include <iostream>
#include <fstream>
#include <string>
#include "HTMLcreator.h"
#include "FilesStructure.h"


std::string findTextFile(Elem* head, std::string& p) { //sprawdzanie czy dana œcie¿ka prowadzi do pliku .txt
	while (head) {
		if (head->type == ".txt") {
			p = head->data;
			return head->name;							//zwraca nazwê pliku tekstowego
			break;
		}
		head = head->next;
	}
}
void addText(Elem* head, std::ofstream& html) //kopiowanie tekstu
{
	std::string line;
	std::fstream text;
	std::string p = "NULL";
	std::string title;
	title = findTextFile(head->firstChild, p);

	if (p != "NULL") {													//je¿eli istnieje plik txt
		html << "<div id = \"article\">\n";								//elementy jêzyka HTML
		html << "<h1 id = \"articleName\">" << title << "</h1>\n";		// |
		html << "<div class = \"tekst\">\n";							// |
		text.open(p.c_str());
		while (getline(text, line)) {									//kopiowanie linijek tekstu
			html << line;
			html << " <br/>";											//element jêzyka HTML
		}
		html << "</div>\n</div>\n";										//element jêzyka HTML
		text.close();
	}
}
void addLinks(Elem* head, std::ofstream& html, std::string htmlTemplate, std::string folder) //dodawanie linkow do podstron
{
	Elem* tmp = head->firstChild;
	html << "\n<ul>";
	while (tmp) {
		if (tmp->type.empty()) {										//jezeli element jest folderem tworzymy 
			html << "<li>";												//elementy jêzyka HTML
			html << "<a href = \"" << tmp->name + ".html" << "\" >";
			html << tmp->name << "</a>\n</li>\n";
			createHTML(tmp, htmlTemplate, folder);
		}
		tmp = tmp->next;
	}
	html << "\n</ul>\n";												//element jêzyka HTML
}


void createHTML(Elem* head, std::string htmlTemplate, std::string folder) { //tworzenie pliku html
	std::ofstream html;					//plik html, do ktorego zapisujemy nasza strone
	std::ifstream tmpl;					//plik szablonu
	std::string siteName = head->name;	//nazwa strony
	std::string line;					//zmienna pomocnicza
	siteName += ".html";				//dodanie rozszerzenia do pliku
	siteName = folder + siteName;		//zapisanie w lokalizacji
	html.open(siteName.c_str());		//otwieranie plikow
	tmpl.open(htmlTemplate.c_str());	// -||-
	while (getline(tmpl, line)) {						//kopiowanie do momentu, a¿ \/
		if (line == "<!--Paste Links Here-->") {		//natrafimy na linie informuj¹c¹, gdzie trzeba wkleiæ linki do podstron
			addLinks(head, html, htmlTemplate, folder); //wklejamy linki
			break;
		}
		else {
			html << line;								//w p.p. kopiujemy dalej
		}
	}
	while (getline(tmpl, line)) {						//kopiowanie do momentu, a¿ \/
		if (line == "<!--Paste Article Here-->") {		//natrafimy na linie informuj¹c¹, gdzie wkleiæ tekst
			addText(head, html);
			break;
		}
		else {
			html << line;								//w p.p. kopiujemy dalej
		}
	}
	while (getline(tmpl, line)) {						//kopiujemy do koñca
			html << line;
	}
	html.close();
}


