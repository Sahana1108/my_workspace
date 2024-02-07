#include "game.h"
#include "board.h"
#include <vector>
#include <string>
#include "helper.h"
#include <iostream>
#include <unordered_map>

using std::string;
using std::vector;
using std::cout;
using std::endl;

// creating an unordered map so that user input can be mapped to each enum when the user specifies
// a direction when they are initialising their position on their board.
  std::unordered_map<std::string, Direction> arrow_direction = {
        {"north", NORTH},
        {"east", EAST},
        {"south", SOUTH},
        {"west", WEST}
    };

// creating an unordered map so that the string directions can be mapped to each TurnDirection enum
// when the user specifies a direction that they want to turn when they are playing the game.
    std::unordered_map<std::string, TurnDirection> move_direction = {
        {COMMAND_TURN_LEFT_SHORTCUT, TURN_LEFT},
        {COMMAND_TURN_LEFT, TURN_LEFT},
        {COMMAND_TURN_RIGHT_SHORTCUT, TURN_RIGHT},
        {COMMAND_TURN_RIGHT, TURN_RIGHT}
        
    };



Game::Game()
{
            board = new Board(); 
            player = new Player();
           
}

Game::~Game()
{
    delete board;
    board = nullptr;
    delete player;
    player = nullptr;
}


void Game::start()
{
  // game_started will track whether the user wants to remain in the game or if the user enters quit and wants
  // to return to the main menu
    bool game_started = true;

  // the user may change their board during the game, it has been set to 0 for now
    int change_num = 0;
    

    // making sure that there is always a board loaded, either the same one from the beginning or a different on
    //depending on user choice
    if (!loadBoard() || !changeBoard(change_num)){
        game_started = false;
    }

    // if the board has been initialised but the play hasn't been then the game_started is false and
    // the program must return to main menu
    if (game_started && !initializePlayer()){
      
        game_started = false;
    } 
    // if all above is true, then the user is able to play the game
    if (game_started){
        play();
    } else {
        cout <<"Goodbye"<< endl;
    }
    
    
}

bool Game::loadBoard(){

     //mention the acceptable commands at this stage
      std::string user_input;
      std::cout<< "load <g>"<<std::endl;
      std::cout<< "quit"<<std::endl;
      std::cout << "Please choose a board" << std::endl;
      std::getline(std::cin, user_input);
      

      // Handles incorrect input, must load a board or quit
      while (user_input != "load 1" && user_input != "load 2"&& user_input != "quit"){
           // if user enters ctrl + d then the program must terminate
           if (std::cin.eof()){
                exit(0);
           }
        
         std::cout<<"Invalid Input"<<std::endl;
        // the user is prompted again
         std::getline(std::cin, user_input);

      }
// if the user wishes to quit then this flag will be set to false and the start() method will return to the main menu
bool board_flag = true;
      
      //loads board 1, sets initial position on board to 0,0
      if (user_input == "load 1"){
        
        int b = 1;
        this->board->load(b);
        player->position.x = 0;
        player->position.y = 0;
        
      //loads board 2, sets initial position on board to 0,0
      } else if (user_input == "load 2"){
        
        int b = 2;
        this->board->load(b);
        player->position.x = 0;
        player->position.y = 0;
        
        //returns to main menu, flag is set to false
      }else if (user_input == "quit"){
        
        board_flag = false;
      }

      

return board_flag;
  
}

bool Game::changeBoard(int change_num){
        
        // is similar to loadBoard, if a new board is loaded it returns true
        //bool changeBoard_flag = true;

        std::cout << std::endl;
        
        this->board->load(change_num);
        player->position.x = 0;
        player->position.y = 0;   
      

//return changeBoard_flag;
return true;
  

}

