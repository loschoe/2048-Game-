# 🎮 Jeu 2048 en C (Console)
Une version moderne, colorée et optimisée du célèbre jeu **2048**, entièrement développée en *langage C* pour le terminal Windows. Ce projet a été réalisé dans le cadre de l'enseignement des langages compilés à **STRASBOURG YNOV CAMPUS**


## 🚀 Fonctionnalités Principales & Bonus

* **Difficulté et Taille de Grille Variables :** Plus besoin de se limiter au 4x4 ! Un menu dédié vous permet de choisir entre 3 modes :
    * **Standard (4x4)** : L'expérience classique.
    * **Medium (5x5)** : Pour des parties plus stratégiques.
    * **Hard (8x8)** : Pour les joueurs en quête de défi.

* **Interface Dynamique et Colorée :** Utilisation intensive des codes ANSI pour colorer individuellement chaque tuile en fonction de sa valeur. <br>L'affichage s'adapte dynamiquement et offre un rendu visuel moderne et flatteur, calqué sur les tons bleus du titre ASCII.
* **Système de Score en Temps Réel :** Le score s'incrémente automatiquement à chaque fusion de tuiles et reste visible en tête de grille.
* **Contrôle Fluide au Clavier :** Déplacements instantanés à l'aide des flèches directionnelles du clavier (sans avoir besoin d'appuyer sur Entrée à chaque coup) et possibilité de quitter la partie en cours à tout moment avec la touche `ÉCHAP`.
* **Boucle de Jeu Infinie (Rejouabilité) :** Une fois la partie terminée (Victoire ou Game Over), le jeu affiche un écran de fin stylisé avec votre score final, puis vous permet de retourner proprement au menu principal pour relancer une partie sans fermer l'application.

---

## 📁 Arborescence du Projet

Le code a été découpé de manière chirurgicale afin de séparer la configuration, l'affichage et la logique pure du jeu. Tous les fichiers sont situés dans le même répertoire :

```text
📂 2048-C/
├── 📄 game.h         # Définition de la structure du jeu, constantes et inclusions globales.
├── 📄 affichage.h    # Prototypes des fonctions visuelles et des menus.
├── 📄 affichage.c    # Code source de l'interface, des couleurs ANSI et de la grille.
├── 📄 moteur.h       # Prototypes de la logique de jeu et des entrées clavier.
├── 📄 moteur.c       # Code source des mouvements, fusions, allocations et vérifications.
├── 📄 main.c         # Point d'entrée du programme et gestion de la boucle principale.
└── 📄 README.md      # Documentation du projet (ce fichier).
```

--- 
## 🛠️ Gestion des Erreurs et Robustesse
Une attention toute particulière a été portée à la stabilité du programme afin d'éliminer les "erreurs de débutant" classiques en langage C :

- **Sécurisation des Saisies** (`scanf`) : Les menus sont protégés contre les entrées invalides (lettres tapées à la place de chiffres). Si une saisie est incorrecte, le programme ne boucle pas à l'infini : il nettoie le tampon d'entrée (stdin) via une fonction dédiée, applique un choix par défaut sécurisé et avertit l'utilisateur.

- **Zéro Fuite de Mémoire** (`Memory Leaks`) : La grille étant allouée dynamiquement en fonction de la difficulté choisie, chaque retour au menu ou fin de partie libère proprement la mémoire (free). Les pointeurs sont réinitialisés à NULL pour éviter les comportements indéfinis lors d'allocations successives. 

- **Optimisation CPU** : Contrairement aux versions naïves qui allouent et libèrent de la mémoire à chaque appui de touche pour mémoriser l'état précédent de la grille (détection des mouvements), cette version utilise une matrice locale statique optimisée, réduisant la fragmentation de la mémoire et la charge processeur.

**Contrôle anti-missclick en fin de partie** : Lors d'un Game Over ou d'une Victoire, le jeu requiert obligatoirement une pression sur la touche ENTRÉE pour valider. Cela empêche l'utilisateur de quitter accidentellement son écran de fin s'il était en train de presser frénétiquement les flèches directionnelles.

## 💻 Compilation et Exécution
Le projet est configuré pour être compilé facilement avec le compilateur GCC sous un environnement Windows (MinGW / PowerShell / CMD).

### Compilation
Ouvrez votre terminal dans le dossier du projet et exécutez la commande suivante pour lier tous les modules :

```Bash
gcc main.c affichage.c moteur.c -o jeu2048.exe
```

### Exécution
Lancez ensuite le jeu avec la commande :

```Bash
./jeu2048.exe
```

**Note** : Le programme intègre l'encodage `CP_UTF8` au démarrage pour garantir le bon affichage des caractères graphiques du tableau et du titre sur les terminaux Windows récents.

## 🤖 Note sur l'utilisation des IA (Copilot & Gemini)
Ce projet a été réalisé en collaboration avec des outils d'Intelligence Artificielle, notamment Copilot et Gemini.

L'usage de l'IA dans ce cadre n'a pas été un substitut de réflexion ni un simple générateur de code "copier-coller". 
<br>Au contraire, elle a été adoptée comme un mentor technologique et un outil d'apprentissage pair-à-pair. Cette synergie a permis de :

- Comprendre en profondeur l'intérêt du découpage modulaire (fichiers .h / .c).
- Identifier et corriger des vulnérabilités de code (comme les dangers de fflush(stdin) ou les fuites de mémoire cachées).
- Découvrir de bonnes pratiques professionnelles (gestion propre du flux stdout, optimisation des structures de données).

L'IA a agi comme un accélérateur de compétences, transformant un projet console classique en une application logicielle robuste, propre et structurée selon les standards de l'industrie.

Inspirations : https://labex.io/fr/tutorials/c-creating-a-2048-game-in-c-298825

## 📷 Aperçu
### Menu principal
<img width="668" height="360" alt="image" src="https://github.com/user-attachments/assets/bdbd7e7d-8568-4956-9bb5-b5df836a016f" />

### Partie en cours
<img width="667" height="546" alt="image" src="https://github.com/user-attachments/assets/52af5336-2813-4d56-b016-c3adb508f8a5" />

