#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <climits>
#include <vector>
using namespace std;


string GetInfoString(const string& infoType) {
    string temp;
    cin >> temp;
    //basic input type/value validation for string, prevents empty strings from being input
    while (temp.length() <= 0) {
        cout << "Invalid " << infoType << ". Please re-enter a valid option.\n";
        cin >> temp;
    }
    return temp;
}

int GetInfoNum(const string& infoType, int min = INT_MIN, int max = INT_MAX) {
    //setting min and max to INT_MIN and INT_MAX in the arguments makes them optional while calling function
    string temp;
    cin >> temp;
    int num;
    //basic input type/value validation for string to num conversions
    while (true) {
        try {
            num = stoi(temp);
            if (num < min || num > max) {
                throw runtime_error("out of range");
            }
            break;
        } catch (...) {
            cout << "Invalid " << infoType << ". Please input a valid value";
            if (max != INT_MAX || min != INT_MIN) {
                cout << " between " << min << " and " << max << "." << endl;
            } else {
                cout << "." << endl;
            }
            cin >> temp;
        }
    }
    return num;
}

vector<double> CalcBatterStats(string& pname) { //Calculates wOBA, wRAA, & BABIP
    double weightedOnBaseAverage;
    double weightedRunsAboveAverage;
    double battingAverageOnBallsInPlay;
    const double wBB = 0.696;
    const double wHBP = 0.726;
    const double wSingles = 0.883;
    const double wDoubles = 1.244;
    const double wTriples = 1.569;
    const double wHR = 2.004;
    const double lgwOBA = 0.318;
    const double wOBAScale = 1.204;
    double uBB, HBP, numSingles, numDoubles, numTriples, homeRuns, AB, IBB, SF, PA, K;
    string playerName;
    //uBB = number of unintentional walks
    //IBB = intentional walks
    //HBP = hit by pitches
    //AB = at bats
    //PA = plate appearances
    //SF = sacrifice fly-outs
    //K = strikeouts


    cout << "Enter player name:" << endl;
    cin >> ws;
    getline (cin, playerName);
    pname = playerName;

    cout << "Enter number of intentional walks:" << endl;
    IBB = GetInfoNum("intentional walks");

    cout << "Enter number of total walks:" << endl;
    cin >> uBB;
    while (uBB < 0) {
        cout << "Invalid number of total walks. Please enter a number greater than or equal to zero.." << endl;
        cin >> uBB;
    }
    uBB = uBB - IBB;

    cout << "Enter number of hit by pitches:" << endl;
    cin >> HBP;
    while (HBP < 0) {
        cout << "Invalid number of hit by pitches. Please enter a number greater than or equal to zero." << endl;
        cin >> HBP;
    }

    cout << "Enter number of singles:" << endl;
    cin >> numSingles;
    while (numSingles < 0) {
        cout << "Invalid number of singles. Please enter a number greater than or equal to zero." << endl;
        cin >> numSingles;
    }

    cout << "Enter number of doubles:" << endl;
    cin >> numDoubles;
    while (numDoubles < 0) {
        cout << "Invalid number of doubles. Please enter a number greater than or equal to zero.." << endl;
        cin >> numDoubles;
    }

    cout << "Enter number of triples:" << endl;
    cin >> numTriples;
    while (numTriples < 0) {
        cout << "Invalid number of triples. Please enter a number greater than or equal to zero." << endl;
        cin >> numTriples;
    }

    cout << "Enter number of home runs:" << endl;
    cin >> homeRuns;
    while (homeRuns < 0) {
        cout << "Invalid number of home runs. Please enter a number greater than or equal to zero." << endl;
        cin >> homeRuns;
    }

    cout << "Enter number of at bats:" << endl;
    cin >> AB;
    while (AB < 0) {
        cout << "Invalid number of at bats. Please enter a number greater than or equal to zero." << endl;
        cin >> AB;
    }

    cout << "Enter number of plate appearances:" << endl;
    cin >> PA;
    while (PA < 0) {
        cout << "Invalid number of plate appearances. Please enter a number greater than or equal to zero." << endl;
        cin >> PA;
    }

    cout << "Enter number of sacrifice fly outs:" << endl;
    cin >> SF;
    while (SF < 0) {
        cout << "Invalid number of sacrifice fly outs. Please enter a number greater than or equal to zero." << endl;
        cin >> SF;
    }

    cout << "Enter the number of strikeouts:" << endl;
    cin >> K;
    while (K < 0) {
        cout << "Invalid number of strikeouts. Please enter a number greater than or equal to zero." << endl;
        cin >> K;
    }

    weightedOnBaseAverage = ((uBB * wBB) + (wHBP * HBP) + (wSingles * numSingles) + (wDoubles * numDoubles) +
                             (wTriples * numTriples) + (wHR * homeRuns)) / (AB + uBB + SF + HBP);
    weightedRunsAboveAverage = ((weightedOnBaseAverage - lgwOBA) / wOBAScale) * PA;
    battingAverageOnBallsInPlay = ((numSingles + numDoubles + numTriples) / (AB - K - homeRuns + SF));

    //cout << fixed << setprecision(3);
    //cout << playerName << " had a wOBA of " << weightedOnBaseAverage << " in 2023." << endl;
    //cout << playerName << " had a BABIP of " << battingAverageOnBallsInPlay << " in 2023." << endl;
    //cout << fixed << setprecision(1);
    //cout << playerName << " had a wRAA of " << weightedRunsAboveAverage << " in 2023." << endl;

    vector<double> stats{weightedOnBaseAverage, weightedRunsAboveAverage,battingAverageOnBallsInPlay};
    return stats;

}
double CalcPitcherStats(string& pname) { //Calculates FIP
    string pitcherName;
    int homeRuns, walks, hitByPitches, strikeouts;
    double inningsPitched;
    double FIP;
    const double fipConstant = 3.255;
    //FIP = fielding independent pitching

    cout << "Enter pitcher name:" << endl;
    cin >> ws;
    getline (cin, pitcherName);
    pname = pitcherName;

    cout << "Enter home runs:" << endl;
    cin >> homeRuns;
    while (homeRuns < 0) {
        cout << "Invalid number of home runs.  Please enter a different number:" << endl;
        cin >> homeRuns;
    }

    cout << "Enter the number of walks:" << endl;
    cin >> walks;
    while (walks < 0) {
        cout << "Invalid number of walks.  Please enter a different number:" << endl;
        cin >> walks;
    }

    cout << "Enter the number of hit by pitches:" << endl;
    cin >> hitByPitches;
    while (hitByPitches < 0) {
        cout << "Invalid number of hit by pitches.  Please enter a different number:" << endl;
        cin >> hitByPitches;
    }

    cout << "Enter the number of strikeouts:" << endl;
    cin >> strikeouts;
    while (strikeouts < 0) {
        cout << "Invalid number of strikeouts.  Please enter a different number:" << endl;
        cin >> strikeouts;
    }

    cout << "Enter the number of innings pitched:" << endl;
    cin >> inningsPitched;
    while (inningsPitched < 0) {
        cout << "Invalid number of innings pitched.  Please enter a different number:" << endl;
        cin >> inningsPitched;
    }

    FIP = (((13 * double(homeRuns)) + (3 * (walks + hitByPitches)) - (2 * strikeouts)) / inningsPitched) + fipConstant;

    //cout << fixed << setprecision(2);
    //cout << pitcherName << "'s FIP is " << FIP << endl;
    return FIP;
}

