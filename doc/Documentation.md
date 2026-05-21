## [src/main.cpp](../src/main.cpp)

- `main(int argc, char **argv)` : point d’entrée du programme. Vérifie les arguments, crée l’instance de `Core` avec la bibliothèque graphique initiale, lance la boucle principale et gère les erreurs fatales.

---

## [src/Arcade/DLLoader.cpp](../src/Arcade/DLLoader.cpp)

- `DLLoader::DLLoader(const std::string &path, bool keepResident)` : ouvre immédiatement une bibliothèque partagée.
- `DLLoader::~DLLoader()` : ferme automatiquement la bibliothèque chargée.
- `DLLoader::DLLoader(DLLoader &&other) noexcept` : déplace l’état d’un chargeur vers un autre.
- `DLLoader::operator=(DLLoader &&other) noexcept` : remplace l’état courant par celui d’un autre chargeur déplacé.
- `DLLoader::open(const std::string &path, bool keepResident)` : charge une bibliothèque avec `dlopen`.
- `DLLoader::close() noexcept` : libère la bibliothèque si elle est chargée.
- `DLLoader::scanLibraries(const std::string &directory)` : parcourt un dossier et conserve les fichiers se terminant par `.so`.
- `DLLoader::isOpen() const noexcept` : indique si une bibliothèque est actuellement ouverte.
- `DLLoader::getPath() const noexcept` : retourne le chemin de la bibliothèque ouverte.
- `DLLoader::getLibraries() const noexcept` : retourne la liste des bibliothèques scannées.
- `DLLoader::selectLibrary(std::size_t index) const` : retourne la bibliothèque correspondant à un index.
- `DLLoader::getSymbolRaw(const std::string &symbolName) const` : récupère un symbole brut avec `dlsym`.

---

## [src/Core/Core.cpp](../src/Core/Core.cpp)

### Fonction locale

- `capFrameRate(const std::chrono::steady_clock::time_point &frameStart)` : limite la vitesse de la boucle principale à un nombre de FPS cible.

### Méthodes de `Core`

- `Core::Core(const std::string &initialLib)` : initialise le moteur, charge la première bibliothèque graphique et prépare les listes de jeux et graphiques.
- `Core::~Core()` : détruit les modules chargés.
- `Core::scanLibs()` : scanne `./lib` et trie les bibliothèques selon leur type graphique ou jeu.
- `Core::loadDisplay(const std::string &path)` : remplace le module graphique courant par une nouvelle bibliothèque.
- `Core::loadGame(const std::string &path)` : remplace le jeu courant par une nouvelle bibliothèque.
- `Core::run()` : initialise l’affichage, lance le menu puis ferme l’affichage à la sortie.
- `Core::loadMenu()` : charge le module menu et lui fournit les jeux, les graphismes et les scores.
- `Core::runMenu()` : exécute la boucle du menu principal.
- `Core::runGame()` : exécute la boucle de jeu.
- `Core::saveScores()` : ajoute le score courant dans `scores.txt`.
- `Core::loadScores()` : lit `scores.txt`, trie les meilleurs scores et conserve les 10 premiers.

---

## [src/Menu/MenuModule.cpp](../src/Menu/MenuModule.cpp)

- `MenuModule::init()` : remet le menu dans son état initial.
- `MenuModule::reset()` : efface la sélection courante de jeu et de bibliothèque graphique.
- `MenuModule::close()` : ferme le module menu.
- `MenuModule::getName() const` : retourne le nom du module.
- `MenuModule::handleInput(Key key)` : traite les touches de navigation, la saisie du nom, le choix du jeu, le choix du moteur graphique et la sortie.
- `MenuModule::update()` : met à jour le menu, sans logique supplémentaire pour l’instant.
- `MenuModule::getRenderData()` : construit la vue texte du menu avec la liste des jeux, graphismes, scores et aides clavier.
- `MenuModule::getScore() const` : retourne toujours 0, car le menu ne possède pas de score.
- `MenuModule::isGameOver() const` : indique si le menu doit se fermer.
- `MenuModule::getSelectedGame() const` : retourne le jeu sélectionné.
- `MenuModule::getSelectedLib() const` : retourne la bibliothèque graphique sélectionnée.
- `MenuModule::getPlayerName() const` : retourne le nom saisi par le joueur.
- `MenuModule::setGameLibs(const std::vector<std::string> &libs)` : enregistre les bibliothèques de jeux disponibles.
- `MenuModule::setGraphicLibs(const std::vector<std::string> &libs)` : enregistre les bibliothèques graphiques disponibles.
- `MenuModule::setScores(const std::vector<ScoreEntry> &scores)` : enregistre les scores à afficher.
- `createMenu()` : fabrique et retourne une instance du module menu pour le chargement dynamique.

