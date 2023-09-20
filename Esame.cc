//Matteo Morabito    matteo.morabito930@edu.unito.it   918551
//Andrea Scalenghe   andrea.scalenghe925@edu.unito.it  913359


#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <map>
using namespace std;

class Giocatore {                                     //La classe rappresenta un signolo giocatore, che è a sua volta rappresentato da:
private:
    string nome;                                      //Il nome
    int valutazione;                                  //La valutazione, compresa tra 0 e 1000
    int stato_giocatore;                              //Il suo stato: - malato = 1   - sano = 0
    int partite_giocate_consecutivamente;             //Il numero di partite giocate consecutivamente
public:
    Giocatore(const string&, int = 0);                                                 //Nel costruttore sono richiesti il nome e la valutazione del giocatore
    int prendi_valutazione() const { return valutazione; };                            //Restituisce la valutazione
    string prendi_nome() const { return nome; };                                       //Restituisce il nome
    int prendi_stato_giocatore() const { return stato_giocatore; };                    //Restituisce lo stato del giocatore
    int prendi_partite_giocate() const { return partite_giocate_consecutivamente; };   //Restituisce le partite giocate dal giocatore
    void cambia_partite_giocate(const int&);                                           //Cambia il numero di partite giocate del giocatore con il numero dato in input 
    void cambia_stato_giocatore0();                                                    //cambia lo stato del giocatore a sano (=0)
    void forse_cambia_stato_giocatore();                                               //Generando un numero casuale tra 1 e 100, se la somma di esso con le partite giocate e maggiore di 100 rende malato il giocatore (=1)
};


Giocatore::Giocatore(const string& s, int n) {
    nome = s;
    if(n < 0 || n > 1000)
        throw domain_error("Valutazione negativa o maggiore di 1000");
    valutazione = n;
    stato_giocatore = 0;
    partite_giocate_consecutivamente = 0;
}

void Giocatore::cambia_partite_giocate(const int& n) {
    partite_giocate_consecutivamente = n;
}

void Giocatore::cambia_stato_giocatore0() {
    stato_giocatore = 0;
    cambia_partite_giocate(0);
}

void Giocatore::forse_cambia_stato_giocatore() {
    srand(time(NULL));
    int n = rand()%100 + 1;
    int k = partite_giocate_consecutivamente;
    if(n+k > 100) stato_giocatore = 1;      
}

bool operator==(const Giocatore& a, const Giocatore& b) {
return a.prendi_nome() == b.prendi_nome() && a.prendi_valutazione() == b.prendi_valutazione();
}

bool operator!=(const Giocatore& a, const Giocatore& b) {
return a.prendi_valutazione() != b.prendi_valutazione() || a.prendi_valutazione() != b.prendi_valutazione();
}

std::ostream& operator<<(std::ostream& os, const Giocatore& a) {
os << a.prendi_nome() << " (valutazione: " << a.prendi_valutazione() <<  "; stato_giocatore: " << a.prendi_stato_giocatore() << ")";
return os;
}


//Definiamo ora una squadra

typedef list<Giocatore> giocatori;

giocatori crea_lista_di_giocatori(const int& n) {   
    giocatori A;
    int i = 0;
    cout << "Per creare una lista di giocatori, inserire in ordine nome (string) e valutazione (int) di ciascuno" << endl;
    while (i < n) {
        cout << "giorcatore numero " << i + 1 << ":" << endl;
        string nome;
        int valutazione;
        cin >> nome;
        cin >> valutazione;
        Giocatore g(nome, valutazione);
        A.insert(A.end(), g);
        i++;
    }
    return A;
}

std::ostream& operator<<(std::ostream& os, const giocatori& a) {  
    giocatori::const_iterator it = a.cbegin();
    while (it != a.cend()) {
        os << *it << endl;
        it++;
    }
    return os;
}


