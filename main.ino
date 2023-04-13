#include <LiquidCrystal.h> //Inclure la bibliothèque LiquidCrystal

byte leftBlock[8] = {
  B00001,
  B00001,
  B00011,
  B01111,
  B11111,
  B01111,
  B00011,
  B00001
};

byte midBlock[8] = {
  B11101,
  B11111,
  B11111,
  B10101,
  B11111,
  B10001,
  B10101,
  B11111
};

byte rightBlock[8] = {
  B10000,
  B10000,
  B11000,
  B11000,
  B11000,
  B11100,
  B11100,
  B11100
};

byte upHead[8] = {
  B01100,
  B01100,
  B00000,
  B11110,
  B01101,
  B11111,
  B10000,
  B00000
};

byte upNoHead[8] = {
  B11110,
  B01101,
  B11111,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte headOnly[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B01100,
  B01100,
  B00000
};

byte walk1[8] = {
  B01100,
  B01100,
  B00000,
  B01110,
  B11100,
  B01100,
  B11010,
  B10011
};

byte walk2[8] = {
  B01100,
  B01100,
  B00000,
  B01100,
  B01100,
  B01100,
  B01100,
  B01110
};

// Constantes pour les broches, la vitesse de jeu et les décoration du menu
#define PLAY_BUTTON 3
#define JUMP_BUTTON 2
#define POT A3
int FPS = 5;
char charTitle[] = "-|OX"; // Caractère s'affichant à cote du titre
int numCharTitle = 0; // Nombre choisissant le caractere a cote du titre

// Créer un objet LiquidCrystal avec les broches 13, 12, 11, 10, 7 et 6 pour l'écran LCD
LiquidCrystal lcd(13, 12, 11, 10, 7, 6);

// Structures de données pour le personnage et l'obstacle
struct character {

  int jumpStateNum = 0;
  char state = 'n';
  int walkStateNum = 0;

} character;

struct obstacle {

  int leftPos = 16;
  int obsSize = 3;

} obstacle;

// Variables globales pour l'état du jeu
bool onMenu = true;
bool onDeathScreen = false;
int score;
bool wasOnObs = false;
bool justBegin = false;

// Fonction pour vérifier si le personnage est sur un obstacle
bool onObstacle() {

  if(character.jumpStateNum == 4 && obstacle.leftPos <= 2 && obstacle.leftPos + obstacle.obsSize > 1){

    wasOnObs = true;
    return true;

  }
  return false;

}

// Affiche le personnage sur l'écran LCD
void drawCharacter() {

  // Si le personnage n'est pas à l'état normal (en train de sauter ou de tomber) et n'est pas sur un obstacle
  if('n' != character.state && onObstacle() == false) {

    // Incrémente ou décrémente l'état de saut du personnage en fonction de la direction du saut
    'u' == character.state ? character.jumpStateNum++ : character.jumpStateNum--;

    // Si le personnage est à l'état normal
    if(character.jumpStateNum == 0) {

      lcd.setCursor(1, 1);
      lcd.write(byte(5));
      character.state = 'n';

    }
    
    // Si le personnage est à l'état de saut numéro 1
    else if(character.jumpStateNum == 1) {

      lcd.setCursor(1, 1);
      lcd.write(byte(5));

    }
    
    // Si le personnage est à l'état de saut numéro 2
    else if(character.jumpStateNum == 2) {

      lcd.setCursor(1, 0);
      lcd.write(byte(7));
      lcd.setCursor(1, 1);
      lcd.write(byte(6));

    }

    // Si le personnage est à l'état de saut numéro 3
    else if(character.jumpStateNum == 3) {

      lcd.setCursor(1, 0);
      lcd.write(byte(0));

    }

    // Si le personnage est à l'état de saut numéro 4
    else if(character.jumpStateNum == 4) {

      lcd.setCursor(1, 0);
      lcd.write(byte(5));
      character.state = 'd';

    }
  }

  // Si le personnage est à l'état normal et n'est pas sur un obstacle
  else {

    // Change l'état de marche du personnage à chaque appel de la fonction
    character.walkStateNum = (character.walkStateNum + 1) % 2;
    lcd.setCursor(1, 1 - (int)(character.jumpStateNum / 4));
    lcd.write(byte(character.walkStateNum));
    
  }  
}

// Fonction pour faire sauter le personnage
void jump() {

  // Si le personnage n'est pas déjà en train de sauter
  if(character.jumpStateNum == 0)

    character.state = 'u'; // Mettre l'état du personnage à "saut"

}

// Fonction pour afficher les obstacles
void landscape(){

  // Si la position de l'obstacle de gauche est supérieure ou égale à 0
  if(obstacle.leftPos >= 0) {

    lcd.setCursor(obstacle.leftPos, 1); // Placer le curseur de l'écran LCD sur la position de l'obstacle de gauche
    lcd.write(byte(2)); // Afficher le caractère byte(2) qui correspond à l'obstacle de gauche

  }
  
  // Pour chaque obstacle entre l'obstacle de gauche et l'obstacle de droite
  for(int i = 1; i < obstacle.obsSize; i ++) {

    // Si la position de l'obstacle actuel est supérieure ou égale à 0
    if(obstacle.leftPos + i >= 0) {

      lcd.setCursor(obstacle.leftPos + i, 1); // Placer le curseur de l'écran LCD sur la position de l'obstacle actuel
      lcd.write(byte(3)); // Afficher le caractère byte(3) qui correspond à l'obstacle du milieu

    }

  }
  
  // Si la position de l'obstacle de droite est supérieure ou égale à 0
  if(obstacle.leftPos + obstacle.obsSize >= 0) {

    lcd.setCursor(obstacle.leftPos + obstacle.obsSize, 1); // Placer le curseur de l'écran LCD sur la position de l'obstacle de droite
    lcd.write(byte(4)); // Afficher le caractère byte(4) qui correspond à l'obstacle de droite

  }

}

// Fonction pour créer une taille aléatoire
int randomSize() {

  randomSeed(analogRead(0)); // Generation d'une nouvelle seed aléatoire à chaque fois
  return random(2, 6); // Renvoie un nombre aléatoire entre 2 et 6

}

// Fonction pour vérifier si le personnage est mort
void checkDeath() {  

  // Si l'obstacle de gauche est sur la même colonne que le personnage et que le personnage n'est pas sur un obstacle
  if(obstacle.leftPos == 1 && !onObstacle()) {

    Serial.println("You're dead"); // Afficher "You're dead" dans la console série
    onDeathScreen = true; // Passer en mode "écran de mort"
    lcd.clear(); // Effacer l'écran LCD
    numCharTitle = 0; // Remet à l'etat 0 les caractères autour du titre
  }

}

// Fonction pour afficher l'arrière-plan
void drawBackground() {

  // Déplacer l'obstacle de gauche d'une colonne vers la gauche
  obstacle.leftPos--;
  // Si l'obstacle de gauche sort de l'écran
  if(obstacle.leftPos < -obstacle.obsSize) {
	obstacle.obsSize = randomSize();
    obstacle.leftPos = 20;
  }
  
  landscape(); // Afficher les obstacles à l'écran

}

// Fonction pour calculer le score
void Score() {

  if(onObstacle()) { // Vérifie si le personnage est sur un obstacle

    wasOnObs = true; // Met la variable wasOnObs à true

  }
  
  else {

    if (wasOnObs == true){ // Si le personnage n'est plus sur un obstacle

      score += (int)(FPS / 3); // Ajoute le score (vitesse / 3) à la variable score
      Serial.println(score); // Affiche le score sur la console série
      wasOnObs = false; // Met la variable wasOnObs à false

    }

  }
  
  // Affiche le score à l'écran LCD , décalage selon le score 
  if(score < 10)
    lcd.setCursor(15, 0);
  else if(score < 100)
    lcd.setCursor(14, 0);
  else
    lcd.setCursor(13, 0);
  
  lcd.print(score);

}

// Fonction pour changer la vitesse de jeu en fonction de la valeur du potentiomètre
void changeSpeed() {

  // La vitesse varie entre 3 et 13
  Serial.println(FPS);
  FPS = 3 + (int)((float)analogRead(POT) / 1023.0 * 10.0) ;

}

// Fonction pour démarrer le jeu
void start() {
  
  if(!onMenu)
    return;

  // Initialise les variables pour commencer une nouvelle partie
  onMenu = false;
  obstacle.leftPos = 16;
  character.jumpStateNum = 0;
  character.state = 'n';
  score = 0;
  justBegin = true;
  lcd.clear();
}

// Cette fonction affiche un écran de menu sur l'écran LCD
void menuScreen() {
  lcd.clear(); // Efface l'écran LCD
  
  // Affiche des symboles personnalisés sur la deuxième ligne de l'écran LCD
  lcd.setCursor(-1 + numCharTitle % 23, 1);
  lcd.write(byte(numCharTitle % 2)); 

  lcd.setCursor(-7 + numCharTitle % 23, 1);
  lcd.write(byte(2)); 
  
  lcd.setCursor(-6 + numCharTitle % 23, 1);
  lcd.write(byte(3)); 
  
  lcd.setCursor(-5 + numCharTitle % 23, 1);
  lcd.write(byte(4)); 
  
  numCharTitle++; // Incrémente la variable numCharTitle

  // Affiche le titre du jeu avec des symboles personnalisés
  lcd.setCursor(0,0);
  lcd.print(charTitle[numCharTitle % 4]);
  lcd.print(" - ISEN RUN - ");
  lcd.print(charTitle[numCharTitle % 4]);

  delay(300); // Attend 300 millisecondes
}

// Cette fonction affiche un écran de fin de partie sur l'écran LCD
void deathScreen() {
  // Fait clignoter des "X" rouges sur l'écran LCD pendant 8 itérations
  for(int i = 0; i < 8; i++) {
      lcd.setCursor(i, 0);
      lcd.print("X");

      lcd.setCursor(i, 1);
      lcd.print("X");

      lcd.setCursor(15 - i, 0);
      lcd.print("X");

      lcd.setCursor(15 - i, 1);
      lcd.print("X");

      delay(150); // Attend 150 millisecondes
    }

    delay(1000); // Attend 1 seconde
    lcd.clear(); // Efface l'écran LCD
   
    // Affiche "GAME OVER" et le score obtenu sur l'écran LCD
    lcd.setCursor(0,0);
    lcd.print("X  GAME  OVER  X");
    lcd.setCursor(0,1); 
    lcd.print("X  SCORE : ");
    lcd.print(score);
    lcd.setCursor(15 ,1); 
    lcd.print("X");

    delay(4000); // Attend 4 secondes
    
    // Réinitialise les variables de jeu et affiche l'écran de menu
    onMenu = true;
    onDeathScreen = false;
    lcd.clear();
}

void gameBeginScreen() {
	lcd.clear();

	lcd.setCursor(0,0);
	lcd.print("X   START IN   X");
	lcd.setCursor(0,1);
	lcd.print("X              X");

	lcd.setCursor(7,1);
	lcd.print("03");

	delay(1000);

	lcd.setCursor(7,1);
	lcd.print("02");

	delay(1000);

	lcd.setCursor(7,1);
	lcd.print("01");

	delay(1000);

	justBegin = false;
}


// Fonction d'initialisation du jeu
void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  // Crée les personnages personnalisés à afficher sur l'écran LCD
  lcd.createChar(byte(0), walk1); // Marche phase 1
  lcd.createChar(byte(1), walk2); // Marche phase 2

  lcd.createChar(byte(2), leftBlock); // Bloc gauche
  lcd.createChar(byte(3), midBlock);  // Bloc milieu
  lcd.createChar(byte(4), rightBlock);// Bloc droite
  
  lcd.createChar(byte(5), upHead); // Saut : Tete + corps
  lcd.createChar(byte(6), upNoHead); // Saut : Corps
  lcd.createChar(byte(7), headOnly); // Saut : Tete

  // Configuration des pins pour les boutons de saut et de démarrage du jeu
  pinMode(JUMP_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(JUMP_BUTTON), jump, FALLING);

  pinMode(PLAY_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PLAY_BUTTON), start, FALLING);

}

//fonction loop() 
void loop() {

  // Si on est sur le menu, affiche le titre sur l'écran LCD
  if(onMenu)
    menuScreen();
  
  // Sinon, si on est sur l'écran de mort, exécute le code de l'écran de mort et réinitialise les variables correspondantes
  else if(onDeathScreen)
    deathScreen();

  // Sinon, on est dans le jeu, on efface l'écran LCD, on dessine le personnage, le fond, on affiche le score, on vérifie si le personnage est mort et on change la vitesse
  else {
    
    // Si le jeu vient de commencer, affiche un compte à rebours
    if(justBegin) 
			gameBeginScreen();

    // Efface l'écran LCD et dessine le personnage et le fond
    lcd.clear();
		
    drawCharacter();
    drawBackground();
    
    // Affiche le score deux fois
    Score();
    
    // Change la vitesse de défilement du fond
    changeSpeed();
    
    // Vérifie si le personnage est mort
    checkDeath();
    
    // Limite le taux de rafraîchissement de l'écran à FPS images par seconde
    delay((int)(1000 / FPS)); 

  }
  
}