void CalcTeamStats() { // Calculates & Interprets Pythagorean Winning Percentage
    string teamName;
    int runsScored, runsAllowed, numGames, losses;
    double base, exp, winPercentage, expectedWins, winsOverExpected, winsUnderExpected, wins, realWinPercentage;

    cout << "Enter team name:" << endl;
    cin >> ws;
    getline (cin, teamName);

    cout << "Enter the total runs scored by the " << teamName << endl;
    cin >> runsScored;
    while (runsScored < 0) {
        cout << "Invalid number of runs scored.  Please enter a different number:" << endl;
        cin >> runsScored;
    }

    cout << "Enter the total runs allowed by the " << teamName << endl;
    cin >> runsAllowed;
    while (runsAllowed < 0) {
        cout << "Invalid number of runs allowed.  Please enter a different number:" << endl;
        cin >> runsAllowed;
    }

    cout << "Enter the total number of wins by the " << teamName << endl;
    cin >> wins;
    while (wins < 0) {
        cout << "Invalid number of wins.  Please enter a different number:" << endl;
        cin >> wins;
    }

    cout << "Enter the total of losses by the " << teamName << endl;
    cin >> losses;
    while (losses < 0) {
        cout << "Invalid number of losses.  Please enter a different number:" << endl;
        cin >> losses;
    }

    numGames = wins + losses;
    realWinPercentage = wins / numGames;
    base = ((double)runsScored + runsAllowed) / numGames;
    exp = pow(base, 0.287);
    winPercentage = (pow(runsScored, exp)) / (pow(runsScored, exp) + pow(runsAllowed, exp));
    expectedWins = winPercentage * numGames;

    if (expectedWins < wins) {
        winsOverExpected = wins - expectedWins;
        cout << fixed << setprecision(3);
        cout << "The " << teamName << " pythagorean win percentage is " << winPercentage << ", while their real win percentage is " << realWinPercentage << "." << endl;
        cout << fixed << setprecision(0);
        cout << "The " << teamName << " over-preformed and won " << winsOverExpected << " more games than was expected." << endl;
    }

    else if (expectedWins > wins) {
        winsUnderExpected = expectedWins - wins;
        cout << fixed << setprecision(3);
        cout << "The " << teamName << " pythagorean win percentage is " << winPercentage << ", while their real win percentage is " << realWinPercentage << "." << endl;
        cout << fixed << setprecision(0);
        cout << "The " << teamName << " under-preformed and lost " << winsUnderExpected << " more games than was expected." << endl;
    }
}