class Squadra {                //La classe rappresenta una squadra, che è a sua volta rappresentata da:
private: 
    string nome;               //Il nome della squadra
    giocatori rosa;            //I giocatori che la compongono, la rosa. Deve essere non nulla e non può avere giocatori uguali              
    int soldi;                 //La disponibilità economica, i soldi. Un valore generico, una squadra può andare in rosso
public:
    Squadra(giocatori, const string&, int = 0);      //Nel costruttore si chiedono una lista di giocatori, un nome e il patrimonio della squadra
    string prendi_nome() const { return nome; };     //Restituisce il nome
    giocatori prendi_rosa() const { return rosa; };  //Restituisce la rosa
    int prendi_soldi() const { return soldi; };      //Restituisce i soldi
    bool contiene(const Giocatore&) const;           //Verifica se la squadra contiene il giocatore in input
    void speculazioni(const int& n) { soldi += n; };  //Cambia i soldi della aggiungendo il numero natuale in input (Se negativo sottrae)
    void togli_giocatore(const Giocatore&);          //Toglie il giocatore in input alla squadra
    void acquisto(Squadra&, const Giocatore&);       //La squadra in input vende il giocatore in input alla squadra su cui è invocato il metodo
};

Squadra::Squadra(giocatori l, const string& s, int m) {
    if(l.size() < 1) throw domain_error("Ogni rosa deve essere composta da almeno 1 giocatore");
    nome = s;
    int count = 0;
    giocatori::const_iterator it1 = l.cbegin();
    giocatori::const_iterator it2 = l.cbegin();
    while(it1 != l.cend()) {
        while(it2 != l.cend()) {
            if(*it1 == *it2) count++;
            it2++;
        }
        if(count != 1)
            throw domain_error("Ogni giocatore può essere inserito una sola volta");
        else it1++;
    }
    rosa = l;
    soldi = m;
}

bool Squadra::contiene(const Giocatore& x) const {
    giocatori::const_iterator it = rosa.cbegin();
    while(it != rosa.cend() && *it != x) it++;
    return *it == x;
}

bool operator< (const Squadra& a, const Squadra& b) {  //Ordine per Squadre nella mappa, dove le squadre sono usate come chiave.
return a.prendi_nome() < b.prendi_nome();}

bool piu_punti(const pair<Squadra, int>& A, const pair<Squadra,int>& B) {
    return A.second > B.second;
}

void Squadra::togli_giocatore(const Giocatore& p) {
    giocatori::iterator at = rosa.begin();
    while(*at != p) at++;
    rosa.erase(at);
}

void Squadra::acquisto(Squadra& A, const Giocatore& p) {  
    if(A.rosa.size() < 2) throw domain_error("Le squadre devono avere almeno 2 giocatori per poterne vendere 1");
    if(!A.contiene(p)) throw domain_error("Il giocatore non e' nella squadra");
    A.togli_giocatore(p);
    rosa.push_back(p);
    int n = p.prendi_valutazione();
    speculazioni(-n);
    A.speculazioni(n);
}

bool operator==(const Squadra& a, const Squadra& b) {
    giocatori rosa1 = a.prendi_rosa();
    giocatori rosa2 = b.prendi_rosa();
    int l1 = rosa1.size();
    int l2 = rosa2.size();
    string nome1 = a.prendi_nome();
    string nome2 = b.prendi_nome();
    int count = 0;
    giocatori::const_iterator it1 = rosa1.cbegin();
    giocatori::const_iterator it2 = rosa2.cbegin();
    while (it1 != rosa1.cend()) {
        while (it2 != rosa2.cend()) {
            if (*it1 == *it2) count++;
            it2++;
        }
        it1++;
    }
    if(l1 == l2 && nome1 == nome2 && count == l1) return 1;
    else return 0;;
}

//Definiamo ora il campionato

typedef map <int, Squadra> squadre;
typedef map<Squadra, int> squadre_punteggi;
typedef vector<pair<Squadra, int>> squadre_ordinate;
typedef pair<Squadra, Squadra> coppiaS;
typedef list<coppiaS> giornata;
typedef map<int, giornata> tipo_calendario;


class Campionato {                           //La classe rapprresenta un campionato, che e' a sua volta rappresentato da:
private:
    squadre partecipanti;                    //Le squadre partecipanti, che devono essere un numero pari di almeno 2
    tipo_calendario calendario;              //Il calendario delle partite           
    squadre_punteggi pre_classifica;         //I punteggi delle squadre, non ordinati
    squadre_ordinate classifica;             //I punteggi delle squadre, ordinati
    int numero_giornata;                     //La giornata del campionato
public:
    Campionato(squadre);                                                 //Il costruttore richiede un insieme di squadre (una mappa)
    squadre prendi_partecipanti() const { return partecipanti; };        //Restituisce le squadre partecipanti 
    tipo_calendario prendi_calendario() const { return calendario; };    //Restitusice il calendario
    int prendi_giornata() const { return numero_giornata; };             //Restituisce l'ultima giornata giocata
    squadre_ordinate prendi_classifica() const { return classifica; };   //Restituisce la classifica
    void stampa_classifica() const;                                      //Stampa la classifica
    void giornata_(int);                                                 //Svolge la giornata il cui numero è passato in input
};

