#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>


#pragma GCC optimize("Ofast", "unroll-loops", "inline")
#pragma GCC option("arch=native", "tune=native")
#define NDEBUG

#include <stdexcept>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <random>
#include <array>
#include <sstream>
#include <algorithm>
#include <functional>
#include <fstream>
#include <string>
#include "common.hpp"

#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>


State   GenerateMap() {
    State s;

    return s;
}

int		get_cost(State &s, Action a) {
    int player = s.info.player;
    
    switch (a.type)
    {
    case Action_type::seed :
		return (s.info.trees_size[player][0]);
    case Action_type::grow :
		switch (s.grid[a.from].size)
		{
		case 0:
			return (1 + s.info.trees_size[player][1]);
		case 1:
			return (3 + s.info.trees_size[player][2]);
		case 2:
			return (7 + s.info.trees_size[player][3]);
		}
    case Action_type::complete :
		return 4;
    case Action_type::wait :
		return 0;
    default:
		return 0;
    }
}

Action	extract_action(std::string str) {
	Action a;
	char skip[20];
	int from, to;

	switch (str[0]) {
		case 'S' :
			sscanf(str.c_str(), "%s%d%d", skip, &from , &to);
			a.from = from;
			a.to = to;
			a.type = Action_type::seed;
			break;
		case 'G' :
			sscanf(str.c_str(), "%s%d", skip, &from);
			a.from = from;
			a.type = Action_type::grow;			
		break;
		case 'W' :
			a.type = Action_type::wait;
			break;
		case 'C' :
			sscanf(str.c_str(), "%s%d", skip, &from);
			a.from = from;
			a.type = Action_type::complete;
			break;
	}
	
	return a;
}

void	generate_all_actions_no_score(State &s, std::vector<Action>& actions) {
    unsigned char prix;
	int player = s.info.player;

	if (s.final_state())
		return ;

    actions.emplace_back(Action_type::wait, 0, 0, 0);
	if (s.info.wait[player])
		return ;
    for (unsigned char i = 0; i < 37; i++) {
        if (!s.grid[i].empty and s.grid[i].player == player and !s.grid[i].sleep) {
            switch (s.grid[i].size)
            {
                case 0: {
                    prix = 1 + s.info.trees_size[player][1];
                    if (prix <= s.info.sun[player]) {
                        Action a(Action_type::grow, i, 0, prix);
                        actions.push_back(a);
                    }
                    break;
                }
                case 1: {
                    prix = 3 + s.info.trees_size[player][2];
                    if (prix <= s.info.sun[player]) {
                        Action a(Action_type::grow, i, 0, prix);
                        actions.push_back(a);
                    }
                    prix = s.info.trees_size[player][0];
                    if (prix > s.info.sun[player])
                        break;
                    for (int j = 0; j < n[i].size[0]; j++) {
                        int to = n[i].neigbours[j];
                        if (s.grid[to].empty and s.grid[to].richness != 0) {
                            Action a(Action_type::seed, i, to, prix);
                            actions.push_back(a);
                        }
                    }
                    break;
                }
                case 2: {
                    prix = 7 + s.info.trees_size[player][3];
                    if (prix <= s.info.sun[player]) {
                        Action a(Action_type::grow, i, 0, prix);
                        actions.push_back(a);
                    }                
                    prix = s.info.trees_size[player][0];
                    if (prix > s.info.sun[player])
                        break;
                    for (int j = 0; j < n[i].size[1]; j++) {
                        int to = n[i].neigbours[j];
                        if (s.grid[to].empty and s.grid[to].richness != 0) {
                            Action a(Action_type::seed, i, to, prix);
                            actions.push_back(a);
                        }
                    }
                    break;
                }
                case 3: {
                    if (s.info.sun[player] >= 4) {
                        Action a(Action_type::complete, i, 0, 4);
                        actions.push_back(a);
                    }
                    prix = s.info.trees_size[player][0];
                    if (prix > s.info.sun[player])
                        break;
                    for (int j = 0; j < n[i].size[2]; j++) {
                        int to = n[i].neigbours[j];
                        if (s.grid[to].empty and s.grid[to].richness != 0) {
                            Action a(Action_type::seed, i, to, prix);
                            actions.push_back(a);
                        }
                    }
                    break;
                }
                default: {
                    std::cerr << "Error in parser" << std::endl;
                    break;
                }
            }
        }
    }
}

