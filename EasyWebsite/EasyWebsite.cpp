//C++17
#include <iostream>
#include <fstream>
#include <string>
#include "HTMLcreator.h"
#include "FilesStructure.h"
#include <filesystem>


int main()
{
	Elem* root = NULL;
	std::string command;
	std::string templ = "test";
	bool LIST_EXIST = false;
	std::cout << ": ";
	while (std::cin >> command) {
		if (command == "close") exit(0);
		else if (command == "clear") system("cls");
		else if (command == "help") {
			std::cout << "help - pomoc\nclear - wyczysc konsole\nwypisz - wypisz katalogi\nutworz - utworz liste katalogow\nusun - usun liste katalogow\nclose - zakoncz program";
		}
		else if (command == "utworz") {
			LIST_EXIST = CreateTree(root);
			std::cout << "Done!\a";
		}
		else if (command == "wypisz") {
			if (LIST_EXIST) {
				int numb = 0;
				if (root->firstChild)
					print(root->firstChild, 0, numb);
			}
			else
				std::cout << "Lista pusta";
		}
		/*else if (command == "szablon") {
			std::cin>> templ;
			std::cout << "Done!\n\a";
		}*/
		else if (command == "HTML" && root != NULL) {
			std::string folder;

			std::cout << "PODAJ NAZWE FOLDERU DO ZAPISU: ";
			//std::cin >> folder;
			std::getchar();  //pułapka na krasnoludki wciskające enter
			std::getline(std::cin, folder);
			createHTML(root, "temp.txt", folder);
			std::cout << "Done!\a";
		}
		else if (command == "usun" && LIST_EXIST) {
			deleteTree(root->firstChild);
			delete root;
			LIST_EXIST = false;
		}
		else std::cout << "Nieznana komenda";
		std::cout << "\n: ";
	}


	//string name = "art";
	//string mainFolder = "MySite";
	//string dataFolder = "Data";
	//string siteFolder = "aSite ";
	//string templateFolder ="Templates";
	///*cin >> dataFolder;
	//cin >> siteFolder;
	//cin >> templateFolder;*/

	//HTMLtemplate E:\Prywatne\PW\SEM II\ZAP\EasyWebsite\EasyWebsite\EasyWebsite\MySite\Templates\ArticleTemplate.html

	//E:\Prywatne\PW\SEM II\ZAP\EasyWebsite\EasyWebsite\EasyWebsite
	//createSite("MySite\\aSite\\art.html", "MySite\\Data\\art1.txt", "MySite\\Templates\\ArticleTemplate.html");
		/*createSite( mainFolder + '\\' + siteFolder + '\\' + name + a + ".html",
					mainFolder + '\\' + dataFolder + '\\' + name + a + ".txt",
					mainFolder + '\\' + templateFolder + '\\' + name + ".html");*/
}



