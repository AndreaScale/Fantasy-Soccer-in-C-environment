#include <cassert>
#include <iostream>

#define main project_main
#include "../Esame.cc"
#undef main

int main() {
    // Create players
    Giocatore g1("Wojciech Szczesny", 870);
    Giocatore g2("Giorgio Chiellini", 860);
    Giocatore g3("Matthijs de Ligt", 850);
    giocatori rosa = {g1, g2, g3};
    Squadra team(rosa, "Juventus F.C.");

    // Player in roster
    assert(team.contiene(g2));

    // Player not in roster
    Giocatore g4("Cristiano Ronaldo", 930);
    assert(!team.contiene(g4));

    std::cout << "test_squadra_contiene passed" << std::endl;
    return 0;
}