State   parse_state(int i) {
    std::string route = "map/map" + std::to_string(i) + ".txt";

    std::ifstream in(route);
    std::streambuf *cinbuf = std::cin.rdbuf();
    std::cin.rdbuf(in.rdbuf());

    std::array<Cell, 37>    map;
    Info                    info;

    // std::streambuf *psbuf;
    // std::stringstream new_stream;

    // psbuf = new_stream.rdbuf();
    // std::cout.rdbuf(psbuf);

    int numberOfCells; // 37
    std::cin >> numberOfCells; std::cin.ignore();

    for (int i = 0; i < numberOfCells; i++) {
        int index, richness, neigh; 
        std::cin >> index >> richness >> neigh >> neigh >> neigh >> neigh >> neigh >> neigh; std::cin.ignore();
        map[index].richness = richness;
        map[index].empty = true;
    }
    info.wait[0] = false;

    int day; // the game lasts 24 days: 0-23
    std::cin >> day; std::cin.ignore();
    int nutrients; // the base score you gain from the next COMPLETE action
    std::cin >> nutrients; std::cin.ignore();

    info.days = day;
    info.nutriments = nutrients;

    int sun;
    int score;

    std::cin >> sun >> score; std::cin.ignore();
    info.player = 0;
    info.sun[0] = sun;
    info.score[0] = score;

    int wait;
    std::cin >> sun >> score >> wait; std::cin.ignore();
    info.sun[1] = sun;
    info.score[1] = score;
    info.wait[1] = wait;

    int numberOfTrees;
    std::cin >> numberOfTrees; std::cin.ignore();

    info.trees_size[0].fill(0);
    info.trees_size[1].fill(0);
    info.trees_richness[0].fill(0);
    info.trees_richness[1].fill(0);
    //std::cout << "WTF " << numberOfTrees << std::endl;
    for (int i = 0; i < numberOfCells; i++) {
        map[i].empty = true;
    }
    for (int i = 0; i < numberOfTrees; i++) {
        int cellIndex, size;
        int isMine, isDormant;
        std::cin >> cellIndex >> size >> isMine >> isDormant; std::cin.ignore();
        map[cellIndex].size = size;
        map[cellIndex].player = !isMine;
        map[cellIndex].sleep = isDormant;
        map[cellIndex].empty = false;
        info.trees_size[0][size] += isMine;
        info.trees_size[1][size] += !isMine;

        info.trees_richness[!isMine][map[cellIndex].richness - 1]++;
    }

    int numberOfPossibleMoves;
    std::cin >> numberOfPossibleMoves; std::cin.ignore();
    std::string 				possibleMove_ia;
    std::vector<std::string>	possibleMoves_ia;

    for (int i = 0; i < numberOfPossibleMoves; i++) {
        getline(std::cin, possibleMove_ia);
        possibleMoves_ia.emplace_back(possibleMove_ia);
        //std::cerr << "IA " << possibleMove_ia << std::endl;
    }

    std::cin.rdbuf(cinbuf);   //reset to standard input again

    info.player = 0;

    return (State(info, map));
}

static void    print_map(int fd, State& s) {
    dprintf(fd, "37\n");
	for (int i = 0; i < 37; i++) {
		int richness = s.grid[i].richness;
        dprintf(fd, "%d %d", i, richness);
        for (int j =0 ; j < 6; j++) {
            if (j < n[i].size[0]) {
                dprintf(fd, " %d", n[i].neigbours[j]);
            } else {
                dprintf(fd, " -1");
            }
        }
        dprintf(fd, "\n");
	}
}
static void     print_update(int fd, State& s) {
    int player = s.info.player;
    
    int day = s.info.days;
    int nutrients = s.info.nutriments;

    dprintf(fd, "%d\n", day);
    dprintf(fd, "%d\n", nutrients);

	int sun = s.info.sun[player];
	int score = s.info.score[player];

    dprintf(fd, "%d %d\n", sun, score);

	int wait = s.info.wait[!player];
	sun = s.info.sun[!player];
	score = s.info.score[!player];
    dprintf(fd, "%d %d %d\n", sun, score, wait);

	int nb_trees = s.info.trees_size[0][0] + s.info.trees_size[0][1] + s.info.trees_size[0][2] + s.info.trees_size[0][3]
		+ s.info.trees_size[1][0] + s.info.trees_size[1][1] + s.info.trees_size[1][2] + s.info.trees_size[1][3];
    dprintf(fd, "%d\n", nb_trees);

	for (int i = 0; i < 37; i++) {
		if (!s.grid[i].empty) {
			int size = s.grid[i].size;
			int isMine = s.grid[i].player == player;
			int sleep = s.grid[i].sleep;
            dprintf(fd, "%d %d %d %d\n", i, size, isMine, sleep);
		}
	}

    std::vector<Action> actions;
    generate_all_actions_no_score(s, actions);
    dprintf(fd, "%lu\n", actions.size());
	for (Action& a : actions) {
        std::ostringstream stream;
        stream << a;
        dprintf(fd, "%s\n", stream.str().c_str());
	}
}

