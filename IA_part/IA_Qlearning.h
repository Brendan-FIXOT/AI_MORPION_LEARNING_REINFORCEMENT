#ifndef IA_QLEARNING_H
#define IA_QLEARNING_H

#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <fstream>   // pour std::ofstream et std::ifstream
#include <sstream>   // pour std::stringstream
#include "../morpion_base/tab_morpion.h"

using State = std::vector<int>; // état du plateau
using Action = int; // action, représentant une case de 0 à 8

class Qclass {
private :
    // Table Q
    std::map<std::pair<State, Action>, float> Q;
public :
    Qclass() {}
    // Fonction pour obtenir la valeur de Q pour un état et une action
    float get_Q_value(const State& state, Action action);

    void save_Q_table(const std::string &filename);
    void load_Q_table(const std::string &filename);

    // Fonction pour mettre à jour la valeur de Q pour un état, une action, une récompense et un état suivant
    void update_Q_value(const State& state, Action action, float reward, const State& next_state, float alpha_parameter, float gamma_parameter);

    // Fonction pour choisir une action à partir d'un état donné (exploration/exploitation)
    Action action_choice(State state, float epsilon_param);
    
    void print_Q_table();

};

#endif // IA_QLEARNING_H