#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 100;
int population[N][8];
int F[N];
int S[N];
// Fitness function
int checkConflicts(const int* queens) {
    int conflicts = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            // Check rows
            if (queens[i] == queens[j]) {
                conflicts++;
            }
            // Check diagonals
            if (abs(queens[i] - queens[j]) == abs(i - j)) {
                conflicts++;
            }
        }
    }
    return conflicts;
}


void selection(int matingPool[N][8]) {
    // Calculate total fitness
    int totalFitness = 0;
    for (int i = 0; i < N; i++) {
        totalFitness += F[i];
    }

    // Calculate Intervals
    S[0] = F[0];
    for (int i = 1; i < N; i++) {
        S[i] = S[i - 1] + F[i];
    }


    for (int i = 0; i < N; i++) {
        int b = rand() % totalFitness;
        for (int j = 0; j < N; j++) {
            if (b < S[j]) {
                for (int k = 0; k < 8; k++) {
                    matingPool[i][k] = population[j][k];
                }
                break;
            }
        }
    }
}


int matingPool[N][8];
int offspring[N][8];
void crossover() {
    for (int i = 0; i < N; i += 2) {
        int r1 = rand() % 7 + 1;
        int r2 = rand() % 7 + 1;

        for (int j = 0; j < 8; j++) {
            if (j < r1 || j >= r2) {
                // remain same
                offspring[i][j] = matingPool[i][j];
                offspring[i + 1][j] = matingPool[i + 1][j];
            } else {
                // exchange
                offspring[i][j] = matingPool[i + 1][j];
                offspring[i + 1][j] = matingPool[i][j];
            }
        }
    }
}


void mutation() {
    double p_m = 0.00005;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 8; j++) {
            if (static_cast<double>(rand()) / RAND_MAX < p_m) {
                offspring[i][j] = rand() % 8;
            }
        }
    }
}


int calculateFitness(const int* queens) {
    int conflicts = checkConflicts(queens);
    return 28 - conflicts;
}



int main() {
    srand(time(0));

    // Step 1: Generation of the initial population
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 8; j++) {
            population[i][j] = rand() % 8;
        }
    }

    // Step 2: Selection
    // a) Evaluation
    int iterations = 0;
    bool solutionFound = false;
    for (int i = 0; i < N; i++) {
        F[i] = calculateFitness(population[i]);

        if (F[i] == 28) {
            cout << "Solution Found in Parent G" << i + 1 << " with configuration: ";
            for (int j = 0; j < 8; j++) {
                cout << population[i][j] << " ";
            }
            cout << endl;
            solutionFound = true;
            break;
        }
    }

    while (!solutionFound && iterations < 100000000) {

    // b) Roulette wheel
    selection(matingPool);
    // Step 3: Crossover
    crossover();
    // Step 4: Mutation
    mutation();

    /* print offsprings
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 8; j++) {
            cout << offspring[i][j] << " ";
        }
        cout << endl;
    }

*/
// Recalculate fitness for the offspring
		for (int i = 0; i < N; i++) {
   			F[i] = calculateFitness(offspring[i]);
	}

	// Check for solution in the offspring population
	for (int i = 0; i < N; i++) {
    	if (F[i] == 28) {
        	cout << "Solution found in iteration " << iterations + 1 << " with configuration: ";
        	for (int j = 0; j < 8; j++) {
            	cout << offspring[i][j] << " ";
        	}
        	cout << " ---- Score: " << F[i] << endl;
        	solutionFound = true;
        	break;
    		}
	}
        iterations++;
        if (!solutionFound) {
            // copy population
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < 8; j++) {
                    population[i][j] = offspring[i][j];

                }
            }
        }
    }

    if (!solutionFound) {
        cout << "No solution found within " << iterations << " iterations." << endl;

    }

    return 0;
}

