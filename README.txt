Youth Soccer Registration Program
Version 1

DESIGN DOCUMENT -- FINAL


Global constant:
	
	int current_year;

COMPONENT: AgeError

Exception Class

Method:

	AgeError(const string d)
		Initializes an exception of type AgeError
	const string what()
		A get method for an object of class AgeError




COMPONENT: Player

Represents a player's information, excluding their name.

Methods:   

    Player(int birth_year0, string category0, string reg_status0)    
	A constructor that initializes all the private data members of an object of type 	Player.	 

    int birth_year()
    string category()
    string reg_status()
	These are "get methods" used to easily access the class' private data.


    void const write(ofstream & ofs)
	write an object's private data members to a given file.
    
    void const display()
   	display an object's private data members to the user.



COMPONENT: calc_category

Responsibilities:
	-Returns string Ux, depending on the appropriate age group for the player

Collaborators: AgeError



COMPONENT: Add_Player

Responsibilities:
	-Reads in variables that are of the same type as private members of class Player
	-returns new player object

Collaborators: calc_category

COMPONENT: run_registration

Responsibilities:
	-runs the registration tool
	-Handles all user interaction through other components

Collaborators: Add_player, Player, calc_category 