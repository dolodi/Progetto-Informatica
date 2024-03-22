#include "./include/classifica.hpp"
#define HEADER_SIZE_X 25

//  costruttore
classifica::classifica(char *fileName)
{
    //  inizializzo attributi
    this->punteggi = new node;
    this->n_punteggi = 0;
    this->filename = fileName;

    // Apri il file in modalità lettura
    ifstream file_punteggi(this->filename);

    //ritorna un errore nel caso il file non esista (ad esempio)
    if (!file_punteggi.is_open())
        cerr << "Impossibile aprire il file." << endl;
    
    //  uso il flusso aperto verso il file in modalità lettura per leggere riga per riga il file
    //  su ogni riga ci sarà un punteggio (intero) diverso ottenuto in una delle partite passate
    //  chiuse e salvate
    int iter;

    //  mentre ci sono ancora righe da leggere --> [iter != 0] (le righe vuote sono NULL, e NULL)
    //  se si arriva alla fine del file (quindi si ha una riga NULL) [file_punteggi >> iter] verrà
    //  valutata come NULL, e NULL come intero viene considerato 0 (spiegato molto informalmente)
    while (file_punteggi >> iter) {     
        
        //  effettuo un inserimento (ordinato in maniera decrescente) nella lista circolare dei punteggi
        punteggi = insert_ordered(punteggi, iter);
       
       // tengo conto della dimensione della lista dei punteggi
       ++n_punteggi;
    }

    //  chiudo il flusso di lettura creato prima
    file_punteggi.close();
}

// distruttore
classifica::~classifica() {}

void classifica::drawClassifica(WINDOW *win){
	int choice = 0;
	int start_line = 28;

    WINDOW *header_win = newwin(8, 66 , LINES/2 -25, COLS/2 - 33);
    WINDOW *inner_win = newwin(30, 20 , LINES/2 -10, COLS/2 - 12);

    wrefresh(inner_win);
    
    // Crea la finestra scrollabile
    keypad(inner_win, TRUE);
    scrollok(inner_win, TRUE);
    curs_set(FALSE);
    list tmp = punteggi;
    int index = 0;
    
    do
    {   print_menu(inner_win, start_line, tmp, index);
        drawHeader(header_win);
        
        wrefresh(inner_win);

        switch (choice = wgetch(inner_win)) {
            case KEY_UP:
                if (start_line > 28) {
                    --start_line;
                    tmp = tmp->prev;
                    --index;
                }
                break;
            case KEY_DOWN:
                if (start_line < n_punteggi) {
                    ++start_line;
                    ++index;
                    tmp=tmp->next;
                }
                break;
            default:
                break;
        }
    }while (choice != KEY_LEFT);
}

void classifica::print_menu(WINDOW *win, int start_line, list to_draw, int index) {
    int starty = 1;
    list tmp = to_draw;

    for(int i = index; i < start_line && i < n_punteggi; i++)
	{	mvwprintw(win, starty, 1, "    %d. %d    ", i+1, tmp->val);
        ++starty; 
        tmp = tmp->next;
	}
    wrefresh(win);
}

void classifica::drawHeader(WINDOW *win){
    mvwprintw(win, 2, 2, "   ____   _                       _    __   _                ");
    mvwprintw(win, 3, 2, "  / ___| | |   __ _   ___   ___  (_)  / _| (_)   ___    __ _ ");
    mvwprintw(win, 4, 2, " | |     | |  / _` | / __| / __| | | | |_  | |  / __|  / _` |");
    mvwprintw(win, 5, 2, " | |___  | | | (_| | \\__ \\ \\__ \\ | | |  _| | | | (__  | (_| |");
    mvwprintw(win, 6, 2, "  \\____| |_|  \\__,_| |___/ |___/ |_| |_|   |_|  \\___|  \\__,_|");
    wrefresh(win);
}

list classifica::getPunteggi(){
    return punteggi;
}

void classifica::distruggiPunteggi(){
    delete_list(this->punteggi);
}


void classifica::salvaPunteggi(){
    print_reverse(this->punteggi, this->filename);
}

void classifica::inserisciPunteggion(int p){ 
    insert_ordered(this->punteggi, p);
}

unsigned int classifica::getn_Punteggi(){
    return n_punteggi;
}

char *classifica::getFilename(){
    return filename;
}




