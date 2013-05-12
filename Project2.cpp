#include<string>
using std::string;
#include<fstream>
using std::ifstream;
using std::ofstream;
using std::getline;
#include<sstream>
using std::stringstream;
#include<iostream>
using std::istream;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cin;
using std::cout;
using std::getline;
#include<map>
using std::map;

int current_year;



class AgeError
{
    public:

    AgeError(const string d){description = d;}
    const string what(){return description;}

    private:
    string description;
};

class Player
{
    public:
    Player(){birth_year_ = 0; category_ = "U0"; reg_status_ = "not paid";}
    Player(int birth_year0, string category0){birth_year_ = birth_year0; category_ = category0;}
    Player(int birth_year0, string category0, string reg_status0){birth_year_ = birth_year0; category_ = category0; reg_status_ = reg_status0;}

    //Get methods
    int birth_year(){return birth_year_;}
    string category(){return category_;}
    string reg_status(){return reg_status_;}

    //Set methods not implemented in further code
    void set_birth_year(int year){birth_year_ = year;}
    void set_reg_status(string status){reg_status_ = status;}


    void const write(ofstream & ofs)
    {
        ofs << birth_year_ << endl << category_ << endl << reg_status_ << endl;
    }

    void const display()
    {
        cout << birth_year_ << endl << category_ << endl << reg_status_ << endl << endl;
    }

    private:
    int birth_year_; string category_; string reg_status_;
};

string calc_category(int current_year, const int birth_year_) throw(AgeError)
{
    int age = current_year - birth_year_;
    if(age < 4 || age > 16)
        {
            throw( AgeError("This person does not meet the league's age requirement. \n"));
        }
    if(age < 17 && age >= 14)
        return "U17";
    if(age < 14 && age >= 12)
        return "U14";
    if(age < 12 && age >= 10)
        return "U12";
    if(age < 10 && age >= 8)
        return "U10";
    if(age < 8 && age >= 6)
        return "U8";
    if(age < 6 && age >=4)
        return "U6";
}

Player Add_player() //does not necessarily add the player to the file, but returns a Player object with the user's specifications for the player to be added.
{
    string new_player_name, new_player_category, new_player_reg_status, str_birth_year;
    int int_birth_year;
    stringstream ss;
    cout << "Give the year of birth of the player you are registering: ";
    getline(cin, str_birth_year);
    ss << str_birth_year;
    ss >> int_birth_year;
    new_player_category = calc_category(current_year, int_birth_year);
    cout << "Is this player's registration status paid or not paid? ";
    getline(cin, new_player_reg_status);
    return Player(int_birth_year, new_player_category, new_player_reg_status);
}

void run_registration()
{
    ifstream ifs("League.txt");
    map<string, Player> Players_info;
    string player_name, str_birth_year_dummy, reg_status0, category0, blank_line;
    int int_birth_year;
    stringstream ss;

    while(getline(ifs, player_name))
    {
        getline(ifs, str_birth_year_dummy); //
        ss << str_birth_year_dummy;         //necessary to avoid issues with streams
        ss >> int_birth_year;               //
        getline(ifs, category0);
        getline(ifs, reg_status0);
        Players_info[player_name] = Player(int_birth_year,
                                                category0,
                                                    reg_status0);
        getline(ifs, blank_line); //Without this, the blank line separating players' info would be read in as the next player name
    }

    char command = '-';
    while(true){ //while user does not want to quit and save
    cout << "(s)ave and quit   (a)dd new player to league   (g)enerate age group roster" << endl
         << "(e)dit player information   (l)ookup a player" << endl;
    cout << "command: ";
    cin >> command;
    cin.get();

    switch(command){
        case 's':{ //Save updated league player info to file
            ofstream ofs("League.txt");
            for(map<string, Player>::iterator itr = Players_info.begin(); itr != Players_info.end(); ++itr)
                {
                    ofs << itr->first << endl;
                    (itr->second).write(ofs);
                    ofs << endl;
                }
            return;
        }
        case 'a':{ //add player to league
            string new_player_name;
            Player new_player;
            cout << "Please give the name of the player to add: ";
            getline(cin, new_player_name);
            try{
                new_player = Add_player();
            }
            catch(AgeError e){
                cout << e.what() << endl;
                break;
            }
            Players_info[new_player_name] = new_player;
            cout << "Your player has been added to the system. " << endl << endl;
            break;
        }
        case 'g':{ //generate list of all players in a category
            string write_category, save_file;
            cout << "For which age group would you like to create a list of players? "; //Will Take Ux input
            getline(cin, write_category);
            cout << "Name a file to which the list will be saved. ";
            getline(cin, save_file);
            ofstream ofs(save_file.c_str());
            for(map<string,Player>::iterator itr = Players_info.begin(); itr != Players_info.end(); ++itr)
            {
                if((itr->second).category() == write_category)
                {
                    ofs << itr->first << endl;
                    (itr->second).write(ofs);
                    ofs << endl;
                }
            }
            cout << "Read the file to see the generated roster. " << endl;
            break;
        }
        case 'e':{ //Edit a player's information
            string New_Name, str_New_Birth_Year, New_Category, New_Reg_Status;
            int int_New_Birth_Year;
            string Player_Name;
            stringstream Temp;
            cout << "Player who's info to edit: ";
            getline(cin, Player_Name);
            map<string,Player>::iterator temp_itr = Players_info.find(Player_Name);
            cout <<  "Enter the player's name: ";
            getline(cin, New_Name);
            cout << "Enter the player's birth year: ";
            getline(cin, str_New_Birth_Year);
            Temp << str_New_Birth_Year;
            Temp >> int_New_Birth_Year;
            try{
                New_Category = calc_category(current_year, int_New_Birth_Year);
            }
            catch(AgeError e){
                cout << e.what() << endl << endl;
                break;
            }
            cout << "Is the player's status now paid or not paid? ";
            getline(cin, New_Reg_Status);
            Players_info.erase(temp_itr);
            Players_info[New_Name] = Player(int_New_Birth_Year, New_Category, New_Reg_Status);
            cout << "The player's information has been successfully edited!" << endl << endl;
            break;
        }
        case 'l':{
            string search_player;
            cout << "Player's name: ";
            getline(cin, search_player);
            map<string, Player>::iterator search_itr = Players_info.find(search_player);
            if(search_itr == Players_info.end())
            {
                cout << "Player not found" << endl << endl;
                break;
            }
            cout << endl << (search_itr->first) << endl;
            (search_itr->second).display();
            break;
        }

                    }

                }
    }


int main()
{
    stringstream temp;
    ifstream ifs("current_year.txt");
    string str_current_year;
    getline(ifs, str_current_year);
    temp << str_current_year;
    temp >> current_year;

    run_registration();
    return 0;
}