double  exec(State& s, const char* algo1, const char *algo2) {
    pid_t pid = 0;
    pid_t pid2 = 0;
    int inpipefd_algo1[2];
    int outpipefd_algo1[2];

    int inpipefd_algo2[2];
    int outpipefd_algo2[2];



    int status;

    pipe(inpipefd_algo1);
    pipe(outpipefd_algo1);
	pipe(inpipefd_algo2);
    pipe(outpipefd_algo2);

    pid = fork();
    if (pid == 0)
    {
        close(outpipefd_algo1[1]);
        dup2(outpipefd_algo1[0], STDIN_FILENO);
        close(inpipefd_algo1[0]);
        dup2(inpipefd_algo1[1], STDOUT_FILENO);

        execl(algo1, "LUL", (char*) NULL);
        std::cerr << "NOT OK " << std::endl;
        exit(1);
    }

	pid2 = fork();
	if (pid2 == 0)
	{
        close(outpipefd_algo2[1]);
        dup2(outpipefd_algo2[0], STDIN_FILENO);
        close(inpipefd_algo2[0]);
        dup2(inpipefd_algo2[1], STDOUT_FILENO);

        execl(algo2, "LUL", (char*) NULL);
        std::cerr << "NOT OK " << std::endl;
        exit(1);
	}

    close(outpipefd_algo1[0]);
    close(inpipefd_algo1[1]);
	close(outpipefd_algo2[0]);
    close(inpipefd_algo2[1]);


	print_map(outpipefd_algo1[1], s);
	print_map(outpipefd_algo2[1], s);
	char buffer[128];
	int len = 0;
	while (!s.final_state()) {
		print_update(outpipefd_algo1[1], s);
		len = read(inpipefd_algo1[0], buffer, 128);
		buffer[len] = '\0';

		Action algo1_action = extract_action(buffer);
		algo1_action.cost = get_cost(s, algo1_action);
		s.do_action(algo1_action);

		print_update(outpipefd_algo2[1], s);
		len = read(inpipefd_algo2[0], buffer, 128);
		buffer[len] = '\0';

		Action algo2_action = extract_action(buffer);
		algo2_action.cost = get_cost(s, algo2_action);
		s.do_action(algo2_action);
	}

	kill(pid, SIGKILL);
	kill(pid2, SIGKILL);
    waitpid(pid, &status, 0);
    waitpid(pid2, &status, 0);

    if (s.info.score[0] > s.info.score[1])
        return 1;
    if (s.info.score[0] == s.info.score[1])
        return 0.5;
    return 0;
}

int     main(int argc, char **argv) {
    double victoire = 0;

    if (argc != 3) {
        std::cerr << "NEED TO PLAYER TO EXECUTE THE CODE" << std::endl;
        return 0;
    }

    std::string p1 = argv[1];
    std::string p2 = argv[2];

    p1 = "./player/" + p1;
    p2 = "./player/" + p2;

    std::cerr << argv[1] << " vs " << argv[2] << std::endl;

    for (int i = 0; i < 20; i++) {
        State s = parse_state(i);
        victoire += exec(s, p1.c_str(), p2.c_str());
    }
    for (int i = 0; i < 20; i++) {
        State s = parse_state(i);
        victoire += exec(s, p2.c_str(), p1.c_str());
    }
    std::cout << argv[1] << " : " << victoire  << " " << argv[2] << " : " << 40 - victoire << std::endl;

}



// int     main(void) {


//     std::cout << exec("./algo1") << std::endl;
//     return 0;
// }