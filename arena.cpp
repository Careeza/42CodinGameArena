#include "simulation.hpp"

#include <iostream>
#include <dirent.h>
#include <signal.h>

# define PLAYOUT 20

# define CSI "\033["
# define CSI_GREEN CSI "32;01m"
# define CSI_WHITE CSI "37;01m"
# define CSI_BLUE CSI "34;01m"
# define CSI_YELLOW CSI "33;01m"
# define CSI_RED CSI "31m"
# define CSI_RESET CSI "0m"

# define MAX_EMPTY_CELLS 10
# define MAX_TREES 4

int     get_opp(int pos) {
    int opp_pos;

    if (pos == 0) {
        opp_pos = 0;
    } else if (pos <= 6) {
        opp_pos = pos + 3;
        if (opp_pos > 6) {
            opp_pos -= 6;
        }
    } else if (pos <= 18) {
        opp_pos = pos + 6;
        if (opp_pos > 18) {
            opp_pos -= 12;
        }
    } else {
        opp_pos = pos + 9;
        if (opp_pos > 36) {
            opp_pos -= 18;
        }
    }
    return opp_pos;
}

int     next_coord(int pos) {
    int next_coord;

    if (pos == 0) {
        next_coord = 0;
    } else if (pos <= 6) {
        next_coord = pos + 1;
        if (next_coord > 6) {
            next_coord = 1;
        }
    } else if (pos <= 18) {
        next_coord = pos + 1;
        if (next_coord > 18) {
            next_coord = 7;
        }
    } else {
        next_coord = pos + 1;
        if (next_coord > 36) {
            next_coord = 19;
        }
    }
    return next_coord;
}

int     prev_coord(int pos) {
    int next_coord;

    if (pos == 0) {
        next_coord = 0;
    } else if (pos <= 6) {
        next_coord = pos - 1;
        if (next_coord < 1) {
            next_coord = 6;
        }
    } else if (pos <= 18) {
        next_coord = pos - 1;
        if (next_coord < 7) {
            next_coord = 18;
        }
    } else {
        next_coord = pos - 1;
        if (next_coord < 19) {
            next_coord = 36;
        }
    }
    return next_coord;
}

