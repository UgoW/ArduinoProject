# ISEN Runner

## Fonctionnement global

Le code se base principalement sur la fonction **void loop()** qui gère l'affichage sur la carte.  

Nous différencions 3 étapes/écrans majeures distinguées par des conditions sur l'état de jeu actuel (*onMenu*, *onDeathScreen*) qui appellent les fonctions associées (*menuScreen()*, *deathScreen()*) :  
* **Menu :** affichage du nom du jeu (avec des petites animations des 2 côtés du titre) + affichage du personnage avec l'obstacle en mouvement (pour dynamiser le menu).
* **Ecran de mort :** (en 2 étapes principales)
  * Animation de mort : l'écran se remplit de 'X' afin de cacher le jeu et d'introduire la séquence suivante.
  * Affichage des scores : on affiche "Game Over" ainsi que le score réalisé par le joueur.
* **Ecran de jeu :** Permet de jouer en exécutant successivement des fonctions avec chacune un but précis.
  
## Le système de "calques"

Pour la partie de jeu, le code se base sur un système de calque. Dans notre cas, 3 calques se superposent sur l'écran LCD.
* Le premier calque, c'est l'affichage du personnage avec *drawCharacter()*.
* Le deuxième calque, c'est l'affichage du fond avec *drawBackground()*.
* Le troisième calque, c'est l'affichage du score avec *Score()*

Une fois superposée, ces 3 "calques" forment le jeu.


## Le score

Le score est basé sur une variable globale **score**. Il va être principalement traité lors de l'appel de la fonction **Score()** dans la boucle de jeu.  

A chaque appel de la fonction, on va incrémenter le score. Plus la vitesse/FPS (choisie par le joueur via le potentiomètre) est élevée, plus les scores augmentent vite :
* **1 point :** entre 3 et 5 FPS
* **2 points :** entre 6 et 8 FPS
* **3 points :** entre 9 et 11 FPS
* **4 points :** entre 12 et 13 FPS

En résumé, nous prenons les FPS et nous les divisons par 3, on arrondit par défaut et on a le score à incrémenter.  

La deuxième partie de la fonction permet d'afficher le score en haut à droite de l'écran. Afin que le score reste "collé" au bord droit, nous avons implémenté un système de palier (entre 0 et 9, on écrit à la case 15 - entre 10 et 99, on écrit à la case 14 - etc.).  

Pour la partie plus technique pour savoir quand incrémenter le score, nous avons une variable **bool wasOnObs** qui regarde si nous sommes sur un obstacle. Si nous ne sommes plus sur un obstacle (mais que nous y étions vérifiable avec la variable), on incrémente le score.


## Mouvement du personnage

Pour le mouvement du personnage, nous utilisons la fonction **drawCharacter()**.  

Cette fonction se base principalement sur la structure **character** composé de trois attributs :
* **int jumpStateNum** - permet de connaitre l'avancement dans le saut (0 = au sol | 4 = tout en haut)
* **char state** - donne l'etat/l'action en cours du personnage (n = neutral, marche classique / u = up, en train de monter / d = down, en train de descendre)
* **int walkStateNum** - permet de changer son image de marche (1 ou 0)

**Au sol**

> Le personnage alterne juste l'etat de marche entre 0 et 1

**Sur un obstacle**

> Le personnage alterne entre les 2 etats de marche avec la subtilité que des qu'il n'est plus sur l'obstacle, il descend

**En montée / en descente**

> Si le personnage monte, on incrémente son état de saut et l'une des conditions s'exécutera en fonction de cet état et affichera le personnage (et changera l'etat du personnage dans certains cas).  
> Si le personnage descend, même principe mais on décrémente l'etat de saut


## Le saut

Pour le saut, nous utilisons un **attachInterrupt()** (déclaré dans le setup).  

Cet attachInterrupt est relié à la fonction saut qui a pour seul but de changer l'état du personnage en le passant en mode montée (`state = 'u'`) pour que la fonction drawCharacter() exécute les actions en conséquence.  

A noter que nous utilisons le attachInterrupt() pour passer outre des délais imposés par les FPS afin que nous puissions sauter n'importe quand.


## Le fond (background)

Pour afficher et gérer le déplacement des blocs, nous utilisons principalement la fonction **drawBackground()** et **landscape()**.  

Chaque bloc est basé sur la structure `obstacle` composé de 2 attributs :
* **int leftPos** - correspond à l'emplacement de la carte LCD ou le caractère le plus à gauche du bloc doit s'afficher.
* **int obsSize** - correspond à la taille du bloc. Le minimum est de 2 (3 caractères affichés) à 6 (7 caractères affichés).

A chaque frame, le bloc va se déplacer d'une case vers la gauche. Si cette position devient négative, une partie du bloc commencera à être cachée.  
Si tout le bloc est caché, on le remet à la fin en mettant son indice `leftPos` à 20 afin qu'il ne soit pas directement visible. On détermine ensuite aléatoirement la taille du bloc entre 2 et 6 et enfin on l'affiche (si `leftPos < 16`).

A noter que pour faire un bloc à taille variable, nous utilisons une boucle affichant le bon nombre de caractères.


## La vitesse de jeu

La vitesse de jeu se base sur la variable **FPS** (Frame Per Second) qui impacte directement le delay de la boucle de jeu.

Cette variable **FPS** est recalculé à chaque image basée sur la valeur retournée par le potentiomètre (entre 0 et 1023). Le minimum est 3 et le maximum est 13. Le calcul estle suivant : `FPS = 3 + (valPot / 1023 * 10)`.


## La mort

Pour regarder si le joueur est mort, c'est plutôt simple. On regarde si l'obstacle est sur la position du joueur et qu'il n'est pas sur l'obstacle (en train de marcher).


## Autres

Le reste ne sont que des détails ou des choses plutôt basiques déjà commentés suffisament dans le code.

Par exemple, la fonction **start()** basé sur un attachInterrupt permet de lancer le jeu en initialisant les variables à la bonne valeur