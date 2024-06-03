#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <cstdlib>

using namespace std;

char square[9] = {'0','1','2','3','4','5','6','7','8'};
const int CARD_SIZE = 5;
const int CARD_ROWS = 5;
const int MAX_NUM = 25;

struct User {
    string username;
    string password;
    string email_id;
    string age;
    string bio;
    string game_preferences;
    int score;
};
map<string, User> users;
void loadUsers();
void saveUsers();
void signup();
bool isValidEmail(const string& email);
bool isValidPassword(const string& password);
bool login(string& username);
void resetPassword();
void deleteAccount();
void logout();
void DisplayNotLoggedInMenu();
void LoggedInMenu();
void displayOfGames();
void hangman();
void trivia();
void highLow();
void RockPaperScissor();
void tic_tac();
int checkwin();
void display();
void movePlayer(int& playerPos, int roll, map<int, int>& snl);
void mark(int player, int box);
void drawHangman(int wrong_guesses);
void leaderboards(string gameName);
void displayBadges(const string& game, const map<string, int>& scores);
void displayUserProfile(const string& username, const map<string, string>& game_preferences);
void generateCard(int card[CARD_ROWS][CARD_SIZE]);
bool isNumberInCard(int card[CARD_ROWS][CARD_SIZE], int num);
bool checkForWin(int card[CARD_ROWS][CARD_SIZE]);
void printCard(int card[CARD_ROWS][CARD_SIZE]);
void bingo();
int getRank(const map<string, int>& scores, const string& username);
string goldbadge();
string currentime();
string bronzebadge();
string silverbadge();
void snakeandladder();
void achievements(const string& username);

bool logged=false;

int main() {
    loadUsers();


    int choice;
    string username;
    do{
        if(!logged){
            DisplayNotLoggedInMenu();
        }else{
            LoggedInMenu();
        }
        cout<<"Enter your choice: "<<endl;
        cout<<endl;
        cout<<"______________________________________________________________________________"<<endl;
        cin>>choice;

        switch(choice){

            case 1:
                if(!logged){
                    signup();
                }else{
                    displayOfGames();

                }
                break;
            case 2:
                if(!logged){
                    logged= login(username);
                    if(logged){
                        cout<<endl;
                        cout<<endl;
                        cout<<endl;
                        cout << "            Welcome " << username << "! Get ready to climb the leaderboards." << endl;
                        cout<<endl;
                        cout<<endl;


                    }
                } else{
                    map<string, string> game_preferences;
                    displayUserProfile(username, game_preferences);


                }
                break;
            case 3:
                if(!logged){
                    deleteAccount();  }


                else{
                    cout << "Enter the game name to display the leaderboard: [1.tictactoe 2.hangman 3.rockpaperscissor 4trivia 5.highlow \n6.Bingo 7.snakeandladder]";
                    string gameName;
                    cin >> gameName;
                    leaderboards(gameName);


                }
                break;
            case 4:
                achievements(username);
                break;




            case 5:
                logout();
                logged=false;


                break;
            case 6:
                deleteAccount();
                break;
            case -1:
                break;
            default:
                cout<<"You have Entered Wrong Value! Try Again"<<endl;
        }
    }while(choice!=-1);




    return 0;
}
// Function to load user data from file
void loadUsers() {
  system("clear");
    ifstream inFile("../pfproject/user.txt");
    string username, password, email_id, age,bio,game_preferences;
    while (inFile >> username >> password >> email_id>> age >> bio >> game_preferences )  {
        User user;
        user.username = username;
        user.password = password;
        user.email_id = email_id;
        user.age = age;
        user.bio = bio;
        user.game_preferences = game_preferences;
        user.score=0;

        users[username] = user;
    }
    inFile.close();
}
// Function to display menu on opening th system
void DisplayNotLoggedInMenu(){


    cout<<endl;
    cout<<"\n"

          <<"\n"
            "     _  _  ____  __     ___  __   _  _  ____          \n"
            "    / )( \\(  __)(  )   / __)/  \\ ( \\/ )(  __)         \n"
            "    \\ /\\ / ) _) / (_/\\( (__(  O )/ \\/ \\ ) _)          \n"
            "    (_/\\_)(____)\\____/ \\___)\\__/ \\_)(_/(____)         \n"
            "                 ____  __                             \n"
            "                (_  _)/  \\                            \n"
            "                  )( (  O )                           \n"
            "                 (__) \\__/                            \n"
            "  ___   __   _  _  __  __ _   ___    _  _  _  _  ____ \n"
            " / __) / _\\ ( \\/ )(  )(  ( \\ / __)  / )( \\/ )( \\(  _ \\\n"
            "( (_ \\/    \\/ \\/ \\ )( /    /( (_ \\  ) __ () \\/ ( ) _ (\n"
            " \\___/\\_/\\_/\\_)(_/(__)\\_)__) \\___/  \\_)(_/\\____/(____/"<<endl   ;
    cout<<endl;




    cout << "                                     ""1. Signup" << endl;
    cout << "                                     ""2. Login" << endl;
    cout << "                                     ""3. Delete Account" << endl;


    cout << "                                     ""-1: Exit" << endl;


    cout << endl;
    cout << "______________________________________________________________________________" << endl;
    cout << endl;
    cout << "Already have an account? Log in to access games and leaderboards!" << endl;
    cout<<endl;


}


// Function to register a new user
void signup() {


    string username, password, email_id, age, bio, game_preferences;


    cout<<endl;
    cout << "______________________________________________________________________________" << endl;
    cout << "\nEnter a new username: (Write it in the following way: Ollie-Kendal)\n";
    cin >> username;
    cout << "Enter a new password: (Must be at least 8 characters long and contain at least one number and one special character)\n";
    cin >> password;
    cout << "Enter your email address: \n";
    cin >> email_id;
    cout << "Enter your age: ";
    cin >> age;


    cout << "Enter your bio: ";
    getline(cin, bio);
    getline(cin, bio);


    cout << "Enter your game preferences (comma-separated): ";
    getline(cin, game_preferences);
    // Check if the email address is valid
    if (!isValidEmail(email_id)) {
        cout << "Invalid email address. Please try again.\n";
        return;
    }


    // Check if the password meets the requirements
    if (!isValidPassword(password)) {
        cout << "Password must be at least 8 characters long and contain at least one number and one special character. Please try again.\n";
        return;
    }


    // Check if the username already exists
    if (users.find(username) != users.end()){
        cout << "Username already exists. Please try again.\n";
        return;
    }


    // Create a new user object and add it to the map
    User user;
    user.username = username;
    user.password = password;
    user.email_id = email_id;
    user.age = age;
    user.bio = bio;
    user.game_preferences = game_preferences;


    users[username] = user;




    saveUsers();


    cout << "\nAccount created successfully! A confirmation email has been sent to " << email_id << endl;


    logged=true;


}


bool isValidEmail(const string& email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);
    return (atPos != string::npos && dotPos != string::npos && dotPos > atPos);
}


bool isValidPassword(const string& password) {
    bool hasNumber = false;
    bool hasSpecial = false;
    for (char c : password) {
        if (isdigit(c)) {
            hasNumber = true;
        } else if (!isalnum(c)) {
            hasSpecial = true;
        }
    }
    return (password.length() >= 8 && hasNumber && hasSpecial);
}
// Function to save user data to file
void saveUsers() {
    ofstream outFile("../pfproject/user.txt", ios::trunc);
    for (auto& user : users) {
        outFile << user.second.username << " "
                << user.second.password << " "
                << user.second.email_id << " "
                << user.second.age << " "
                << user.second.bio << " "
                << user.second.game_preferences << endl;
    }
    outFile.close();


}