//Queste operazioni sui vettori servono a costruire il calendario

vector<int> crea_vettore_forza_n (int n) {
    vector<int> V;
    for (int i = 1; i < n+1; i++) V.push_back(i);
    return V;
}

vector<int> elimina_elemento (vector<int>& v, const int s) {       //Elimina da vettore in input l'elemento in input
    int l = v.size();
    for(int i = 0; i < l; i++) {
        if(v[i] == s) {
        for(int j = i; j < l-1; j++) v[j] = v[j+1];
        v.pop_back();
        return v;
        }
    }
    return v;
}

vector<vector<int>> vettore_di_vettori(int n) {    //Crea vettore il cui i-esimo elemento e' un vettore di interi a cui manca l'i+1-esimo numero
    vector<vector<int>> Vector;
    for(int i = 0; i < n; i++) {
        vector<int> v = crea_vettore_forza_n(n);
        Vector.push_back(v);
    }
    for(int i = 0; i < n-1; i++) elimina_elemento(Vector[i], i+1);
    return Vector;
}


bool contiene(const vector<int>& c, const int& n) {
    int l = c.size();
    for (int i = 0; i < l; i++) {
        if (c[i] == n) return true;
    }
    return false;
}

Campionato::Campionato(squadre S) {
    int n = S.size();
    if (n <= 1 || n%2 != 0) throw domain_error("Il numero di squadre partecipanti deve essere pari e strettamente positivo");
    partecipanti = S;
    tipo_calendario calendario0;
    vector<vector<int>> Vector = vettore_di_vettori(n);  //vettore di vettori con tutte le combinazioni possibili tra squadre
    for (int j = 1; j < n; j++) {                        //Compongo una giornata
        giornata g;
        vector<int> Primo = crea_vettore_forza_n(n);  //vettore di estrazione
        srand(time(NULL));
        for(int i = 1; i <= n/2; i++) {              //Trovo gli accoppiamenti
            int A = rand()%Primo.size();             //Trovo prima squadra
            int A2 = Primo[A];                       //
            elimina_elemento(Primo, Primo[A]);       //Tolgo la prima squadra dalla giornata
            int B = rand()%Primo.size();             //Trovo seconda squadra
            int Su = 0;
            while(Su == 0) {                                    
                if(contiene(Vector[A2-1], Primo[B])) Su = 1;  //Verifico che non si siano già incontrate
                else B = rand()%Primo.size();
            }
            int B2 = Primo[B];
            elimina_elemento(Primo, Primo[B]);              //Tolgo la seconda squadra dalla giornata 
            elimina_elemento(Vector[A2-1], B2);             //Tolgo la seconda squadra dalle possibili future avversarie della prima  
            elimina_elemento(Vector[B2-1], A2);             //Tolgo la prima squadra dalle possibili future avversarie della seconda
            coppiaS vs(S.at(A2),S.at(B2));
            g.push_back(vs);
        }
        pair<int, giornata> K(j,g);                        
        calendario0.insert(K);                                     //Inserisco la giornata composta nel calendario e itero
    }
    calendario = calendario0;
    squadre_ordinate v;
    for(int w = 1; w <= n; w++) {
        pair<Squadra, int> Q(S.at(w), 0);
        v.push_back(Q);
    }
    classifica = v;
    squadre_punteggi punti;
    for(int p = 1; p <= n; p++) punti[S.at(p)];
    pre_classifica = punti;
    numero_giornata = 0;
}


