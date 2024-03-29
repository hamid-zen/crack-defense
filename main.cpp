#include <iostream>
#include "src/grid.h"
#include "src/game.h"
using namespace std;
#include <ncurses.h>

int main() {
   /* initscr(); // Initialiser l'écran pour ncurses
    cbreak(); // Activer le mode de saisie cbreak pour obtenir des saisies caractère par caractère
    noecho(); // Désactiver l'affichage des caractères saisis
    keypad(stdscr, TRUE); // Activer la prise en charge des touches spéciales

    int ch;
    printw("Appuyez sur une touche (q pour quitter) : ");
    while (true) {
        ch = getch(); // Attendre une saisie de l'utilisateur
        if (ch == 'q')
            break;
        else
            printw("Vous avez appuyé sur la touche : %c\n", ch);
    }

    endwin(); // Terminer l'utilisation de ncurses
*/
game g;
g.show();
std::cout<<g.update_dy()<<std::endl;
    return 0;
}