// Function to login
bool login(string& username) {
    cout << "______________________________________________________________________________" << endl;
    string password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;


    if (users.find(username) == users.end()) {
        cout << "Username does not exist. Please try again." << endl;
        return false;
    }


    while (users[username].password != password) {
        cout << "Incorrect password. Enter '1' to try again, '2' to reset your Password" << endl;
        int reset;
        cin >> reset;
        switch (reset) {
            case 1:
                cout << "Enter your password again: ";
                cin >> password;
                break;
            case 2:
                resetPassword();
                return false;
            default:
                cout << "Invalid Entry" << endl;
        }
    }


    cout << "Login successful!" << endl;
    return true;
}
// Function to reset password
void resetPassword() {
    cout<<endl;
    cout << "______________________________________________________________________________" << endl;


    string username, email_id;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your email address: ";
    cin >> email_id;


    if (users.find(username) == users.end()) {
        cout << "Username does not exist. Please try again." << endl;
        return;
    }


    if (users[username].email_id!= email_id) {
        cout << "Email address does not match. Please try again." << endl;
        return;
    }


    string newPassword;
    cout << "Enter a new password: ";
    cin >> newPassword;
    if (!isValidPassword(newPassword)) {
        cout << "Password must be at least 8 characters long and contain at least one number and one special character. Please try again.\n";
        return;
    }
    users[username].password = newPassword;
    cout << "Password reset successfully!" << endl;
    saveUsers();
}
// Function to delete an existing account
void deleteAccount() {
    cout<<endl;
    cout << "______________________________________________________________________________" << endl;


    string username;
    cout << "Enter the username to delete: ";
    cin >> username;




    if (users.find(username) == users.end()) {
        cout << "Username does not exist. Please try again." << endl;
        return;
    }




    users.erase(username);
    cout << "Account deleted successfully!" << endl;
    saveUsers();
}


// Function to log out
void logout() {
    cout<<endl;
    cout<<endl;




    cout << "Logout successful!" << endl;
    cout << "______________________________________________________________________________" << endl;


}


// Function to display menu when user has logged in
void LoggedInMenu(){
    cout<<"______________________________________________________________________________"<<endl;
    cout<<endl;
    cout<<"                                ""1: Play Games"<<endl;
    cout<<"                                ""2: View Profile"<<endl;
    cout<<"                                ""3: Leaderboard"<<endl;
    cout<<"                                ""4: Achievements"<<endl;
    cout<<"                                ""5: Logout"<<endl;
    cout<<"                                ""6: Delete Account"<<endl;
    cout<<"                                ""-1: Exit"<<endl;
    cout<<endl;
    cout<<"______________________________________________________________________________"<<endl;
    cout<<endl;


}
void displayOfGames() {
    cout<<endl;
    cout << "______________________________________________________________________________" << endl;


    cout << "Here, are the Gaming Options available for you:\n"<<endl
         << "1. Tic-Tac-toe\t    \t 2. Hangman \t    \t 3. Rock,Paper,Scissor \n4. Trivia\t    \t 5. High-Low\t    \t 6. Snake and Ladder\n7. Randomaly-Selected Game by Computer";
    cout<<endl;


    int choices;
    cout<<endl;
    cout << "Enter your choice: ";
    cin >> choices;


    switch (choices) {
        case 1:
            tic_tac();
            cout<<endl;
            cout<<endl;


            break;
        case 2: {


            hangman();
            cout<<endl;
            break;


            case 3:
                RockPaperScissor();
            cout<<endl;


            break;
            case 4:
                trivia();
            cout<<endl;


            break;
            case 5:
                highLow();
            cout<<endl;


            break;
            // case 6:
            //     bingo();
            // cout<<endl;


            break;
            case 6:
                snakeandladder();
            cout<<endl;


            break;




            case 7:
                srand(time(0));
            int random_game = rand() % 7 + 1;
            cout << "The computer has selected game number " << random_game << " for you!" << endl;
            switch (random_game) {
                case 1:
                    tic_tac();
                    break;
                case 2:
                    hangman();
                    break;
                case 3:
                    RockPaperScissor();
                    break;
                case 4:
                    trivia();
                    break;
                case 5:
                    highLow();
                    break;
                // case 6:
                //     bingo();
                //     break;
                case 6:
                    snakeandladder();
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }


            break;
        }






//        default:
//            cout << "Invalid choice. Please try again." << endl;
//            break;
    }


}


