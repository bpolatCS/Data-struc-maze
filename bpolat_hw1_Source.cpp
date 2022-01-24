#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "bpolat_hw1_Header.h"
#include <vector>

using namespace std;

struct cellStruct //struct for the maze. 
{
	int x,y;
	int u,d,l,r;
	bool visited;

	cellStruct()
		:x(), y(), u(1), d(1), l(1), r(1), visited(false)
	{}

	cellStruct(int _x, int _y)
		:x(_x), y(_y), u(1), d(1), l(1), r(1), visited(false)
	{}
};

bool isAvailable(Stack<cellStruct> mazes, int M, int N, int currentX, int currentY)
{
	//control system if coordiante already in the mazes
	bool isAvailable = true;

	while (!mazes.isEmpty())
	{
		cellStruct cell = mazes.topAndPop();
		if (currentX == cell.x && currentY == cell.y)
		{
			return false;
		}
	}
	return isAvailable;
}

bool isOutSide(Stack<cellStruct> & mazes, int M, int N, int currentX, int currentY)
{
	//control system if outside or not
	bool outSide = true;

	if (currentX < 0 || currentY < 0 || currentX >= N || currentY >= M)
	{
		outSide = false;
	}
	return outSide;
}


void writingProcess(vector<Stack<cellStruct>> mazeList, int M, int N)
{
	//writing maze files
	string fileName;
	for (int i = 0; i < mazeList.size(); i++)
	{
		ofstream outdata;
		Stack<cellStruct> eachMaze = mazeList[i];
		Stack<cellStruct> tempMaze;
		fileName = "maze_" + to_string(i+1) + ".txt";

		outdata.open(fileName.c_str());
		outdata<<M<<" "<<N<<endl;

		for (int i = 0; i < N; i++)
		{
			for (int k = 0; k < M; k++)
			{
				while (!eachMaze.isEmpty())
				{
					cellStruct cell = eachMaze.topAndPop();
					tempMaze.push(cell);
					if (cell.x == i && cell.y == k)
					{
						outdata<<"x="<<cell.x<<" y="<<cell.y<<" l="<<
							cell.l<<" r="<<cell.r<<" u="<<cell.u<<" d="<<cell.d<<endl;
					}					
				}
				while (!tempMaze.isEmpty())
				{
					cellStruct comeBack = tempMaze.topAndPop();
					eachMaze.push(comeBack);
				}
			}
		}
		outdata.close();
	}
}

cellStruct chooseDirection(Stack<cellStruct> possCoord)
{
	//chose one direciton randomly
	cellStruct choosenCoordinat;
	Stack<cellStruct> tempCoord(possCoord);
	int counter = 0;
	while (!tempCoord.isEmpty())
	{
		tempCoord.pop();
		counter++;
	}

	int a = rand() % counter; //create random number and pop accordingly
	for (int i = 0; i <= a; i++)
	{
		choosenCoordinat = possCoord.topAndPop();
	}
	return choosenCoordinat;
}


void findRandomDirections(Stack<cellStruct> &possCoord, Stack<cellStruct> uniqueMaze, int M, int N)
{//for the createMaze's first part.
	possCoord.makeEmpty();

	int currentX = uniqueMaze.top().x;
	int currentY = uniqueMaze.top().y;

	//same algorithm with backTracingRandomDirections

	if(isOutSide(uniqueMaze, M, N, currentX-1, currentY) && isAvailable(uniqueMaze, M, N, currentX-1, currentY)) //look left
	{
		cellStruct coords(currentX-1, currentY);
		possCoord.push(coords);
	}
	if(isOutSide(uniqueMaze, M, N, currentX, currentY+1) && isAvailable(uniqueMaze, M, N, currentX, currentY+1 )) //look up
	{
		cellStruct coords(currentX, currentY+1);
		possCoord.push(coords);
	}
	if(isOutSide(uniqueMaze, M, N, currentX+1, currentY) && isAvailable(uniqueMaze, M, N, currentX+1, currentY)) //look right
	{
		cellStruct coords(currentX+1, currentY);
		possCoord.push(coords);
	}
	if(isOutSide(uniqueMaze, M, N, currentX, currentY-1) && isAvailable(uniqueMaze, M, N, currentX, currentY-1)) //look down
	{
		cellStruct coords(currentX, currentY-1);
		possCoord.push(coords);
	}
}


