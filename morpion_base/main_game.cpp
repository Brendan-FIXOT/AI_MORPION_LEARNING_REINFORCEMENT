#include "../IA_part/IA_Qlearning.h"
#include "tab_morpion.h"

int main() {
    int currentPlayer;
    int player1 = 1, player2IA = 2;
    Action chosen_action;

    load_Q_table("../save_training/IA_1.dat");

    print_Q_table();

    // Initialisation du tableau avec que des 0
    std::vector<int> board(9);

    // Définitions des paramètres d'apprentissage
    float alpha_parameter = 0.1;   // taux d'apprentissage
    float gamma_parameter = 0.9;   // Facteur d'actualisation
    float epsilon_parameter = 0.1; // Paramètre d'exploration

    for (int turn = 0; turn < 9; ++turn) {
        
        // Déterminer le joueur actuel : Joueur 1 pour les tours pairs, Joueur 2 pour les tours impairs
        currentPlayer = (turn % 2 == 0) ? player1 : player2IA;
        
        // Affichage du tableau
        std::cout << interface_board(board) << std::endl;

        // Affichage du joueur qui doit jouer
        std::cout << "Joueur " << currentPlayer << ", choisi entre 0 et 8 : " << std::endl;

        if (currentPlayer == player1) {
            board = morpion_choice(board, currentPlayer);
        }
        if (currentPlayer == player2IA) {
            do {
                chosen_action = action_choice(board, epsilon_parameter); // Choisir une action selon la Q-table
                std::cout << chosen_action << std::endl;
            } while (board[chosen_action] != 0);
            board[chosen_action] = -1;
            std::cout << "L'IA a joué en : " << chosen_action << std::endl;
        }
    
        // Vérifier si le joueur actuel gagne
        if (check_win(board)) {
            if (currentPlayer == player2IA) {
                float reward = 1.0;
                update_Q_value(board, chosen_action, reward, board, alpha_parameter, gamma_parameter);
            } else {
                float reward = -1.0;
                update_Q_value(board, chosen_action, reward, board, alpha_parameter, gamma_parameter); // Màj des Q-valeurs pour le gagnant
            }
            std::cout << "Partie Terminée, Joueur " << currentPlayer << " gagnant !" << std::endl;
            // Affichage du tableau en fin de partie
            std::cout << interface_board(board) << std::endl;
            break;
        }

        // Si on arrive au dernier tour sans gagnant
        if (turn == 8) {
            float reward = 0.0;
            update_Q_value(board, chosen_action, reward, board, alpha_parameter, gamma_parameter);
            std::cout << "Partie Terminée, égalité !" << std::endl;
        }
    }
    return 0;
}