State   GenerateMap() {
    State state;

    state.grid[0] = {3};
    for (int i = 0; i < 36; i++) {
        int pos = n[0].neigbours[i];
        state.grid[pos].empty = true;
        if (i < 6) {
            state.grid[pos].richness = 3;
        } else if (i < 18) {
            state.grid[pos].richness = 2;
        } else {
            state.grid[pos].richness = 1;
        }
    }

    int wantedEmptyCells = random_index(0, MAX_EMPTY_CELLS);
    int actualEmptyCells = 0;

    state.info.trees_size.fill({0, 0, 0, 0});
    state.info.trees_richness.fill({0, 0, 0});

    while (actualEmptyCells < wantedEmptyCells - 1) {
        int coord = random_index(0, 37);

        if (state.grid[coord].richness != 0) {
            state.grid[coord].richness = 0;
            state.grid[get_opp(coord)].richness = 0;

            actualEmptyCells += 2;
        }
    }

    int actualTree = 0;
    while (actualTree < MAX_TREES) {
        int coord = random_index(n[0].size[1] + 1, n[0].size[2]);

        if (!state.grid[next_coord(coord)].empty || !state.grid[prev_coord(coord)].empty)
            continue;
        if (!state.grid[next_coord(next_coord(coord))].empty || !state.grid[prev_coord(prev_coord(coord))].empty)
            continue;

        if (state.grid[coord].richness != 0 and state.grid[coord].empty) {
            state.info.trees_size[0][1] += 1;
            state.info.trees_size[1][1] += 1;
            state.grid[coord].size = 1;
            state.grid[get_opp(coord)].size = 1;
            state.grid[coord].empty = false;
            state.grid[get_opp(coord)].empty = false;
            state.grid[coord].player = 0;
            state.grid[get_opp(coord)].player = 1;


            actualTree += 2;
        }
    }
    state.info.nutriments = 20;
    state.info.days = 0;
    state.info.sun[0] = 2;
    state.info.sun[1] = 2;
    state.info.score[0] = 0;
    state.info.score[1] = 0;
    state.info.player = 0;
    state.info.wait[0] = 0;
    state.info.wait[1] = 0;

    return state;
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

std::ofstream   score_log;

double  exec(State s, const char* algo1, const char *algo2) {
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
        if (!s.info.wait[0]) {
            print_update(outpipefd_algo1[1], s);
            len = read(inpipefd_algo1[0], buffer, 128);
            buffer[len] = '\0';

            Action algo1_action = extract_action(buffer);
            algo1_action.cost = get_cost(s, algo1_action);
            s.do_action(algo1_action);
        } else {
            s.do_action({Action_type::wait, 0, 0, 0});
        }
        if (!s.info.wait[1]) {
            print_update(outpipefd_algo2[1], s);
            len = read(inpipefd_algo2[0], buffer, 128);
            buffer[len] = '\0';

            Action algo2_action = extract_action(buffer);
            algo2_action.cost = get_cost(s, algo2_action);
            s.do_action(algo2_action);
        } else {
            s.do_action({Action_type::wait, 0, 0, 0});
        }

	}

	kill(pid, SIGKILL);
	kill(pid2, SIGKILL);
    waitpid(pid, &status, 0);
    waitpid(pid2, &status, 0);

    int score_p1 = s.info.score[0] + s.info.sun[0] / 3;
    int score_p2 = s.info.score[1] + s.info.sun[1] / 3;


    score_log << algo1 << " : " << score_p1 << " vs " << algo2 << " : " << score_p2 << std::endl;
    if (score_p1 > score_p2) {
        return 1;
    } else if (score_p1 == score_p2) {
        int nb_treeP1 = s.info.trees_size[0][0] + s.info.trees_size[0][1] + s.info.trees_size[0][2] + s.info.trees_size[0][3];
        int nb_treeP2 = s.info.trees_size[1][0] + s.info.trees_size[1][1] + s.info.trees_size[1][2] + s.info.trees_size[1][3];

        if (nb_treeP1 > nb_treeP2)
            return 1;
        else if (nb_treeP1 == nb_treeP2) {
            return 0.5;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

void    match(std::string p1_name, std::string p2_name) {
    double victoire = 0;

    std::string log_socre_str = "log/" + p1_name + p2_name + "score.txt";

    score_log.open(log_socre_str);
    std::string p1_exec = "./opponents/" + p1_name;
    std::string p2_exec = "./opponents/" + p2_name;
    printf("%s", CSI_WHITE);
    std::cout << std::setw(58);
    std::cout << p1_name << " vs " << p2_name << std::endl;
    printf("%s", CSI_RESET);

    for (int i = 0; i < PLAYOUT; i++) {
        State s = GenerateMap();
        victoire += exec(s, p1_exec.c_str(), p2_exec.c_str());
        victoire += 1 - exec(s, p2_exec.c_str(), p1_exec.c_str());

        int nb_partie = 2 * (i + 1); 

        int ratio_p1 = victoire * 100 / nb_partie;
        int ratio_p2 = 100 - ratio_p1;

        std::string ratio_p1_str(ratio_p1, '#');
        std::string ratio_p2_str(ratio_p2, '#');

        printf("\r%s %.1f %s%s %s%s%s%s%s%s %s%s %.1f%s", CSI_WHITE, victoire, p1_name.c_str(), CSI_RESET, CSI_GREEN, ratio_p1_str.c_str(), CSI_RESET, CSI_RED, ratio_p2_str.c_str(), CSI_RESET, CSI_WHITE, p2_name.c_str(), (nb_partie - victoire), CSI_RESET);
        fflush(stdout);
    }
    printf("%s", CSI_WHITE);
    std::cout << std::setw(56);
    std::cout << std::endl << p1_name << " : " << victoire  << " " << p2_name << " : " << PLAYOUT * 2 - victoire << std::endl << std::endl;
    printf("%s", CSI_RESET);
}

std::vector<std::string>    get_oppenents(std::string p1) {
    DIR *folder;
    struct dirent *entry;
    std::vector<std::string>    opponents;

    folder = opendir("opponents");

    while( (entry=readdir(folder)) )
    {
        std::string new_opponent = entry->d_name;

        if (new_opponent.compare(".") == 0 or new_opponent.compare("..") == 0 or new_opponent.compare(p1) == 0 or new_opponent.compare(".empty") == 0)
            continue;
        opponents.push_back(new_opponent);
    }
    return opponents;
}

int     main(int argc, char **argv) {

    if (argc == 2) {
        std::vector<std::string> opponents = get_oppenents(argv[1]);
        for (std::string opponent : opponents) {
            match(argv[1], opponent);
        }
    } else if (argc > 2) {
        for (int i = 2; i < argc; i++) {
            match(argv[1], argv[i]);
        }
    } else {
        printf("%s", CSI_RED);
        std::cerr << "Usage : ./arena exe\t\t\t(launch the exe vs all the other exe in player folder)" << std::endl;
        std::cerr << "        ./arena exe1 exe2 exe3 ..\t(launch the exe1 vs exe2, exe3, ...)" << std::endl;
        printf("%s", CSI_RESET);
    }
    return 0;
}