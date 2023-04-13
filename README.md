# ArduinoProject
*Projet ARDUINO — ISENRUN*

Ce projet est un petit jeu en C++ pour Arduino Uno qui se joue sur un écran LCD.

## Bibliothèques

Ce projet utilise la bibliothèque LiquidCrystal pour l'affichage sur l'écran LCD.

## Fonctionnalités
Dans ce jeu, le joueur contrôle un petit personnage qui doit sauter par-dessus des obstacles. Le personnage peut sauter en appuyant sur le bouton de saut. Le jeu se termine lorsque le personnage touche un obstacle ou tombe en bas de l'écran.

Le jeu dispose d'un menu qui permet au joueur de démarrer une nouvelle partie ou de quitter le jeu. 
Il y a aussi un écran de fin de partie qui affiche le score du joueur et lui permet de revenir au menu principal ou de recommencer une partie.

Le jeu est contrôlé à l'aide des boutons de jeu suivants :

* Bouton de lecture : permet de démarrer le jeu ou de relancer une partie après une fin de partie.
* Bouton de saut : permet au personnage de sauter par-dessus les obstacles.

## Schéma de câblage
Le jeu nécessite un écran LCD, deux boutons poussoirs (pour le démarrage et le saut) et un potentiomètre pour ajuster le contraste de l'écran. Le schéma de câblage est le suivant :
 
**Pour Tinkercad :**
``` diff

# Ecran LCD :
- RS : broche 13
- E : broche 12
- D4 : broche 11
- D5 : broche 10
- D6 : broche 7
- D7 : broche 6
- VSS : GND
- VDD : 5V
- V0 : potentiomètre

# Bouton de lecture :
- Broche : 3
- Résistance : 10kOhm
- GND

# Bouton de saut :
- Broche : 2
- Résistance : 10kOhm
- GND
```
**Pour Carte Arduino ISEN** :

``` diff

# Ecran LCD :
- RS : broche 15
- E : broche 14
- D4 : broche 4
- D5 : broche 5
- D6 : broche 6
- D7 : broche 7
- VSS : GND
- VDD : 5V
- V0 : potentiomètre

# Bouton de lecture :
- Broche : 3
- Résistance : 10kOhm
- GND

# Bouton de saut :
- Broche : ?
- Résistance : ?
- GND

```

## Installation
Téléchargez ou clonez ce dépôt sur votre ordinateur.
Ouvrez le fichier "game.ino" avec l'IDE Arduino.
Branchez votre carte Arduino Uno à votre ordinateur à l'aide d'un câble USB.
Sélectionnez votre carte et votre port série dans l'IDE Arduino.
Chargez le programme sur votre carte en appuyant sur le bouton de téléversement.

## Auteur
Ce projet a été créé par *TOM LORIDANT*, *DAMIA CLAUS*, *ANATOLE NOWOCZYN* et UGO WAREMBOURG dans le cadre d'un projet scolaire ou personnel.
