// ******************** This code demonstrates CODE REUSABILITY through modular functions and clean structure. ********************
// ******************** Each function has a single responsibility, making the code EASY TO READ and MAINTAIN. ********************

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib> //For "system()" (Colors)
#include <ctime> //For Random Function

using namespace std;

// Enum to represent difficulty levels of questions
enum enQuestionLevel { Easy = 1, Med, Hard, Mix };

// Enum to represent mathematical operation types
enum enOperationType { Add = 1, Sub, Mul, Div, MixOp };

//Structre To Store Game Result
struct stResult {int NumberOfQs = 0 ; int NumberOfRightAnswers = 0; int NumberOfWrongAnswer = 0; string QsLVL; string Optype; };

// You Will Need it for Generating Questions :)
int RandomNumbers(int From, int To)
{
    // Function To Generate Random Number

    int Rands = rand() % (To - From + 1) + From;
    return Rands;

    // rand() % (To - From + 1) → gives the number of values you need, always starting from 0.
    // + From → shifts these values from 0 to the actual start of the range.



}


// Ask The user for the number of questions they want to answer
int Ask4HowManyQuestions(stResult &Result)
{
    int NumberOfQuestions;

    cout << "How Many Questions do you want to answer ? " << endl;
    cin >> NumberOfQuestions;

    Result.NumberOfQs = NumberOfQuestions;

    return NumberOfQuestions;
}

// Ask The user to select Difficulty Level 
enQuestionLevel Ask4QuestionLevel()
{
    int Questionlvl;

    cout << "\nEnter Questions Level [1] Easy , [2] Med , [3] Hard , [4] Mix ? " << endl;
    cin >> Questionlvl;


    // Convert Difficulty Level to its enum
    return (enQuestionLevel)Questionlvl;
}


// Ask The user to select Operation Type 
enOperationType Ask4OperationType()
{
    int OperationType;

    cout << "Enter Operation Type [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix ? " << endl;
    cin >> OperationType;

    // Convert Operation Type to its enum
    return (enOperationType)OperationType;

}

// Generate two random numbers based on Difficulty Level
void NumbersDependsOnLevel(enQuestionLevel Level, int& Number1, int& Number2)
{
    if (Level == enQuestionLevel::Easy)
    {
        Number1 = RandomNumbers(1, 10);  // Easy: 1-10 range
        Number2 = RandomNumbers(1, 10);
    }
    else if (Level == enQuestionLevel::Med)
    {
        Number1 = RandomNumbers(10, 50); // Medium: 10-50 range
        Number2 = RandomNumbers(10, 50);
    }
    else if (Level == enQuestionLevel::Hard)
    {
        Number1 = RandomNumbers(50, 100); // Hard: 50-100 range
        Number2 = RandomNumbers(50, 100);
    }
    else
    {
        Number1 = RandomNumbers(1, 100); // Mix: 1-100 range
        Number2 = RandomNumbers(1, 100);
    }

}

// To Generate and display a math question, then returns the correct answer
int TypeDependsOnTypeNumber(enOperationType Operation, enQuestionLevel Level,stResult &Result)
{
    int Number1, Number2;
    

    // Generate random numbers based on difficulty level
    NumbersDependsOnLevel(Level, Number1, Number2);

    // Perform operation and display question based on operation type
    switch (Operation)
    {
    case enOperationType::Add:
        cout << Number1 << " + " << Number2;
        return Number1 + Number2;

    case enOperationType::Sub:
        cout << Number1 << " - " << Number2;
        return Number1 - Number2;

    case enOperationType::Mul:
        cout << Number1 << " * " << Number2;
        return Number1 * Number2;

    case enOperationType::Div:
        cout << Number1 << " / " << Number2;
        return (Number2 != 0) ? Number1 / Number2 : 0;  // Prevent division by zero

    case enOperationType::MixOp:
        return TypeDependsOnTypeNumber((enOperationType)RandomNumbers(1, 4), Level , Result); //Choosing Random Operation


    }
    return 0;
}


string GetQuestionLevelText(enQuestionLevel Level)
{
    switch (Level)
    {
    case Easy: return "Easy";
    case Med: return "Medium";
    case Hard: return "Hard";
    default: return "Mix";
    }
}

string GetOpTypeText(enOperationType Op)
{
    switch (Op)
    {
    case Add: return "Addition";
    case Sub: return "Subtraction";
    case Mul: return "Multiplication";
    case Div: return "Division";
    default: return "Mixed Operations";
    }
}

void FailOrPass(stResult& Result)
{
    cout << "\n----------------------------------------------------\n";

    if (Result.NumberOfRightAnswers > Result.NumberOfWrongAnswer)
    {
        cout << "\nFinal Result is PASS :)\n";
    }
    else
    {
        cout << "\nFinal Result is FAIL :(\n";

    }

    cout << "\n----------------------------------------------------\n";
}


void PrintFinalResult(stResult& Result)
{

    cout << "Number Of Questions\t: " << Result.NumberOfQs << endl;
    cout << "Questions Level \t: " << Result.QsLVL << endl;
    cout << "OpType \t\t\t: " << Result.Optype << endl;
    cout << "Number Of Right Answers : " << Result.NumberOfRightAnswers << endl;
    cout << "Number Of Wrong Answers : " << Result.NumberOfWrongAnswer << endl;

    cout << "\n----------------------------------------------------\n";



}


// Main quiz generator : runs the complete quiz game
void QuizGenerator(stResult &Result)
{


    
    // Get quiz settings from user
    int NumberOfQuestions = Ask4HowManyQuestions(Result);
    enQuestionLevel Level = (enQuestionLevel)Ask4QuestionLevel();
    enOperationType Operation = (enOperationType)Ask4OperationType();

    Result.QsLVL = GetQuestionLevelText(Level);
    Result.Optype = GetOpTypeText(Operation);

    // Loop through each question
    for (int i = 1; i <= NumberOfQuestions; i++)
    {
        // Display question number
        cout << "\n Question [" << i << "/" << NumberOfQuestions << "]" << endl;

        // Generate question and get correct answer
        int CorrectAnswer = TypeDependsOnTypeNumber(Operation, Level,Result);


        // Get user's answer
        int UserAnswer;
        cout << "\n-----------------\n";
        cin >> UserAnswer;

        // Check answer and provide feedback
        if (UserAnswer == CorrectAnswer)
        {
            system("color 2F"); // Green background for correct answer
            cout << endl;
            cout << "Right Answer :) " << endl;
            Result.NumberOfRightAnswers++;
            cout << endl;

        }
        else
        {
            system("color 4F"); // Red background for wrong answer
            cout << endl;
            cout << "Wrong Answer :( " << endl;
            Result.NumberOfWrongAnswer++;
            cout << "The Right Answer is : " << CorrectAnswer << endl;
            cout << endl;



        }

    }


    //Display Final Results
    FailOrPass(Result);
    PrintFinalResult(Result);


    
}



char AskToReplay()
{
    char Response;

    cout << "Do You Want To Play Again ? Y/N ? " << endl;
    cin >> Response;

    return Response;
}

void Replay()
{
    char Response ;
    stResult Result;

    do
    {
        system("cls");        // Clear screen 
        system("color 0F");  // Reset to default colors (black bg, white text)

        //Run the Gamr First
        QuizGenerator(Result);

        //Ask To Replay
        Response = AskToReplay();



    } while (Response == 'y' || Response == 'Y');
}

void StartGame()
{
    Replay();
}


// Program entry point
int main()
{

    // Seed the random number generator with the current time - Called Only Once ! -
    srand((unsigned)time(NULL));

    // Start the quiz game
    StartGame();

    return 0;
}