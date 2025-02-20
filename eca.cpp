#include <iostream>
#include <string>

using namespace std;

char applyRule(int rule, char left, char middle, char right) {
    if (left == '0' && middle == '0' && right == '0') {
        return (rule & 1) ? '1' : '0';
    }
    else if (left == '0' && middle == '0' && right == '1') {
        return (rule & 2) ? '1' : '0';
    }
    else if (left == '0' && middle == '1' && right == '0') {
        return (rule & 4) ? '1' : '0';
    }
    else if (left == '0' && middle == '1' && right == '1') {
        return (rule & 8) ? '1' : '0';
    }
    else if (left == '1' && middle == '0' && right == '0') {
        return (rule & 16) ? '1' : '0';
    }
    else if (left == '1' && middle == '0' && right == '1') {
        return (rule & 32) ? '1' : '0';
    }
    else if (left == '1' && middle == '1' && right == '0') {
        return (rule & 64) ? '1' : '0';
    }
    else if (left == '1' && middle == '1' && right == '1') {
        return (rule & 128) ? '1' : '0';
    }
    return '0';
}

string generateNew(const string& old, int rule) {
    string newLine(old.size(), ' ');

    for (int i = 0; i < old.size(); i++) {
        char left = old[(i + old.size() - 1) % old.size()];
        char middle = old[i];
        char right = old[(i + 1) % old.size()];

        char nextCell = applyRule(rule, left, middle, right);
        newLine[i] = nextCell;
    }

    return newLine;
}

void drawAutomaton(const string& line) {
    for (int i = 0; i < line.size(); i++) {
        char cell = line[i];
        if (cell == '1') {
            cout << "*";
        } else {
            cout << " ";
        }
    }
    cout << endl;
}

int main() {
    string initialLine;
    cout << "Please enter the initial line of cells: ";
    cin >> initialLine;

    int rule;
    cout << "Please enter the rule number (0-255): ";
    cin >> rule;

    int generations;
    cout << "Please enter the number of generations to simulate: ";
    cin >> generations;

    drawAutomaton(initialLine);

    for (int l = 1; l <= generations; l++) {
        string newLine = generateNew(initialLine, rule);
        drawAutomaton(newLine);
        initialLine = newLine;
    }

    return 0;
}
