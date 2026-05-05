/*
* File: Game.cpp
* Author: Brian Noutchang
* Description: This file contains the Game class definitions
*/

#include "Game.h"

// Name: Game Constructor
// Desc - Sets m_filename based on string passed
// Preconditions - Input file passed
// Postconditions - m_filename updated
Game::Game(string filename) {
    m_filename = filename;
}


// Name: LoadFile
// Desc - Opens file and reads in each Pokemon into m_PokeDex
// Preconditions - Input file passed and populated with Pokemon
// Postconditions - m_pokeDex populated with Pokemon
void Game::LoadFile()
{
    ifstream inpStream; // used to read from the file
    inpStream.open(m_filename);

    for (int i = 0; i < TOTAL_POKEMON; i++) {
        
        int num, cp, rarity; // attributes of the pokemon
        string name;

        // file is in order -> num name cp rarity, so read from the file 4 times per iteration
        inpStream >> num;
        inpStream >> name;
        inpStream >> cp;
        inpStream >> rarity;

        // create a new pokemon with the read attributes
        Pokemon currPokemon = Pokemon(num, name, cp, rarity);
        // add the pokemon to the array
        m_pokeDex[i] = currPokemon;

        Pokemon p = m_pokeDex[i];
    }
    
    inpStream.close();
}

// Name: DisplayPokeDex
// Desc - Display all Pokemon in the m_pokeDex
// Preconditions - m_pokeDex populated with Pokemon
// Postconditions - None
void Game::DisplayPokeDex()
{
    for (int i = 0; i < TOTAL_POKEMON; i++) {
        Pokemon p = m_pokeDex[i]; //current pokemon
        cout << setw(NUM_WIDTH) << p.GetNum() << ' ' << setw(NAME_WIDTH) << p.GetName() << ' ' << setw(NUM_WIDTH) << p.GetCP() << ' ' << p.GetRarity() << endl;
    }
    cout << endl;
}

// Name: MainMenu
// Desc - Displays main menu
// Preconditions - m_pokeDex populated
// Postconditions - Keeps calling until quit chosen
void Game::MainMenu()
{
    int choice; // used to choose a menu entry

    do
    {
        cout << "What would you like to do?:\n";
        cout << "1. Display Complete PokeDex\n";
        cout << "2. Display your Team\n";
        cout << "3. Search for a new Pokemon\n";
        cout << "4. Battle your Pokemon\n";
        cout << "5. Train your Pokemon\n";
        cout << "6. Exit\n";

        cin >> choice;
        /*execute different actions based on menu choice
        invalid entry will reprompt */
        switch (choice) {
            case 1: DisplayPokeDex();
            break;
            case 2: DisplayTeam();
            break;
            case 3: CatchPokemon();
            break;
            case 4: BattlePokemon();
            break;
            case 5: TrainPokemon();
            break;
            case 6: cout << "Thank you for playing!\n\n";
            break;
            default: cout << "Invalid entry\n";
        }

    } while (choice !=6);
}

// Name: CatchPokemon
// Desc - Main function for catching pokemon. Does the following:
//        1. Calls CatchMenu and stores rarity chosen
//        2. Randomly chooses a number between 0 - 99
//        3. If random number is less than rarity, calls FoundPokemon
//        4. If random number is greater than rarity, indicates none found
//        5. Call AddPokemon if new Pokemon is caught
// Preconditions - m_pokeDex has maximum CP for Pokemon
// Postconditions - After random Pokemon of that rarity is chosen,
//                  this function reduces the CP of between 30-50%
//                  and adds to m_team
void Game::CatchPokemon()
{
    int rarity = CatchMenu(); // the rarity that the user chooses in CatchMenu
    int randNum = rand() % 100; // choose a random number between 0-99;
    cout << "You start to search...\n";

    //common
    if (rarity == 1)
    {
        if (randNum < COMMON)
            AddPokemon(FoundPokemon(rarity));
        else
            cout << "No Pokemon found.\n\n";
    }
    //uncommon
    else if (rarity == 2)
    {
        if (randNum < UNCOMMON)
            AddPokemon(FoundPokemon(rarity));
        else
            cout << "No Pokemon found.\n\n";
    }
    //ultra rare
    else if (rarity == 3)
    {
        if (randNum < ULTRA)
            AddPokemon(FoundPokemon(rarity));
        else
            cout << "No Pokemon found.\n\n";
    }

}

