#include "IA_Qlearning.h"
#include "../morpion_base/tab_morpion.h"

int main() {
    int currentPlayer;
    int player1IA = 1, player2IA = 2;

    Action chosen_action1IA;
    Action chosen_action2IA;

    // Définitions des paramètres d'apprentissage
    float alpha_parameter = 0.3;   // taux d'apprentissage
    float gamma_parameter = 0.9;   // Facteur d'actualisation
    //float epsilon_parameter = 0.5; // Paramètre d'exploration
    int number_training = 8000;

    load_Q_table("../save_training/IA_1.dat");

    for (int episode = 0; episode < number_training; episode++) {
        float epsilon = std::max(0.1, 0.9 - episode * 0.001);
        // Initialisation du tableau avec que des 0
        State old_board(9, 0);
        State current_board(9, 0);
        State new_board(9, 0);

        for (int turn = 0; turn < 9; ++turn) {
            
            // Déterminer le joueur actuel : Joueur 1 pour les tours pairs, Joueur 2 pour les tours impairs
            currentPlayer = (turn % 2 == 0) ? player1IA : player2IA;
            old_board = current_board;
            current_board = new_board;
            
            if (currentPlayer == player1IA) {
                // Action choisie par l'IA
                do {
                    chosen_action1IA = action_choice(current_board, epsilon); // Choisir une action selon la Q-table
                } while (current_board[chosen_action1IA] != 0);
                if (not_block(current_board, chosen_action1IA, 1) == true) {
                    float middlereward1IA = -0.5;
                    update_Q_value(current_board, chosen_action1IA, middlereward1IA, new_board, alpha_parameter, gamma_parameter); // Màj des Q-valeurs pour le gagnant
                }
                // Qui fait l'action ?
                new_board[chosen_action1IA] = 1;
            }
            if (currentPlayer == player2IA) {
                // Action choisie par l'IA
                do {
                    chosen_action2IA = action_choice(current_board, epsilon); // Choisir une action selon la Q-table
                } while (current_board[chosen_action2IA] != 0);
                if (not_block(current_board, chosen_action2IA, -1) == true) {
                    float middlereward2IA = -0.5;
                    update_Q_value(current_board, chosen_action2IA, middlereward2IA, new_board, alpha_parameter, gamma_parameter); // Màj des Q-valeurs pour le gagnant
                }
                // Qui fait l'action ?
                new_board[chosen_action2IA] = -1;
            }
    
            // Vérifier si le joueur actuel gagne
            if (check_win(new_board)) {
                float reward1IA = (currentPlayer == player1IA) ? 1.0 : -1.0; // Récompense pour le joueur 1, pénalité pour le joueur 2
                float reward2IA = (currentPlayer == player2IA) ? 1.0 : -1.0;
                if (currentPlayer == player1IA) {
                    update_Q_value(current_board, chosen_action1IA, reward1IA, new_board, alpha_parameter, gamma_parameter); // Màj des Q-valeurs pour le gagnant
                    update_Q_value(old_board, chosen_action2IA, reward2IA, current_board, alpha_parameter, gamma_parameter); // Màj des Q-valeurs pour le gagnant
                } else {
                    update_Q_value(old_board, chosen_action1IA, reward1IA, current_board, alpha_parameter, gamma_parameter); // Màj des Q-valeurs pour le gagnant
                    update_Q_value(current_board, chosen_action2IA, reward2IA, new_board, alpha_parameter, gamma_parameter); // Màj des Q-valeurs pour le gagnant
                }
                std::cout << "Episode " << episode + 1 << " terminé : Joueur " << currentPlayer << " a gagné !" << std::endl;
                break;
            }

            // Si on arrive au dernier tour sans gagnant
            if (turn == 8) {
                float reward = 0.0;
                if (currentPlayer == player1IA) {
                    update_Q_value(current_board, chosen_action1IA, reward, new_board, alpha_parameter, gamma_parameter); // Màj des Q-valeurs pour le gagnant
                    update_Q_value(old_board, chosen_action2IA, reward, current_board, alpha_parameter, gamma_parameter); // Màj des Q-valeurs pour le gagnant
                } else {
                    update_Q_value(old_board, chosen_action1IA, reward, current_board, alpha_parameter, gamma_parameter); // Màj des Q-valeurs pour le gagnant
                    update_Q_value(current_board, chosen_action2IA, reward, new_board, alpha_parameter, gamma_parameter); // Màj des Q-valeurs pour le gagnant
                }
                std::cout << "Episode " << episode + 1 << " terminé : égalité ! " << std::endl;
            }
        }
    }
    save_Q_table("../save_training/IA_1.dat");
    return 0;
}