void findRandomDirectionsWithBackTracing(Stack<cellStruct> &possCoord, Stack<cellStruct> uniqueMaze, Stack<cellStruct> backTracing, int M, int N)
{
	//for the createMaze's else part.
	//each turn make empty, take current coordinates and push backtracing again. Here important thing is taking current's from uniqmaze first then pushing others.
	possCoord.makeEmpty();

	int currentX = uniqueMaze.top().x;
	int currentY = uniqueMaze.top().y;

	while (!backTracing.isEmpty())
	{
		uniqueMaze.push(backTracing.topAndPop());
	}

	if(isOutSide(uniqueMaze, M, N, currentX-1, currentY) && isAvailable(uniqueMaze, M, N, currentX-1, currentY)) // look left
	{
		cellStruct coords(currentX-1, currentY);
		possCoord.push(coords);
	}
	if(isOutSide(uniqueMaze, M, N, currentX, currentY+1) && isAvailable(uniqueMaze, M, N, currentX, currentY+1 )) //look up
	{
		cellStruct coords(currentX, currentY+1);
		possCoord.push(coords);
	}
	if(isOutSide(uniqueMaze, M, N, currentX+1, currentY) && isAvailable(uniqueMaze, M, N, currentX+1, currentY)) //look right
	{
		cellStruct coords(currentX+1, currentY);
		possCoord.push(coords);
	}
	if(isOutSide(uniqueMaze, M, N, currentX, currentY-1) && isAvailable(uniqueMaze, M, N, currentX, currentY-1)) //look down
	{
		cellStruct coords(currentX, currentY-1);
		possCoord.push(coords);
	}
}

