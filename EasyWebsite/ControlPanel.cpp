#include "Control.h"
#include "HTMLcreator.h"
#include "FilesStructure.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>



void greeting() {
	std::cout << "Witaj w prgramie EasyWebsite wersja ALPHA\n";
	std::cout << "Aby sprawdzic liste dostepnych komend wpisz help\n";
}
void help() {
	std::cout << "help - pomoc\n";	
	std::cout << "dzialanie - wyswietl opis dzialania programu\n";
	std::cout << "utworzK - utworz strukture katalogow\n";
	std::cout << "wypiszK - wypisz strukture katalogów\n";
	std::cout << "usunK - usun liste katalogow\n";
	std::cout << "wczytajH - wczytaj sciezke do szablonu HTML\n";
	std::cout << "wypiszH - wypisz nazwe szablonu HTML\n";
	std::cout << "HTML! - wykonaj wlasciwy program\n";
	std::cout << "clear - wyczysc konsole\n";
	std::cout << "close - zakoncz program";

}
void manual() {  //instrukcja
	std::ifstream manual;
	std::string line;
	manual.open("manual.txt");
	while (std ::getline(manual, line)) {
		std::cout<< line <<'\n';
	}
	manual.close();
}
void printStructure(Elem* head, int level, int& numb) {				//wypisywanie struktury
	int i = 0;
	numb++;
	std::cout << numb << ". ";
	while (i < level) {
		std::cout << "  "; i++;
	}
	std::cout << "->" << head->name << '\n';

	if (head->firstChild != NULL) {
		printStructure(head->firstChild, level + 1, numb);
	}
	while (head->next) {

		i = 0;
		numb++;
		std::cout << numb << ". ";
		while (i < level) {
			std::cout << "  "; i++;
		}
		head = head->next;
		std::cout << "->" << head->name << '\n';

		if (head->firstChild != NULL) {
			printStructure(head->firstChild, level + 1, numb);
		}

	}
}
void readPath(std::string& path) {  //wczytywanie œcie¿ki do folderu zapisu
	std::getchar();  //pu³apka na krasnoludki czaj¹ce siê w buforze
	std::getline(std::cin, path);
	if(path[path.size()-1]!='\\') path+='\\';
}
void readTempl(std::string& s) {  //wczytywanie œcie¿ki do szablonu strony
	std::getchar();  //pu³apka na krasnoludki czaj¹ce siê w buforze
	std::getline(std::cin, s);
	std::filesystem::path p(s.c_str());    
	if (is_regular_file(p) && p.extension()==".html") {
		return;
	}
	else {
		s = "NotDeclared";
	}
}
void printK(Elem* root, bool LIST_EXIST) {  //wypisanie struktury katalogów
		if (LIST_EXIST) {
			int numb = 0;
			if (root->firstChild)
				printStructure(root->firstChild, 0, numb);
			else
				std::cout << "Lista pusta";
		}
		else
			std::cout << "Lista nieistnieje";
}
void del(Elem*& root, bool& LIST_EXIST) {	//usuwanie struktury katalogów
	if (LIST_EXIST) {
		deleteTree(root->firstChild);
		delete root;
		root = NULL;
		LIST_EXIST = false;
	}
}
void HTML(Elem* root, bool LIST_EXIST, std::string siteTempl){ //tworzenie stron internetowych
	if (LIST_EXIST && siteTempl!="NotDeclared") {
		std::string folder;
		std::cout << "PODAJ NAZWE FOLDERU DO ZAPISU: ";	
		readPath(folder);										//podanie folderu zapisu
		std::filesystem::path p(folder.c_str());				//sprawdzenie czy sciezka jest folderem
		if (is_directory(p)) {									
			createHTML(root, siteTempl, folder);
			std::cout << '\a';
		}
		else {
			std::cout << "Bledna sciezka do folderu zapisu";
		}
	}
	else {
		std::cout << "Error";
		exit(1);
	}
}
void close(Elem*& root, bool& LIST_EXIST) {				//zamykanie programu
	del(root, LIST_EXIST);
	exit(0);
}


void panel() {
	Elem* root = NULL;
	std::string command;
	std::string siteTempl = "NotDeclared";
	bool LIST_EXIST = false;
	std::cout << ": ";
	while (std::cin >> command) {
		if (command == "close") close(root, LIST_EXIST);
		else if (command == "clear") system("cls");
		else if (command == "help") help();
		else if (command == "dzialanie") manual();
		else if (command == "utworzK") LIST_EXIST = CreateTree(root);
		else if (command == "wypiszK") printK(root, LIST_EXIST);
		else if (command == "usunK" && LIST_EXIST) del(root, LIST_EXIST);
		else if (command == "wczytajH") readTempl(siteTempl);
		else if (command == "wypiszH") std::cout << siteTempl;
		else if (command == "HTML!") HTML(root, LIST_EXIST, siteTempl);
		else std::cout << "Nieznana komenda";
		std::cout << "\n: ";
	}
}