// Name: CatchMenu
// Desc - User chooses which rarity of Pokemon to try and catch
// Preconditions - m_pokeDex has rarities of 1-3
// Postconditions - Returns choice of 1-3
int Game::CatchMenu()
{
    int choice;
    //input validation with do-while
    do {
        cout << "What rarity of Pokemon would you like catch?:\n";
        cout << "1. Common (High Probability)\n";
        cout << "2. Uncommon (Normal Probability)\n";
        cout << "3. Ultra Rare (Extremely Low Probability)\n";
        cin >> choice;
    } while (choice < 1 || choice > 3);

    return choice;
}

// Name: FoundPokemon
// Desc - Based on rarity passed in, randomly chooses one Pokemon
//        from the m_pokeDex, updates the CP, and adds to m_team
// Preconditions - m_pokeDex has maximum CP for Pokemon
// Postconditions - After random Pokemon of that rarity is chosen,
//                  this function reduces the CP of between 30-50%
//                  and adds to m_team
Pokemon Game::FoundPokemon(int rarity)
{
    Pokemon pk; //the found pokemon
    do {
        int i = rand() % TOTAL_POKEMON; //choose a random pokemon out of the full list (0-150)
        pk = m_pokeDex[i];
    } while (pk.GetRarity() != rarity); //keep looping as long as chosen pokemon doesn't match the rarity

    cout << "You found a " << pk.GetName() << endl;

    //generate random number between 30-50 to find percent reduction for the cp
    int reduceAmount = rand() % (MAX_FIND + 1 - MIN_FIND) + MIN_FIND;
    int newCP = pk.GetCP() - (pk.GetCP() * reduceAmount/100); //the new cp after the percent reduction
    pk.SetCP (newCP);
    return pk;
}

// Name: AddPokemon
// Desc - Figures out where to insert newly found Pokemon
//        If m_team has opening, inserts into first open slot
//        If m_team is full, inserts into first slot with lower CP
//        If m_team is full, and new Pokemon has lower CP, does not insert
//        Tells user if not inserted
// Preconditions - None
// Postconditions - New Pokemon is added to m_team if possible
//                  or user is notified that there is no room
void Game::AddPokemon(Pokemon newPokemon)
{
    //if team isn't full, find first open slot and insert there
    if (TeamSize() < NUM_TEAM)
    {
        for (int i = 0; i < NUM_TEAM; i++) {
            if (FindPokemon(m_team[i].GetName()) == -1) {
                m_team[i] = newPokemon;
                cout << newPokemon.GetName() << " added to your team!\n\n";
                return;
            }
        }
    }
    //if the team is full, find first lower cp and replace
    else if (TeamSize() == NUM_TEAM)
    {
        for (int i = 0; i < NUM_TEAM; i++) {
            if (m_team[i].GetCP() < newPokemon.GetCP()) {
                cout << newPokemon.GetName() << " replaced " << m_team[i].GetName() << endl << endl;
                m_team[i] = newPokemon;
                return;
            }
        }
    }
    //this will only run if unsuccesful in adding to team
    cout << newPokemon.GetName() << " was not added to the team-- CP is too low.\n\n";
}

// Name: TeamSize
// Desc - Iterates through m_team to see how many team members exist
// Preconditions - m_team exists
// Postconditions - Returns 0 if empty otherwise up to 4
int Game::TeamSize() {
    int counter = 0;
    for (int i = 0; i < NUM_TEAM; i++) {
        //check if the name is found in pokeDex
        if (FindPokemon(m_team[i].GetName()) != -1)
            counter++;
    }

    return counter;
}

