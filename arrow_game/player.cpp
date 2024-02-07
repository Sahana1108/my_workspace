#include "player.h"
#include "game.h"

Position::Position()
{
    //TODO
}


Position::Position(int x, int y)
{
   this->x = x;
   this->y = y;

	
    
}

Player::Player()
{
    //TODO
}

void Player::initialisePlayer(Position* position, Direction direction)
{
    this->position = *position;
    this->direction = direction;
    this->moves = 0;
    

}

void Player::turnDirection(TurnDirection turnDirection)
{
    // direction is the player's current direction and it is set to a new direction based upon the value of turnDirection
    // This is for the right turns:
    if (direction == NORTH && turnDirection == TURN_RIGHT){
         direction = EAST;

    } else if (direction == EAST && turnDirection == TURN_RIGHT){
         direction = SOUTH;

    } else if (direction == SOUTH && turnDirection == TURN_RIGHT){
         direction = WEST;

    } else if (direction == WEST && turnDirection == TURN_RIGHT){
         direction = NORTH;

    // This is for the left turns:
    } else if (direction == NORTH && turnDirection == TURN_LEFT){
         direction = WEST;

    } else if (direction == WEST && turnDirection == TURN_LEFT){
         direction = SOUTH;

    } else if (direction == SOUTH && turnDirection == TURN_LEFT){
         direction = EAST;

    } else if (direction == EAST && turnDirection == TURN_LEFT){
         direction = NORTH;
    }
}

Position Player::getNextForwardPosition()
{
    //if the user is going forward by one position facing north, then y will decrease
    if (direction == NORTH){
        this-> position.y -= 1;
        
    //if the user is going forward by one position facing east, then x will increase
    } else if (direction == EAST){
        this-> position.x += 1;
        
    //if the user is going forward by one position facing south, then y will increase
    } else if (direction == SOUTH){
        this-> position.y += 1;
        
    //if the user is going forward by one position facing west, then x will decrease
    } else if (direction == WEST){
        this-> position.x -= 1;
        

    }


    return this->position;
}

void Player::updatePosition(Position position)
{
    this->position = position;
    moves = moves + 1; // everytime the position is changed, moves will be increased by one
}

void Player::displayDirection()
{
    // these are the arrows that will be displayed throughout the game, they have been printed to 
    // board for the cell containing the player
    if (direction == NORTH){
        printf(DIRECTION_ARROW_OUTPUT_NORTH);

    } else if (direction == EAST){
        printf(DIRECTION_ARROW_OUTPUT_EAST);

    } else if (direction == SOUTH){
        printf(DIRECTION_ARROW_OUTPUT_SOUTH);

    } else if (direction == WEST){
        printf(DIRECTION_ARROW_OUTPUT_WEST);

    } 

}




