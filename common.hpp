#pragma once

#include <iostream>
#include <unistd.h>
#include <chrono>
#include <random>
#include <array>
#include <sstream>
#include <algorithm>
#include <functional>
#include <fstream>

int random_index(int lower, int higher);

struct Cell {
	bool			player : 1; // player of ?
	bool			sleep : 1; // sleeping
	bool			empty : 1; // vide or not
	unsigned char	size : 2; // 0 to 3
	unsigned char	richness : 2; // 0 to 3
	bool			info : 1; // info supplementaire bool dispo
}; // TAILLE TOTAL 1 Octet = taille char
struct	Info {
	bool			player;
	unsigned char	days; // 0 - 64 Les jours ne vont que a 24
	int				nutriments;

	std::array<bool, 2>					wait;
	std::array<short, 2>				score; // 0 - 4096
	std::array<short, 2>				sun; // 0 - 4096
    std::array<std::array<int, 4>, 2> 	trees_size;
    std::array<std::array<int, 3>, 2> 	trees_richness;
}; // TAILLE TOTAL 8 Octet = taille long long int
//std::function<bool(State&, Action, int, int)> t[4] = {seed_action, grow_action, complete_action, wait_action};
enum struct Action_type {
	seed,
	grow,
	complete,
	wait,
	none,
};
struct Action {
    Action_type		type; // 1 1 1 => 7
	unsigned char   from; // index from
	unsigned char   to; // index to for seed
    unsigned char   cost;
    double          score;
    // Il reste 4 bytes

	Action() {}
    Action(Action_type ty, unsigned char f, unsigned char t, unsigned char c) : type(ty), from(f), to(t), cost(c) {}
}; // TAILLE TOTAL 4 Octet = taille of int
struct State {
    Info                    info;
    std::array<Cell, 37>    grid;
    Action                  a;

	State() {}
	State(const Info& i, const std::array<Cell, 37>& g) : info(i), grid(g) {}
    
	void	simulate_action(State& new_s, Action a);
	void	do_action(Action a);
	bool	final_state() const;
	void	print_map();

};
struct Diag {
    std::array<int , 3> size;
    std::array<bool , 36> diag;

    Diag(const std::array<int , 3>& s, const std::array<bool , 36>& d) : size(s), diag(d) {};
};

extern Diag d[37];

struct Neigbours {
    std::array<int , 3> size;
    std::array<unsigned char , 36> neigbours;

    Neigbours(const std::array<int , 3>& s, const std::array<unsigned char , 36>& n) : size(s), neigbours(n) {};
};

extern Neigbours n[37];

struct Shadow {
    std::array<std::array<int, 3>, 37> shadow;
    Shadow(const std::array<std::array<int, 3>, 37>& s) : shadow(s) {};
};
extern Shadow s[6];

std::ostream&   operator<<(std::ostream& f, Action_type a);
std::ostream&   operator<<(std::ostream& f, Action a);

int     adjacent_trees(State& s, int index, int player);
bool    isDiagonal(int from, int to);
bool    inSecondLayer(int from, int to);
bool    shadow_next_turn(State& state, int day, int id);
void	pass_day(State &state);
bool	seed_action(State &s, Action a, int player, int info);
bool	complete_action(State &s, Action a, int player, int info);
bool	grow_action(State &s, Action a, int player, int info);
bool	wait_action(State &s, Action a, int player, int info);

extern std::function<bool(State&, Action, int, int)> t[4];

double  score_action(State& s, Action a);