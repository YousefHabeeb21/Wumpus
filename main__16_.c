 /* ---------------------------------------------
Program 1: wumpus
Course: CS 211, Fall 2022. Tues 12pm lab
System: MacOS using replit
Author: Yousef Habeeb
UIN: 652622525
---------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>		// for srand
#include <ctype.h>
#include <stdbool.h> // boolean 


 // prevents the game from going on if the player is dead
bool stopGame(int player, int wumpus, int pit1, int pit2){

    //checks to see if the player died to the pits
  if ((player == wumpus)&&(wumpus % 2 == 0)){
      printf("\nExiting Program ...\n");
      return true;
  }
    //checks to see if the player died to the pits
  if ((player == pit1) || (player == pit2)){
      printf("\nExiting Program ...\n"); 
      return true;
  }
  return false;
}



//prevents the room number of the player from being displayed after death
void checkPlayer (int player, int wumpus, int pit1, int pit2){
  bool checker;
  
  if (player == wumpus){
    checker = true;
  }
  else if (player == pit1){
    checker = true;
  }
  else if(player == pit2){
    checker = true;
  }
  else{
    checker = false;
  }
  if (checker == false){
    printf("You are in room %d", player);
    printf(". ");
  }
}
/////////////////////////////////////////////////////////




// resets the positins in the game according to the user's choice 
//updates the player, wumpus , pit1, and pit2 location
void reset (int *player, int *wumpus, int *pit1, int *pit2, int *bat1, int *bat2, int *arrow){

  int subPlayer, subWumpus, subPit1, subPit2, subBat1, subBat2, subArrow;
  
  printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow: \n");
  
  scanf(" %d %d %d %d %d %d %d", &subPlayer, &subWumpus, &subPit1, &subPit2, &subBat1, &subBat2, &subArrow);
  
  *player = subPlayer;
  *wumpus = subWumpus;
  *pit1 = subPit1;
  *pit2 = subPit2;
  *bat1 = subBat1;
  *bat2 = subBat2;
  *arrow = subArrow;
}
/////////////////////////////////////////////////////////


// allows the player to guess which room the wumpus is in 
void winCheck (int wumpus){

  int guess;
  int check = wumpus;
  printf("Enter room (1..20) you think Wumpus is in: ");
  scanf(" %d", &guess);
  if (guess == check){
    wumpus = guess;
    printf("You won!\n");
  }
  else{
     printf("You lost.\n");
  }
}
/////////////////////////////////////////////////////////




// displays death messages or moves the wumpus to another room if odd
bool encounters(int player, int *wumpus, int pit1, int pit2, int cr1, int cr2, int cr3){
   bool gamestate = true;

  if ((player == *wumpus) && (*wumpus % 2 == 1)){
    *wumpus = cr1;
    printf( "You hear a slithering sound, as the Wumpus slips away. \n"
      "Whew, that was close! \n");
    printf("You are in room %d. ", player);
  }
  if ((player == *wumpus) && (*wumpus % 2 == 0)){
    printf(	"You briefly feel a slimy tentacled arm as your neck is snapped. \n"
      "It is over.\n");
    gamestate = false;
  }
  if ((player == pit1) || (player == pit2)){
    printf("Aaaaaaaaahhhhhh....   \n");
    printf("    You fall into a pit and die. \n");
    gamestate = false;
  }
  return gamestate;
}


// displays game messages to the player if its close to the pit or Wumpus
void pitAndWumpusAndBat(int player, int wumpus, int pit1, int pit2, int bat1, int bat2, int cr1, int cr2, int cr3){

  if (cr1 == wumpus){
    printf("You smell a stench. ");
  }
  if (cr2 == wumpus){
    printf("You smell a stench. ");
  }
  if (cr3 == wumpus){
    printf("You smell a stench. ");
  }

  if((cr1 == pit1)||(cr1 == pit2)){
    printf("You feel a draft. ");
  }
  if((cr2 == pit1)||(cr2 == pit2)){
    printf("You feel a draft. ");
  }
  if ((cr3 == pit1)||(cr3 == pit2)){
    printf("You feel a draft. ");
  }

  if((cr1 == bat1)||(cr1 == bat2)){
    printf("You hear rustling of bat wings. ");
  }
  if((cr2 == bat1)||(cr2 == bat2)){
    printf("You hear rustling of bat wings. ");
  }
  if ((cr3 == bat1)||(cr3 == bat2)){
    printf("You hear rustling of bat wings. ");
  }
  
}
/////////////////////////////////////////////////////////







// allows the bat to carry the player to another oom while relocating itself
bool bats1(int *player, int wumpus, int pit1, int pit2, int *bat1, int *bat2, int arrow){

  int tempPlayer = *player;
  bool position = false; 
  bool checker = false;
  
  if(*player == *bat1){
    printf("Woah... you're flying! \n");
    *player = rand() % 20 + 1;
    
    while(!position){
      int random = rand() % 20 + 1;
      if (random != wumpus && random != pit1 && random != pit2 && random != *bat2 && random != *player && random != arrow && random != *bat1){
        *bat1 = random;
        position = true;
      }
    }
  }
  
  position = false;
  if(*player == *bat2){
    printf("Woah... you're flying! \n");
    *player = rand() % 20 + 1;
    while(!position){
      int random = rand() % 20 + 1;
      if (random != wumpus && random != pit1 && random != pit2 && random != *bat2 && random != *player && random != arrow && random != *bat1){
        *bat1 = random;
        position = true;
      }
    }
  }

  if(tempPlayer != *player){
    printf("You've just been transported by bats to room %d.\n", *player);
    checker = true;
  }
  return checker;
}



// assigns the connected rooms to the current room in order
// updates the current value of each assigned room 
void  assignRooms(int player, int *cr1, int *cr2, int *cr3, int *wcr1, int *wcr2, int *wcr3, int wumpus){

  //dynamically allocated array 
  int **rooms = (int**)malloc(20*sizeof(int*));
  for(int i = 0 ; i<20 ; i++){
    rooms[i] = (int*)malloc(3*sizeof(int));
  }
  
  rooms[0][0] = 2; rooms[0][1] = 5; rooms[0][2] = 8; 
  rooms[1][0] = 1; rooms[1][1] = 3; rooms[1][2] = 10; 
  rooms[2][0] = 2; rooms[2][1] = 4; rooms[2][2] = 12; 
  rooms[3][0] = 3; rooms[3][1] = 5; rooms[3][2] = 14; 
  rooms[4][0] = 1; rooms[4][1] = 4; rooms[4][2] = 6; 
  rooms[5][0] = 5; rooms[5][1] = 7; rooms[5][2] = 15; 
  rooms[6][0] = 6; rooms[6][1] = 8; rooms[6][2] = 17; 
  rooms[7][0] = 1; rooms[7][1] = 7; rooms[7][2] = 9; 
  rooms[8][0] = 8; rooms[8][1] = 10; rooms[8][2] = 18; 
  rooms[9][0] = 2; rooms[9][1] = 9; rooms[9][2] = 11; 
  rooms[10][0] = 10; rooms[10][1] = 12; rooms[10][2] = 19; 
  rooms[11][0] = 3; rooms[11][1] = 11; rooms[11][2] = 13; 
  rooms[12][0] = 12; rooms[12][1] = 14; rooms[12][2] = 20; 
  rooms[13][0] = 4; rooms[13][1] = 13; rooms[13][2] = 15; 
  rooms[14][0] = 6; rooms[14][1] = 14; rooms[14][2] = 16; 
  rooms[15][0] = 15; rooms[15][1] = 17; rooms[15][2] = 20; 
  rooms[16][0] = 7; rooms[16][1] = 16; rooms[16][2] = 18; 
  rooms[17][0] = 9; rooms[17][1] = 17; rooms[17][2] = 19;
  rooms[18][0] = 11; rooms[18][1] = 18; rooms[18][2] = 20;
  rooms[19][0] = 13; rooms[19][1] = 16; rooms[19][2] = 19;
  
  // connected player rooms
  for(int i = 0; i<20; i++){
    for(int j = 0; j<3; j++){
      if((i+1) == player){
        *cr1 = rooms[i][0];
        *cr2 = rooms[i][1];
        *cr3 = rooms[i][2];        
      }// connected wumpus rooms
      if((i+1) == wumpus){
        *wcr1 = rooms[i][0]; 
        *wcr2 = rooms[i][1]; 
        *wcr2 = rooms[i][2]; 
      }
    }
  }
  free(rooms);
}
/////////////////////////////////////////////////////////



// checks connected rooms to see if the player can move, and moves the player
// also allows the player to pick up an arrow
void movement(int *player, int *cr1, int *cr2, int *cr3, int *counter, int *arrow){
  int tempPlayer, invalid = *player;
  
  scanf("%d", &tempPlayer);

  if (tempPlayer == *cr1){
    *player = tempPlayer;
    (*counter)++;
  }
  else if (tempPlayer == *cr2){
    *player = tempPlayer;
    (*counter)++;
  }
  else if (tempPlayer == *cr3){
    *player = tempPlayer;
    (*counter)++;
  }
  else{
    *player = invalid;
    printf("Invalid move.  Please retry. \n");
  }

  if(*player == *arrow){
    *arrow = -1;
    printf("Congratulations, you found the arrow and can once again shoot.\n");
  }
}
/////////////////////////////////////////////////////////




//assigns random positions to all game componeents
void assignPositions(int *player, int *wumpus, int *pit1, int *pit2, int *bat1, int *bat2, int *arrow){

  *player = rand() % 20 + 1;
  *wumpus = rand() % 20 + 1;
  
  if(*wumpus == *player){
    *wumpus = rand() % 20 + 1;
  }
  
  *pit1 = rand() % 20 + 1;
  if(*pit1 == *wumpus || *pit1 == *player){
    *pit1 = rand() % 20 + 1;
  }
  
  *pit2 = rand() % 20 + 1;
  if(*pit2 == *pit1 || *pit2 == *wumpus || *pit2 == *player){
    *pit2 = rand() % 20 + 1;
  }
  
  *bat1 = rand() % 20 + 1;
  if(*bat1 == *pit2 || *bat1 == *pit1 || *bat1 == *wumpus || *bat1 == *player){
    *bat1 = rand() % 20 + 1;
  }

  *bat2 = rand() % 20 + 1;
  if(*bat2 == *pit2 || *bat2 == *pit1 || *bat2 == *wumpus || *bat2 == *player || *bat2 == *bat1){
    *bat2 = rand() % 20 + 1;
  }
  *bat2 = rand() % 20 + 1;
  
  *arrow = rand() % 20 + 1;
  if(*arrow == *pit2 || *arrow == *pit1 || *arrow == *wumpus || *arrow == *player || *arrow == *bat1 || *arrow == *bat2){
    *arrow = rand() % 20 + 1;
  }
}




// displayes the cave
void displayCave(){
    printf(
      "\n       ______18______       \n"
    		"      /      |       \\           \n"
    		"     /      _9__      \\          \n"
    		"    /      /    \\      \\        \n"
    		"   /      /      \\      \\       \n"
    		"  17     8        10     19       \n"
    		"  | \\   / \\      /  \\   / |    \n"
    		"  |  \\ /   \\    /    \\ /  |    \n"
    		"  |   7     1---2     11  |       \n"
    		"  |   |    /     \\    |   |      \n"
    		"  |   6----5     3---12   |       \n"
    		"  |   |     \\   /     |   |      \n"
    		"  |   \\       4      /    |      \n"
    		"  |    \\      |     /     |      \n"
    		"  \\     15---14---13     /       \n"
    		"   \\   /            \\   /       \n"
    		"    \\ /              \\ /        \n"
    		"    16---------------20           \n"
    		"\n");
}
/////////////////////////////////////////////////////////



// displayes instructions for the game 
void displayInstructions(){
  displayCave();
  printf( "Hunt the Wumpus:                                             \n"
      "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
      "room has 3 tunnels leading to other rooms.                   \n"
      "                                                             \n"
      "Hazards:                                                     \n"
        "1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
        "2. Two other rooms have super-bats.  If you go there, the bats grab you and     \n"
        "   fly you to some random room, which could be troublesome.  Then those bats go \n"
        "   to a new room different from where they came from and from the other bats.   \n"
      "3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and    \n"
        "   is too heavy for bats to lift.  Usually he is asleep.  Two things wake       \n"
        "    him up: Anytime you shoot an arrow, or you entering his room.  The Wumpus   \n"
        "    will move into the lowest-numbered adjacent room anytime you shoot an arrow.\n"
        "    When you move into the Wumpus' room, then he wakes and moves if he is in an \n"
        "    odd-numbered room, but stays still otherwise.  After that, if he is in your \n"
        "    room, he snaps your neck and you die!                                       \n"
        "                                                                                \n"
        "Moves:                                                                          \n"
        "On each move you can do the following, where input can be upper or lower-case:  \n"
        "1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
        "   then a room number.                                                          \n"
        "2. Shoot your guided arrow through a list of up to three adjacent rooms, which  \n"
        "   you specify.  Your arrow ends up in the final room.                          \n"
        "   To shoot enter 'S' followed by the number of rooms (1..3), and then the      \n"
        "   list of the desired number (up to 3) of adjacent room numbers, separated     \n"
        "   by spaces. If an arrow can't go a direction because there is no connecting   \n"
        "   tunnel, it ricochets and moves to the lowest-numbered adjacent room and      \n"
        "   continues doing this until it has traveled the designated number of rooms.   \n"
        "   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You  \n"
        "   automatically pick up the arrow if you go through a room with the arrow in   \n"
        "   it.                                                                          \n"
        "3. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
        "4. Enter 'C' to cheat and display current board positions.                      \n"
        "5. Enter 'D' to display this set of instructions.                               \n"
        "6. Enter 'P' to print the maze room layout.                                     \n"
        "7. Enter 'X' to exit the game.                                                  \n"
        "                                                                                \n"
        "Good luck!                                                                      \n"
        " \n\n");
}//end displayInstructions()




// these functions display messages if an arrow reaches the player or wumpus
// they exit the game as they are displayed at a win or a loss
//-----------------------------------------------------------------------
void accidentaldeath(){
  printf( "You just shot yourself, and are dying.\n"
            "It didn't take long, you're dead.\n");
  printf("\nExiting Program ...\n");
  exit(0);
}

void bouncedeath(){
  printf( "You just shot yourself.  \n"
            "Maybe Darwin was right.  You're dead.\n");
  printf("\nExiting Program ...\n");
  exit(0);
}

void wumpusdeath(){
  printf( "Wumpus has just been pierced by your deadly arrow! \n"
            "Congratulations on your victory, you awesome hunter you.\n");
  printf("\nExiting Program ...\n");
  exit(0);
}

void luckywin(){
  printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
            "Accidental victory, but still you win!\n");
  printf("\nExiting Program ...\n");
  exit(0);
}
//------------------------------------------------------------------------



// this function is for shooting to just 1 room 
void shoot1(int player, int *wumpus, int cr1, int cr2, int cr3,int wcr1,int wcr2, int wcr3, int *arrow, int choose1){
  //choose is the room the player chooses to shoot
  if (choose1 == cr1){ *arrow = cr1; }
  else if(choose1 == cr2){ *arrow = cr2; }
  else if(choose1 == cr3){ *arrow = cr3; }
    
  else{
    printf("Room %d is not adjacent.  Arrow ricochets...\n", choose1);
    *arrow = cr1;
  }
  
  if(*arrow == player){
    accidentaldeath();
  }
  if(*arrow == *wumpus && choose1 != *wumpus){
    luckywin();
  }
  if(*arrow == *wumpus){
    wumpusdeath();    
  }
  else{ 
    *wumpus = wcr1; 
  }
}


// this function is for shooting 2 rooms
void shoot2(int player, int *wumpus, int cr1, int cr2, int cr3,int wcr1,int wcr2, int wcr3, int *arrow, int choose1, int choose2){

  bool bounce1 = false;
  bool bounce2 = false;
  
  if (choose1 == cr1){ *arrow = cr1; }
  else if(choose1 == cr2){ *arrow = cr2; }
  else if(choose1 == cr3){ *arrow = cr3; }
  else if (choose1 != cr1 && choose1 != cr2 && choose1 != cr3){ 
    printf("Room %d is not adjacent.  Arrow ricochets...\n", choose1);
    *arrow = cr1;
    //assigns rooms connected to lower adjecent if the chosen room is incorrect
    assignRooms(*arrow, &cr1, &cr2, &cr3, &wcr1, &wcr2, &wcr3, *wumpus);
  }  
  bounce1 = true;
  // assigns connected rooms to the first chosen room if it is actually connected to the players
  assignRooms(choose1, &cr1, &cr2, &cr3, &wcr1, &wcr2, &wcr3, *wumpus);
  
  
  if (choose2 == cr1){ *arrow = cr1; }
  else if(choose2 == cr2){ *arrow = cr2; }
  else if(choose2 == cr3){ *arrow = cr3; }
  else if (choose2 != cr1 && choose2 != cr2 && choose2 != cr3){  
    printf("Room %d is not adjacent.  Arrow ricochets...\n", choose2);
    *arrow = cr1;
  }

  if(bounce1 && choose2 == player){
    bouncedeath();
  }
  else if(cr1 == player && *arrow == player){
    accidentaldeath();
  }
  if(choose2 != *wumpus && *arrow == *wumpus){
    luckywin();
  }
  else if(*arrow == *wumpus){
    wumpusdeath();   
  }
  else{
    *wumpus = wcr1;
  }
}


// this function is for shooting 2 rooms
void shoot3(int player, int *wumpus, int cr1, int cr2, int cr3,int wcr1,int wcr2, int wcr3, int *arrow, int chose1, int chose2, int chose3){
  
  if (chose1 == cr1){ *arrow = cr1; }
  else if(chose1 == cr2){ *arrow = cr2; }
  else if(chose1 == cr3){ *arrow = cr3; }
  else if (chose1 != cr1 && chose1 != cr2 && chose1 != cr3){ 
    printf("Room %d is not adjacent.  Arrow ricochets...\n", chose1);
    *arrow = cr1;
    //assigns rooms connected to lower adjecent if the chosen room is incorrect
    assignRooms(*arrow, &cr1, &cr2, &cr3, &wcr1,&wcr2,&wcr3, *wumpus);
  }
  // assigns connected rooms to the first chosen room if it is actually connected to the players
  assignRooms(chose1, &cr1, &cr2, &cr3, &wcr1,&wcr2,&wcr3, *wumpus);
  
  if (chose2 == cr1){ *arrow = cr1; }
  else if(chose2 == cr2){ *arrow = cr2; }
  else if(chose2 == cr3){ *arrow = cr3; }
  else{ 
    printf("Room %d is not adjacent.  Arrow ricochets...\n", chose2);
    *arrow = cr1;
    //assigns rooms connected to lower adjecent if the chosen room is incorrect
    assignRooms(*arrow, &cr1, &cr2, &cr3, &wcr1,&wcr2,&wcr3, *wumpus);
  }
// assigns connected rooms to the first chosen room if it is actually connected to the players
  assignRooms(chose2, &cr1, &cr2, &cr3, &wcr1,&wcr2,&wcr3, *wumpus);
  
  if (chose3 == cr1){ *arrow = cr1; }
  else if(chose3 == cr2){ *arrow = cr2; }
  else if(chose3 == cr3){ *arrow = cr3; }
  else if (chose3 != cr1 && chose3 != cr2 && chose3 != cr3){ 
    printf("Room %d is not adjacent.  Arrow ricochets...\n", chose3);
    *arrow = cr1;
  }

  if(*arrow == player){
   accidentaldeath();
  }
  if(chose3 != *wumpus && *arrow == *wumpus){
    luckywin();
  }
  else if(*arrow == *wumpus){
    wumpusdeath();
  }
  else{
    *wumpus = wcr1;
  }
}



// this function is the one that calls the sub functions to shoot arrows to chosen rooms if the player has an arrow
void shootArrows(int player, int *wumpus, int cr1, int cr2, int cr3,int wcr1,int wcr2,int wcr3, int *arrow){
  
  // bool tracker = true; // checks if you have an arrow
  int rooms, chose1, chose2, chose3, temp, extra;

  //checks if theres an arrow in the players possession
  if(*arrow != -1){
    printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n");
  }
  // allows the user to decide how many rooms to fire the arrow in
  else{
    printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ");

  scanf("%d", &rooms);

    if (rooms > 3){
      printf("Sorry, the max number of rooms is 3.  Setting that value to 3.");
      rooms = 3;
    }
    if (rooms == 1){
      scanf("%d", &chose1);
      shoot1(player, wumpus, cr1, cr2, cr3, wcr1, wcr2, wcr3, arrow, chose1);
    }
    if (rooms == 2){
      scanf("%d %d", &chose1, &chose2);
      shoot2(player, wumpus, cr1, cr2, cr3, wcr1, wcr2, wcr3, arrow, chose1,chose2);
    }
    if (rooms == 3){
      scanf("%d %d %d", &chose1, &chose2, &chose3);
      shoot3(player, wumpus, cr1, cr2, cr3, wcr1, wcr2, wcr3, arrow, chose1, chose2, chose3);
    }
  }
}




/////////////////////////////////////////////////////////
int main() {
  srand(1);
  int *player, *wumpus, *pit1, *pit2, *bat1, *bat2, *arrow, *cr1, *cr2, *cr3, *wcr1, *wcr2, *wcr3, 
  //counter is used for displaying the movement number
  counter = 1, game = 0;
  //this is where the game components are assigned random values
  assignPositions(&player,&wumpus,&pit1,&pit2,&bat1,&bat2,&arrow);
 
  while (game == 0){

    //assigns the connected rooms 
    assignRooms(player, &cr1, &cr2, &cr3, &wcr1, &wcr2, &wcr3, wumpus);
    
    //if the bats relocate the player then the connected rooms must be asigned once more
    if (bats1(&player, wumpus, pit1, pit2, &bat1, &bat2, arrow)){
      assignRooms(player, &cr1, &cr2, &cr3, &wcr1, &wcr2, &wcr3, wumpus);
    }

    //checks to see what room the player is in if not already dead
    checkPlayer(player, wumpus, pit1, pit2);

    // checks if the player died to the wumpus or pit and displays other messages if not
    if(encounters(player, &wumpus, pit1,pit2, cr1, cr2, cr3)){
      
    //displays messages based on where the player is in relation to the pit and Wumpus
      pitAndWumpusAndBat(player, wumpus, pit1, pit2, bat1, bat2, cr1, cr2, cr3); 
    }
    
    //checks to see if the player died to the Wumpus or pit and if so, stops the game 
    if(stopGame(player, wumpus, pit1, pit2)){
      break;
    }
    printf("\n\n"); 
    printf("%d", counter); 
    printf(". Enter your move (or 'D' for directions): ");
    
    char choice;
    scanf(" %c", &choice);
    choice = tolower(choice);
    
    switch (choice){
      case 'm': movement(&player, &cr1, &cr2, &cr3, &counter, &arrow);
      break;
      
      case 'r': reset(&player, &wumpus, &pit1, &pit2, &bat1, &bat2, &arrow);
      break;    
      
      case 'c': printf( "Cheating! Game elements are in the following rooms: \n"
    		"Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
    		"%4d %5d %6d %5d %5d %5d %5d \n\n", player, wumpus, pit1, pit2, bat1, bat2, arrow);
      break;
      
      case 'd': displayInstructions();
      break;
      
      case 'p': displayCave();
      break;

      case 's': shootArrows(player, &wumpus, cr1, cr2, cr3, wcr1, wcr2, wcr3, &arrow);
                counter++;
      break;
      
      case 'g': winCheck(wumpus);
      
      case 'x': printf("\nExiting Program ...\n");
                game++;
      break;
    }
  }  
  return 0;
}