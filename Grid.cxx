#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 20

class Tile
{
    public:
	// On/Off, <^>v
	bool Walls[5];
	Tile();
	//Other methods?
};

Tile::Tile()
{
	for(int i = 0; i < 5; i++)
	{
		*(Walls+i) = false;
	}
}



class Grid
{
 
    public:
	Tile Tiles[(M+1)*(M+1)];    // Array of Tiles
	Grid(int N);         // Function for activating outer walls and top row of tiles
	void genMaze();	//Function for traversing it, building maze
	void PrintMaze();     // Fn for printing Grid ‾_|‾|_| 	
    protected:
	int Up(int Pos); 		//Returns M*M if impossible or array pos result of move
	int Down(int Pos);		//Returns M*M if impossible or array pos result of move
	int Left(int Pos);		//Returns M*M if impossible or array pos result of move
	int Right(int Pos);        //Returns M*M if impossible or array pos result of move
	bool Blocked(int Pos); 	//Returns True if Pos has any directions it can move
	int walkDir(int Pos);
	int startWalk();
	void Move(int Pos, int Next);
};

void Grid::PrintMaze()
{	

    Grid printGame = 0; // Grid bools for <^>v middle walls: ╶╵╴╷
    int uplt = 0;
    int uprt = 0;	
    int dnlt = 0;
    int dnrt = 0;

    //Loop tiles
    for(int i = 0; i < M*M; i++)
    {
	uplt = (i%M) + (i/M)*(M+1);
	uprt = (i%M)+1 + (i/M)*(M+1);
	dnlt = (i%M) + ((i/M)+1)*(M+1);
	dnrt = (i%M)+1 + ((i/M)+1)*(M+1);

	    
	if(this->Tiles[i].Walls[4]){ //std::cout << "__";
	    printGame.Tiles[dnlt].Walls[3] = true;  // Turn on bottom left
	    printGame.Tiles[dnrt].Walls[1] = true; // Turn on bottom right
	}
	if(this->Tiles[i].Walls[3]){ //std::cout << " ]"; 
	    printGame.Tiles[uprt].Walls[4] = true; // Turn on top right
	    printGame.Tiles[dnrt].Walls[2] = true; // Turn on bottom right
	}	      
	if(this->Tiles[i].Walls[2]){ //std::cout << "‾‾"; 
	    printGame.Tiles[uplt].Walls[3] = true; // Turn on top left
	    printGame.Tiles[uprt].Walls[1] = true; // Turn on top right
	}
	if(this->Tiles[i].Walls[1]){ //std::cout << "[ "; 
	    printGame.Tiles[uplt].Walls[4] = true; // Turn on top left
	    printGame.Tiles[dnlt].Walls[2] = true; // Turn on bottom left
	}
    }
    for(int j = 0; j < (M+1)*(M+1); j++)	
    {
	if (j%(M+1) == 0) std::cout << "\n";
	int sum = (8*printGame.Tiles[j].Walls[1])+(4*printGame.Tiles[j].Walls[2])+(2*printGame.Tiles[j].Walls[3])+(printGame.Tiles[j].Walls[4]);
    	if (sum == 0) std::cout << " ";
    	if (sum == 1) std::cout << "╷";
    	if (sum == 2) std::cout << "╶";
    	if (sum == 3) std::cout << "┌";
    	if (sum == 4) std::cout << "╵";
    	if (sum == 5) std::cout << "│";
    	if (sum == 6) std::cout << "└";
    	if (sum == 7) std::cout << "├";
    	if (sum == 8) std::cout << "╴";
    	if (sum == 9) std::cout << "┐";
    	if (sum == 10) std::cout << "─";
    	if (sum == 11) std::cout << "┬";
    	if (sum == 12) std::cout << "┘";
    	if (sum == 13) std::cout << "┤";
    	if (sum == 14) std::cout << "┴";
    	if (sum == 15) std::cout << "┼";
    }
    std::cout<< "\n";
}



Grid::Grid(int N)
{
//	std::cout << "Setting Grid\n";
	for(int x = 0; x < N; x++)
	{
		for(int y = 0; y < N; y++)
		{
			if(x == 0)
			{
				Tiles[(N*y)+x].Walls[1] = true;
			} //  *(Tiles+(N*y)+x)
			if(x == N-1)
			{
				Tiles[(N*y)+x].Walls[3] = true;
			}
			if(y == 0)
			{
				Tiles[(N*y)+x].Walls[4] = true;
			}
			if(y == N-1)
			{
				Tiles[(N*y)+x].Walls[0] = true;
				Tiles[(N*y)+x].Walls[2] = true;
			}
		}
	}
	this->PrintMaze();	
//	this->genMaze();
}
int Grid::Up(int Pos) 		//Returns M*M if impossible or array pos result of move
{
	if(Pos >= (M*M)-M) return M*M;
	if(Tiles[Pos+M].Walls[0] != false) return M*M;
	return Pos+M;
}
int Grid::Down(int Pos)		//Returns M*M if impossible or array pos result of move
{
	if(Pos <= M) return M*M;
	if(Tiles[Pos-M].Walls[0] != false) return M*M;
	return Pos-M;

}
int Grid::Left(int Pos)		//Returns M*M if impossible or array pos result of move
{
	if(Pos%M == 0) return M*M;
	if(Tiles[Pos-1].Walls[0] != false) return M*M;
	return Pos-1;
}
int Grid::Right(int Pos)        //Returns M*M if impossible or array pos result of move
{
	if(Pos%M == M-1) return M*M;
	if(Tiles[Pos+1].Walls[0] != false) return M*M;
	return Pos+1;
}
bool Grid::Blocked(int Pos) 	//Returns True if Pos has any directions it can move
{
	return (this->Up(Pos)+this->Down(Pos)+this->Left(Pos)+this->Right(Pos) == 4*M*M);
}

