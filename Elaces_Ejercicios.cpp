#include <iostream>
#include <string>
using namespace std;

// Estructura de nodo para la lista enlazada
struct Player {
    int id;
    string name;
    int score;
    Player* next;
};

// Función para agregar un nodo a la lista
void addPlayer(Player*& head, int id, string name, int score) {
    Player* newPlayer = new Player{id, name, score, nullptr};
    if (head == nullptr) {
        head = newPlayer;
    } else {
        Player* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newPlayer;
    }
}

// Función para calcular el promedio
double calculateAverage(Player* head) {
    int sum = 0, count = 0;
    Player* temp = head;

    while (temp != nullptr) {
        sum += temp->score;
        count++;
        temp = temp->next;
    }
    return (count == 0) ? 0 : (double)sum / count;
}

// Función para encontrar los puntajes más altos y bajos
void findHighestAndLowest(Player* head, Player*& highest, Player*& lowest) {
    if (head == nullptr) return;

    highest = head;
    lowest = head;
    Player* temp = head;

    while (temp != nullptr) {
        if (temp->score > highest->score) {
            highest = temp;
        }
        if (temp->score < lowest->score) {
            lowest = temp;
        }
        temp = temp->next;
    }
}

// Función para eliminar nodos con puntajes menores al promedio
void removeBelowAverage(Player*& head, double average) {
    while (head != nullptr && head->score < average) {
        Player* temp = head;
        head = head->next;
        delete temp;
    }

    Player* current = head;
    while (current != nullptr && current->next != nullptr) {
        if (current->next->score < average) {
            Player* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
}

// Programa principal
int main() {
    Player* head = nullptr;

    // Agregar datos manualmente en lugar de leer de un archivo
    addPlayer(head, 1, "Alice", 85);
    addPlayer(head, 2, "Bob", 90);
    addPlayer(head, 3, "Charlie", 78);
    addPlayer(head, 4, "Diana", 92);

    // Calcular promedio
    double average = calculateAverage(head);
    cout << "Puntaje promedio: " << average << "\n";

    // Encontrar puntajes extremos
    Player *highest = nullptr, *lowest = nullptr;
    findHighestAndLowest(head, highest, lowest);

    if (highest != nullptr) {
        cout << "Mayor puntaje: " << highest->name << " con " << highest->score << "\n";
    }
    if (lowest != nullptr) {
        cout << "Menor puntaje: " << lowest->name << " con " << lowest->score << "\n";
    }

    // Eliminar jugadores por debajo del promedio
    removeBelowAverage(head, average);

    // Liberar memoria
    while (head != nullptr) {
        Player* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
