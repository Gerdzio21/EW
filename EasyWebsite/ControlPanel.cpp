#include "Control.h"
#include "HTMLcreator.h"
#include "FilesStructure.h"
#include <iostream>
#include <string>
#include <filesystem>


//zmienne
int kolumny = 0;
int rzedy = 0;
char tekst[] = "Wyswietlany tekst!";
void greeting() {
	std::cout << "WITAJ w prgramie EasyWebsite wersja ALPHA\n";
	std::cout << "-> Aby sprawdzicliste dostepnych komend wpisz help\n";
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
void printStructure(Elem* head, int level, int& numb) {
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
void readPath(std::string& path) {
	std::getchar();  //pu³apka na krasnoludki czaj¹ce siê w buforze
	std::getline(std::cin, path);
	if(path[path.size()-1]!='\\') path+='\\';
}
void readTempl(std::string& s) {
	std::getchar();  //pu³apka na krasnoludki czaj¹ce siê w buforze
	std::getline(std::cin, s);
	std::filesystem::path p(s.c_str());    
	if (is_regular_file(p)&& p.extension()==".html") {
		return;
	}
	else {
		s = "BadFile";
	}
}
void print(Elem* root, bool LIST_EXIST) {
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
void del(Elem*& root, bool& LIST_EXIST) {
	if (LIST_EXIST) {
		deleteTree(root->firstChild);
		delete root;
		root = NULL;
		LIST_EXIST = false;
	}
}
void HTML(Elem* root, bool LIST_EXIST){
	if (LIST_EXIST) {
		std::string folder;
		std::cout << "PODAJ NAZWE FOLDERU DO ZAPISU: ";
		readPath(folder);
		std::filesystem::path p(folder.c_str());
		if (is_directory(p)) {
			createHTML(root, "temp.txt", folder);
			std::cout << '\a';
		}
		else {
			std::cout << "Bledna sciezka do folderu zapisu";
		}
	}
	else {
		std::cout << "LISTA NIE ISTNIEJE!!!";
	}
}
void close(Elem*& root, bool& LIST_EXIST) {
	del(root, LIST_EXIST);
	exit(0);
}


void panel(Elem*& root) {
	std::string command;
	std::string siteTempl = "NotDeclared";
	bool LIST_EXIST = false;
	std::cout << ": ";
	while (std::cin >> command) {
		if (command == "close") close(root, LIST_EXIST);
		else if (command == "clear") system("cls");
		else if (command == "help") help();
		else if (command == "utworzK") LIST_EXIST = CreateTree(root);
		else if (command == "wypiszK") print(root, LIST_EXIST);
		else if (command == "usunK" && LIST_EXIST) del(root, LIST_EXIST);
		else if (command == "wczytajH") readTempl(siteTempl);
		else if (command == "wypiszH") std::cout << siteTempl;
		else if (command == "HTML!") HTML(root, LIST_EXIST);
		else std::cout << "Nieznana komenda";
		std::cout << "\n: ";
	}
}