// Function to play tic_tac
void tic_tac(){
    int score=0;
    srand(time(0));
    string username;


    cout<<"\n"
          "   _    _    _      _      _     _     _      _      _     _     _  \n"
          "  / \\  / \\  / \\    / \\    / \\   / \\   / \\    / \\    / \\   / \\   / \\ \n"
          " ( T )( I )( C )  ( - )  ( T ) ( A ) ( C )  ( - )  ( T ) ( O ) ( E )\n"
          "  \\_/  \\_/  \\_/    \\_/    \\_/   \\_/   \\_/    \\_/    \\_/   \\_/   \\_/ ";


    cout<<endl;
    cout<<endl;


    cout << "Enter your username: ";
    cin >> username;


    int count1 = 0;
    int count2 = 0;
    int player1 = 1, player2 = 2;


    int box, result = 0, flag = 0;


    for (int i = 1; i < 5; i++)
    {
        cout << "_________________________" << endl;
        cout << username << endl
             << "Enter The Box( from 0-8): ";
        cin >> box;
        mark(player1, box);
        display();


        result = checkwin();
        if (result == 1)
        {
            cout << "_________________________" << endl;
            cout << "Congratulations! " << username << "! You have Won this game. " << endl;
            cout << "_________________________" << endl;
            flag = 1;
            count1++;
            break;
        }


        int computerBox = rand() % 9 + 1;
        while (square[computerBox - 1] != '1' && square[computerBox - 1] != '2' && square[computerBox - 1] != '3' && square[computerBox - 1] != '4' && square[computerBox - 1] != '5' && square[computerBox - 1] != '6' && square[computerBox - 1] != '7' && square[computerBox - 1] != '8' && square[computerBox - 1] != '9')
        {
            computerBox = rand() % 9 + 1;
        }
        mark(player2, computerBox);
        display();


        result = checkwin();
        if (result == 2)
        {
            cout << "_________________________" << endl;
            cout << "Computer has Won. " << endl;
            cout << "_________________________" << endl;
            flag = 1;
            count2++;
            break;
        }
    }


    if (flag == 0)
    {
        cout << "_________________________" << endl;
        cout << "Match Draw!" << endl;
        cout << "_________________________" << endl;
    }


    if(flag==1){
        score = 10;
        cout<<endl;
        cout<<"You have scored = "<<score<<endl;
        cout<<endl;
    }






    // read the existing score from the file
    map<string, int> tictacScores;
    ifstream scoreFile("../pfproject/tictactoe_scores.txt");
    if (scoreFile.is_open()) {
        string line;
        while (getline(scoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                tictacScores[user] = userScore;
            }
        }
        scoreFile.close();
    }
    cout<<"Scoreboard for Tic-Tac-Toe is: \n";
    cout<<endl;
    cout<<"Your previous score for this game was : "<<tictacScores[username]<<endl;
    // add the new score to the existing score
    if (tictacScores.find(username) == tictacScores.end()) {
        tictacScores[username] = score;


    } else {
        tictacScores[username] += score;
    }


    // write the updated score back to the file
    ofstream scoreFiles("../pfproject/tictactoe_scores.txt", ios::trunc);
    if (scoreFiles.is_open()) {
        for (const auto& entry : tictacScores) {
            scoreFiles << entry.first << ": " << entry.second << endl;
        }
        scoreFiles.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
    cout<<"Your new Score for this game is "<<tictacScores[username]<<endl;
    cout<<"Your position rank for this game is: "<<getRank(tictacScores, username)<<endl;


}
void mark(int player, int box)
{
    if (player == 1)
    {
        square[box ] = 'X';
    }
    else
        square[box ] = 'O';
}


int checkwin()
{
    if (square[0] == square[1] && square[1] == square[2])
    {
        if (square[0] == 'X')
            return 1;
        else
            return 2;
    }
    else if (square[3] == square[4] && square[4] == square[5])
    {
        if (square[3] == 'X')
            return 1;
        else
            return 2;
    }
    else if (square[6] == square[7] && square[7] == square[8])
    {
        if (square[6] == 'X')
            return 1;
        else
            return 2;
    }
    else if (square[0] == square[3] && square[3] == square[6])
    {
        if (square[0] == 'X')
            return 1;
        else
            return 2;
    }
    else if (square[1] == square[4] && square[4] == square[7])
    {
        if (square[1] == 'X')
            return 1;
        else
            return 2;
    }
    else if (square[2] == square[5] && square[5] == square[8])
    {
        if (square[2] == 'X')
            return 1;
        else
            return 2;
    }
    else if (square[0] == square[4] && square[4] == square[8])
    {
        if (square[0] == 'X')
            return 1;
        else
            return 2;
    }
    else if (square[2] == square[4] && square[4] == square[6])
    {
        if (square[2] == 'X')
            return 1;
        else
            return 2;
    }
    else
        return 0;
}
void display() {
    cout << "   |   |   " << endl;
    cout << " " << square[0] << " | " << square[1] << " | " << square[2] << endl;
    cout << "___|___|___" << endl;
    cout << "   |   |   " << endl;
    cout << " " << square[3] << " | " << square[4] << " | " << square[5] << endl;
    cout << "___|___|___" << endl;
    cout << "   |   |   " << endl;
    cout << " " << square[6] << " | " << square[7] << " | " << square[8] << endl;
    cout << "___|___|___" << endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
}
// Function to play Hangman game
void hangman() {
    cout<<"                       \n"
          "  ___ ___                                                           ._.\n"
          " /   |   \\  _____      ____      ____     _____   _____      ____   | |\n"
          "/    ~    \\ \\__  \\    /    \\    / ___\\   /     \\  \\__  \\    /    \\  | |\n"
          "\\    Y    /  / __ \\_ |   |  \\  / /_/  > |  Y Y  \\  / __ \\_ |   |  \\  \\|\n"
          " \\___|_  /  (____  / |___|  /  \\___  /  |__|_|  / (____  / |___|  /  __\n"
          "                                                                                ";


    vector<string> words = {"airplane","woman","window","cake","sweet","school","cheque","book","helicopter","computer","telegraph","microsoft","difficult","many","dictionary", "guns","rainbow","tortoise"};
    srand(time(0));
    string word = words[rand() % words.size()];
    string unknown(word.length(), '*');
    string guessedLetters;
    int num_of_wrong_guesses = 0;
    int score = 0;
    cout<<endl;
    cout<<endl;
    cout << "Choose a level:\n";
    cout << "1. Limited tries (10 attempts)\n";
    cout << "2. Time attack (45 seconds)\n";
    int level;
    cin >> level;


    if (level == 1) {
        // Limited tries level
        const int MAX_WRONG_GUESSES = 7;
        string hangman_man[MAX_WRONG_GUESSES] = {
                " +---+\n"
                " |   |\n"
                "     |\n"
                "     |\n"
                "     |\n"
                "     |\n"
                "==========",
                " +---+\n"
                " |   |\n"
                " O   |\n"
                "     |\n"
                "     |\n"
                "     |\n"
                "==========",
                " +---+\n"
                " |   |\n"
                " O   |\n"
                " |   |\n"
                "     |\n"
                "     |\n"
                "==========",
                " +---+\n"
                " |   |\n"
                " O   |\n"
                "/|   |\n"
                "     |\n"
                "     |\n"
                "==========",
                " +---+\n"
                " |   |\n"
                " O   |\n"
                "/|\\  |\n"
                "     |\n"
                "     |\n"
                "==========",
                " +---+\n"
                " |   |\n"
                " O   |\n"
                "/|\\  |\n"
                "/    |\n"
                "     |\n"
                "==========",
                " +---+\n"
                " |   |\n"
                " O   |\n"
                "/|\\  |\n"
                "/ \\  |\n"
                "     |\n"
                "=========="
        };


        while (num_of_wrong_guesses < MAX_WRONG_GUESSES && unknown != word) {
            char guess;
            cout << "Enter your guess(lower-cased Letters): ";
            cin >> guess;


            guessedLetters += guess;


            bool correct_guess = false;
            for (int i = 0; i < word.length(); i++) {
                if (word[i] == guess && unknown[i] == '*') {
                    unknown[i] = guess;
                    correct_guess = true;
                }
            }


            if (!correct_guess) {
                num_of_wrong_guesses++;
                cout << hangman_man[num_of_wrong_guesses - 1] << endl;
            }


            cout << "Guess the word: " << unknown << endl;
        }


        if (num_of_wrong_guesses == MAX_WRONG_GUESSES) {
            cout << "You lost! The word was: " << word << endl;
        } else {
            cout << "You won! The word was: " << word << endl;
            score = 10;
            cout<<endl;
            cout<<"You have scored = "<<score<<endl;// award 10 points for each correct guess
            cout<<endl;
        }
    } else if (level == 2) {
        // Time attack level
        auto start_time = chrono::high_resolution_clock::now();
        int wrong_guesses = 0;
        while (true) {
            char guess;
            cout << "Enter your guess: ";
            cin >> guess;


            guessedLetters += guess;


            bool correct_guess = false;
            for (int i = 0; i < word.length(); i++) {
                if (word[i] == guess && unknown[i] == '*') {
                    unknown[i] = guess;
                    correct_guess = true;
                }
            }


            if (correct_guess) {
                cout << "Correct! Guess the word: " << unknown << endl;
            } else {
                cout << "Incorrect. Guess the word: " << unknown << endl;
                wrong_guesses++;
                drawHangman(wrong_guesses); // draw hangman after every wrong guess
            }


            auto current_time = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed_time = current_time - start_time;
            // if (elapsed_time.count() >= 9) {
            //     wrong_guesses++;
            //     drawHangman(wrong_guesses); // draw hangman after 9 seconds
            // }


            if (elapsed_time.count() >= 45) {
                cout << "Time's up! The word was: " << word << endl;
                break;
            }


            if (unknown == word) {
                cout << "You won! The word was: " << word << endl;
                cout<<endl;
                score = 10; // award 10 points for each correct guess
                cout<<"You have scored"<<score<<endl;
                break;
            }
        }
    }


    string username;
    cout << "Enter your username: "<<endl;
    cin >> username;


    // read the existing score from the file
    map<string, int> hangmanScores;
    ifstream scoreFile("../pfproject/hangman_scores.txt");
    if (scoreFile.is_open()) {
        string line;
        while (getline(scoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                hangmanScores[user] = userScore;
            }
        }
        scoreFile.close();
    }
    cout<<"Scoreboard for Hangman is: \n";
    cout<<endl;
    cout<<"Your previous score for this game was : "<<hangmanScores[username]<<endl;


    // add the new score to the existing score
    if (hangmanScores.find(username) == hangmanScores.end()) {
        hangmanScores[username] = score;
    } else {
        hangmanScores[username] += score;
    }


    // write the updated score back to the file
    ofstream scoreFiles("../pfproject/hangman_scores.txt", ios::trunc);
    if (scoreFiles.is_open()) {
        for (const auto& entry : hangmanScores) {
            scoreFiles << entry.first << ": " << entry.second << endl;
        }
        scoreFiles.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
    cout<<"Your new Score for this game is "<<hangmanScores[username]<<endl;
    cout<<"Your position rank for this game is: "<<getRank(hangmanScores, username)<<endl;


}
//Function to drawHangman
void drawHangman(int wrong_guesses) {
    switch (wrong_guesses) {
        case 1:
            cout << " _______\n"
                 << "|       |\n"
                 << "|       O\n"
                 << "|       \n"
                 << "|       \n"
                 << "|_______\n";
            break;
        case 2:
            cout << " _______\n"
                 << "|       |\n"
                 << "|       O\n"
                 << "|       |\n"
                 << "|       \n"
                 << "|_______\n";
            break;
        case 3:
            cout << " _______\n"
                 << "|       |\n"
                 << "|       O\n"
                 << "|      /|\n"
                 << "|       \n"
                 << "|_______\n";
            break;
        case 4:
            cout << " _______\n"
                 << "|       |\n"
                 << "|       O\n"
                 << "|      /|\\\n"
                 << "|       \n"
                 << "|_______\n";
            break;
        case 5:
            cout << " _______\n"
                 << "|       |\n"
                 << "|       O\n"
                 << "|      /|\\\n"
                 << "|      /\n"
                 << "|_______\n";
            break;
        case 6:
            cout << " _______\n"
                 << "|       |\n"
                 << "|       O\n"
                 << "|      /|\\\n"
                 << "|      / \\\n"
                 << "|_______\n";
            break;
        case 7:
            cout << " _______\n"
                 << "|       |\n"
                 << "|       O\n"
                 << "|      /|\\\n"
                 << "|      / \\\n"
                 << "|       /\n"
                 << "|_______\n";
            break;
        case 8:
            cout << " _______\n"
                 << "|       |\n"
                 << "|       O\n"
                 << "|      /|\\\n"
                 << "|      / \\\n"
                 << "|       / \\\n"
                 << "|_______\n";
            break;
        case 9:
            cout << " _______\n"
                 << "|       |\n"
                 << "|       O\n"
                 << "|      /|\\\n"
                 << "|      / \\\n"
                 << "|       / \\\n"
                 << "|_______\n"
                 << "       /\n";
            break;
        case 10:
            cout << " _______\n"
                 << "|       |\n"
                 << "|       O\n"
                 << "|      /|\\\n"
                 << "|      / \\\n"
                 << "|       / \\\n"
                 << "|_______\n"
                 << "       /\n"
                 << "      / \\\n";
            break;
        case 11:
            cout << " _______\n"
                 << "|       |\n"
                 << "|       O\n"
                 << "|      /|\\\n"
                 << "|      / \\\n"
                 << "|       / \\\n"
                 << "|_______\n"
                 << "       /\n"
                 << "      / \\\n"
                 << "      /\n";
            break;
        case 12:
            cout << " _______\n"
                 << "|       |\n"
                 << "|       O\n"
                 << "|      /|\\\n"
                 << "|      / \\\n"
                 << "|       / \n";
        default:


            break;
    }
}
// Function to play RockPaperScissor
void RockPaperScissor(){
    cout<<"\n"
        <<"\n"
          " ____  ____  ____  _  __     ____  ____  ____  _____ ____      ____  ____  _  ____  ____  ____  ____ \n"
          "/  __\\/  _ \\/   _\\/ |/ /    /  __\\/  _ \\/  __\\/  __//  __\\    / ___\\/   _\\/ \\/ ___\\/ ___\\/  _ \\/  __\\\n"
          "|  \\/|| / \\||  /  |   /     |  \\/|| / \\||  \\/||  \\  |  \\/|    |    \\|  /  | ||    \\|    \\| / \\||  \\/|\n"
          "|    /| \\_/||  \\_ |   \\     |  __/| |-|||  __/|  /_ |    /    \\___ ||  \\_ | |\\___ |\\___ || \\_/||    /\n"
          "\\_/\\_\\\\____/\\____/\\_|\\_\\    \\_/   \\_/ \\|\\_/   \\____\\\\_/\\_\\    \\____/\\____/\\_/\\____/\\____/\\____/\\_/\\_\\\n"
          "                                                                                                     ";


    cout<<endl;
    cout<<endl;


    cout<<"1.With Computer \n2.Multiplayer";
    int option;
    cout<<"Enter your choice";
    cin>>option;
    int score=0;
    bool win = false;
    if(option==1) {


        int player, computer;




        srand(time(0)); // seed the random number generator


        cout << "Player 1, enter your move (0 for rock, 1 for paper, 2 for scissors): ";
        cin >> player;


        // generate a random move for the computer
        computer = rand() % 3;


        if (player == computer) {
            cout << "It's a draw!" << endl;
            cout << "Player 1 move :" << player << endl;
            cout << "Computer move :" << computer << endl;
        } else if (player == 0 && computer == 1) {
            cout << "Computer wins!" << endl;


            cout << "Player 1 move :" << player << endl;
            cout << "Computer move :" << computer << endl;
        } else if (player == 0 && computer == 2) {
            cout << "Player 1 wins!" << endl;
            win = true;
            cout << "Player 1 move :" << player << endl;
            cout << "Computer move :" << computer << endl;
        } else if (player == 1 && computer == 0) {
            cout << "Player 1 wins!" << endl;
            win = true;
            cout << "Player 1 move :" << player << endl;
            cout << "Computer move :" << computer << endl;
        } else if (player == 1 && computer == 2) {
            cout << "Computer wins!" << endl;
            cout << "Player 1 move :" << player << endl;
            cout << "Computer move :" << computer << endl;
        } else if (player == 2 && computer == 0) {
            cout << "Computer wins!" << endl;
            cout << "Player 1 move :" << player << endl;
            cout << "Computer move :" << computer << endl;
        } else if (player == 2 && computer == 1) {
            cout << "Player 1 wins!" << endl;
            win = true;
            cout << "Player 1 move :" << player << endl;
            cout << "Computer move :" << computer << endl;
        } else {
            cout << "Invalid input, please try again." << endl;
        }
        if (win== true) {
            score = 10;
            cout<<endl;


            cout<<"You have scored = "<<score<<endl;
            cout<<endl;


        }

        string username;
        cout << "Enter your username: ";
        cin >> username;


        map<string, int> rockpaperscissorScores;
        ifstream scoreFile("../pfproject/rockpaperscissor_scores.txt");
        if (scoreFile.is_open()) {
            string line;
            while (getline(scoreFile, line)) {
                size_t pos = line.find(':');
                if (pos != string::npos) {

                    //string indexes , pos=:

                    string user = line.substr(0, pos);

                    int userScore = stoi(line.substr(pos + 1));
                    rockpaperscissorScores[user] = userScore;
                }
            }
            scoreFile.close();
        }
        cout<<"Scoreboard for Rock Paper Scissor is: \n";
        cout<<endl;


        cout<<"Your previous score for this game was : "<<rockpaperscissorScores[username]<<endl;
        // add the new score to the existing score
        if (rockpaperscissorScores.find(username) == rockpaperscissorScores.end()) {
            rockpaperscissorScores[username] = score;
        } else {
            rockpaperscissorScores[username] += score;
        }


        // write the updated score back to the file
        ofstream scoreFiles("../pfproject/rockpaperscissor_scores.txt", ios::trunc);
        if (scoreFiles.is_open()) {
            for (const auto& entry : rockpaperscissorScores) {
                scoreFiles << entry.first << ": " << entry.second << endl;
            }
            scoreFiles.close();
        } else {
            cout << "Unable to open file for writing." << endl;
        }
        cout<<"Your new Score for this game is "<<rockpaperscissorScores[username]<<endl;
        cout<<"Your position rank for this game is: "<<getRank(rockpaperscissorScores, username)<<endl;


    }


    else if(option==2){
        int player1, player2;
        cout << "Player 1, enter your move (0 for rock, 1 for paper, 2 for scissors): ";
        cin >> player1;
        cout << "Player 2, enter your move (0 for rock, 1 for paper, 2 for scissors): ";
        cin >> player2;


        if (player1 == player2) {
            cout << "It's a draw!" << endl;


        } else if (player1 == 0 && player2 == 1) {
            cout << "Player 2 wins!" << endl;


        }
        else if (player1 == 0 && player2 == 2) {
            cout << "Player 1 wins!" << endl;


        } else if (player1 == 1 && player2 == 0) {
            cout << "Player 1 wins!" << endl;


        } else if (player1 == 1 && player2 == 2) {
            cout << "Player 2 wins!" << endl;


        } else if (player1 == 2 && player2 == 0) {
            cout << "Player 2 wins!" << endl;


        } else if (player1 == 2 && player2 == 1) {
            cout << "Player 1 wins!" << endl;
        } else {
            cout << "Invalid input, please try again." << endl;
        }


    }


}
// Function to play trivia
void trivia(){
    int score = 0;
    cout<<"------------------------------------------------------------------------------------";
    cout<<"\n";
    cout<<"\n"
          "_____________________._______   ____.___   _____   \n"
          "\\__    ___/\\______   \\   \\   \\ /   /|   | /  _  \\  \n"
          "  |    |    |       _/   |\\   Y   / |   |/  /_\\  \\ \n"
          "  |    |    |    |   \\   | \\     /  |   /    |    \\\n"
          "  |____|    |____|_  /___|  \\___/   |___\\____|__  /\n"
          "                   \\/                           \\/ ";
    cout<<endl;
    cout<<"------------------------------------------------------------------------------------";
    cout<<endl;
    cout<<endl;


    cout<<"\nEnter 'yes' to continue: \n";
    string ctn;
    cin>>ctn;
    cout<<"------------------------------------------------------------------------------------";
    if (ctn=="yes"){
        cout<<"\n Choose A Category: \n 1. Science & Technology \n 2. Art & Literature \n 3. History \n 4. Geography\n";
        cout<<"------------------------------------------------------------------------------------ \n";
        int right=0;
        int wrong=0;
        string ans;
        int ctg;
        cout<<"Enter Your Choice: ";
        cin>>ctg;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(ctg==1){
            cout<<"------------------------------------------------------------------------------------ \n";
            cout<<"                                  Science Trivia\n";
            cout<<"------------------------------------------------------------------------------------ \n";
            cout<<"Q. Who invented the first programming language?\n";
            getline(cin,ans);

            if(ans=="Ada Lovelace" || ans=="ada lovelace" || ans=="Eda Lovelace"){
                cout<<"Correct Answer!! \n\n";
                right+=1;
            }
            else{
                cout<<"Wrong Answer!! \n\n";
                wrong+=1;
            }
            cout<<"Q. How many bones are in the adult human body?\n";
            getline(cin,ans);

            if(ans=="206"){
                cout<<"Correct Answer!! \n\n";
                right+=1;
            }
            else{
                cout<<"Wrong Answer!! \n\n";
                wrong+=1;
            }


            cout<<"Q. Which company developed the Android operating system?\n";
            getline(cin,ans);

            if(ans=="Google" || ans=="google"){
                cout<<"Correct Answer!! \n\n";
                right+=1;
            }
            else{
                cout<<"Wrong Answer!! \n\n";
                wrong+=1;
            }

        }




        if(ctg==2){
            cout<<"------------------------------------------------------------------------------------ \n";
            cout<<"                           Art & Literature Trivia\n";
            cout<<"------------------------------------------------------------------------------------ \n";
            cout<<"Q. Who painted the Mona Lisa?\n";
            getline(cin,ans);

            if(ans=="Leonardo da Vinci" || ans=="Leonardo Da Vinci" || "leonardo da vinci"){
                cout<<"Correct Answer!! \n\n";
                right+=1;
            }
            else{
                cout<<"Wrong Answer!! \n\n";
                wrong+=1;
            }
            cout<<"Q. Who wrote the novel '1984'? \n";
            getline(cin,ans);

            if(ans=="George Orwell" || ans=="george orwell"){
                cout<<"Correct Answer!! \n\n";
                right+=1;
            }
            else{
                cout<<"Wrong Answer!! \n\n";
                wrong+=1;
            }


            cout<<"Q. In what city is the Louvre Museum located?\n";
            getline(cin,ans);

            if(ans=="Paris" || ans=="paris"){
                cout<<"Correct Answer!! \n\n";
                right+=1;
            }
            else{
                cout<<"Wrong Answer!! \n\n";
                wrong+=1;
            }

        }

        if(ctg==3){
            cout<<"------------------------------------------------------------------------------------ \n";
            cout<<"                                 History Trivia\n";
            cout<<"------------------------------------------------------------------------------------ \n";
            cout<<"Q. Who was the first President of the United States?\n";
            getline(cin,ans);

            if(ans=="George Washington" || ans=="george washington" || ans=="Washington" || ans=="washington"){
                cout<<"Correct Answer!! \n\n";
                right+=1;
            }
            else{
                cout<<"Wrong Answer!! \n\n";
                wrong+=1;
            }
            cout<<"Q. What ancient civilization built the pyramids?\n";
            getline(cin,ans);

            if(ans=="Egyptians" || ans=="egyptians"){
                cout<<"Correct Answer!! \n\n";
                right+=1;
            }
            else{
                cout<<"Wrong Answer!! \n\n";
                wrong+=1;
            }


            cout<<"Q. Who was the first man to walk on the moon?\n";
            getline(cin,ans);

            if(ans=="Neil Armstrong" || ans=="neil armstrong" || ans=="Armstrong" || ans=="armstrong"){
                cout<<"Correct Answer!! \n\n";
                right+=1;
            }
            else{
                cout<<"Wrong Answer!! \n\n";
                wrong+=1;
            }

        }
        if(ctg==4){
            cout<<"------------------------------------------------------------------------------------ \n";
            cout<<"                                 Geography Trivia\n";
            cout<<"------------------------------------------------------------------------------------ \n";
            cout<<"Q. What is the longest river in the world?\n";
            getline(cin,ans);

            if(ans=="The Nile River" || ans=="Nile River" || ans=="River Nile" || ans=="nile" || ans=="Nile" ){
                cout<<"Correct Answer!! \n\n";
                right+=1;
            }
            else{
                cout<<"Wrong Answer!! \n\n";
                wrong+=1;
            }
            cout<<"Q. What is the tallest mountain in the world?\n";
            getline(cin,ans);

            if(ans=="Mount Everest" || ans=="mount everest" || ans=="Everest"){
                cout<<"Correct Answer!! \n\n";
                right+=1;
            }
            else{
                cout<<"Wrong Answer!! \n\n";
                wrong+=1;
            }


            cout<<"Q. What is the capital of Japan?\n";
            getline(cin,ans);

            if(ans=="Tokyo" || ans=="tokyo"){
                cout<<"Correct Answer!! \n\n";
                right+=1;
            }
            else{
                cout<<"Wrong Answer!! \n\n";
                wrong+=1;
            }

        }

        cout<<"The number of wrong answers :"<<wrong<<endl;
        cout<<"The number of right answers :"<<right;
        score=10*right;
        cout<<endl;


        cout<<"Your have scored = "<<score<<endl;
        cout<<endl;




    }


    cout<<endl;
    cout<<endl;
    string username;
    cout << "Enter your username: ";
    cin >> username;


    // read the existing score from the file
    map<string, int> triviaScores;
    ifstream scoreFile("../pfproject/trivia_scores.txt");
    if (scoreFile.is_open()) {
        string line;
        while (getline(scoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                triviaScores[user] = userScore;
            }
        }
        scoreFile.close();
    }
    cout<<"Scoreboard for Trivia is: \n";
    cout<<endl;


    cout<<"Your previous score for this game was : "<<triviaScores[username]<<endl;
    // add the new score to the existing score
    if (triviaScores.find(username) == triviaScores.end()) {
        triviaScores[username] = score;
    } else {
        triviaScores[username] += score;
    }


    // write the updated score back to the file
    ofstream scoreFiles("../pfproject/trivia_scores.txt", ios::trunc);
    if (scoreFiles.is_open()) {
        for (const auto& entry : triviaScores) {
            scoreFiles << entry.first << ": " << entry.second << endl;
        }
        scoreFiles.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
    cout<<"Your new Score for this game is "<<triviaScores[username]<<endl;
    cout<<"Your position rank for this game is: "<<getRank(triviaScores, username)<<endl;


}
// Function to play highLow
void highLow(){
    int secretNumber, userGuess;
    int attempts = 0;
    bool gameOver = false;
    int score = 0;
    srand(time(0));
    secretNumber = rand() % 100 + 1;


    cout << "\n"
            "  ___ ___ .___  ________  ___ ___           .____    ________  __      __._.\n"
            " /   |   \\|   |/  _____/ /   |   \\          |    |   \\_____  \\/  \\    /  \\  |\n"
            "/    ~    \\   /   \\  ___/    ~    \\  ______ |    |    /   |   \\   \\/\\/   /  |\n"
            "\\    Y    /   \\    \\_\\  \\    Y    / /_____/ |    |___/    |    \\        /  \\|\n"
            " \\___|_  /|___|\\______  /\\___|_  /          |_______ \\_______  /\\__/\\  /   __\n"
            "                                                                                     " << endl;
    cout << "I'm thinking of a number between 1 and 100." << endl;
    cout << "Can you guess what it is?" << endl;


    while (!gameOver) {
        cout << "Enter your guess: ";
        cin >> userGuess;
        attempts++;


        if (userGuess < secretNumber) {
            cout << "Too low!" << endl;
        } else if (userGuess > secretNumber) {
            cout << "Too high!" << endl;
        } else {
            cout << "Congratulations! You guessed the number in " << attempts << " attempts." << endl;
            gameOver = true;
            score = 10;
            cout<<endl;


            cout<<"You have scored = "<<score<<endl;
            cout<<endl;


        }
    }


    string username;
    cout << "Enter your username: ";
    cin >> username;


    // read the existing score from the file
    map<string, int> highLowScores;
    ifstream scoreFile("../pfproject/highlow_scores.txt");
    if (scoreFile.is_open()) {
        string line;
        while (getline(scoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                highLowScores[user] = userScore;
            }
        }
        scoreFile.close();
    }
    cout<<"Scoreboard for High-Low is: \n";
    cout<<endl;


    cout<<"Your previous score for this game was : "<<highLowScores[username]<<endl;
    // add the new score to the existing score
    if (highLowScores.find(username) == highLowScores.end()) {
        highLowScores[username] = score;
    } else {
        highLowScores[username] += score;
    }
    // write the updated score back to the file
    ofstream scoreFiles("../pfproject/highlow_scores.txt", ios::trunc);
    if (scoreFiles.is_open()) {
        for (const auto& entry : highLowScores) {
            scoreFiles << entry.first << ": " << entry.second << endl;
        }
        scoreFiles.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
    cout<<"Your new Score for this game is "<<highLowScores[username]<<endl;
    cout<<"Your position rank for this game is: "<<getRank(highLowScores, username)<<endl;


}

string currentime()
{
    time_t tt;


    struct tm* ti;


    time(&tt);


    ti = localtime(&tt);


    cout << "="
         << asctime(ti);
    return "currentime\n";
}
void leaderboards(string gameName) {
    cout<<endl;
    cout<<endl;
    cout << "\n"
            "  _      ______          _____  ______ _____    ____   ____          _____  _____  \n"
            " | |    |  ____|   /\\   |  __ \\|  ____|  __ \\  |  _ \\ / __ \\   /\\   |  __ \\|  __ \\ \n"
            " | |    | |__     /  \\  | |  | | |__  | |__) | | |_) | |  | | /  \\  | |__) | |  | |\n"
            " | |    |  __|   / /\\ \\ | |  | |  __| |  _  /  |  _ <| |  | |/ /\\ \\ |  _  /| |  | |\n"
            " | |____| |____ / ____ \\| |__| | |____| | \\ \\  | |_) | |__| / ____ \\| | \\ \\| |__| |\n"
            " |______|______/_/    \\_\\_____/|______|_|  \\_\\ |____/ \\____/_/    \\_\\_|  \\_\\_____/ \n"
            "                                                                                   \n"
            "                                                                                   ";
    cout<<endl;
    cout<<endl;
    cout << " Today is " << currentime() << ". Let's see who's on top!" <<endl;

    map<string, int> scores;
    ifstream scoreFile("../pfproject/" + gameName + "_scores.txt");
    if (scoreFile.is_open()) {
        string line;
        while (getline(scoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                scores[user] = userScore;
            }
        }
        scoreFile.close();
    } else {
        cout << "Scoreboard not found." << endl;
        return;
    }


    multimap<int, string, greater<int>> sortedScores;
    for (const auto& entry : scores) {
        sortedScores.insert(make_pair(entry.second, entry.first));
    }
    cout<<endl;


    cout << "Leaderboard for " << gameName << ":" << endl;
    cout << setw(10) << left << "Rank" << setw(20) << left << "Username" << setw(10) << left << "Score" << endl;
    cout << "---------------------------------------------------------" << endl;
    int rank = 1;
    int topThree = 3;
    for (const auto& entry : sortedScores) {
        string username = entry.second;
        int score = scores[username];
        if (rank <= topThree) {
            string bold = "\033[1m";
            string reset = "\033[0m";
            cout << setw(10) << left << rank << setw(28) << left << bold + username + reset << setw(10) << left << score << endl;
        } else {
            cout << setw(10) << left << rank << setw(20) << left << username << setw(10) << left << score << endl;
        }
        rank++;
    }
}
string goldbadge(){




    cout<<"\033[1;33m"
          "\n"
          "                    \n"
          "     .::--. .:.     \n"
          "     :.:=:. . :     \n"
          "      .:=:. :.      \n"
          "      .=+=:.-.      \n"
          "        -*=:        \n"
          "         =:         \n"
          "       .=+:..       \n"
          "      *=*+-.-+      \n"
          "     .::::::...     \033[0m  \n";
    return "Gold Badge";


}
string silverbadge(){


    cout<<"\033[1;37m"
          "\n"
          "                    \n"
          "     .::--. .:.     \n"
          "     :.:=:. . :     \n"
          "      .:=:. :.      \n"
          "      .=+=:.-.      \n"
          "        -*=:        \n"
          "         =:         \n"
          "       .=+:..       \n"
          "      *=*+-.-+      \n"
          "     .::::::...     \033[0m  \n";
    return "Silver Badge";


}
string bronzebadge(){


    cout<<"\033[38;5;160m"
          "\n"
          "                    \n"
          "     .::--. .:.     \n"
          "     :.:=:. . :     \n"
          "      .:=:. :.      \n"
          "      .=+=:.-.      \n"
          "        -*=:        \n"
          "         =:         \n"
          "       .=+:..       \n"
          "      *=*+-.-+      \n"
          "     .::::::...     \033[0m  \n";
    return "Bronze Badge";
}


void displayUserProfile(const string& username, const map<string, string>& game_preferences) {
    if (users.find(username) == users.end()) {
        cout << "User not found." << endl;
        return;
    }


    const User& user = users[username];


    cout << endl;
    cout << "Username: " << user.username << endl;
    cout << "Email: " << user.email_id << endl;
    cout << "Age: " << user.age << endl;
    cout << "Bio: " << user.bio << endl;
    cout << "Game Preferences: " << user.game_preferences << endl;


    cout << endl;
    cout << "Scores:" << endl;
    cout << endl;


    // Initialize score maps with default values of 0 for all users
    map<string, int> tictactoeScores;
    map<string, int> hangmanScores;
    map<string, int> rockpaperscissorScores;
    map<string, int> triviaScores;
    map<string, int> highLowScores;
    map<string, int> BingoScores;
    map<string, int> snakeandladderScores;
    for (const auto& user_pair : users) {
        tictactoeScores[user_pair.first] = 0;
        hangmanScores[user_pair.first] = 0;
        rockpaperscissorScores[user_pair.first] = 0;
        triviaScores[user_pair.first] = 0;
        highLowScores[user_pair.first] = 0;
    }


    // Load scores for each game
    ifstream tictactoeScoreFile("../pfproject/tictactoe_scores.txt");
    if (tictactoeScoreFile.is_open()) {
        string line;
        while (getline(tictactoeScoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                tictactoeScores[user] = userScore;
            }
        }
        tictactoeScoreFile.close();
    }


    ifstream hangmanScoreFile("../pfproject/hangman_scores.txt");
    if (hangmanScoreFile.is_open()) {
        string line;
        while (getline(hangmanScoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                hangmanScores[user] = userScore;
            }
        }
        hangmanScoreFile.close();
    }


    ifstream rpsScoreFile("../pfproject/rockpaperscissor_scores.txt");
    if (rpsScoreFile.is_open()) {
        string line;
        while (getline(rpsScoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                rockpaperscissorScores[user] = userScore;
            }
        }
        rpsScoreFile.close();
    }


    ifstream triviaScoreFile("../pfproject/trivia_scores.txt");
    if (triviaScoreFile.is_open()) {
        string line;
        while (getline(triviaScoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                triviaScores[user] = userScore;
            }
        }
        triviaScoreFile.close();
    }


    ifstream highLowScoreFile("../pfproject/highlow_scores.txt");
    if (highLowScoreFile.is_open()) {
        string line;
        while (getline(highLowScoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                highLowScores[user] = userScore;
            }
        }
        highLowScoreFile.close();
    }
    ifstream BingoScoreFile("../pfproject/Bingo_scores.txt");
    if (BingoScoreFile.is_open()) {
        string line;
        while (getline(BingoScoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                BingoScores[user] = userScore;
            }
        }
        BingoScoreFile.close();
    }
    ifstream snakeandladderScoreFile("../pfproject/snakeandladder_scores.txt");
    if (snakeandladderScoreFile.is_open()) {
        string line;
        while (getline(snakeandladderScoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                snakeandladderScores[user] = userScore;
            }
        }
        snakeandladderScoreFile.close();
    }
    // Display scores and ranks
    cout << setw(22) << left << "Game" << setw(10) << left << "Score" << setw(10) << left << "Rank" << endl;
    cout << setw(22) << left << "Tic-Tac-Toe" << setw(10) << left << tictactoeScores[username] << setw(10) << left << getRank(tictactoeScores, username) << endl;
    cout << setw(22) << left << "Hangman" << setw(10) << left << hangmanScores[username] << setw(10) << left << getRank(hangmanScores, username) << endl;
    cout << setw(22) << left << "Rock Paper Scissors" << setw(10) << left << rockpaperscissorScores[username] << setw(10) << left << getRank(rockpaperscissorScores, username) << endl;
    cout << setw(22) << left << "Trivia" << setw(10) << left << triviaScores[username] << setw(10) << left << getRank(triviaScores, username) << endl;
    cout << setw(22) << left << "High Low" << setw(10) << left << highLowScores[username] << setw(10) << left << getRank(highLowScores, username) << endl;
    cout << setw(22) << left << "Bingo" << setw(10) << left << BingoScores[username] << setw(10) << left << getRank(BingoScores, username) << endl;
    cout << setw(22) << left << "Snake and Ladder" << setw(10) << left << snakeandladderScores[username] << setw(10) << left << getRank(snakeandladderScores, username) << endl;
    cout << endl;
}


int getRank(const map<string, int>& scores, const string& username) {
    int rank = scores.size() + 1;
    if (scores.count(username) > 0) {
        rank = 1;
        for (const auto& score_pair : scores) {
            if (score_pair.first != username && score_pair.second > scores.at(username)) {
                rank++;
            }
        }
    }
    return rank;
}
void bingo(){
    cout<<endl;
    cout<<endl;
    cout<<"\n"
          "                                                                                           \n"
          "                                            ,--.                                ,----..    \n"
          "    ,---,.            ,---,               ,--.'|          ,----..              /   /   \\   \n"
          "  ,'  .'  \\        ,`--.' |           ,--,:  : |         /   /   \\            /   .     :  \n"
          ",---.' .' |        |   :  :        ,`--.'`|  ' :        |   :     :          .   /   ;.  \\ \n"
          "|   |  |: |        :   |  '        |   :  :  | |        .   |  ;. /         .   ;   /  ` ; \n"
          ":   :  :  /        |   :  |        :   |   \\ | :        .   ; /--`          ;   |  ; \\ ; | \n"
          ":   |    ;         '   '  ;        |   : '  '; |        ;   | ;  __         |   :  | ; | ' \n"
          "|   :     \\        |   |  |        '   ' ;.    ;        |   : |.' .'        .   |  ' ' ' : \n"
          "|   |   . |        '   :  ;        |   | | \\   |        .   | '_.' :        '   ;  \\; /  | \n"
          "'   :  '; |        |   |  '        '   : |  ; .'        '   ; : \\  |         \\   \\  ',  /  \n"
          "|   |  | ;         '   :  |        |   | '`--'          '   | '/  .'          ;   :    /   \n"
          "|   :   /          ;   |.'         '   : |              |   :    /             \\   \\ .'    \n"
          "|   | ,'           '---'           ;   |.'               \\   \\ .'               `---`      \n"
          "`----'                             '---'                  `---`                            \n"
          "                                                                                           ";

    cout<<endl;
    cout<<endl;
    srand(time(0));
    int card[CARD_ROWS][CARD_SIZE];
    generateCard(card);
    int num;
    bool won;
    do {
        printCard(card);
        cout<<endl;
        cout<<endl;
        cout << "Enter a number between 1 and 25: ";
        cin >> num;
        if (num > 0 && num <= MAX_NUM) {
            for (int i = 0; i < CARD_ROWS; i++) {
                for (int j = 0; j < CARD_SIZE; j++) {
                    if (card[i][j] == num) {
                        card[i][j] = 0;
                    }
                }
            }
        } else {
            cout << "Invalid number." << std::endl;
        }
        won = checkForWin(card);
    } while (!won);
    cout << "Congratulations! You won!" << std::endl;


    int score=10;
    cout<<endl;


    cout<<"You have scored = "<<score<<endl;
    cout<<endl;


    string username;
    cout << "Enter your username: ";
    cin >> username;


    // read the existing score from the file
    map<string, int> BingoScores;
    ifstream scoreFile("../pfproject/Bingo_scores.txt");
    if (scoreFile.is_open()) {
        string line;
        while (getline(scoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                BingoScores[user] = userScore;
            }
        }
        scoreFile.close();
    }
    cout<<"Scoreboard for Bingo is: \n";
    cout<<endl;


    cout<<"Your previous score for this game was : "<<BingoScores[username]<<endl;
    // add the new score to the existing score
    if (BingoScores.find(username) == BingoScores.end()) {
        BingoScores[username] = score;
    } else {
        BingoScores[username] += score;
    }


    // write the updated score back to the file
    ofstream scoreFiles("../pfproject/Bingo_scores.txt", ios::trunc);
    if (scoreFiles.is_open()) {
        for (const auto& entry : BingoScores) {
            scoreFiles << entry.first << ": " << entry.second << endl;
        }
        scoreFiles.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
    cout<<"Your new Score for this game is "<<BingoScores[username]<<endl;
    cout<<"Your position rank for this game is: "<<getRank(BingoScores, username)<<endl;




}
void generateCard(int card[CARD_ROWS][CARD_SIZE]) {
    int num;
    for (int i = 0; i < CARD_ROWS; i++) {
        for (int j = 0; j < CARD_SIZE; j++) {
            do {
                num = rand() % MAX_NUM + 1;
            } while (isNumberInCard(card, num));
            card[i][j] = num;
        }
    }
    card[2][2] = 0; // Free space
}


bool isNumberInCard(int card[CARD_ROWS][CARD_SIZE], int num) {
    for (int i = 0; i < CARD_ROWS; i++) {
        for (int j = 0; j < CARD_SIZE; j++) {
            if (card[i][j] == num) {
                return true;
            }
        }
    }
    return false;
}


bool checkForWin(int card[CARD_ROWS][CARD_SIZE]) {
    int count;
    for (int i = 0; i < CARD_ROWS; i++) {
        count = 0;
        for (int j = 0; j < CARD_SIZE; j++) {
            if (card[i][j] == 0) {
                count++;
            }
        }
        if (count == CARD_SIZE) {
            return true;
        }
    }
    for (int j = 0; j < CARD_SIZE; j++) {
        count = 0;
        for (int i = 0; i < CARD_ROWS; i++) {
            if (card[i][j] == 0) {
                count++;
            }
        }
        if (count == CARD_ROWS) {
            return true;
        }
    }
    if (card[0][0] == 0 && card[1][1] == 0 && card[2][2] == 0 && card[3][3] == 0 && card[4][4] == 0) {
        return true;
    }
    if (card[0][4] == 0 && card[1][3] == 0 && card[2][2] == 0 && card[3][1] == 0 && card[4][0] == 0) {
        return true;
    }
    return false;
}


void printCard(int card[CARD_ROWS][CARD_SIZE]) {
    for (int i = 0; i < CARD_ROWS; i++) {
        for (int j = 0; j < CARD_SIZE; j++) {
            if (card[i][j] == 0) {
                cout << "[--] ";
            } else {
                cout << "[" << card[i][j] << "] ";
            }
        }
        cout << std::endl;
    }
}
void snakeandladder(){
    srand(time(0)); // seed the random number generator


    map<int, int> snl = {{4, 14}, {9, 31}, {17, 7}, {20, 38}, {28, 84}, {40, 59}, {51, 67}, {54, 34}, {62, 19}, {63, 81}, {64, 60}, {71, 91}, {87, 24}, {93, 73}, {95, 75}, {99, 78}};


    int player1Pos = 1, player2Pos = 1;
    int currentPlayer = 1;
    cout<<"_______________________________________________________________________________________"<<endl;
    cout<<"\n"
          " ___  _  _    __    _  _  ____      __    _  _  ____     __      __    ____  ____  ____  ____ \n"
          "/ __)( \\( )  /__\\  ( )/ )( ___)    /__\\  ( \\( )(  _ \\   (  )    /__\\  (  _ \\(  _ \\( ___)(  _ \\\n"
          "\\__ \\ )  (  /(__)\\  )  (  )__)    /(__)\\  )  (  )(_) )   )(__  /(__)\\  )(_) ))(_) ))__)  )   /\n"
          "(___/(_)\\_)(__)(__)(_)\\_)(____)  (__)(__)(_)\\_)(____/   (____)(__)(__)(____/(____/(____)(_)\\_)";
    while (true) {
        cout<<endl;
        cout<<endl;
        cout<<"___________________________________________________________________________________"<<endl;




        cout << "Player " << currentPlayer << ", it's your turn. You are on square " << (currentPlayer == 1 ? player1Pos : player2Pos) << "." << endl;
        cout << "Player " << currentPlayer << ", enter your roll: ";
        int roll;
        cin >> roll;


        if (roll < 1 || roll > 6) {
            cout << "Invalid roll. Please enter a number between 1 and 6." << endl;
            continue;
        }


        if (currentPlayer == 1) {
            movePlayer(player1Pos, roll, snl);
            if (player1Pos == 100) {


                cout << "Congratulations!! Player 1 wins!" << endl;
                break;
            }
            currentPlayer = 2;
        } else {
            movePlayer(player2Pos, roll, snl);
            if (player2Pos == 100) {
                cout << "Congratulations!! Player 2 wins!" << endl;
                break;
            }
            currentPlayer = 1;
        }
    }
    int score=10;
    cout<<endl;


    cout<<"Your have scored = "<<endl;
    cout<<endl;


    string username;
    cout << "Enter your username: ";
    cin >> username;


    // read the existing score from the file
    map<string, int> snakeandladderScores;
    ifstream scoreFile("../pfproject/snakeandladder_scores.txt");
    if (scoreFile.is_open()) {
        string line;
        while (getline(scoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                snakeandladderScores[user] = userScore;
            }
        }
        scoreFile.close();
    }
    cout<<"Scoreboard for Snake and Ladder is: \n";
    cout<<endl;
    cout<<"Your previous score for this game was : "<<snakeandladderScores[username]<<endl;
    // add the new score to the existing score
    if (snakeandladderScores.find(username) == snakeandladderScores.end()) {
        snakeandladderScores[username] = score;
    } else {
        snakeandladderScores[username] += score;
    }


    // write the updated score back to the file
    ofstream scoreFiles("../pfproject/snakeandladder_scores.txt", ios::trunc);
    if (scoreFiles.is_open()) {
        for (const auto& entry : snakeandladderScores) {
            scoreFiles << entry.first << ": " << entry.second << endl;
        }
        scoreFiles.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
    cout<<"Your Score for this game is "<<snakeandladderScores[username]<<endl;
    cout<<"Your position rank for this game is: "<<getRank(snakeandladderScores, username)<<endl;




}
void movePlayer(int& playerPos, int roll, map<int, int>& snl) {
    playerPos += roll;
    if (snl.find(playerPos) != snl.end()) {
        cout << "Oops, landed on a snake! Player moves from " << playerPos << " to " << snl[playerPos] << endl;
        playerPos = snl[playerPos];
    } else if (playerPos > 100) {
        cout << "Oops, exceeded the board limit! Player moves from " << playerPos << " to " << (playerPos - roll) << endl;
        playerPos -= roll;
    }
}




void achievements(const string& username) {
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"\n"
          "               _     _                                     _       \n"
          "     /\\       | |   (_)                                   | |      \n"
          "    /  \\   ___| |__  _  _____   _____ _ __ ___   ___ _ __ | |_ ___ \n"
          "   / /\\ \\ / __| '_ \\| |/ _ \\ \\ / / _ \\ '_ ` _ \\ / _ \\ '_ \\| __/ __|\n"
          "  / ____ \\ (__| | | | |  __/\\ V /  __/ | | | | |  __/ | | | |_\\__ \\\n"
          " /_/    \\_\\___|_| |_|_|\\___| \\_/ \\___|_| |_| |_|\\___|_| |_|\\__|___/\n"
          "                                                                   \n"
          "                                                                   ";


    cout<<endl;
    cout<<endl;
    cout<<endl;
    map<string, int> tictactoeScores;
    map<string, int> hangmanScores;
    map<string, int> rockpaperscissorScores;
    map<string, int> triviaScores;
    map<string, int> highLowScores;
    map<string, int> BingoScores;
    map<string, int> snakeandladderScores;


    // Load scores for each game
    ifstream tictactoeScoreFile("../pfproject/tictactoe_scores.txt");
    if (tictactoeScoreFile.is_open()) {
        string line;
        while (getline(tictactoeScoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                if (user == username) {
                    tictactoeScores[user] = userScore;
                }
            }
        }
        tictactoeScoreFile.close();
    }


    ifstream hangmanScoreFile("../pfproject/hangman_scores.txt");
    if (hangmanScoreFile.is_open()) {
        string line;
        while (getline(hangmanScoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                if (user == username) {
                    hangmanScores[user] = userScore;
                }
            }
        }
        hangmanScoreFile.close();
    }


    ifstream rockpaperscissorScoreFile("../pfproject/rockpaperscissor_scores.txt");
    if (rockpaperscissorScoreFile.is_open()) {
        string line;
        while (getline(rockpaperscissorScoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                if (user == username) {
                    rockpaperscissorScores[user] = userScore;
                }
            }
        }
        rockpaperscissorScoreFile.close();
    }


    ifstream triviaScoreFile("../pfproject/trivia_scores.txt");
    if (triviaScoreFile.is_open()) {
        string line;
        while (getline(triviaScoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                if (user == username) {
                    triviaScores[user] = userScore;
                }
            }
        }
        triviaScoreFile.close();
    }


    ifstream highLowScoreFile("../pfproject/highlow_scores.txt");
    if (highLowScoreFile.is_open()) {
        string line;
        while (getline(highLowScoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                if (user == username) {
                    highLowScores[user] = userScore;
                }
            }
        }
        highLowScoreFile.close();
    }


    ifstream BingoScoreFile("../pfproject/bingo_scores.txt");
    if (BingoScoreFile.is_open()) {
        string line;
        while (getline(BingoScoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                if (user == username) {
                    BingoScores[user] = userScore;
                }
            }
        }
        BingoScoreFile.close();
    }


    ifstream snakeandladderScoreFile("../pfproject/snakeandladder_scores.txt");
    if (snakeandladderScoreFile.is_open()) {
        string line;
        while (getline(snakeandladderScoreFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string user = line.substr(0, pos);
                int userScore = stoi(line.substr(pos + 1));
                if (user == username) {
                    snakeandladderScores[user] = userScore;
                }
            }
        }
        snakeandladderScoreFile.close();
    }


    // Display badges for each game
    displayBadges("Tic-Tac-Toe", tictactoeScores);
    displayBadges("Hangman", hangmanScores);
    displayBadges("Rock, Paper, Scissor", rockpaperscissorScores);
    displayBadges("Trivia", triviaScores);
    displayBadges("High Low", highLowScores);
    displayBadges("Bingo", BingoScores);
    displayBadges("Snake and Ladder", snakeandladderScores);
}


void displayBadges(const string& game, const map<string, int>& scores) {
    cout << "--------------------" << game << " Badges--------------------" << endl;


    for (const auto& score : scores) {
        if (score.second >= 1000) {
            cout << score.first << " earned a Golden Badge for " << game << "!" << endl;
            goldbadge();
        } else if (score.second >= 500) {
            cout << score.first << " earned a Silver Badge for " << game << "!" << endl;
            silverbadge();
        } else if (score.second >= 200) {
            cout << score.first << " earned a Bronze Badge for " << game << "!" << endl;
            bronzebadge();
        } else {
            cout << score.first << " did not earn a badge for " << game << "." << endl;
        }
    }
}

