#include "FilesStructure.h"
#include <filesystem>
#include <iostream>
#include <string>
//funkcja g≥Ûwna tworzenia listy dla danego wskaünika;
bool CreateTree(Elem*& root) {
	std::cout << "PODAJ SCIEZKE: ";
	std::string pth;
	getchar();  //pu≥apka na krasnoludki wciskajπce enter
	std::getline(std::cin, pth);
	//std::getline(std::cin, pth);
	//std::cout << pth;
	root = new Elem;
	root->data = pth;
	root->name = "index";
	root->next = NULL;
	root->firstChild = showPath(pth);
	std::cout << '\a';
	return true;
}
//tworzenie list podkatalogow dla jednego elementu
Elem* showPath(std::string pth) {
	std::filesystem::path p(pth.c_str());    //deklaracja zmiennej sciezka
	if (is_regular_file(p)) {			//jezeli sciezka prowadzi do pliku to nie ma dzieci wiÍc wskaünik firstChild na NULL
		return NULL; 
	}
	else if (is_directory(p)) { //jezeli sciezka prowadzi do folderu to tworzymy liste elementÛw naleøπcyh do folderu
		Elem* head = NULL;
		Elem* tail = NULL;
		for (const auto& e : std::filesystem::directory_iterator(p)) {			//pÍtla sluøπca do przechodzenia po folderze
			Elem* n = new Elem;
			n->data = e.path().string();			//zapisanie sciezki do elementu
			n->name = e.path().filename().string();	//zapisanie nazwy elementu
			n->type = e.path().extension().string();//zapisanie rozszerzenia elementu, folder nie ma rozszerzenia wiÍc .empty() bedzie = true;
			n->next = NULL;							//wskaünik na nastÍpny element na NULL
			n->firstChild = NULL;					//wskaønik na pierwszy podelement danego elementu
			if (head == NULL) {
				head = n;
				tail = n;
			}
			else {
				n->next = NULL;
				tail->next = n;
				tail = n;
			}
			n->firstChild = showPath(e.path().string());//sprawdzenie sciezki pierwszego podelementu
		}
		return head;
	}
	else if (exists(p)) { //plik o niznanym rozszerzeniu
		//std::cout << p << " is a special file\n";
		return NULL;
	}
	else {
		//std::cout << p << " doesn't exist\n";
		return NULL;
	}
}


void deleteTree(Elem*& elem) {					//usuwanie struktury
	if (elem->firstChild != NULL) {
		deleteTree(elem->firstChild);
	}

	while (elem->next) {
		Elem* tmp = elem;
		elem = elem->next;

		if (elem->firstChild != NULL) {
			deleteTree(elem->firstChild);
		}
		delete tmp;
	}
	delete elem;

}
