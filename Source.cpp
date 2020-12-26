#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

//Day12 Part 1
//Given a list of instructions in the format of a single character and a numeric value, which are the directional instructions for a ferry, use them to determine where
//the ferry ends up and then get the manhattan distance of the final coordinates.
//The Instruction Legend
//Action N means to move north by the given value.
//Action S means to move south by the given value.
//Action E means to move east by the given value.
//Action W means to move west by the given value.
//Action L means to turn left the given number of degrees.
//Action R means to turn right the given number of degrees.
//Action F means to move forward by the given value in the direction the ship is currently facing.

//So given these instructions, if we pretend we are on a coordinate plane, where the center is 0,0. x represents east/west movement and y represents north west 
//movement.Going east will add the value, going west will subtract the value, going south will add the value and going north will subtract the value. We can divide 
//R and L instruction values by 90 to determine the number of turns. We will also need to keep track of where we are facing for F instructions.


//Day12 Part 2
//The meaning of the instructions has changed, now the N, S, E, W instructions move a waypoint in those directions by the given value so N3 moves the way point north
//by 3, the L and R instructions now rotate this waypoint around the ferry so if the way point is 10 East and 3 north and the instruction is R90 then the way point 
//will become 10 South and 3 East, and finally the F instructions moves the ferry by multiplying the value by the coordinates of the waypoint so if the instruction 
//is F10 and the way point is 10 South and 3 East then the ferry will move 100 units south and 30 units east. 

//So the big difference is the waypoint's rotation because it will swap between the x and y position, for each turn we need to swap the x and y and flip the sign if
//needed, looking at some code online rotating left will cause the Y coordinate to flip and rotating right will cause the x coordinate to flip, so a for loop can be
//used to iterate the number of rotations by increasing by 90, then we swap x and y and flip the sign for Y if going left or flip the sign for X if going right.

std::vector<std::string> getPuzzleInput()
{
	std::vector<std::string> input;

	std::ifstream file;
	std::string line;
	file.open("puzzle-input.txt");
	while (std::getline(file, line))
	{
		input.push_back(line);
	}

	return input;
}


int findAnswerPart1(std::vector<std::string> input)
{
	char direction = 'E';
	int x = 0;
	int y = 0;
	int indexCurrent = 0;
	int rotation = 0;
	int newDirection = 0;
	std::string directions = "NESW";

	for (auto i : input)
	{
		char instruction = i[0];
		int value = std::stoi(i.substr(1));

		if (instruction == 'F')
			instruction = direction;

		switch (instruction)
		{
		case 'N':
			y -= value;
			break;
		case 'S':
			y += value;
			break;
		case 'E':
			x += value;
			break;
		case 'W':
			x -= value;
			break;
		case 'L':
			indexCurrent = directions.find(direction);
			rotation = value / 90;
			newDirection = (indexCurrent - rotation);
			while (newDirection < 0)
			{
				newDirection += 4;
			}
			direction = directions[newDirection];
			break;
		case 'R':
			indexCurrent = directions.find(direction);
			rotation = value / 90;
			newDirection = (indexCurrent + rotation) % 4;
			direction = directions[newDirection];
			break;
		}
	}

	return std::abs(x) + std::abs(y);
}

int findAnswerPart2(std::vector<std::string> input)
{
	int ferryX = 0;
	int ferryY = 0;

	int wayX = 10;
	int wayY = 1;

	int tempX = 0;
	int tempY = 0;

	for (auto i : input)
	{
		char instruction = i[0];
		int value = std::stoi(i.substr(1));

		switch (instruction)
		{
		case 'N':
			wayY += value;
			break;
		case 'S':
			wayY -= value;
			break;
		case 'E':
			wayX += value;
			break;
		case 'W':
			wayX -= value;
			break;
		case 'L':
			for (int i = 0; i < value; i += 90)
			{
				tempX = wayX;
				tempY = wayY;
				tempY *= -1;

				wayX = tempY;
				wayY = tempX;
			}
			break;
		case 'R':
			for (int i = 0; i < value; i += 90)
			{
				tempX = wayX;
				tempX *= -1;
				tempY = wayY;

				wayX = tempY;
				wayY = tempX;
			}
			break;
		case 'F':
			ferryX += wayX * value;
			ferryY += wayY * value;
			break;
		}
	}

	return std::abs(ferryX) + std::abs(ferryY);

}

int main()
{
	std::vector<std::string> input = getPuzzleInput();

	std::cout << findAnswerPart1(input) << '\n';

	std::cout << findAnswerPart2(input) << '\n';

	return 0;
}