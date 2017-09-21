// @author: Sean Nash
// @login@ C00217019
// Date 14/9/17
// LAB 1, TEXT BASED MISSILE COMMAND?
// Time Taken: 1 hour
// Bugs:

#include <string>
#include <iostream>

typedef struct Position //Defines Co Ordinates as Positions
{
	int xPos;
	int yPos;

	void print()
	{
		std::cout << "X Position - " << xPos << std::endl << "Y Position - " << yPos << std::endl;
	}
};

typedef struct twats //Defines Target Struct
{
	Position baseLocation;
	bool twatDead;
};

enum Warhead { WHITE_PHOSPHOR, BAD_STUFF, DAYTIME_TELEVISION }; //Defines the ENUM of the Payload

struct Missile //Defines the struct of the missile
{ 
	Warhead loadout; //Enum Declared
	Position currentLocation;//Current location of Missile
	Position targetLocation;//End goal of missile
	bool buttonPressed;//Is missile live or dead?
	int range;
	int handling;
	int strength;
	int turnTracker;

	void armed()//Kills or sets missile alive
	{
		if (buttonPressed == true)
		{
			buttonPressed = false;
		}
		else
		{
			buttonPressed = true;
		}
	}

	void update()//Moves the missile closer to end goal
	{
		if (buttonPressed == true)
		{
			currentLocation.xPos += 1;
			turnTracker++;
			if (turnTracker == handling)
			{
				turnTracker = 0;
				if (currentLocation.yPos < targetLocation.yPos)
				{
					currentLocation.yPos += 1;
				}
				if (currentLocation.yPos > targetLocation.yPos)
				{
					currentLocation.yPos -= 1;
				}
			}
			std::cout << std::endl << "Satelite Tracking - X Pos " << currentLocation.xPos << " - Y Pos " << currentLocation.yPos;
		}
	}
};
void setUpMissiles(Missile &BOOM)//Sets up the Missile and asks for payload input
{
	BOOM.currentLocation.xPos = 0;
	BOOM.currentLocation.yPos = 0;//Default Start Position
	BOOM.buttonPressed = false;
	int loadAmmo = 0;//Reset Payload
	bool notPicked = true;//Used to catch invalid
	BOOM.turnTracker = 0;
	while (notPicked)
	{
		std::cin >> loadAmmo;
		if (loadAmmo == 1)
		{
			BOOM.loadout = WHITE_PHOSPHOR;//ADD PAYLOAD CHOICE
			BOOM.range = 5;
			BOOM.handling = 1;
			BOOM.strength = 0;
			notPicked = false;
		}
		else if (loadAmmo == 2)
		{
			BOOM.loadout = BAD_STUFF;//ADD PAYLOAD CHOICE
			BOOM.range = 10;
			BOOM.handling = 2;
			BOOM.strength = 1;
			notPicked = false;
		}
		else if (loadAmmo == 3)
		{
			BOOM.loadout = DAYTIME_TELEVISION;//ADD PAYLOAD CHOICE
			BOOM.range = 5;
			BOOM.handling = 1;
			BOOM.strength = 2;
			notPicked = false;
		}
		else if (loadAmmo != 1 || loadAmmo != 2 || loadAmmo != 3)
		{
			std::cout << "We dont have any of that, pick what we have" << std::endl;
		}
	}
}

