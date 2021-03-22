#ifndef FilesStructure_H
#define FilesStructure_H
#include<string>
struct Elem {
	std::string data; //adres 
	std::string name; //nazwa pliku/folderu
	std::string type; //typ pliku (domyslnie folder)
	Elem* next = NULL; //wskaznik do nastepnego podelementu 
	Elem* firstChild = NULL; //wskaznik do pierwszego podelementu
};
Elem* showPath(std::string pth);
//void printStructure(Elem* head, int level, int& numb);
void deleteTree(Elem*& elem);
bool CreateTree(Elem*& root);
#endif // !