void createMaze(int M, int N, int K, vector<Stack<cellStruct>> &mazes)
{
	int mazeSize = M*N-1;
	Stack<cellStruct> possCoord; //possible coordinates
	Stack<cellStruct> uniqueMaze; //maze list
	cellStruct firstCell(0,0);
	uniqueMaze.push(firstCell); //pushing 0 0 cell

	while (mazeSize != 0)
	{
		findRandomDirections(possCoord, uniqueMaze, M, N); //find direciton according to limitations (look inside function)
														// two type of possCoord, empty or not.

		if (!possCoord.isEmpty()) //if posscoord is available
		{
			cellStruct choosenCell = chooseDirection(possCoord);
			if (choosenCell.x > uniqueMaze.top().x ) // if posibble coordinate goes right
			{	//change relevant structs l and r.			
				choosenCell.l = 0;
				choosenCell.visited = true;
				cellStruct topCell = uniqueMaze.topAndPop();
				topCell.r = 0;
				topCell.visited = true;	
				uniqueMaze.push(topCell);
				uniqueMaze.push(choosenCell);
			}
			else if (choosenCell.x < uniqueMaze.top().x ) // if posibble coordinate goes left
			{	//change relevant structs l and r.
				choosenCell.r = 0;
				choosenCell.visited = true;
				cellStruct topCell = uniqueMaze.topAndPop();
				topCell.l = 0;
				topCell.visited = true;	
				uniqueMaze.push(topCell);
				uniqueMaze.push(choosenCell);
			}
			else if (choosenCell.y > uniqueMaze.top().y ) // if posibble coordinate goes up
			{	//change relevant structs d and u
				choosenCell.d = 0;
				choosenCell.visited = true;
				cellStruct topCell = uniqueMaze.topAndPop();
				topCell.u = 0;
				topCell.visited = true;	
				uniqueMaze.push(topCell);
				uniqueMaze.push(choosenCell);
			}
			else if (choosenCell.y < uniqueMaze.top().y ) // if posibble coordinate goes down
			{	//change relevant structs d and u.
				choosenCell.u = 0;
				choosenCell.visited = true;
				cellStruct topCell = uniqueMaze.topAndPop();
				topCell.d = 0;
				topCell.visited = true;	
				uniqueMaze.push(topCell);
				uniqueMaze.push(choosenCell);
			}
		}
		else //if posscoord is not available
		{
			Stack<cellStruct> backTracing; //when go back for finding coordinate push here.
			do
			{ //each loop go one step back, and look if there is available coordinate.
				backTracing.push(uniqueMaze.topAndPop());
				findRandomDirectionsWithBackTracing(possCoord, uniqueMaze, backTracing, M, N);
				
			} while (possCoord.isEmpty());

			cellStruct choosenCell = chooseDirection(possCoord); //take possible coordinate and look for new direcitons on below

			if (choosenCell.x > uniqueMaze.top().x ) //look for right
			{				
				choosenCell.l = 0;
				choosenCell.visited = true;
				cellStruct topCell = uniqueMaze.topAndPop();
					
				topCell.r = 0;
				topCell.visited = true;	
				uniqueMaze.push(topCell);
				while (!backTracing.isEmpty()) //put backtraced coordinates back to the uniquemaze
				{
					uniqueMaze.push(backTracing.topAndPop());
				}			
				uniqueMaze.push(choosenCell);
			}

			else if (choosenCell.x < uniqueMaze.top().x )//look for left
			{			
				choosenCell.r = 0;
				choosenCell.visited = true;
				cellStruct topCell = uniqueMaze.topAndPop();
			
				topCell.l = 0;
				topCell.visited = true;	
				uniqueMaze.push(topCell);
				while (!backTracing.isEmpty()) //put backtraced coordinates back to the uniquemaze
				{
					uniqueMaze.push(backTracing.topAndPop());
				}	
				uniqueMaze.push(choosenCell);
			}

			else if (choosenCell.y > uniqueMaze.top().y ) //look for up
			{				
				choosenCell.d = 0;
				choosenCell.visited = true;
				cellStruct topCell = uniqueMaze.topAndPop();
							
				topCell.u = 0;
				topCell.visited = true;	
				uniqueMaze.push(topCell);
				while (!backTracing.isEmpty()) //put backtraced coordinates back to the uniquemaze
				{
					uniqueMaze.push(backTracing.topAndPop());
				}
				uniqueMaze.push(choosenCell);
			}
			else if (choosenCell.y < uniqueMaze.top().y ) //look for down
			{
				choosenCell.u = 0;
				choosenCell.visited = true;
				cellStruct topCell = uniqueMaze.topAndPop();
					
				topCell.d = 0;
				topCell.visited = true;	
				uniqueMaze.push(topCell);
				while (!backTracing.isEmpty()) //put backtraced coordinates back to the uniquemaze
				{
					uniqueMaze.push(backTracing.topAndPop());
				}		
				uniqueMaze.push(choosenCell);
			}
			
		}		
		mazeSize--;
	}
	mazes.push_back(uniqueMaze);
}

bool isPathAvailable(Stack<cellStruct> pathStack, Stack<cellStruct> blStack, int x, int y)
{
	//control function for path finding process
	bool isPathAvailable = true;

	while (!pathStack.isEmpty())
	{
		cellStruct cell = pathStack.topAndPop();
		
		if (x == cell.x && y == cell.y)
		{
			return false;
		}
	}

	while (!blStack.isEmpty()) //here is differnet than createMaze part. BlackListStack keeps restricted cells.
	{
		cellStruct cell = blStack.topAndPop();
		
		if (x == cell.x && y == cell.y)
		{
			return false;
		}
	}
	return isPathAvailable;
}

