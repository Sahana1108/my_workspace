#include "board.h"
#include "helper.h"
#include <iostream>
#include <string>
#include <ctype.h>
#include <map>

using std::vector;

const vector<vector<Cell>> Board::BOARD_1 =
{
    { BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED }
};

const vector<vector<Cell>> Board::BOARD_2 =
{
    { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

Board::Board()
{
   
    // created an empty board with empty cells
    vector<vector<Cell>> board_0;
    board_0.push_back({EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY });
    board_0.push_back({EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY });
    board_0.push_back({EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY });
    board_0.push_back({EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY });
    board_0.push_back({EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY });
    board_0.push_back({EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY });
    board_0.push_back({EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY });
    board_0.push_back({EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY });
    board_0.push_back({EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY });
    board_0.push_back({EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY });
    
    //allocate memory and let board point at it
    board = new vector<vector<Cell>>();
    

    //copy board_0 content to the memory that board is pointing at
    for(unsigned i=0; i<board_0.size();++i){
        board->push_back(board_0[i]);
       }
    //printing out the empty board using the pointer
    std::cout << "Print out 2D vector pointed at by board" << std::endl;
    std::cout<< "|   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |"<< std::endl;
      for(unsigned i=0;i<board->size();i++){
        std::cout<<LINE_OUTPUT <<" "<< i << " "<< LINE_OUTPUT;
      for(unsigned j=0;j<board->size();j++){
         if (board_0[i][j]== EMPTY){
           std::cout<<" " << EMPTY_OUTPUT << " ";
      }
      std::cout<<LINE_OUTPUT;
      }
      std::cout<<std::endl;
      }

   
    

     
}

Board::~Board()
{
    delete board;
    board = nullptr;
    
}




void Board::load(int boardId)
{

        //printing out BOARD_1 in the memory allocated earlier
        if (boardId == 1){
            
           board = new vector<vector<Cell>>(BOARD_1);
            
          

        //printing out BOARD_2 in the memory allocated earlier
        } else if (boardId == 2){

            board = new vector<vector<Cell>>(BOARD_2);
          
           
        }

    }


bool Board::placePlayer(Position position)
{
// boolean flag has been used to minimise return statements, if it is set to false then the position will not be 
// initialised on the board
   bool position_flag = true;
   
if ((*board)[position.y][position.x] == BLOCKED){
        std::cout<<"This position is blocked. Please try again."<<std::endl;
        position_flag = false;
     
    }else if ((*board)[position.y][position.x] == EMPTY){   
    
     (*board)[position.y][position.x] = PLAYER; // changing the contents of the cell to now represent the PLAYER
     position_flag = true;  
    } 
    return position_flag;

 }


// updating the player's position across the board

PlayerMove Board::movePlayerForward(Player* player)
{
       
       PlayerMove move_player = PLAYER_MOVED;
       // these are the current x,y positions
       int x_prev = player->position.x;
       int y_prev = player->position.y;
       
       // bring in the next forward position and set the current cell to empty
       player->updatePosition(player->getNextForwardPosition());

       (*board)[y_prev][x_prev] = EMPTY;
       // the car cannot go out of bounds i.e if x or y are less than 0 or greater that 9
        if (player->position.x > 9 || player->position.x < 0 ||  player->position.y < 0 || player->position.y > 9){
            std::cout << "The car is at the edge of the board and cannot move in that direction."<<std::endl;
             
            move_player = OUTSIDE_BOUNDS;
            player->position.y = y_prev; // the new position will be the same as the old one
            player->position.x = x_prev;
            (*board)[y_prev][x_prev] = PLAYER;// and the old position will still hold the PLAYER
            
        // the player may not access cells that are blocked
        } else if ((*board)[player->position.y][player->position.x] == BLOCKED){
            std::cout << "Error: cannot move forward because the road is blocked."<<std::endl;
            
            move_player = CELL_BLOCKED;

            player->position.y = y_prev; // the new position will be the same as the old one
            player->position.x = x_prev;
          
            (*board)[y_prev][x_prev] = PLAYER; // and the old position will still hold the PLAYER
            
        // if the cell is empty, then then the new co-ordinates will hold the value of PLAYER
        } else if ((*board)[player->position.y][player->position.x] == EMPTY){
            
            
            (*board)[player->position.y][player->position.x] = PLAYER;
            
            player->updatePosition(player->position); // the position will not be updated since the cell is empty

            move_player = PLAYER_MOVED; // the move is a success

        }

    return move_player;
}


void Board::display(Player* player)
{

    // prints out the board consisting of EMPTY, BLOCKED and the PLAYER CELL with the correct arrow signifying the direction
    std::cout<< "player is at " << player->position.x << ", " << player->position.y<<std::endl;
    
        std::cout<< "|   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |"<< std::endl;
        
              for (int i = 0; i <DEFAULT_BOARD_DIMENSION; i++){
                std::cout<<LINE_OUTPUT <<" "<< i << " "<< LINE_OUTPUT;

                for (int j = 0; j < DEFAULT_BOARD_DIMENSION; j++){ 
                       if ((*board)[i][j] == BLOCKED){
                          std::cout<<" "<<BLOCKED_OUTPUT<<" ";
                       }else if((*board)[i][j] == EMPTY && (j !=player->position.x || i != player->position.y)){
                          std::cout<<" "<<EMPTY_OUTPUT<<" ";
                          
                       }else if((*board)[i][j] == PLAYER ){
                                           
                       
                        std::cout<<" ";
                             player->displayDirection();
                             std::cout<<" ";
                    
                       
                }
                std::cout<<LINE_OUTPUT;
                
            }
            std::cout<<std::endl;
            
      

    
}

}


