# Fantasy Soccer League in C++

This project implements a simplified fantasy soccer (football) league in **C++** to showcase object‑oriented programming techniques.  
It models players, teams and an entire league with functionality for:

- Creating and managing player rosters
- Checking if a player belongs to a team
- Tracking player health and match participation
- Simulating a league schedule and standings
- Performing player trades between teams

The code is contained in a single source file `Esame.cc` and a small test suite.

## Getting Started

### Prerequisites
- A C++11 compliant compiler (e.g. `g++`)

### Build
Compile the main program:
```bash
g++ -std=c++11 Esame.cc -o fantasy-soccer
```
Run the resulting executable:
```bash
./fantasy-soccer
```
The program is interactive and will prompt for input to set up teams and simulate matches.

### Run Tests
A minimal set of unit tests is provided in the `tests` directory. Compile and execute them with:
```bash
g++ -std=c++11 tests/test_squadra_contiene.cpp -o test_squadra_contiene
./test_squadra_contiene
```
These tests verify core functionality such as checking whether a team contains a given player.

## Repository Structure
```
.
├── Esame.cc                 # Main implementation of the fantasy league
├── README.md                # Project documentation
└── tests
    └── test_squadra_contiene.cpp  # Example unit test
```

## Authors
- Andrea Scalenghe
- Matteo Morabito

## License
This project is released under the [MIT License](https://opensource.org/licenses/MIT).