void Campionato::giornata_(int i) {
    numero_giornata = i;
    giornata l = calendario.at(i);
    vector<coppiaS> VECTOR;                                                                      //Costruisco vettore con le coppie della giornata
    for(giornata::const_iterator it = l.cbegin(); it != l.cend(); it++) VECTOR.push_back(*it);
    int L = VECTOR.size();
    for (int I = 0; I < L; I++) {                                                                //Per ogni coppia di squadre costruisco i vettori dei giocatori
        giocatori A = VECTOR[I].first.prendi_rosa();                                            
        giocatori B = VECTOR[I].second.prendi_rosa();
        vector<Giocatore> v1;                                                                    
        giocatori::const_iterator it1 = A.cbegin();
        while(it1 != A.cend()) {
            v1.push_back(*it1);
            it1++;
        }
        vector<Giocatore> v2;
        giocatori::const_iterator it2 = B.cbegin();
        while(it2 != B.cend()) {
            v2.push_back(*it2);
            it2++;
        }
        srand(time(NULL));
        int ran = rand()%1000;
        int count1 = 0;
        int count2 = 0;
        int l1 = v1.size();
        int l2 = v2.size();
        for(int i = 0; i < l1; i++) {                                                          //Per ogni giocatore verifico che:
            if (v1[i].prendi_partite_giocate() > 15) v1[i].cambia_partite_giocate(0);          //- Non abbia giocato più di 15 partite
            else {                                                                            
                v1[i].forse_cambia_stato_giocatore();
                if(v1[i].prendi_stato_giocatore() == 1) v1[i].cambia_stato_giocatore0();      //- Non sia infortunato in quella partita
                else {
                    if (ran <= v1[i].prendi_valutazione()) count1++;                          //Se gioca verifico che abbia una valutazione maggiore del numero randomico tra 1 e 1000 prima scelto
                    v1[i].cambia_partite_giocate(v1[i].prendi_partite_giocate()+1);           //Se è così lui conta un punto e gli aggiungo una partita
                }
            }
        }
        for(int j = 0; j < l2; j++) {
            if (v2[j].prendi_partite_giocate() > 15) v2[j].cambia_partite_giocate(0);
            else {
                v2[j].forse_cambia_stato_giocatore();
                if(v2[j].prendi_stato_giocatore() == 1) v2[j].cambia_stato_giocatore0();
                else {
                    if (ran <= v2[j].prendi_valutazione()) count2++;
                    v2[j].cambia_partite_giocate(v2[j].prendi_partite_giocate()+1);
                }
            }
        }                                                                                     //Chi a fatto più punti vince, se i punti sono uguali si pareggia
        if(count1 > count2) {
            pre_classifica[VECTOR[I].first] += 3;
        }
        else if(count2 > count1) {
            pre_classifica[VECTOR[I].second] += 3;
        }
        else {
            pre_classifica[VECTOR[I].first]++;
            pre_classifica[VECTOR[I].second]++;
        }
    }
    squadre_ordinate v = squadre_ordinate(pre_classifica.begin(), pre_classifica.end());    //Ordino la classifica
    sort(v.begin(), v.end(), piu_punti);
    classifica = v;
}



