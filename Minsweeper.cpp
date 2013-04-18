//Minesweeper Program: 5X5 Grid(25 cells) with 6 Mines

#include <iostream>
#include <ctime>
using namespace std;

//-----------------------------------------------------
//class Cell
//represents one grid element in the Minesweeper game
//-----------------------------------------------------

class Cell { //class name Cell
public: //Methods/Constructors for public
	Cell();  //Declaring Cell constructor
	void print();
	void peek(); 
	void unittest();
	bool getMined();
	void setMined(bool b); //bool b
	bool getMarked();
	void setMarked(bool b);//bool b
	bool getCovered();
	void setCovered(bool b);//bool b
	int  getAdjcount();
	void setAdjcount(int b);//int b

private: //Methods/Constructors for Private
	bool covered; //boolean for covered cell
	bool marked;  //boolean for marked cell
	bool mined;   //boolean for mined cell
	int adjcount; //adjacent count for # of mines around a cell
}; 

//--------------------------
//functions for class Cell
//--------------------------++

Cell::Cell() { 
	covered = true;
	marked = false;
	mined = false; 
	adjcount = 0;
}//0-param constructor


bool Cell::getMined(){
	return mined;
}//getMined method


void Cell::setMined(bool b){
	mined = b;
}//setMined method


bool Cell::getMarked(){
	return marked;
}//getMarked method


void Cell::setMarked(bool b){
	marked = b;
}//setMarked method


bool Cell::getCovered(){
	return covered;
}//getCovered method


void Cell::setCovered(bool b){
	covered = b;
}//setCovered method


int Cell::getAdjcount(){
	return adjcount;
}//getAdjcount method


void Cell::setAdjcount(int b){
	adjcount = b;
}//setAdjcount method

//Print Method of the cell
void Cell::print() {
	if (marked) { 
		cout << "  L  "; 
	}else { 
		if (covered){ 
			cout << "  ?  "; 
		}else {  
			if (mined) {
				cout << "  x  "; 
			}else if (adjcount == 0) { 
				cout << "  _  ";
			}else {
				cout << "   " << adjcount << " ";
			}//inner else
		}//inner else
	}//outer else
}//print method

//Peek Method, used to uncover cell
void Cell::peek() { 
	if (mined){ cout << "  x  "; 
	}else if (adjcount == 0) {
		cout << "  _  "; 
	}else{
		cout << "   " << adjcount << " ";
	}//else
}//peek method

//Test for individual cell
void Cell::unittest() {

	covered = false;
	print(); cout << endl;
	
	adjcount = 4;
	print(); cout << endl;
	
	mined = true;
	print(); cout << endl;
	
	covered = true;
	print(); cout << endl;
	
	marked = true;
	print(); cout << endl;
}//unit test

//-----------------------------------
// class Board
// this class represents a 2 dimensional
// array of Cell objects for the game
// of minesweeper
//-----------------------------------

class Board	{
public:
	Board();
	void cmd();
	void print();
	void setMines();
	void shuffleMines();
	void generateAdjcount(); 
	void cheat();
	bool WinLose();
private:
	static const int rows = 5;
	static const int cols = 5;
	Cell cells[rows][cols];
	int mines;
};

//--------------------------
//Functions for Class Board
//-------------------------

Board::Board()	{
	mines = 8;
}//0-param constructor

void Board::print()	{ //prints out board
	for (int i = 0; i<rows; i++){
		for (int j = 0; j<cols; j++){
			cells[i][j].print();
		}//inner for
		cout << endl << endl;
	}//outer for
}//print method

void Board::cmd(){ 
	//Stores the user's input with a array size of 80
	char line [80]; 

	while(true)	{
		cout << "> ";
		cin.getline(line,79);

		if(strcmp(line,"quit")==0)	{ 
			cout << "Bye!" << endl; 
			return;
		}else if (strcmp(line,"show")==0){ 
			generateAdjcount();
			print(); 
		}else if (strcmp(line,"cheat")==0){
			generateAdjcount();
			cheat(); 
		}else{ 
			//stores three different commands each with 10 words
			char t1[10], t2[10], t3[10];
			int r,c; 
			char *p; 
			p = strtok(line," "); 
			strcpy(t1,p); 
			p = strtok(NULL," "); 
			strcpy_s(t2,p); 
			p = strtok(NULL," "); 
			strcpy_s(t3,p); 
			//parsing commands
			r= atoi (t2); 
			c= atoi (t3); 
			
			 //checking if row/column are in range
			 if (r >= 0 && r < rows && c >= 0 && c < cols)	{
				//lets the user input uncover 'u'
				if(strcmp(t1,"u")==0){ 
					cells[r][c].setCovered(false); 
					generateAdjcount();
					print(); 
					if (WinLose()==false){
						cout << "Sorry, you have clicked on a mine! Please try again!" << endl;
					}//when user loses
				}else if (strcmp(t1,"m")==0){ 
					cells[r][c].setMarked(true);
					generateAdjcount();
					print(); 
					if (WinLose()==false){
						cout << "You have lost the game, please try again!!" << endl;
					}//check whether user has lost
				}//wanting to mark cell
			}else{ //row and column numbers are in invalid range
					cout << "Sorry, you cannot mark there" << endl; 
			}//inner else
		}//outer else
	}//while
}//main method