// Name: DisplayTeam
// Desc - Iterates through m_team to display information about team
// Preconditions - m_team exists
// Postconditions - None
void Game::DisplayTeam()
{
    for (int i = 0; i < TeamSize(); i++) {
        Pokemon p = m_team[i]; //current pokemon
        cout << i+1 << " - " << setw(NAME_WIDTH) << p.GetName() << ' ' << setw(NUM_WIDTH) << p.GetCP() << endl;
    }

    if (TeamSize() == 0) {
        cout << "You have no team yet. Maybe search for a Pokemon?!\n";
    }
}

// Name: FindPokemon
// Desc - Iterates through m_pokeDex to see if matching name exists
//        Returns index if found else -1
// Preconditions - m_pokeDex exists
// Postconditions - Returns index of match, else -1
int Game::FindPokemon(string name)
{
    for (int i = 0; i < TOTAL_POKEMON; i++) {
        //check if the name matches
        if (m_pokeDex[i].GetName() == name)
            return i;
    }
    return -1;
}

// Name: TrainPokemon
// Desc - If m_team size is 0. If 0, tells user and returns to main menu
//        If m_team size > 0, displays team (DisplayTeam)
//        Asks user to chose one team member
//        Calls Train on chosen team member and passes corresponding CP
//             value from m_pokeDex (m_pokeDex holds max CP for all)
// Preconditions - m_team and m_pokeDex exists
// Postconditions - Calls Train on chosen team member
void Game::TrainPokemon() {
    if (TeamSize() == 0) {
        cout << "You have no team yet. Maybe search for a Pokemon?!\n\n";
        return;
    }

    //get a choice from the user
    int choice;
    do {
        cout << "Which of your Pokemon would you like to train?:\n";
        DisplayTeam();
        cin >> choice;
    } while (choice < 1 || choice > TeamSize());

    Pokemon chosenPk = m_team[choice-1]; //the chosen pokemon
    int maxCP = m_pokeDex[FindPokemon(chosenPk.GetName())].GetCP(); //the max cp of the chosen pokemon

    //finally train
    m_team[choice-1].Train(maxCP);
    cout << "Your " << chosenPk.GetName() << "'s CP goes up!\n\n";
}

// Name: BattlePokemon
// Desc - If m_team size is 0. If 0, tells user and returns to main menu
//        If m_team size > 0, randomly chooses Pokemon to fight from
//        m_pokeDex. Asks which team member to use in battle.
//        Random enemy has a CP of 0 - max CP + 200.
//        Compares CP for random enemy and team member.
//        If team member wins, indicates and returns to main menu
//        If team member loses, indicates, sets CP to 0, returns to menu
// Preconditions - m_team exists
// Postconditions - Either the player wins or team member's CP is set to 0
void Game::BattlePokemon() {
    if (TeamSize() == 0) {
        cout << "You have no team yet. Maybe search for a Pokemon?!\n\n";
        return;
    }

    int randOpp = rand() % TOTAL_POKEMON; //choose random pokemon to fight against
    Pokemon randPk = m_pokeDex[randOpp];
    int randCP = rand() % (randPk.GetCP() + ENEMY_ADD); //give enemy a CP between 0 - maxCP+200
    randPk.SetCP (randCP);

    cout << "You are going to fight a " << randPk.GetName() << endl;
    cout << "The enemy has a CP of " << randPk.GetCP() << endl;

    //get a choice from the user
    int choice;
    do {
        cout << "Which of your Pokemon would you like to use?:\n";
        DisplayTeam();
        cin >> choice;
    } while (choice < 1 || choice > TeamSize());

    Pokemon chosenPk = m_team[choice-1]; //the pokemon that the user chose

    //if your pokemon cp is greater then you win, else you lose
    if (chosenPk.GetCP() > randPk.GetCP())
        cout << "You won!!\n\n";
    else {
        cout << "You lost.\n" << "Your " << chosenPk.GetName() << " can't lift its head.\n";
        cout << "You should replace it.\n\n";
        m_team[choice-1].SetCP(0);
    }

}

// Name: Start
// Desc - Calls LoadFile then MainMenu
// Preconditions - m_fileName is populated
// Postconditions - Exits game when done running
void Game::Start() {
    LoadFile();
    MainMenu();
}