int main() {
    cout << "Welcome to the advanced baseball stats calculator." << endl
         << "Would you like to know about a batter, pitcher, or a team?" << endl;
    cout << "For batter enter 1" << endl << "For pitcher enter 2" << endl << "For team enter 3" << endl;
    int statsSelection;
    cin >> statsSelection;
    while (statsSelection < 1 || statsSelection > 3) {
        cout << "Invalid selection.  Please enter 1 for batter, 2 for pitcher, or 3 for team." << endl;
        cin >> statsSelection;
    }

    if (statsSelection == 1) {
        string p1name;
        vector<double> batter1 = CalcBatterStats(p1name);
        cout << "Would you like to compare batter stats with another batter? Enter 1 for yes and 2 for no.";
        int option = GetInfoNum("option", 1, 2);
        if (option == 1) {
            string p2name;
            vector<double> batter2 = CalcBatterStats(p2name);
            cout << fixed << setprecision(3);
            cout << p1name << " had a wOBA of " << batter1[0] << " while " << p2name << " had a wOBA of " << batter2[0] << "." << endl;
            cout << p1name << " had a BABIP of " << batter1[2] << " while " << p2name << " had a BABIP of " << batter2[2] << "." << endl;
            cout << fixed << setprecision(1);
            cout << p1name << " had a wRAA of " << batter1[1] << " while " << p2name << " had a wRAA of " << batter2[1] << "." << endl;

        } else if (option == 2) {
            cout << fixed << setprecision(3);
            cout << p1name << " had a wOBA of " << batter1[0] << " in 2023." << endl;
            cout << p1name << " had a BABIP of " << batter1[2] << " in 2023." << endl;
            cout << fixed << setprecision(1);
            cout << p1name << " had a wRAA of " << batter1[1] << " in 2023." << endl;
        }

    } else if (statsSelection == 2) {
        string p1name;
        double pitcher1 = CalcPitcherStats(p1name);
        cout << "Would you like to compare pitcher stats with another pitcher? Enter 1 for yes and 2 for no.";
        int option = GetInfoNum("option", 1, 2);
        if (option == 1) {
            string p2name;
            double pitcher2 = CalcPitcherStats(p2name);
            cout << fixed << setprecision(2);
            cout << p1name << "'s FIP is " << pitcher1 << " while " << p2name << " had a FIP of " << pitcher2 << "." << endl;
        } else if (option == 2) {
            cout << fixed << setprecision(2);
            cout << p1name << "'s FIP is " << pitcher1 << endl;
        }
    } else if (statsSelection == 3) {
        CalcTeamStats();
    }


}
