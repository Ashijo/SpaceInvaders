#include "Ecrans.h"
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "UIKit.h"
#include "Timer.h"
#include "Vaisseau.h"
#include "Martien.h"
#include "Laser.h"
#include "TesterCollision.h"
#include "Jeu.h"




void Ecran::ecranFinal() {

	system("cls");

	Jeux::initialisation();

	UIKit::gotoXY(37,7);
	cout << "##   ## ##### ####  ##### #####";
	UIKit::gotoXY(37, 8);
	cout << "# # # # #     #   # #       #  ";
	UIKit::gotoXY(37, 9);
	cout << "#  #  # #     #   # #       #  ";
	UIKit::gotoXY(37, 10);
	cout << "#     # ###   ####  #       #  ";
	UIKit::gotoXY(37, 11);
	cout << "#     # #     # ##  #       #  ";
	UIKit::gotoXY(37, 12);
	cout << "#     # #     #  #  #       #  ";
	UIKit::gotoXY(37, 13);
	cout << "#     # ##### #  ## ##### #####";

	UIKit::gotoXY(6, 99);
};




int Ecran::ecranDebut() {

	UIKit::setDimensionFenetre(1, 1, 170, 75);

	//Affiche un fichier .txt
	string getFileContents(ifstream&);
	ifstream Reader("alien.txt");
	string Art = getFileContents(Reader);
	int lvl = 0;
	bool screen = false;
	char touche;
	UIKit::color(10);
	cout << Art;
	Reader.close();

	//recupere la reponse du joueur
	while (!screen) {
		if (_kbhit()) {
			touche = _getch();

			switch (touche)
			{
			case '1':
				screen = true;
				lvl = 1; break;
			case '2':
				screen = true;
				lvl = 2; break;
			case '3':
				screen = true;
				lvl = 3; break;
			case '4':		
			case '#':
				screen = true;
				lvl = 4;break;
			}

			system("cls");

		}
	}


	return lvl;

};


//permet d'afficher
string getFileContents(ifstream& File)
{
	string Lines = "";

	if (File)
	{
		while (File.good())
		{
			string TempLine;
			getline(File, TempLine);
			TempLine += "\n";

			Lines += TempLine;
		}
		return Lines;
	}
	else
	{
		return "ERROR File does not exist.";
	}
}