void Campionato::stampa_classifica() const {
    int l = classifica.size();
    cout << "L'attuale classifica e' la seguente" << endl;
    for(int i = 0; i < l; i++) {
        cout << i + 1 << "  " << classifica[i].first.prendi_nome() << " con punti: " << classifica[i].second << endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Squadra& a) {
    cout << "NOME SQUADRA: " << a.prendi_nome() << endl;
    cout << a.prendi_rosa() << endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const squadre& a) {
    int l = a.size();
    for (int i = 1; i <= l; i++) {
        cout << "SQUADRA NUMERO " << i << " :" << endl;
        cout << a.at(i).prendi_nome() << endl;}
    return os;
}

std::ostream& operator<<(std::ostream& os, const coppiaS& a) {
    cout << a.first.prendi_nome() << " vs " << a.second.prendi_nome();
    return os;
}

std::ostream& operator<<(std::ostream& os, const giornata& a) {
    giornata::const_iterator it = a.cbegin();
    while (it != a.cend()) {
        cout << *it << endl;
        it++;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Campionato& a) {
    int l = a.prendi_partecipanti().size();
    cout << "ELENCO SQUADRE:" << endl;
    cout << a.prendi_partecipanti() << endl;
    cout << "CALENDARIO: " << endl;
    for (int i = 1; i < l; i++) {
        cout << "Giornata " << i << ":" << endl;
        cout << a.prendi_calendario().at(i);
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const squadre_ordinate& a) {
    int l = a.size();
    for (int i = 0; i < l; i++) {
        cout << a[i].first.prendi_nome() << endl;
    }
    return os;
}

Squadra crea_squadra(const int& n) {
    string nome;
    cout << "inserire il nome della squadra" << endl;
    cin >> nome;
    int soldi;
    cout << "inserire i soldi della squadra (numero intero)" << endl;
    cin >> soldi;
    giocatori rosa = crea_lista_di_giocatori(n);
    Squadra S(rosa, nome, soldi);
    return S;
}

squadre crea_squadre(const int& n) {
    if (n <= 1 || n%2 != 0) throw domain_error("Il numero di squadre partecipanti deve essere pari e strettamente positivo");
    squadre SQ;
    for (int i = 1; i <= n; i++) {
        int m;
        cout << "quanti giocatori ha la squadra numero " << i << "?" << endl;
        cin >> m;
        Squadra S = crea_squadra(m);
        pair <int, Squadra> a(i,S);
        SQ.insert(a);
    }
    return SQ;
}






int main() {
    cout << "Si offrono due esperienze di gioco:" << endl;
    cout << "                                    - Se si vuole usare un campionato gia' preimpostato si prema 1" << endl;
    cout << "                                    - Se si vuole costruire il proprio campionato si digiti il numero di partecipanti che si vuole (strettamente positivo e pari)" << endl;
    cout << "Inoltre si prema 0 se si vuole assistere alla compravendita tra Juve e Milan di due giocatori (Szczęsny per Donnarumma)" << endl;
    int c;
    cin >> c;
    if(c == 0) {
        Giocatore ws("Wojciech Szczęsny", 870);
        Giocatore gc("Giorgio Chiellini", 860);
        Giocatore md("Matthijs de Ligt", 850);
        Giocatore lb("Leonardo Bonucci", 840);
        Giocatore jc("Juan Cuadrado", 840);
        Giocatore ar("Aaron Ramsey", 820);
        Giocatore cr("Cristiano Ronaldo", 930);
        Giocatore fc("Federico Chiesa", 790);
        Giocatore al("Alvavro Morata", 830);
        Giocatore pd("Paulo Dybala", 870);
        Giocatore dk("Dejan Kulusevski", 780);
        Giocatore ar1("Adrien Rabiot", 810);
        Giocatore wm("Weston Mckennie", 770);
        Giocatore dd("Danilo", 800);
        giocatori j = {ws,gc,md,lb,jc,ar,cr,fc,al,pd,dk,ar,wm,dd};
        Squadra Juventus(j, "Juventus F.C.", 850);
        Giocatore gdd("Gianluigi Donnarumma", 900);
        Giocatore sk("Simon Kjaer", 820);
        Giocatore th("Theo Hernandez", 840);
        Giocatore arr("Alessio Romagnoli", 820);
        Giocatore fk("Frank Kessié", 820);
        Giocatore hc("Hakan Calhanoglu", 810);
        Giocatore arrr("Ante Rebic", 790);
        Giocatore zi("Zatlan Ibrahimovic", 840);
        Giocatore rl("Rafael Leao", 770);
        Giocatore mm("Mario Mandzukic", 780);
        Giocatore ib("Ismael Benaccer", 780);
        Giocatore ft("Fikayo Tomori", 800);
        Giocatore st("Sandro Tonali", 770);
        Giocatore ars("Alexis Saelemaekers", 780);
        giocatori m = {gdd,sk,th,arr,fk,hc,arrr,zi,rl,mm,ib,ft,st,ars};
        Squadra Milan(m, "AC Milan", 750);
        squadre C = {{1, Juventus},{2, Milan}};
        Campionato SerieA(C);
        cout << Juventus << endl;
        cout << Milan << endl;
        cout << "Soldi Juventus: " << Juventus.prendi_soldi() << endl;
        cout << "Soldi Milan: " << Milan.prendi_soldi() << endl;
        Juventus.acquisto(Milan, gdd);
        Milan.acquisto(Juventus, ws);
        cout << endl << endl;
        cout << "A compravendita finita si ottiene:" << endl;
        cout << Juventus << endl;
        cout << Milan << endl;
        cout << "Soldi Juventus: " << Juventus.prendi_soldi() << endl;
        cout << "Soldi Milan: " << Milan.prendi_soldi() << endl;
    }
    else if(c == 1) {
        Giocatore ws("Wojciech Szczęsny", 870);
        Giocatore gc("Giorgio Chiellini", 860);
        Giocatore md("Matthijs de Ligt", 850);
        Giocatore lb("Leonardo Bonucci", 840);
        Giocatore jc("Juan Cuadrado", 840);
        Giocatore ar("Aaron Ramsey", 820);
        Giocatore cr("Cristiano Ronaldo", 930);
        Giocatore fc("Federico Chiesa", 790);
        Giocatore al("Alvavro Morata", 830);
        Giocatore pd("Paulo Dybala", 870);
        Giocatore dk("Dejan Kulusevski", 780);
        Giocatore ar1("Adrien Rabiot", 810);
        Giocatore wm("Weston Mckennie", 770);
        Giocatore dd("Danilo", 800);
        giocatori j = {ws,gc,md,lb,jc,ar,cr,fc,al,pd,dk,ar,wm,dd};
        Squadra Juventus(j, "Juventus F.C.", 850);
        Giocatore sa("Samir Handanovic", 870);
        Giocatore ah("Achraf Hakimi", 830);
        Giocatore sd("Stefan de Vrij", 850);
        Giocatore ab("Alessanrdo Bastoni", 830);
        Giocatore ms("Milan Skriniar", 860);
        Giocatore ak("Aleksandar Kolarov", 790);
        Giocatore mb("Marcelo Brozovic", 840);
        Giocatore ce("Christian Eriksen", 830);
        Giocatore nb("Nicolò Barella", 850);
        Giocatore av("Arturo Vidal", 810);
        Giocatore as("Alexis Sàanchez", 800);
        Giocatore rm("Romelu Lukaku", 860);
        Giocatore ss("Stefano Sensi", 780);
        Giocatore iv("Ivan Perisic", 810);
        giocatori i = {sa,ah,sd,ab,ms,ak,mb,ce,nb,av,as,rm,ss,iv};
        Squadra Inter(i, "Internazionale F.C.", 800);
        Giocatore pg("Pierluigi Gollini", 810);
        Giocatore bj("Berat Djimsiti", 810);
        Giocatore rb("Robin Gosens", 830);
        Giocatore rf("Rafael Toloi", 780);
        Giocatore crr("Cristian Romero", 810);
        Giocatore mdd("Marten de Roon", 810);
        Giocatore rmm("Ruslan Malinovskyj", 800);
        Giocatore rff("Remo Freuler", 790);
        Giocatore hh("Hans Hateboer", 790);
        Giocatore am("Aleksej Mirancuk", 810);
        Giocatore ji("Josip Ilicic", 840);
        Giocatore dz("Duvan Zapata", 830);
        Giocatore lm("luis Muriel", 820);
        Giocatore mp("Mario Pasalic", 800);
        giocatori a = {pg,bj,rb,rf,crr,mdd,rmm,rff,hh,am,ji,dz,lm,mp};
        Squadra Atalanta(a, "Atalanta BC", 600);
        Giocatore gdd("Gianluigi Donnarumma", 900);
        Giocatore sk("Simon Kjaer", 820);
        Giocatore th("Theo Hernandez", 840);
        Giocatore arr("Alessio Romagnoli", 820);
        Giocatore fk("Frank Kessié", 820);
        Giocatore hc("Hakan Calhanoglu", 810);
        Giocatore arrr("Ante Rebic", 790);
        Giocatore zi("Zatlan Ibrahimovic", 840);
        Giocatore rl("Rafael Leao", 770);
        Giocatore mm("Mario Mandzukic", 780);
        Giocatore ib("Ismael Benaccer", 780);
        Giocatore ft("Fikayo Tomori", 800);
        Giocatore st("Sandro Tonali", 770);
        Giocatore ars("Alexis Saelemaekers", 780);
        giocatori m = {gdd,sk,th,arr,fk,hc,arrr,zi,rl,mm,ib,ft,st,ars};
        Squadra Milan(m, "AC Milan", 750);
        squadre C = {{1, Juventus},{2, Milan},{3, Inter},{4, Atalanta}};
        Campionato SerieA(C);
        cout << SerieA << endl << endl;
        int I = SerieA.prendi_calendario().size();
        for(int i = 1; i <= I; i++) {
            SerieA.giornata_(i);
            cout << "classifica alla giornata " << i << ":" << endl;
            SerieA.stampa_classifica();
            cout << endl;
        }
    }
    else {
        squadre A = crea_squadre(c);
        Campionato C(A);
        cout << endl << endl;
        cout << C << endl << endl;
        int I = C.prendi_calendario().size();
        for(int i = 1; i <= I; i++) {
            C.giornata_(i);
            cout << "classifica alla giornata " << i << ":" << endl;
            C.stampa_classifica();
            cout << endl;
        }
    }
}