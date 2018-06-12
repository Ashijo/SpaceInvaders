#pragma once
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <fstream>
#include <stdlib.h>

#include "UIKit.h"
#include "Timer.h"
#include "Vaisseau.h"
#include "Martien.h"
#include "Laser.h"
#include "TesterCollision.h"
#include "Jeu.h"
#include "Maringuin.h"
#include "Terminators.h"
#include "LaserTerminators.h"


#define MARTIENS 15
#define MAX_LASERS 50


int Jeux::jeux(int lvl) {

	initialisation();

	//Initialisation des variable pour le tableau des scores
	int score = 0;
	int tempsX = clock() / 1000;
	int tempsY = 0;
	bool finDeJeu = false;

	//	le vaisseau du joueur
	Vaisseau monVaisseau;


	//Les timers
	Timer timerVaisseau(100);
	Timer timerLaser(300);
	Timer timerMartiens(800 / lvl);
	Timer timerMarin(300 / lvl);
	Timer timerTermin(400 / lvl);
	Timer timerLaserTermin(900 / lvl);
	Timer timerScore(1000);

	timerScore.start();
	timerLaserTermin.start();
	timerTermin.start();
	timerMarin.start();
	timerLaser.start();
	timerMartiens.start();


	//	un laser (pas à l'écran au début)
	Laser mesLasers[MAX_LASERS];
	for (int i = 0; i < MAX_LASERS; i++)
		mesLasers[i].isAlive = false;

	//Laser ennemis
	LaserTerminators lasersEnemis[MAX_LASERS];
	for (int i = 0; i < MAX_LASERS; i++)
		lasersEnemis[i].isAlive = false;


	//les martien

	UIKit::color(12);
	int espMars = 0;
	Martien * lesMartiens[MARTIENS];
	for (int i = 0; i < MARTIENS; i++) {
		lesMartiens[i] = new Martien(65, 100);
		lesMartiens[i]->coord.setPositionX(20 + espMars);
		lesMartiens[i]->coord.setPositionY(5);
		espMars += 5;
	}


	//Les maringuins
	UIKit::color(13);
	int espMarin = 0;
	Maringuin * lesMarins[22];
	for (int i = 0; i < 22; i++) {
		lesMarins[i] = new Maringuin(86, 200);
		lesMarins[i]->coord.setPositionX(10 + espMarin);
		lesMarins[i]->coord.setPositionY(25);
		espMarin += 4;
	};

	// Les terminators
	UIKit::color(5);
	int espTerm = 0;
	Terminators * lesTermineurs[23];
	for (int i = 0; i < 23; i++) {
		lesTermineurs[i] = new Terminators(89, 300);
		lesTermineurs[i]->coord.setPositionX(10 + espTerm);
		lesTermineurs[i]->coord.setPositionY(15);
		espTerm += 4;
	};


	//	boucle principale de jeu
	while (!finDeJeu) {


		//appel de la fonction qui affiche le score et le timer
		if (tempsX != clock() / 1000) {
			tempsX = clock() / 1000;
			tempsY++;
			Jeux::timer(tempsY);
		}

		//Faire bouger les marsiens 
		if (timerMartiens.estPret()) {
			UIKit::color(12);
			for (int i = 0; i < MARTIENS; i++) {
				if (lesMartiens[i]->isAlive)
					lesMartiens[i]->jiggleMartien();
			
			}
		
		}

		//Faire bouger les maringuins
		if (timerMarin.estPret()) {
			UIKit::color(13);
			for (int i = 0; i < 22; i++) {
				if (lesMarins[i]->isAlive)
					lesMarins[i]->travelMaringuin();
			}
		
		}

		//Faire bouger les Terminators
		if (timerTermin.estPret()) {
			UIKit::color(5);
			for (int i = 0; i < 23; i++) {
				if (lesTermineurs[i]->isAlive)
					lesTermineurs[i]->jiggleTerminators();

			}
		}

		//	gestion du clavier
		if (_kbhit() && timerVaisseau.estPret()) {
			char touche = _getch();

			if (touche == ' ') {
				//	on recherche un laser libre
				UIKit::color(11);

				/*
				Pourquoi ca marche pas comme ca ><, ??

				for (int i = 0; i < MAX_LASERS; i++) {
					if (mesLasers[i].isAlive) {
						mesLasers[i+1].startLaser(monVaisseau.coord.getPositionX());
					}

				}*/


				int i = 0;
				while (i < MAX_LASERS && mesLasers[i].isAlive)
					i++;

				if (i < MAX_LASERS) {
					mesLasers[i].startLaser(monVaisseau.coord.getPositionX());}
			}

			else {
				UIKit::color(10);
				monVaisseau.modifierPosition(touche);
			}
		}

		//Laser des ennemis
		if (timerLaserTermin.estPret()) {
			
			for (int j = 0; j < 23; j++) {
				
					if (lesTermineurs[j]->isAlive && !lasersEnemis[j].isAlive)
					lasersEnemis[j].startLaserTer(lesTermineurs[j]->coord.getPositionX());
				
			}
		}



		//Si le vaisseau  sort du cadre, game over
		if (Col::testerCollisionColo(monVaisseau.coord.getPositionX())) finDeJeu = true;

		UIKit::color(11);
		//	on déplace le laser
		if (timerLaser.estPret()) {
			for (int i = 0; i < MAX_LASERS; i++) {
				if (mesLasers[i].isAlive)
					mesLasers[i].moveLaser();
				lasersEnemis[i].moveLaser();
			}
		}

		if (timerLaser.estPret()) {
			
		}

		

		UIKit::color(10);

		//Tuer les martiens
  		for (int i = 0; i < MARTIENS; i++) {
			for (int j = 0; j < MAX_LASERS; j++) {
				if (mesLasers[j].isAlive && lesMartiens[i]->isAlive && Col::testerCollision(lesMartiens[i]->coord.getPositionX(), lesMartiens[i]->coord.getPositionY(), mesLasers[j].coord.getPositionX(), mesLasers[j].coord.getPositionY())) {
					score += lesMartiens[i]->ajouterPoints();
					lesMartiens[i]->removeExtraTerrestre();
					mesLasers[j].killLaser();
					lesMartiens[i]->isAlive = false;
					lesMartiens[i]->reduireNombreExtraTerrestre();
					lesMartiens[i]->~Martien();

				};


			}
		}

		//Tuer les maringuins
		for (int i = 0; i < 22; i++) {
			for (int j = 0; j < MAX_LASERS; j++) {
				if (mesLasers[j].isAlive && lesMarins[i]->isAlive && Col::testerCollision(lesMarins[i]->coord.getPositionX(), lesMarins[i]->coord.getPositionY(), mesLasers[j].coord.getPositionX(), mesLasers[j].coord.getPositionY())) {
					score += lesMarins[i]->ajouterPoints();
					lesMarins[i]->removeExtraTerrestre();
					mesLasers[j].killLaser();
					lesMarins[i]->isAlive = false;
					lesMarins[i]->reduireNombreExtraTerrestre();
					lesMarins[i]->~Maringuin();

				};


			}
		}

		
		//Tuer les terminators
		for (int i = 0; i < 23; i++) {
			for (int j = 0; j < MAX_LASERS; j++) {
				if (mesLasers[j].isAlive && lesTermineurs[i]->isAlive && 
					Col::testerCollision(lesTermineurs[i]->coord.getPositionX(), lesTermineurs[i]->coord.getPositionY(), mesLasers[j].coord.getPositionX(), mesLasers[j].coord.getPositionY())) {
					score += lesTermineurs[i]->ajouterPoints();
					lesTermineurs[i]->removeExtraTerrestre();
					mesLasers[j].killLaser();
					lesTermineurs[i]->isAlive = false;
					lesTermineurs[i]->reduireNombreExtraTerrestre();
					lesTermineurs[i]->~Terminators();

				};


			}
		}

		//Tuer le joueur
		for (int i = 0; i < 23; i++) {
				if (lasersEnemis[i].isAlive &&
					Col::testerCollision(monVaisseau.coord.getPositionX(), 40, lasersEnemis[i].coord.getPositionX(), lasersEnemis[i].coord.getPositionY())) {
					finDeJeu = true;
				};
				
		}
		for (int i = 0; i < 22; i++) {
			if (lesMarins[i]->isAlive && lesMarins[i]->coord.getPositionY() == 40)
				finDeJeu = true;
		}
		


		//Detruction mutuel des lasers
		for (int i = 0; i < MAX_LASERS; i++) {
			for (int j = 0; j < 23; j++) {
				if (Col::testerCollision(mesLasers[i].coord.getPositionX(), mesLasers[i].coord.getPositionY(), lasersEnemis[j].coord.getPositionX(), lasersEnemis[j].coord.getPositionY())) {
					
					mesLasers[i].killLaser();
					lasersEnemis[j].killLaser();
				}
			}
		}

		//Empecher les laser de passer au travers du cadre 
		for (int i = 0; i < MAX_LASERS; i++) {
			if (Col::testerCollisionPlaf(mesLasers[i].coord.getPositionY())) {
				mesLasers[i].killLaser();

			};

		}


		if (timerScore.estPret()) {

			UIKit::color(rand() % 14);
			UIKit::gotoXY(115, 5);
			cout << "### ### ### ### ###";
			UIKit::gotoXY(115, 6);
			cout << "#   #   # # # # #  ";
			UIKit::gotoXY(115, 7);
			cout << "### #   # # ### ## ";
			UIKit::gotoXY(115, 8);
			cout << "  # #   # # ##  #  ";
			UIKit::gotoXY(115, 9);
			cout << "### ### ### # # ###";


			UIKit::gotoXY(115, 25);
			cout << "### ### # # ### ###";
			UIKit::gotoXY(115, 26);
			cout << " #   #  ### #   # #";
			UIKit::gotoXY(115, 27);
			cout << " #   #  # # ### ###";
			UIKit::gotoXY(115, 28);
			cout << " #   #  # # #   ## ";
			UIKit::gotoXY(115, 29);
			cout << " #  ### # # ### # #";


		}


		UIKit::gotoXY(125, 15);
		cout << score;



		//incrementation du niveau
		if (score >= 12800) {
			finDeJeu = true;
			lvl++;
			score = 0;

			for (int i = 6; i < 100; i++) {
				for (int j = 3; j < 45; j++) {
					UIKit::gotoXY(i, j);
					cout << " ";
				}
			}

			
			return lvl;
		}

	}//fin de la boucle principale du jeux


	return 4;
};



void Jeux::initialisation() {

	UIKit::setDimensionFenetre(1, 1, 150, 50);
	UIKit::curseurVisible(false);
	UIKit::cadre(5, 2, 100, 45, 10);
	UIKit::cadre(105, 2, 145, 45, 10);

};

void Jeux::timer(int timerScore) {

	int timerSec = timerScore % 60;
	int timerMin = timerScore / 60;

	if (timerSec < 10) {
		UIKit::gotoXY(124, 35);
		cout << timerMin << ":0" << timerSec;
	}

	else {
		UIKit::gotoXY(124, 35);
		cout << timerMin << ":" << timerSec;
	}

};