#include "IA_Qlearning.h"

// récupérer la table Q
float Qclass::get_Q_value(const State& state, Action action) {
    return Qclass::Q[{state, action}];
}

// Fonction pour sauvegarder la Q-table dans un fichier
void Qclass::save_Q_table(const std::string &filename) {
    std::ofstream file(filename, std::ios::out); // permet de ne pas supprimer le contenu du fichier
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier pour la sauvegarde !" << std::endl;
        return;
    }

    for (const auto &entry : Q) {
        const State &state = entry.first.first;
        Action action = entry.first.second;
        float q_value = entry.second;

        // Convertir l'état en une chaîne de caractères pour faciliter l'écriture
        for (int cell : state) {
            file << cell << " ";  // Écrire chaque élément de l'état
        }
        file << action << " " << q_value << "\n";  // Écrire l'action et la valeur Q
    }
    file.close();
    std::cout << "Q-table sauvegardée dans le fichier " << filename << std::endl;
}

// Fonction pour charger la Q-table depuis un fichier
void Qclass::load_Q_table(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier pour le chargement !" << std::endl;
        return;
    }

    Q.clear();  // Vider la Q-table existante pour éviter les conflits
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        State state(9);  // Supposons un état de taille 9
        Action action;
        float q_value;

        for (int i = 0; i < 9; ++i) {
            ss >> state[i];  // Lire chaque élément de l'état
        }
        ss >> action >> q_value;  // Lire l'action et la valeur Q

        Q[{state, action}] = q_value;  // Stocker dans la Q-table
    }
    file.close();
    std::cout << "Q-table chargée depuis le fichier " << filename << std::endl;
}


void Qclass::update_Q_value(const State& state, Action action, float reward, const State& next_state, float alpha_parameter, float gamma_parameter) {
    float next_max_Q = -std::numeric_limits<float>::infinity(); // iniatialisé au floatant le plus petit possible
    // Boucle sur les 9 actions possibles
    for(Action next_action = 0; next_action < 9; ++next_action) {
        next_max_Q = std::max(next_max_Q, get_Q_value(next_state, next_action));
    }
    float current_Q = get_Q_value(state, action);
    Q[{state, action}] = current_Q + alpha_parameter * (reward + gamma_parameter * next_max_Q - current_Q);
}

Action Qclass::action_choice(State state, float epsilon_param) {
    if ((float)rand() / RAND_MAX < epsilon_param) {
        // Choisit une action aléatoire (exploration)
        Action random_action;
        do {
            random_action = rand() % 9; // Choisit une case aléatoire
        } while (state[random_action] != 0); // S'assure que la case est libre
        return random_action;
    } else {
        // Choix basé sur la Q table (Exploitation)
        float best_Q = -std::numeric_limits<float>::infinity(); // initialisé au floatant le plus petit possible
        Action best_action = -1; // car les actions vont de 0 à 8
        float Q_corresponding;
        for(Action action = 0; action < 9; ++action) {
            Q_corresponding = get_Q_value(state, action);
            if (Q_corresponding > best_Q && state[action] == 0) {
                best_Q = Q_corresponding;
                best_action = action;
            }
        }
        return best_action;
    }
}

void Qclass::print_Q_table() {
    std::cout << "Contenu de la Q-table :" << std::endl;
    for (const auto& entry : Q) {
        const State& state = entry.first.first;
        Action action = entry.first.second;
        float q_value = entry.second;

        // Afficher l'état sous forme de grille 3x3
        std::cout << "État : ";
        for (int i = 0; i < state.size(); ++i) {
            std::cout << state[i] << ((i % 3 == 2) ? "\n" : " ");
        }

        // Afficher l'action et la valeur Q
        std::cout << "Action : " << action << " | Valeur Q : " << q_value << std::endl;
        std::cout << "--------------------------" << std::endl;
    }
}