Stack<cellStruct> pathFinder(vector<Stack<cellStruct>>mazeList, int mazeID, int entryX, int entryY, int exitX, int exitY, int K, int mazeSize, int M, int N)
{
	Stack<cellStruct> pathStack; //will be pushed
	Stack<cellStruct> choosenStack = mazeList[mazeID-1]; //already came from main. includes specific maze
	Stack<cellStruct> blackListStack;
	
	Stack<cellStruct> choosenTempStack(choosenStack);
	Stack<cellStruct> forFirstCell(choosenStack);
	cellStruct firstCell;
	while (!forFirstCell.isEmpty()) //start from end all the way down to starting point. First cell become exit cell.
	{
		firstCell = forFirstCell.topAndPop();
		if (firstCell.x == exitX && firstCell.y == exitY)
		{	
			pathStack.push(firstCell);
		}
	}
	//here we have cellStruct with ending point. pushing pathStack step by step
	bool control = false; 

	while (!control)
	{
		bool found = true;
		if (pathStack.top().l == 0 && isPathAvailable(pathStack, blackListStack, pathStack.top().x -1, pathStack.top().y)) //check left && whether pathStack has direction and has blacklistStack
		{
			while (!choosenTempStack.isEmpty())
			{
				cellStruct cell = choosenTempStack.topAndPop();
				if (cell.x == pathStack.top().x-1 && cell.y == pathStack.top().y)
				{			
					pathStack.push(cell);
					found = false;

				}
			}			
		}
		else if (pathStack.top().r == 0 && isPathAvailable(pathStack, blackListStack, pathStack.top().x +1 ,pathStack.top().y)) //check right && whether pathStack has direction and has blacklistStack
		{
			while (!choosenTempStack.isEmpty())
			{
				cellStruct cell = choosenTempStack.topAndPop();
				if (cell.x == pathStack.top().x +1 && cell.y == pathStack.top().y)
				{				
					pathStack.push(cell);
					
				}
			}
		}
		else if (pathStack.top().u == 0 && isPathAvailable(pathStack, blackListStack, pathStack.top().x  ,pathStack.top().y+1)) //check up && whether pathStack has direction and has blacklistStack
		{
			while (!choosenTempStack.isEmpty())
			{
				cellStruct cell = choosenTempStack.topAndPop();
				if (cell.x == pathStack.top().x && cell.y == pathStack.top().y+1) //cheack cell is 
				{			
					pathStack.push(cell);
					
				}
			}
		}
		else if (pathStack.top().d == 0 && isPathAvailable(pathStack, blackListStack, pathStack.top().x ,pathStack.top().y-1)) //check down && whether pathStack has direction and has blacklistStack
		{
			while (!choosenTempStack.isEmpty())
			{
				cellStruct cell = choosenTempStack.topAndPop();
				if (cell.x == pathStack.top().x && cell.y == pathStack.top().y-1)
				{				
					pathStack.push(cell);
					
				}
			}
		}
		else //comes here if there is no available point. GO back and put in pathStack. 
		{ 
			blackListStack.push(pathStack.topAndPop());
		}
		choosenTempStack = choosenStack; //poping makes choosenTempStack become less. equate to choosenStack and start again

		if (pathStack.top().x == entryX && pathStack.top().y == entryY) //if true it means while must and because all relevant path points are in the stack
		{
			control = true;
		}
	}
	return pathStack;
}

void writingPathProcess(Stack<cellStruct> pathStack, int mazeID, int entryX, int entryY, int exitX,int exitY)
{
	//path writing process
	string fileName;
	ofstream outdata;
	fileName = "maze_" + to_string(mazeID) + "_path_"+to_string(entryX) + "_"+to_string(entryY)+"_" + to_string(exitX) + "_"+to_string(exitY)+".txt";
	outdata.open(fileName.c_str());

	while (!pathStack.isEmpty())
	{
		cellStruct cell = pathStack.topAndPop();		//pathSctak from main, includes only direct paths. each step take out and print it
		outdata<<cell.x<< " "<<cell.y<<endl;							
	}
	outdata.close();
}
int main()
{
	
	vector<Stack<cellStruct>> mazeList;
	
	int K,M,N;

	int mazeID, entryX, entryY, exitX, exitY;
	cout<<"Enter the number of mazes: ";
	cin>>K;
	cout<<endl<<"Enter the number of rows and columns (M and N) ";
	cin>>M>>N;
	cout<<endl<<"All mazes are generated."<<endl;
	

	for (int i = 0; i < K; i++)
	{
		createMaze(M, N, K, mazeList);		//create each maze according to K
	}

	writingProcess(mazeList, M, N);		//here mazes are writing  

	cout<<"Enter a maze ID between 1 to " << K <<" inclusive to find a path: ";
	cin>>mazeID;
	cout<<endl<<"Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin>>entryX>>entryY;
	cout<<endl<<"Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin>>exitX>>exitY;
	int mazeSize = M*N-1;
	Stack<cellStruct> pathList;
	pathList = pathFinder(mazeList, mazeID, entryX, entryY, exitX, exitY, K, mazeSize, M, N);
	writingPathProcess(pathList, mazeID,entryX,entryY,exitX,exitY);

	
	

}