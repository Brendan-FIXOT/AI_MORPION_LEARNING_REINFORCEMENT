#include "tab_morpion.h"

std::vector<int> morpion_choice(std::vector<int> board, int player) {
    
    int index;
    bool finished = false;
    
    for(;finished == false;) {
        std::cin >> index;
        if (index >= 0 && index <= 8) {
            if (board[index] == 0) {
                if (player == 1) {
                    board[index] = 1;
                    finished = true;
                }
                if (player == 2) {
                    board[index] = -1;
                    finished = true;
                }
            } else {
                std::cout << "La place est déjà prise ! Rejouer :";
            }
        } else {
            std::cout << "Entrée non valide, il n'y a que 9 cases, recommence." << std::endl;
        }
    }
    return board;
}

bool check_win(std::vector<int> board) {
    // Pour toutes les lignes
    for (int i = 0; i < 9; i+=3) {
        if (board[i] != 0 && board[i+1] != 0 && board[i+2] != 0 &&
        board[i] == board[i+1] && board[i+1] == board[i+2]) {return true;}
    }
    
    // Pour toutes les colonnes
    for (int i = 0; i < 3; i++) {
        if (board[i] != 0 && board[i+3] != 0 && board[i+6] != 0 &&
        board[i] == board[i+3] && board[i+3] == board[i+6]) {return true;}
    }

    // Pour la première diagonale
    if (board[0] != 0 && board[4] != 0 && board[8] != 0 &&
        board[0] == board[4] && board[4] == board[8]) {return true;}
    
    // Pour la seconde diagonale
    if (board[2] != 0 && board[4] != 0 && board[6] != 0 &&
        board[2] == board[4] && board[4] == board[6]) {return true;}

    return false;
}

std::string interface_board(std::vector<int> board) {
    std::string interface;

    // Vérifié si board en entrée est bien de la bonne taille
    if (board.size() != 9) {
        throw std::invalid_argument("Le vecteur d'entrée n'est pas de la bonne taille");
    }
    
    for (int i = 0; i < 9; ++i) {
        // Ajouter le symbole pour chaque case
        if (board[i] == 0) {
            interface.append("   ");
        } else if (board[i] == 1) {
            interface.append(" X ");
        } else if (board[i] == -1) {
            interface.append(" O ");
        }

        // Ajouter un séparateur vertical après chaque case sauf la troisième
        if ((i + 1) % 3 != 0) {
            interface.append("|");
        } else if (i < 6) {
            // Ajouter une bordure horizontale après chaque ligne sauf la dernière
            interface.append("\n---+---+---\n");
        }
    }

    return interface;
}