#include <iostream>
#include <fstream>
#include <string>
#include <list>
 
using namespace std;

class Coordinate{
	public:
		int i;
		int j;
		Coordinate(int x, int y){
			i = x;
			j = y;
		}
};

class SolutionSet{
		

	public:
		std::list<int> solutions;
		SolutionSet();
		void PrintSolutions();
};

SolutionSet::SolutionSet(){
	for(int i=1; i<10; i++){
		solutions.push_back(i);
	}

}

void SolutionSet::PrintSolutions(){
	for (int val : solutions)
		std::cout << val << ",";
	std::cout << std::endl;
}



class Board{
		// Private variables for the sudoku gameboard
		int n;
		int **matrix;
		SolutionSet ***solutions;
	
	public:
		// Public variables
		Board(int);
		void Init_Board();
		void Print_Board();
		void Read_File(string);
		bool Is_Solved();
		void Init_Solutions();
		void PrintSolutions();
		void PruneSolutions();
		Coordinate *LengthOneExists();
		void CascadeSolve();
};

Board::Board (int size){
	// Constructor for the Sudoku board object
	n = size;
}

void Board::Init_Board (){
	int** a = new int*[n];
	for(int i = 0; i < n; ++i){
   		a[i] = new int[n];
   		for (int j=0; j<n; j++){
   			a[i][j] = 0;
   		}
	}
	matrix = a;
}

void Board::Print_Board (){
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void Board::Read_File (string filename){
	ifstream file(filename);	
	if (file.is_open()){
		int arraysize = 0;
		while (!file.eof() && (arraysize/n != n)){
			int x;
			file >> x;
			if (x != 0) matrix[arraysize/n][arraysize%n] = x;
			arraysize++;
		}

	} else {
		cout << "Unable to open file.\n";
	}
}

bool Board::Is_Solved(){
	/* 
	Check if a sudoku puzzle is solved. Check:
		- Each row contains one through 9
		- Each column contains one through 9
		- Each 3 by 3 square contains one through 9
	*/

	// NOT THOROUGHLY TESTED

	// Each row contains 1 to 9
	for (int i=0; i<9; i++){
		// verify a single row; check for duplicates on first pass
		bool marked[9] = {false};
		for (int j=0; j<9; j++){
			if (matrix[i][j] == 0) return false;
			if (marked[matrix[i][j]-1]) return false;
			else marked[matrix[i][j]-1] = true;
		}
	}

	// Each column contains 1 to 9
	for (int i=0; i<9; i++){
		// verify a single column; check for duplicates on first pass
		bool marked[9] = {false};
		for (int j=0; j<9; j++){
			if (matrix[j][i] == 0) return false;
			if (marked[matrix[j][i]-1]) return false;
			else marked[matrix[j][i]-1] = true;
		}
	}

	// Check each box contains 1 to 9
	for (int i=0; i<9; i+=3){
		for (int j=0; j<9; j+=3){
			bool marked[9] = {false};
			for (int k=0; k<9; k++){
				if (matrix[i+k/3][j+k%3] == 0) return false;
				if (marked[matrix[i+k/3][j+k%3]-1]) return false;
				else marked[matrix[i+k/3][j+k%3]-1] = true;
			}
		}
	}

	return true;
}

void Board::Init_Solutions(){

	solutions = new SolutionSet**[n];
	for (int i=0; i<n; i++){
		solutions[i] = new SolutionSet*[n];
		for (int j=0; j<n; j++){
			solutions[i][j] = new SolutionSet();
		}
	}
}

void Board::PrintSolutions(){
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			solutions[i][j]->PrintSolutions();
		}
	}
}

void Board::PruneSolutions(){
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			// Empty solution arrays if slot was pre-populated in the original puzzle
			if (matrix[i][j] != 0) solutions[i][j]->solutions.clear();


			// First-order pass.

			/* For each non-predetermined slot, from it's solution list:
				- Remove everything in its row
				- Remove everything in its column
				- Remove everything in its box
			*/

			//Iterate over row
			for (int k=0; k<n; k++){
				solutions[i][j]->solutions.remove(matrix[i][k]);
			}

			//Iterate over column
			for (int k=0; k<n; k++){
				solutions[i][j]->solutions.remove(matrix[k][j]);
			}
			
			//Iterate over box
			for (int k=0; k<n; k++){
				solutions[i][j]->solutions.remove(matrix[(i/3)*3+k/3][(j/3)*3+k%3]);
			}
	

		}
	}
}


Coordinate *Board::LengthOneExists(){
	// Check the board for length one solution lists and a return a struct of i,j values else NULL
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			if (solutions[i][j]->solutions.size() == 1){
				Coordinate *temp = new Coordinate(i,j);
				return temp;
			}
		}
	}
	return NULL;
}

void Board::CascadeSolve(){

	/* Search for solution lists of length 1. Assign matrix[i][j] to that value; it's solved.
		Then, remove that possibility from solution lists in same row, column, or box.
		Repeat until no more solution lists of length 1 remain.
	*/
	Coordinate *coords = NULL;

	while ((coords = LengthOneExists()) != NULL){
		// Assign matrix[i][j] to the only thing in the solution list of length 1 and remove length 1 list
		int i = coords->i;
		int j = coords->j;
		int val = solutions[i][j]->solutions.front();
		matrix[i][j] = val;
		solutions[i][j]->solutions.clear();

		//Remove from row
		for (int k=0; k<n; k++){
			solutions[k][j]->solutions.remove(val);
		}

		//Remove from column
		for (int k=0; k<n; k++){
			solutions[i][k]->solutions.remove(val);
		}

		//Remove from box
		int boxi = i/3;
		int boxj = j/3;

		for (int k=0; k<n; k++){
			solutions[boxi*3+k/3][boxj*3+k%3]->solutions.remove(val);
		}

	}

}

int main(){
	
	Board board(9);
	board.Init_Board();
	board.Read_File("example.txt");
	board.Print_Board();
	board.Init_Solutions();
	board.PruneSolutions();
	board.CascadeSolve();
	//board.PrintSolutions();
	if (board.Is_Solved()){
		cout << "Solved:\n";
		board.Print_Board();
	} else {
		cout << "Not solved.\n";
	}
	exit(0);

}
