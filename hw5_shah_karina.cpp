/*
Name: Karina Shah
Date: 4/27/23
Description: Main driver file for zombie conga
Usage: exe -s <int>
*/
#include <iostream>
#include <string.h>
#include "zombie_shah.h"
#include "linkedlist_shah.hpp"

using namespace std;

// Function Protoypes
void engine_action(LinkedList<Zombie>* list, Zombie randomZomb);
void caboose_action(LinkedList<Zombie>* list, Zombie randomZomb);
void jump_in_action(LinkedList<Zombie>* list, Zombie randomZomb);
void everyone_out_action(LinkedList<Zombie>* list, Zombie randomZomb);
void you_out_action(LinkedList<Zombie>* list, Zombie randomZomb);
void brains_action(LinkedList<Zombie>* list, Zombie randomZomb);
void rainbow_action(LinkedList<Zombie>* list, Zombie randomZomb);
void friends_action(LinkedList<Zombie>* list, Zombie randomZomb);

int main(int argc, char** argv){
    if(argc == 3){ // Checks if seed is given along with -s
        srand(atoi(argv[2])); // Assigns given seed
    }
    else{
        srand (time(0)); // If no seed is given, them defaults to 0.
    }
    char colors[] = {'R', 'Y', 'G', 'B', 'C', 'M'}; // Array  for different types
    // Array for different actions
    const char* options[8] = {"Engine!", "Caboose!", "Jump in the Line!", "Everyone Out!", "You Out!", "Brains!", "Rainbow Brains!", "Making new Friends!"};
    LinkedList <Zombie>* list = new LinkedList<Zombie>(); // Creates new Zombie list
    int col = rand() % 6; // Generates random number for color
    Zombie randomZomb(colors[col]); // Creates zombie on the stack
    rainbow_action(list, randomZomb); // Rainbow action to create list
    for(int i = 0; i < 3; i++){ // Three brain actions to create list
        col = rand() % 6; // New color each time
        randomZomb.setType(colors[col]);
        brains_action(list, randomZomb);
    }
    int rounds; // Number of rounds user wants to complete
    int count = 0; // Number of rounds completed
    cout << "It's time to make zombies conga! How many rounds would you like to run for?: "; // Ask user for rounds
    cin >> rounds; // Take in rounds
    while(count != rounds){  // While rounds aren't completed
        if(count % 5 == 0){ // If count is a factor of 5, remove from front and back
            try{
                list->RemoveFromFront();
            }
            catch(invalid_argument){
                cout << "It's empty";
            }
            try{
                list->RemoveFromEnd();
            }
            catch(invalid_argument){
                cout << "It's empty";
            }
        }
        cout << "Round: " << count << endl; // Print out information
        cout <<"Size: " << list->Length() << " :: ";
        list->PrintList();
        int opt = rand() % 8; // Choose a random action
        col = rand() % 6; // Choose a random color
        randomZomb.setType(colors[col]); // Set zombie to new color
        cout << "New BaseZombie: [" << colors[col] << "] -- Action: [" << options[opt] << "]" << endl; // Print out zombie and action info
        switch(opt){ // Switch statements to call a function
            case 0:
                engine_action(list, randomZomb);
                break;
            case 1:
                caboose_action(list, randomZomb);
                break;
            case 2:
                jump_in_action(list, randomZomb);
                break;
            case 3:
                everyone_out_action(list, randomZomb);
                break;
            case 4:
                you_out_action(list, randomZomb);
                break;
            case 5:
                brains_action(list, randomZomb);
                break;
            case 6:
                rainbow_action(list, randomZomb);
                break;
            case 7:
                friends_action(list, randomZomb);
                break;
        }
        if(list->Length() == 0){ // If list length is 0, end game and free all memory
            cout << "Party is Over";
            list->Empty();
            cout << "deleting list" << endl;
            delete list;
            return 0;
        }
        else{ // Print out the new conga line
            cout << "The conga line is now:" << endl;
            cout << "Size: " << list->Length() << " :: ";
            list->PrintList();
            cout << "**************************************************" << endl << endl;
            count++; // Incrememt the count of rounds completed
        }
        if(count == rounds){ // If all rounds are completed
            char ans;
            cout << "Would you like to continue the party? (y/n): "; // Ask user if they want to play more rounds
            cin >> ans;
            while(ans != 'y' && ans != 'n'){ // Make sure answer is valid
                cout << "Invalid input. Please answer y or n: ";
                cin >> ans;
            }
            if(ans == 'n'){ // If they choose to end it, tell them the party is over and free all memory and end the program
                cout << "Party is Over!";
                //delete(randomZomb*);
                list->Empty();
                delete list;
                return 0;
            }
            else{ // Else, reset rounds to the new rounds and then resent count.
                cout << "How many rounds would you like to add?: ";
                cin >> rounds;
                count = 0;
            }
        }
    }
}

// Add randomZomb to the list at the front
void engine_action(LinkedList<Zombie>* list, Zombie randomZomb){
    list->AddToFront(randomZomb);
}

// Add randomZomb to the list at the end
void caboose_action(LinkedList<Zombie>* list, Zombie randomZomb){
    list->AddToEnd(randomZomb);
}

// Add zombie to a random index of the list
void jump_in_action(LinkedList<Zombie>* list, Zombie randomZomb){
    int length = list->Length();
    int pos = rand()%(length + 1);
    try{
        list->AddAtIndex(randomZomb, pos);
    }
    catch(out_of_range const&){
        while(pos > length - 1 && pos < 0){
            pos = rand()%(length + 1);
        }
        list->AddAtIndex(randomZomb, pos);
    }
}

// Remove everyone of a certain type from the list
void everyone_out_action(LinkedList<Zombie>* list, Zombie randomZomb){
    try{
        list->RemoveAllOf(randomZomb);
    }
    catch(invalid_argument const &){
        return;
    }
}

// Remove the first zombie of a certain type from the list
void you_out_action(LinkedList<Zombie>* list, Zombie randomZomb){
    try{
        list->RemoveTheFirst(randomZomb);
    }
    catch(invalid_argument const &){
        return;
    }
}

// Create two copies of randomZomb and add one to the front, one to the back, and one to the middle (round down)
void brains_action(LinkedList<Zombie>* list, Zombie randomZomb){
    Zombie front(randomZomb.getType());
    Zombie back(randomZomb.getType());
    list->AddToFront(front);
    list->AddToEnd(back);
    int length = list->Length();
    list->AddAtIndex(randomZomb, length/2);
}

// Add randomZomb to the front and one zombie of all types to the back
void rainbow_action(LinkedList<Zombie>* list, Zombie randomZomb){
    engine_action(list, randomZomb);
    caboose_action(list, Zombie('R'));
    caboose_action(list, Zombie('Y'));
    caboose_action(list, Zombie('G'));
    caboose_action(list, Zombie('B'));
    caboose_action(list, Zombie('C'));
    caboose_action(list, Zombie('M'));
}

// Find a zombie with the same type as randomZomb in the list and flip a coin to decide if to add randomZomb before or after it
void friends_action(LinkedList<Zombie>* list, Zombie randomZomb){
    Node <Zombie>* found;
    try{
        found = list->Find(randomZomb);
    }
    catch(invalid_argument const &){
        caboose_action(list, randomZomb);
        return;
    }
    int coinFlip = rand()%2;
    if(coinFlip % 2 == 0){
        list->AddBefore(found, randomZomb);
    }
    else{
        list->AddAfter(found, randomZomb);
    }
}