//setMines method for setting mines
void Board::setMines() {
	for (int i=0; i<mines; i++) {
		int r = i/cols; 
		int c = i&cols;
		cells[r][c].setMined(true);
	}//for
}//setMines method

//ShuffleMines method
void Board::shuffleMines(){
	srand (time(NULL));
	for (int i=0; i<1000; i++) {   //creating variables, then you randomize it
		int r1 = rand() % rows -1; 
		int c1 = rand() % cols -1;
		int r2 = rand() % rows -1;
		int c2 = rand() % cols -1;
		if(r1 >=0 && r1<rows
			&& r2 >= 0 && r2<rows
			&& c1 >= 0 && c1<cols
			&& c2 >=0 && c2<cols
			&& r1 != r2 && c1 != c2) {
			 	// swaps the two location in our program 
				bool temp = cells[r1][c1].getMined(); 
				//as long as the mines aren't the same
				cells[r1][c1].setMined(cells[r2][c2].getMined());
				cells[r2][c2].setMined(temp);
		}//if
	}//for
}//shuffleMines

//Calculate adjacency counts for cells into mines
void Board::generateAdjcount(){
for(int i=0; i < rows; i++) {
		for(int j=0; j<cols; j++) {
			int count = 0; //begin at counter 0

			//If there are no mines
			if (!cells[i][j].getMined()) {  
				count = 0;                                                 
			}
			//Check cell to the right, if there is a mine
			if (j+1<cols && cells[i][j+1].getMined()==true) {  
				count++;
			}
			//Check cell at top-right corner, if there is a mine     
			if (i-1>=0 && j+1<cols && cells[i-1][j+1].getMined()==true)  {  
				count++;
			}
			//Check cell above, if there is a mine     
			if (i-1>=0 && cells[i-1][j].getMined()==true) {  
				count ++;
			}      
			//Check cell at top left, if there is a mine
			if (i-1>=0 && j-1>=0 && cells[i-1][j-1].getMined()==true) { 
				count ++;
			}  
			//Check cell on the left, if there is a mine   
			if (j-1>=0 && cells[i][j-1].getMined()==true) {  
				count++;
			}
			//Check cell on the bottom left, if there is a mine    
			if (i+1<rows && j-1>=0 && cells[i+1][j-1].getMined()==true) { 
				count++;
			}
			//Check cell under, if there is a mine
			if (i+1<rows && cells[i+1][j].getMined()==true) {
				count++;
			}
			//Check cell bottom right, if there is a mine    
			if (i+1<rows && j+1<cols && cells[i+1][j+1].getMined()==true){
				count++; 
			}

			cells[i][j].setAdjcount(count);
		}//for j
	}//for i
}//generateAdjcount

//cheat method(uncovers the entire board)
void Board::cheat(){
	int counter = 0;
	for (int i=0; i<rows; i++){
		for (int j=0; j<cols; j++){
			counter++;
			//losing the game, uncovers all the cells
			cells[i][j].setCovered(false);
			cells[i][j].print();
			if (counter % 5 ==0){
				cout << endl << endl;
			}//printing 5 elements per row
		}//rows
	}//columns
}//cheat method

//CheckforWin Method
bool Board::WinLose(){
	bool result = true;
	for (int i=0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			if (cells[i][j].getMined()==true && cells[i][j].getCovered() == false){
				result = false;
			}//if
		}//for
	}//for
	return result;
}//WinLose method


//--------------------------------------------
//main function for testing
//--------------------------------------------

int main (void) {
	cout <<"Welcome to Abel's Minesweeper" << endl << endl;
	cout <<"Here are the instructions on how to play the game" << endl << endl;
	cout <<"Please input 'u row col' followed by show to uncover cell" << endl << endl;
	cout <<"For Example, u 2 2" << endl << endl;
	cout <<"show" << endl << endl;
	cout <<"To give up, type 'cheat' to show the whole board" << endl << endl;
	cout <<"Type 'quit' to end the game" << endl << endl;
	Board b;//creates board b
	b.print(); //prints board
	b.setMines(); //sets mines
	b.shuffleMines(); //shuffle mines
	b.cmd(); //creates user input
	b.cheat();//creates cheat input
	
	return 0;
}//main method
	
	
	
	
	
	