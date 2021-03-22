#ifndef HTMLcrator_H
#define HTMLcrator_H

#include<string>
#include<fstream>
#include "FilesStructure.h"

void createHTML(Elem* head, std::string htmlTemplate, std::string folder);
void addContent(Elem* head, std::ofstream& html, std::string htmlTemplate, std::string folder);
void findTextFile(Elem* head, std::string& p);

#endif // !