---

## [src/Graphics/NCurses/NCursesDisplay.cpp](../src/Graphics/NCurses/NCursesDisplay.cpp)

- `NCursesDisplayModule::NCursesDisplayModule()` : crée un module ncurses non initialisé.
- `NCursesDisplayModule::~NCursesDisplayModule()` : ferme proprement ncurses à la destruction.
- `NCursesDisplayModule::init()` : initialise la fenêtre ncurses et configure le terminal.
- `NCursesDisplayModule::close()` : ferme ncurses si le module est actif.
- `NCursesDisplayModule::getName() const` : retourne le nom du module graphique.
- `NCursesDisplayModule::clear()` : efface l’écran courant.
- `NCursesDisplayModule::render(const RenderData &data)` : dessine la grille et les textes dans le terminal.
- `NCursesDisplayModule::display()` : rafraîchit l’affichage ncurses.
- `NCursesDisplayModule::pollEvent()` : lit une touche clavier et la convertit en `Key` Arcade.
- `NCursesDisplayModule::ensureInitialized() const` : vérifie que ncurses est bien initialisé avant toute action.
- `entryPointDisplay()` : point d’entrée dynamique retournant un affichage ncurses.
- `destroyDisplay(Arcade::IDisplayModule *display)` : détruit un module graphique créé dynamiquement.

---

## [src/Graphics/SDL2/SDL2Display.cpp](../src/Graphics/SDL2/SDL2Display.cpp)

- `SDL2DisplayModule::SDL2DisplayModule()` : crée un module SDL2 non initialisé.
- `SDL2DisplayModule::~SDL2DisplayModule()` : libère automatiquement les ressources SDL2.
- `SDL2DisplayModule::init()` : initialise SDL2, TTF, la fenêtre, le renderer et la police.
- `SDL2DisplayModule::close()` : détruit la fenêtre, le renderer, la police et les caches.
- `SDL2DisplayModule::loadTexture(const std::string &path)` : charge et met en cache une texture image.
- `SDL2DisplayModule::getName() const` : retourne le nom du module graphique.
- `SDL2DisplayModule::toSDLColor(Color color) const` : convertit une couleur Arcade en `SDL_Color`.
- `SDL2DisplayModule::clear()` : efface le rendu SDL2.
- `SDL2DisplayModule::render(const RenderData &data)` : dessine la grille et les textes à l’aide de SDL2 et TTF.
- `SDL2DisplayModule::display()` : présente le rendu à l’écran.
- `SDL2DisplayModule::pollEvent()` : lit les événements SDL et les convertit en `Key` Arcade.
- `entryPointDisplay()` : point d’entrée dynamique retournant un affichage SDL2.
- `destroyDisplay(Arcade::IDisplayModule *display)` : détruit un module graphique créé dynamiquement.

---

## [src/Graphics/Qt5/QT5Display.cpp](../src/Graphics/Qt5/QT5Display.cpp)

- `QT5DisplayModule::QT5DisplayModule()` : crée un module Qt5 non initialisé.
- `QT5DisplayModule::~QT5DisplayModule()` : libère les ressources du module.
- `QT5DisplayModule::init()` : crée ou réutilise l’application Qt, crée la fenêtre principale et affiche la vue.
- `QT5DisplayModule::close()` : masque la fenêtre et marque le module comme fermé.
- `QT5DisplayModule::display()` : traite les événements Qt.
- `QT5DisplayModule::clear()` : ne fait rien, le dessin est géré par Qt au rendu.
- `QT5DisplayModule::render(const RenderData &data)` : transmet les données de rendu à la vue Qt.
- `QT5DisplayModule::pollEvent()` : traite les événements et retourne une touche Arcade ou `QUIT` si la fenêtre est fermée.
- `QT5DisplayModule::getName() const` : retourne le nom du module graphique.
- `entryPointDisplay()` : point d’entrée dynamique retournant un affichage Qt5.
- `destroyDisplay(Arcade::IDisplayModule *display)` : détruit un module graphique créé dynamiquement.

---

## [src/Graphics/Qt5/QT5ArcadeView.cpp](../src/Graphics/Qt5/QT5ArcadeView.cpp)

- `QT5ArcadeView::QT5ArcadeView(QWidget *parent)` : construit la vue Qt et configure le focus clavier.
- `QT5ArcadeView::setRenderData(const RenderData &data)` : stocke les données de rendu et demande un repaint.
- `QT5ArcadeView::popKey()` : renvoie la prochaine touche en attente dans la file interne.
- `QT5ArcadeView::paintEvent(QPaintEvent *event)` : dessine la grille, les sprites et les textes.
- `QT5ArcadeView::keyPressEvent(QKeyEvent *event)` : convertit les touches Qt en touches Arcade.
- `QT5ArcadeView::closeEvent(QCloseEvent *event)` : ajoute `QUIT` lorsque la fenêtre est fermée.

