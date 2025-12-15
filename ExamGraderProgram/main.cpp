#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int NUMBERQUESTIONS = 20; // defines 20 as the number of questions for the exam this program will be used for.

void getAnswers(string, char[]);

int gradeExam(char[], char[], int[], char[][NUMBERQUESTIONS]);

void writeReport(char[][NUMBERQUESTIONS], int[], int);

int main()
{
    // Character arrays for the exam's answer key and the student's given answers.
    char examAnswers[NUMBERQUESTIONS];
    char studentAnswers[NUMBERQUESTIONS];

    // 2D array to hold correct answers and student answers for comparison
    char answerComparison[2][NUMBERQUESTIONS];

    int incorrectNumbers[NUMBERQUESTIONS]; // question numbers that the student got wrong
    int numWrong = 0; // Number of wrong answers

    getAnswers("CorrectAnswers.txt", examAnswers);
    getAnswers("StudentAnswers.txt", studentAnswers);

    numWrong = gradeExam(examAnswers, studentAnswers, incorrectNumbers, answerComparison);

    writeReport(answerComparison, incorrectNumbers, numWrong);

    return 0;
}

/*
    Summary: Opens file, and dumps the answers into a character array, passed in via reference. If the file fails to open, an error is given and the program terminates.
    Parameters: a string for the name of the file to open, fileName, and a character array from main for a list of answers, answerArray[].
    Return: None.
    Preconditions: fileName must be the name of a real file, or program will fail. answerArray should preferably be empty.
    Postconditions: If the file fails to open, an error message is printed, and exit() is called to terminate program. The referenced character array is updated as a result of this function.
*/
void getAnswers(string fileName, char answerArray[])
{
    fstream answerFile(fileName);

    // Error detection
    if (!answerFile)
    {
        cout << "ERROR: CorrectAnswers.txt or StudentAnswers.txt could not be opened.\n";
        exit(1);
    }

    string answer;
    int i = 0;
    while (getline(answerFile, answer))
    {
        answerArray[i] = answer[0]; // Stores first character of line
        i++;
    }

    answerFile.close(); // close the file!!
    return;
}

/*
    Summary: Will compare an answer key to the student's answers, and for each wrong question, it will store the correct and given incorrect answer to 2D array,
    store the question number in an array of answers answered incorrectly. Then, it returns the number of incorrect answers.
    Parameters: Character array for exam answers, exam[], character array for student answers, student[], integer array for incorrect question numbers, and 2D array for wrong answers and
    the correct option on the answer key.
    Return: returns an integer for the number of questions the student missed.
    Preconditions: exam[] and student[] should be filled with answers before function is called. wrong[] and compare[][] should be empty beforehand.
    Postconditions: As they are passed through via reference, wrong[] and compare[][] will be filled as a result of this function's calling, from the parent function.
*/
int gradeExam(char exam[], char student[], int wrong[], char compare[][NUMBERQUESTIONS])
{
    int numWrong = 0;

    for (int i = 0; i < NUMBERQUESTIONS; i++)
    {
        if (exam[i] != student[i])
        {
            compare[0][numWrong] = exam[i];
            compare[1][numWrong] = student[i];

            wrong[numWrong] = i + 1; // Question number, which is i + 1, is stored to the wrong[] array.

            numWrong++; // Increments the number of wrong answers, which can also be used as an index for a question which was wrong.
        }
    }

    return numWrong;
}

/*
    Summary: Prints a report for how well the student does on an exam, including whether they passed, number of questions missed, their percentage grade, and a table for missed answers.
    Parameters: A 2D character array for the correct and student answers, compare[][], an integer array for question numbers that were missed, wrongQuestions[], and how many were missed, numWrong.
    Return: None.
    Preconditions: compare[][] has exam answers stored in [0][], and student answers in [1][], and contains only discrepancies. iomanip is used.
    Postconditions: A report will be written to console, utilizing the inputs to give the information outlines in the summary.
*/
void writeReport(char compare[][NUMBERQUESTIONS], int wrongQuestions[], int numberWrong)
{
    cout << "Number of questions answered incorrectly: " << numberWrong << endl;

    if (numberWrong > 0)
    {
        cout << "Questions Answered Incorrectly\n";
        cout << left << setw(15) << "Question:" << setw(20) << "Correct Answer:" << setw(20) << "Student Answered:" << endl;
    }
    for (int i = 0; i < numberWrong; i++)
    {
        cout << left << setw(15) << wrongQuestions[i] << setw(20) << compare[0][i] << setw(20) << compare[1][i] << endl;
    }

    float percentGrade = (float(NUMBERQUESTIONS - numberWrong) / float(NUMBERQUESTIONS)) * 100;
    cout << fixed << setprecision(2) << "Grade: " << percentGrade << "%\n";

    if (percentGrade >= 70)
    {
        cout << "Student has passed exam.\n";
    }
    else
    {
        cout << "Student has failed exam.\n";
    }

    return;
}
