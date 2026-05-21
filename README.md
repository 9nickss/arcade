# Arcade — Documentation des modules

## Collaboration

Ce projet a été réalisé en collaboration entre notre groupe les groupes **HumanCentipede** et **gucci gang** pour les interfaces du projet (compatibilité entre les .so de chacun, donc libs et jeux).

### Notre groupe
- Yannick — https://github.com/9nickss
- Ugo — https://github.com/Noctoa
- Raphaël — https://github.com/Rofe06

### HumanCentipede
- Gabriel — https://github.com/Rofe06
- Axel — https://github.com/AfyliX
- Florian — https://github.com/Creariax5

### gucci gang
- Hilal — https://github.com/Hilaltrhn
- Ana — https://github.com/ana-b-c
- Soha — https://github.com/AyoSoja

---

## 🧩 Interfaces communes

Les trois fichiers essentiels partagés entre modules sont :

- Le `IDisplayModule` [includes/IDisplayModule/IDisplayModule.hpp](includes/IDisplayModule/IDisplayModule.hpp) pour la comformité de nos bibliothéques graphiques.
- Le `IGameModule` [includes/IGameModule/IGameModule.hpp](includes/IGameModule/IGameModule.hpp) 
- Mais aussi le `Types`[includes/Arcade/Types.hpp](includes/Arcade/Types.hpp) pour la comformité cette fois liée sur d'autres détails nécéssaires afin que tout soit puisse être compatible jusqu'au couleurs, les touches ainsi que les sprites. 

Ils définissent le contrat commun entre le `Core`, les bibliothéques graphiques et les jeux.

---

## 🖥️ Modules graphiques

Chaque module implémente `IDisplayModule`.

### NCurses
- [includes/Graphics/NCurses/NCursesDisplayModule.hpp](includes/Graphics/NCurses/NCursesDisplayModule.hpp)
- [src/Graphics/NCurses/NCursesDisplay.cpp](src/Graphics/NCurses/NCursesDisplay.cpp)

### SDL2
- [includes/Graphics/SDL2/SDL2DisplayModule.hpp](includes/Graphics/SDL2/SDL2DisplayModule.hpp)
- [src/Graphics/SDL2/SDL2Display.cpp](src/Graphics/SDL2/SDL2Display.cpp)

### Qt5
- [includes/Graphics/Qt5/QT5DisplayModule.hpp](includes/Graphics/Qt5/QT5DisplayModule.hpp)
- [src/Graphics/Qt5/QT5Display.cpp](src/Graphics/Qt5/QT5Display.cpp)

Fonctions communes attendues :
- `init()`
- `clear()`
- `render()`
- `display()`
- `pollEvent()`
- `close()`

---

## 🎮 Modules de jeux

Chaque module implémente `IGameModule`.

### Pacman
- [includes/Games/Pacman/PacmanGame.hpp](includes/Games/Pacman/PacmanGame.hpp)
- [src/Games/Pacman/PacmanGame.cpp](src/Games/Pacman/PacmanGame.cpp)

### Space Invaders
- [includes/Games/SpaceInvaders/SpaceInvadersGame.hpp](includes/Games/SpaceInvaders/SpaceInvadersGame.hpp)
- [src/Games/SpaceInvaders/SpaceInvadersGame.cpp](src/Games/SpaceInvaders/SpaceInvadersGame.cpp)

Fonctions communes attendues :
- `init()` 
- `handleInput()`
- `update()`
- `getRenderData()`
- `getScore()`
- `isGameOver()`
- `reset()`
- `close()`

--- 

## ❓​ Pourquoi ce choix là ? 

Le choix de ces fonctions partagé peuvent paraitre minimaliste mais c'est ce qui en fait une force. 
Nous ne partageons seulement le strict minimum afin de laisser d'avantage de possibilté dans le choix des autres groupe.
Chaque fonctions supplementaire pourront etre ajouté dans le `update()`, `display()` ou `handleInput()` pour que chacun de nos groupes puisse avoir un code unique, avec des fonctionnalité différentes mais tout en restant compatible. 

---

## ✅ Compatibilité

La compatibilité entre les jeux et les modules graphiques repose sur :
- le type `RenderData`,
- les enums `Key` et `Color`,
- les interfaces `IDisplayModule` et `IGameModule`.

Ce design permet de changer de jeu ou de moteur graphique sans modifier le `Core`.