bool Game::initializePlayer()
{
               
               this->board->display(player);
                
                 bool init_flag = true;
                //mention the acceptable commands at this stage
                std::cout<< "load <g>"<<std::endl;
                std::cout<< "init <x>,<y>,<direction>"<<std::endl;
                std::cout<< "quit"<<std::endl;
                std::cout << std::endl;
                   
                
                std::cout << "Enter input string: "<<std::endl;
                string input;
                std::getline(std::cin, input);
             
                // storing the input into a vector so that it can be split up
                vector<string> tokens_0;

                //The input requires a space between init and the coordinates
                Helper::splitString(input, tokens_0, " ");
                  std::cout << tokens_0[0] <<std::endl;
                while(tokens_0.empty() ||(input != "load 1" && input != "load 2"  && tokens_0[0] != COMMAND_QUIT && tokens_0[0] != COMMAND_INIT )){
                   // handles ctrl + d
                   if (std::cin.eof()){
                         exit(0);
                     }
                    std::cout <<"Invalid Input"<< std::endl;
                    std::cout << tokens_0[0]<<std::endl;
                    std::cin.clear();

                    std::getline(std::cin, input);
                   // clear and update the tokens_0 vector
                    tokens_0.clear();
                    Helper::splitString(input, tokens_0, " ");
                 }
                    
                      
                      
                // if the user changes their choice of board
                if((input == "load 1") ){
                  
                 int change = 1;
                 
                 std::cout << std::endl;
                  // load the new board and continue on to initialising the player
                 changeBoard(change);
                 
                 initializePlayer();
                  
                  
                // if the user changes their choice of board
                }else if((input == "load 2") ){
                                 
                  int change = 2;
                  
                  std::cout << std::endl;
                  // load the new board and continue on to initialising the player
                  changeBoard(change);
                 
                  initializePlayer();
                  
                  
                  
                }
                // if the first index of tokens_0 is quit, then return to main menu
                else if(tokens_0[0] == COMMAND_QUIT){
                 
                  init_flag = false;

                // if the first index of tokens_0 is init, then proceed with checking the remaining 
                // items, such as x,y and direction
                } else if (tokens_0[0] == COMMAND_INIT) {
                  // validate flag keeps track of whether each item meets its requirements, and returns true if they have
                  bool validate_init = false;

                  int x_value = 0;
                  int y_value = 0;
                  std::string direct;

                  while (!validate_init) {
                        // exits the program
                        if (std::cin.eof()){
                         exit(0);
                          }
                        // Check that there are two tokens
                        if (tokens_0.size() != 2) {
                            std::cout << "Invalid Input" << std::endl;
                        } else {
                            // Split the second token into three parts
                            vector<string> tokens_1;
                            Helper::splitString(tokens_0[1], tokens_1, ",");
                            if (tokens_1.size() != 3) {
                                std::cout << "Invalid Input" << std::endl;
                            } else {
                            // Check that the first two parts are integers and that they are not decimals
                                bool check = Helper::isNumber(tokens_1[0]);
                                bool checkDecimal_0 = Helper::containsDecimalPoint(tokens_1[0]);
                                bool check1 = Helper::isNumber(tokens_1[1]);
                                bool checkDecimal_1 = Helper::containsDecimalPoint(tokens_1[1]);
                            if (!check || !check1 || checkDecimal_0 || checkDecimal_1) {
                               std::cout << "Invalid Input" << std::endl;
                            } else {
                              // if they are integers, then convert from string to int
                               x_value = std::stoi(tokens_1[0]);
                               y_value = std::stoi(tokens_1[1]);
                            // Check that the integers are in the correct range
                            if (x_value < 0 || x_value > 9 || y_value < 0 || y_value > 9) {
                               std::cout << "Invalid Input" << std::endl;
                            } else {
                                // Check that the direction is valid, can only be N, E, S or W
                                direct = tokens_1[2];
                                
                                if (direct != DIRECTION_NORTH && direct != DIRECTION_EAST && direct != DIRECTION_SOUTH && direct != DIRECTION_WEST) {
                                    std::cout << "Invalid Input" << std::endl;
                                } else {
                                    validate_init = true;
                        }
                    }
                }
            }
        }

        if (!validate_init) {
            std::getline(std::cin, input);
            Helper::splitString(input, tokens_0, " ");
        }
    }

    // Create position and direction objects
    Direction direction = arrow_direction[direct];
    Position position = Position(x_value, y_value);
    
              

    //pass these objects to initialise them
    this->player->initialisePlayer(&position, direction);

    // if the x,y co-ordinate is blocked
    if(board->placePlayer(position) == false){
       std::cout<< "Invalid input" << std::endl;
       bool result = board->placePlayer(position);
       std::cout<< result << std::endl;
      initializePlayer();

    // if the player has been successfully initialised, then display the player on the correct board                
    }else if(board->placePlayer(position) == true) {
      board->display(player);
      bool result = board->placePlayer(position);
      std::cout<< result << std::endl;
      init_flag = true;
    }
                
  }
    return init_flag; 
}

void Game::play()
{
    // mention the acceptabe commands at this stage
    std::cout << std::endl;
    std::cout<<"forward (or f)"<< std::endl;
    std::cout<<"turn_right (or r)"<< std::endl;
    std::cout<<"turn_left (or l)"<< std::endl;
    std::cout<<"quit"<< std::endl;

    std::cout << "Enter input string: "<<std::endl;
    string play_input;

    while (true){
    
    std::getline(std::cin, play_input);
    // check that the input is valid f,r,l only
    while ((play_input != COMMAND_FORWARD && play_input != COMMAND_FORWARD_SHORTCUT) && 
        (play_input != COMMAND_TURN_LEFT && play_input != COMMAND_TURN_LEFT_SHORTCUT) && 
        (play_input != COMMAND_TURN_RIGHT && play_input != COMMAND_TURN_RIGHT_SHORTCUT)&&
        play_input != COMMAND_QUIT){
         // exit program
          if (std::cin.eof()){
                exit(0);
            }

         std::cout<<"Invalid Input"<<std::endl;
        
         std::getline(std::cin, play_input);
    }

    
     // if either of the forward commands are issued, then the board should display the new position of the player
     if (play_input == COMMAND_FORWARD_SHORTCUT || play_input == COMMAND_FORWARD){
        if( board->movePlayerForward(player) == PLAYER_MOVED){
          board->display(player);
        }else{
          std::cout<<"Please try again"<<std::endl;
        }
    // turn the arrow left based on the current direction of the arrow, the direction instructions are placed in player.cpp
    } else if (play_input == COMMAND_TURN_LEFT_SHORTCUT || play_input == COMMAND_TURN_LEFT) {
      TurnDirection TurnDirection = move_direction[play_input];
       player->turnDirection(TurnDirection);
       board->display(player); // display after every turn

     // turn the arrow right if either of these commands are inputted, update the current direction and place the result
     // on the board
    } else if (play_input == COMMAND_TURN_RIGHT_SHORTCUT || play_input == COMMAND_TURN_RIGHT) {
      TurnDirection TurnDirection = move_direction[play_input];
       player->turnDirection(TurnDirection);
       board->display(player);

    // the user may exit and if they do, then the total moves will be displayed
    } else if (play_input == COMMAND_QUIT){
      std::cout<< "Total moves: " << player->moves <<std::endl;
      std::cout << std::endl;
      return;

    }
  
    std::cout << std::endl;
    std::cout<<"forward (or f)"<< std::endl;
    std::cout<<"turn_right (or r)"<< std::endl;
    std::cout<<"turn_left (or l)"<< std::endl;
    std::cout<<"quit"<< std::endl;
    std::cout << std::endl;
    std::cout << "Enter input string: "<<std::endl;

    }


    



    
   
}



 