void setUpTwats(twats &dummy, int xPos, int yPos)
{
	dummy.baseLocation.xPos = xPos;
	dummy.baseLocation.yPos = yPos;
	dummy.twatDead = true;

}
void launchCode()
{
	int password = 0;
	while (password != 1234)
	{
		std::cout << "Input Arming Code - **** (There is a small note that reads 'Its 1234 on everything')" << std::endl;
		std::cin >> password;
		if (password != 1234)
		{
			std::cout << "Error!!! WRONG CODE" << std::endl;
		}
	}
}
int main()
{
	Missile ONE;
	twats deadTwats;
	setUpTwats(deadTwats, 1,1);
	twats luckyTwats;
	setUpTwats(luckyTwats, 5, 5);
	while (deadTwats.twatDead || luckyTwats.twatDead)
	{

		std::cout << std::endl << "Please Choose what terrible thing to burden people we dont like with (Enter Number)" << std::endl 
			<< "1 - White Phosphor - Range 5 - Handling - Good (1 Across Per 1 Up/Down) - Str - 0 (Direct Hits)" 
			<< std::endl << "2 - Bad Stuff - Range 10 - Handling - Poor (2 Across Per 1 Up/Down) - Str - 1 (Area of Effect of 1)" 
			<< std::endl << "3 - Daytime Television - Range 5 - Handling - Good (1 Across Per 1 Up/Down) - Str - 2 (Area of Effect of 2) " << std::endl;
		setUpMissiles(ONE);

		std::cout << std::endl << "Choose your Targets" << std::endl;
		if (deadTwats.twatDead)
		{
			std::cout << "Scans Tell us there are soon to be dead twats at " << deadTwats.baseLocation.xPos << " , " << deadTwats.baseLocation.yPos << std::endl;
		}
		if (luckyTwats.twatDead)
		{
			std::cout << "Scans Tell us there are extraordinarily lucky twats at " << luckyTwats.baseLocation.xPos << " , " << luckyTwats.baseLocation.yPos << std::endl;
		}
		int tempX = 0;
		int tempY = 0;
		std::cout << "Input the X CoOrdinates" << std::endl;
		std::cin >> tempX;
		std::cout << "Input the Y CoOrdinates" << std::endl;
		std::cin >> tempY;

		launchCode();

		ONE.targetLocation.xPos = tempX;//ADD TARGET CHOICE
		ONE.targetLocation.yPos = tempY;

		ONE.armed();
		while (ONE.buttonPressed == true)
		{
			ONE.update();
			if (ONE.currentLocation.xPos == ONE.targetLocation.xPos && ONE.currentLocation.yPos == ONE.targetLocation.yPos)
			{
				bool exploded = false;
				std::cout << std::endl << "Checking for enemy...." << std::endl;
				if (ONE.targetLocation.xPos >= (deadTwats.baseLocation.xPos - ONE.strength) //Checks if its more than the lowest in the  X range 
					&& ONE.targetLocation.xPos <= (deadTwats.baseLocation.xPos + ONE.strength) //Checks if its less than the most in the X range
					&& ONE.targetLocation.yPos >= (deadTwats.baseLocation.yPos - ONE.strength)//Checks if its more than the lowest in the Y Range
					&& ONE.targetLocation.yPos <= (deadTwats.baseLocation.yPos + ONE.strength) && deadTwats.twatDead) //Checks if its less than the lowest in the Y Range
				{
					std::cout << "KABOOM! Enemy's Day Ruined" << std::endl;
					exploded = true;
					deadTwats.twatDead = false;
				}
				if (ONE.targetLocation.xPos >= (luckyTwats.baseLocation.xPos - ONE.strength) //Checks if its more than the lowest in the  X range 
					&& ONE.targetLocation.xPos <= (luckyTwats.baseLocation.xPos + ONE.strength) //Checks if its less than the most in the X range
					&& ONE.targetLocation.yPos >= (luckyTwats.baseLocation.yPos - ONE.strength)//Checks if its more than the lowest in the Y Range
					&& ONE.targetLocation.yPos <= (luckyTwats.baseLocation.yPos + ONE.strength) && luckyTwats.twatDead) //Checks if its less than the lowest in the Y Range
				{
					std::cout << "KABOOM! Enemy's Day Ruined" << std::endl;
					exploded = true;
					luckyTwats.twatDead = false;
				}
				if (exploded == false) //If it reaches its destination an isnt in range of any enemies
				{
					std::cout << "No contact... what a waste of perfectly terrible payload.." << std::endl;
				}
			}
			if (ONE.currentLocation.xPos > ONE.range)//Checks to make sure missile hasnt gone outside the Range
			{
				std::cout << std::endl << "LOST SIGNAL, ITS GONE SOMEWHERE, OUT OF SIGHT OUT OF MIND." << std::endl;
				ONE.armed();
			}
		}
		system("PAUSE");
	}

}