int Grid::walkDir(int Pos)
{
//	std::cout << "Getting walkDir\n";
	if (this->Blocked(Pos)) return M*M;
	
	int res = M*M;
	int rNum;
	
	do
	{
		rNum = rand() % 100;
		
		if (rNum < 100)  res = this->Up(Pos); 	// UP
		if (rNum < 90)   res = this->Down(Pos);	// DOWN
		if (rNum < 60)   res = this->Right(Pos);	// RIGHT
		if (rNum < 30)   res = this->Left(Pos);	// LEFT
	} while (res == M*M);
	
	return res; 
}
int Grid::startWalk()
{
//	std::cout << "In startWalk\n";
	int Full = 0;
	int Pos = M*M;
	
	Pos = rand()%(M*M);
//	std::cout << "In startwalk. Pos: " << Pos;

//	Pos = (M*M-(M/2));
	for (int i = 0; i < M*M; i++)
	{
	    if(Tiles[Pos].Walls[0]==true && this->Blocked(Pos)==false)
	    {
		return Pos;
	    }
	    Pos = (Pos+M+1)%(M*M); // zip to closest block.
		
	}
//	std::cout << "Probably full\n";
	return M*M;
}

void Grid::Move(int Pos, int Next)
{
//	std::cout << "Moving!\n";
	this->Tiles[Pos].Walls[0]=true;
	this->Tiles[Next].Walls[0]=true;

	if(this->Left(Next) < M*M) this->Tiles[Next].Walls[1]=true; //Raise the three new walls
	if(this->Up(Next) < M*M) this->Tiles[Next].Walls[2]=true; //Raise the three new walls
	if(this->Right(Next) < M*M) this->Tiles[Next].Walls[3]=true; //Raise the three new walls
	if(this->Down(Next) < M*M) this->Tiles[Next].Walls[4]=true; //Raise the three new walls

	if(Pos-Next ==1) //Left
	{
		this->Tiles[Pos].Walls[1]=false; //Leave the wall down where you came
		this->Tiles[Next].Walls[3]=false; //Raise the three new walls
		return;
	}
	if(Next-Pos ==1) //Right
	{
		this->Tiles[Pos].Walls[3]=false; //Leave the wall down where you came
		this->Tiles[Next].Walls[1]=false; //Raise the three new walls
		return;
	}
	if(Pos-Next ==M) //Up
	{
		this->Tiles[Pos].Walls[2]=false; //Leave the wall down where you came
		this->Tiles[Next].Walls[4]=false; //Raise the three new walls
		return;
	}
	if(Next-Pos ==M) //Down
	{
		this->Tiles[Pos].Walls[4]=false; //Leave the wall down where you came
		this->Tiles[Next].Walls[2]=false; //Raise the three new walls
		return;
	}
}
void Grid::genMaze()
{
	
	this->Tiles[0].Walls[0]=true;
//	std::cout << "In genMaze!\n";
	int Pos, Next;
	bool full = false;
	
	while(full == false)
	{
		Pos=this->startWalk();
		this->Tiles[Pos].Walls[0]=true;
//		std::cout << "Pos: " << Pos << "\n";
		if(Pos==M*M)
		{
//			std::cout << "\n\nFINISHED\n\n";
			full = true;
		}
		while(!this->Blocked(Pos)&&(Pos>M))
		{
//			std::cout << Pos << "\n";	
			Next = this->walkDir(Pos);
			this->Move(Pos, Next);
//			std::cout << "Pos: " << Pos << " Next: " << Next << std::endl;
			Pos = Next;
		}
		for (int j = 0; j < M*M; j++)
		{
//			if(this->Tiles[j].Walls[0]==false) std::cout << " " << j << ", U:" << this->Up(j) << ", D:" << this->Down(j) << ", L:" << this->Left(j) << ", R:" << this->Right(j) << ", B:" << this->Blocked(j);
			if(this->Blocked(j)==false) std::cout << " " << j;			
		} //std::cout << " So far \n";
	}
}

int main()
{
	srand(time(NULL));
	std::cout<<"Main Gen Game\n";
	Grid Game1 = Grid(M); 	// Function for activating outer walls and top row of tiles
//	std::cout << "Main Gen Maze\n";
	Game1.genMaze();		//Function for traversing it, building maze
	std::cout << "Print Maze\n";
	Game1.PrintMaze();      	// Fn for printing Grid ‾_|‾|_| 	
}

