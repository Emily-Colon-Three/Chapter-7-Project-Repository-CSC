#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void getTeams(string, vector<string>&);

int findWinner(string, vector<string>);

int main()
{
    vector<string> teamList;
    vector<string> winList;

    cout << "Welcome to the World Series Champions Program! Input a team name, and looking from 1903 to 2012, you will be told how many times it has won the World Series!\n";

    getTeams("Teams.txt", teamList);
    getTeams("WorldSeriesWinners.txt", winList);

    cout << "Here are the teams:\n";

    for (auto& i : teamList) // Goes through teamList
    {
        cout << i << endl;
    }

    string teamInput;

    cout << endl << "Now, input one of the above teams, or enter \"QUIT\" to quit out of program:\n";
    getline(cin, teamInput);

    while (teamInput != "QUIT")
    {
        int timesWon = 0;
        timesWon = findWinner(teamInput, winList);

        cout << "That team has won the World Series a total of " << timesWon << " times between 1903 and 2012.\n";

        cout << "Enter another team name, or quit program.\n";
        getline(cin, teamInput);
    }

    return 0;
}

/*
    Summary: Gets the lines from a file, usually for a list of teams of some kind, and puts them through a reference to a string vector in parent function.
    Parameters: A string which serves as the name of the file, fileName, and a string vector reference for a list of teams, teams.
    Return: None.
    Preconditions: fileName should be a real file. The string vector passed in as reference should be empty.
    Postconditions: Each line of the opened file will become an element in the vector passed in as teams. If the file fails to open, it prints an error message and exits program.
*/
void getTeams(string fileName, vector<string>& teams)
{
    fstream text(fileName);

    if (!text) // If file fails to open
    {
        cout << "ERROR: File Teams.txt or WorldSeriesWinners.txt could not be found.\n";
        exit(1);
    }

    string line;
    while (getline(text, line))
    {
        teams.push_back(line);
    }

    text.close();
    return;
}

/*
    Summary: Looks through a list of winning teams across a number of years, and finds how many times a team's name shows up in that list.
    Parameters: The (string) name of the team being searched for wins, teamName, and a string vector of winning teams, winningTeams.
    Return: The number of times a team has won in the World Series, timesWon.
    Preconditions: winningTeams is arranged in a manner of victories, where teams show up multiple times for their multiple victories.
    Postconditions: Will only actually return 0; this function is broken, and no fix was found for it.
*/
int findWinner(string teamName, vector<string> winningTeams)
{
    int timesWon = 0;

    for (string name : winningTeams)
    {
        if (teamName == name)
        {
            timesWon++;
        }
    }

    return timesWon;
}
