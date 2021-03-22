#include "FilesStructure.h"
#include <filesystem>
#include <iostream>
#include <string>

//tworzenie list podkatalogow dla jednego elementu
Elem* showPath(std::string pth) {
	std::filesystem::path p(pth.c_str());    //deklaracja zmiennej sciezka
	if (is_regular_file(p)) {
		//std::cout << p << " is a file: \n";
		//std::cout << "fname: " << p.filename() << '\n';
		return NULL;
		// nazwa pliku (z rozszrzeniem)
		//std::cout << "ext: " << p.extension() << '\n'; //rozszerzenie pliku
		//std::cout << "stem: " << p.stem() << '\n'; //trzon nazwy
		//std::cout << "size: " << file_size(p) << '\n'; // rozmiar pliku
	}
	else if (is_directory(p)) {
		Elem* head = NULL;
		Elem* tail = NULL;
		for (const auto& e : std::filesystem::directory_iterator(p)) {
			Elem* n = new Elem;
			//std::cout << e.path().string() <<'\n';
			n->data = e.path().string();
			n->name = e.path().filename().string();
			n->next = NULL;
			n->firstChild = NULL;
			if (head == NULL) {
				head = n;
				tail = n;
			}
			else {
				n->next = NULL;
				tail->next = n;
				tail = n;
			}
			n->type = e.path().extension().string();
			//std::cout << n->type <<'\n';
			n->firstChild = showPath(e.path().string());
		}
		return head;
	}
	else if (exists(p)) {
		//std::cout << p << " is a special file\n";
		return NULL;
	}
	else {
		//std::cout << p << " doesn't exist\n";
		return NULL;
	}
}
void print(Elem* head, int level, int& numb) {
	int i = 0;
	numb++;
	std::cout << numb << ". ";
	while (i < level) {
		std::cout << "  "; i++;
	}
	std::cout << "->" << head->name << '\n';

	if (head->firstChild != NULL) {
		print(head->firstChild, level + 1, numb);
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
			print(head->firstChild, level + 1, numb);
		}

	}
}

void deleteTree(Elem*& elem) {
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
bool CreateTree(Elem*& root) {
	std::cout << "PODAJ SCIEZKE: ";
	std::string pth;
	getchar();  //pu³apka na krasnoludki wciskaj¹ce enter
	std::getline(std::cin, pth);
	//std::getline(std::cin, pth);
	//std::cout << pth;
	root = new Elem;
	root->data = pth;
	root->name = "index";
	root->next = NULL;
	root->firstChild = showPath(pth);
	return true;
}