---

## [src/Games/Pacman/PacmanGame.cpp](../src/Games/Pacman/PacmanGame.cpp)

- `PacmanGame::PacmanGame()` : construit une partie et lance un reset initial.
- `PacmanGame::init()` : initialise la partie en appelant `reset()`.
- `PacmanGame::reset()` : remet le score, les timers, Pacman et les fantômes à zéro.
- `PacmanGame::close()` : ferme le module jeu.
- `PacmanGame::getName() const` : retourne le nom du jeu.
- `PacmanGame::handleInput(Key key)` : met à jour la direction de Pacman et gère le restart.
- `PacmanGame::update()` : exécute la logique principale du tour de jeu.
- `PacmanGame::getRenderData()` : reconstruit et retourne les données de rendu du jeu.
- `PacmanGame::getScore() const` : retourne le score courant.
- `PacmanGame::isGameOver() const` : indique si la partie est terminée.
- `entryPointGame()` : point d’entrée dynamique retournant une instance de Pacman.

---

## [src/Games/Pacman/PacmanMap.cpp](../src/Games/Pacman/PacmanMap.cpp)

- `PacmanGame::buildMap()` : construit la carte de Pacman, les murs, les couloirs et les bonus.
- `PacmanGame::wrap(int x, int y) const` : applique un déplacement cyclique aux coordonnées.
- `PacmanGame::wall(int x, int y) const` : vérifie si une case est un mur.
- `PacmanGame::toward(int x, int y, int tx, int ty) const` : choisit un déplacement qui se rapproche d’une cible.
- `PacmanGame::away(int x, int y, int tx, int ty) const` : choisit un déplacement qui s’éloigne d’une cible.
- `PacmanGame::buildRenderData()` : convertit l’état du jeu en grille et textes colorés pour le moteur graphique.

---

## [src/Games/Pacman/PacmanMove.cpp](../src/Games/Pacman/PacmanMove.cpp)

- `PacmanGame::eatCell()` : consomme une case de la carte et met à jour le score / mode puissance.
- `PacmanGame::releaseGhosts()` : active les fantômes après un délai de départ.
- `PacmanGame::movePacman()` : déplace Pacman selon la direction courante et le délai de mouvement.
- `PacmanGame::moveGhost(Ghost &g, int index)` : déplace un fantôme, gère la poursuite, la fuite et le retour à la base.
- `PacmanGame::moveGhosts()` : applique les mouvements à l’ensemble des fantômes actifs.
- `PacmanGame::checkWin()` : vérifie si tous les points ont été mangés et termine la partie en victoire.

---

## [src/Games/SpaceInvaders/SpaceInvadersGame.cpp](../src/Games/SpaceInvaders/SpaceInvadersGame.cpp)

- `SpaceInvadersGame::init()` : initialise une nouvelle partie, les ennemis, les tirs et les boucliers.
- `SpaceInvadersGame::reset()` : relance une nouvelle partie en appelant `init()`.
- `SpaceInvadersGame::close()` : ferme le module jeu.
- `SpaceInvadersGame::getName() const` : retourne le nom du jeu.
- `SpaceInvadersGame::spawnInvaders()` : crée la formation initiale d’envahisseurs.
- `SpaceInvadersGame::spawnShields()` : crée les boucliers protecteurs du joueur.
- `SpaceInvadersGame::handleInput(Key key)` : déplace le joueur et tire un projectile.
- `SpaceInvadersGame::update()` : met à jour les déplacements, tirs, collisions et état de fin de partie.
- `SpaceInvadersGame::moveInvaders()` : déplace les ennemis et inverse leur direction aux bords.
- `SpaceInvadersGame::movePlayerBullet()` : fait avancer le tir du joueur.
- `SpaceInvadersGame::moveEnemyBullets()` : fait avancer les tirs ennemis.
- `SpaceInvadersGame::enemyShoot()` : choisit un envahisseur et crée un tir ennemi.
- `SpaceInvadersGame::checkCollisions()` : traite les impacts entre tirs, ennemis, boucliers et joueur.
- `SpaceInvadersGame::buildRenderData()` : construit la grille et les textes pour l’affichage.
- `SpaceInvadersGame::getRenderData()` : retourne les données de rendu du jeu.
- `SpaceInvadersGame::getScore() const` : retourne le score courant.
- `SpaceInvadersGame::isGameOver() const` : indique si la partie est terminée.
- `entryPointGame()` : point d’entrée dynamique retournant une instance de Space Invaders.

---

## [tests/test_file.cpp](../tests/test_file.cpp)

Ce fichier ne contient actuellement aucune fonction définie, uniquement des inclusions de test.
