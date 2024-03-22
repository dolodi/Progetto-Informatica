#include "include/my_list.hpp"


list head_insert(list l, int el){
    list tmp = new node;
    tmp->val = el;
    tmp->next = l;
    tmp->prev = NULL;
    l->prev = tmp;
    return tmp;
}


list insert_ordered(list head, int el) {
    // Crea un nuovo nodo e inizializza i suoi puntatori
    list newNode = new node;
    newNode->val = el;
    newNode->next = NULL;
    newNode->prev = NULL;

    // Se la lista è vuota o l'elemento è maggiore della testa, il nuovo nodo diventa la nuova testa
    if (head == NULL || el > head->val) {
        newNode->next = head;
        if (head != NULL) {
            head->prev = newNode;
        }
        return newNode;
    }

    // Altrimenti, scorri la lista fino a trovare il punto di inserimento
    list current = head;
    while (current->next != NULL && el <= current->next->val) {
        current = current->next;
    }

    // Inserisce il nuovo nodo tra current e current->next
    newNode->next = current->next;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;
    newNode->prev = current;

    return head;
}

void print_reverse_helper(list head, ofstream& outputFile) {
    if (head->next != NULL) {
        // Chiamata ricorsiva sulla coda della lista
        print_reverse_helper(head->next, outputFile);
        
        // Stampa il valore del nodo corrente sul file
        outputFile << head->val << endl;
    }
}

void print_reverse(list head, const char* filename) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "Errore nell'apertura del file " << filename << endl;
    } else {
        print_reverse_helper(head, outputFile);
        outputFile.close();
    }
}

void delete_list(list head) {
    while (head->next != NULL) {
        list temp = head;
        head = head->next;
        delete temp;
    }
}