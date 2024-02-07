#include "game.h"
#include "helper.h"
#include <iostream>
#include <string>
#include <ctype.h>
#include <vector>

using std::string;
using std::vector;

// Sahana Sukumar S3897992
// This project required that I create a 10 X 10 board that could display a choice of 2 boards, initialize a player
// and enable the user to move across the board one cell at a time.

// The start-up code provided many of the relevant methods but I also implemented a few more such as checkForLoad()
// and checkForDecimal() to assist with input validation. I have also included a changeBoard(int _ ) function that 
// allows a user to change their choice of board before they initialize their position on it. I have also included
// the vector header file from the c++ library to store the board as well as a map header file which was used to 
// assign or map a string value to a direction enum. In order to abide to the specs, I also used many boolean flags
// to minimise the use of return statements as well prevent the use of break and continue.

// One issue that I initially encountered was allocating memory to the board object and translating the 
// predefined cell values to strings, asterisks and the player to display each of the two boards. During the
// demonstration, my boards displayed a series of 0s and 1s which I was then able to fix through if else statements.
// In the load() method, I also had repeated the for loop that was responsible for printing out Board 1/2
// and I was able to make my code clearer by displaying this for loop once in the display() method.

// When I was moving my arrow across the board, I had a peculiar issue that displayed two arrows if I entered a blocked 
// cell. The second arrow then proceeced to carry out forward commands while the first arrow remained in one position.
// I was able to fix this by assigning the old position values to the next forward position so that the arrow would 
// remain in once cell at a time.

// The methods in the helper.cpp file include break statements which are not good coding practise as they introduce
// many exit points in a program and can make it less readable. Furthermore, the isNumber method does not perform
// sufficient tests on a number to determine if it is an integer, so I had to include a seperate method to 
// accompany it.

// g++ -Wall -Werror -std=c++14 -O -o carboard board.cpp helper.cpp carboard.cpp player.cpp game.cpp




// my details will be printed
void showStudentInformation(string name, string id, string email){ 
    name = "Sahana Sukumar";
    id = "s3897992";
    email = "s3897992@student.rmit.edu.au";

    // Print out my info in the required format
    std::cout<< "Name: " << name << std::endl;
    std::cout<< "Student ID: " << id << std::endl;
    std::cout<< "Email: " << email << std::endl;



}

void showOptions(){
    // creating the main menu and all of its options
    std::cout<<"Welcome to Car Board" << std::endl;
    std::cout<<"--------------------" << std::endl;
    std::cout<<"1. Play game" << std::endl;
    std::cout<<"2. Show student information" << std::endl;
    std::cout<<"3. Quit" << std::endl;
    


}
// displays all of the commands that can be used throughout the game
void showInstructions(){
    std::cout<<"You can choose the following commands to play the game:"<<std::endl;
    std::cout<<"load <g>"<<std::endl;
    std::cout<<"\t g: number of the game board to load"<<std::endl;
    std::cout<<"init <x>,<y>,<direction>"<<std::endl;
    std::cout<<"\t x: horizontal position of the car on the board (between 0 & 9)"<<std::endl;
    std::cout<<"\t y: vertical position of the car on the board (between 0 & 9)"<<std::endl;
    std::cout<<"\t direction: direction of car's movement (north, east, south, west)"<<std::endl;
    std::cout<<"forward (or f)"<<std::endl;
    std::cout<<"turn_left (or l)"<<std::endl;
    std::cout<<"turn_right (or r)"<<std::endl;
    std::cout<<"quit"<<std::endl;
    std::cout<<std::endl;
}




int main(){
      
      

    while (!std::cin.eof()){

    // main menu dialogues
            showOptions();
            std::cout << "Please enter your choice: " << std::endl;
            string user = Helper::readInput();
            bool result_1 = Helper::containsDecimalPoint(user);
            bool result_2 = Helper::isNumber(user);
            
        // making sure that the input "user" is a number but not a decimal i.e should be an integer
            if (result_2 == true && result_1 == false) {
            // converting the input into a integer so that their choice can be presented
                int x = stoi(user);
                
        
        if (x == 1){ 
            
            // Instructions on how to play the game will be displayed
            showInstructions();


            //loading the empty board
            Game* cargame = new Game();

            cargame->start();

            std::cout<<"You have exited the game"<<std::endl;
            
            
             
        // displays my information from the showStudentInformation method above
        }else if (x == 2){
            std::string name;
            std::string id;
            std::string email;
            showStudentInformation(name, id, email);
            std::cout<<std::endl;

        //to exit program
        } else if (x == 3){
            exit(0);
        }
    }

    }
    

    
    

    return EXIT_SUCCESS;
}
