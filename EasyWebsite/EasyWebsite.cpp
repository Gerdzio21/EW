//C++17
#include <iostream>
#include <fstream>
#include <string>
#include "HTMLcreator.h"
#include "FilesStructure.h"
#include "ControlPanel.h"
#include <filesystem>


int main()
{
	Elem* root = NULL;
	greeting();
	panel(root);
	


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



