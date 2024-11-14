#include "IA_Qlearning.h"
#include "../morpion_base/tab_morpion.h"

int main() {
    int currentPlayer;
    int player1IA = 1, player2IA = 2;

    Action chosen_action;

    // Définitions des paramètres d'apprentissage
    float alpha_parameter = 0.1;   // taux d'apprentissage
    float gamma_parameter = 0.9;   // Facteur d'actualisation
    //float epsilon_parameter = 0.5; // Paramètre d'exploration
    int number_training = 80000;

    load_Q_table("../save_training/IA_1.dat");

    for (int episode = 0; episode < number_training; episode++) {
        float epsilon = std::max(0.1, 0.9 - episode * 0.00001);
        // Initialisation du tableau avec que des 0
        State board(9, 0);

        for (int turn = 0; turn < 9; ++turn) {
            
            // Déterminer le joueur actuel : Joueur 1 pour les tours pairs, Joueur 2 pour les tours impairs
            currentPlayer = (turn % 2 == 0) ? player1IA : player2IA;

            // Action choisie par l'IA
            do {
                chosen_action = action_choice(board, epsilon); // Choisir une action selon la Q-table
            } while (board[chosen_action] != 0);

            // Qui fait l'action ?
            board[chosen_action] = (turn % 2 == 0) ? 1 : -1;
    
            // Vérifier si le joueur actuel gagne
            if (check_win(board)) {
                float reward = (currentPlayer == player1IA) ? 1.0 : -1.0; // Récompense pour le joueur 1, pénalité pour le joueur 2
                update_Q_value(board, chosen_action, reward, board, alpha_parameter, gamma_parameter); // Màj des Q-valeurs pour le gagnant
                std::cout << "Episode " << episode + 1 << " terminé : Joueur " << currentPlayer << " a gagné !" << std::endl;
                break;
            }

            // Si on arrive au dernier tour sans gagnant
            if (turn == 8) {
                float reward = 0.0;
                update_Q_value(board, chosen_action, reward, board, alpha_parameter, gamma_parameter);
                std::cout << "Episode " << episode + 1 << " terminé : égalité ! " << std::endl;
            }
        }
    }
    save_Q_table("../save_training/IA_1.dat");
    return 0;
}