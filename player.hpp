/********************************************************************************************************************
** Name: Thomas Lem																								   **
** Date: 12/04/2018																								   **
** Description: Header file for class Player. The player contains an integer for health points, a boolean value    **
** to determine if the player has entered the attic, a pointer to a Space object to keep track of the space the    **
** Player occupies, and a vector to store items as strings.														   **
********************************************************************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

// Forward declaration
class Space;

#include <iostream>
#include <vector>
#include <algorithm>

class Player
{
	protected:
		int healthPoints;
		bool atticOpen;
		Space *currentSpace;
		std::vector<std::string> charInventory;

	public:
		Player();
		~Player();

		// Functions to move character
		void moveTop();
		void moveRight();
		void moveBottom();
		void moveLeft();

		// Functions to set and get current space
		void set_currentSpace(Space *);
		Space* get_currentSpace();
		
		// Functions for healthPoints
		void set_healthPoints(int);
		int get_healthPoints();
		bool playerDeath();

		//Functions for atticOpen
		void set_atticOpen(bool);
		bool get_atticOpen();

		// Functions for inventory
		bool checkItem(std::string);
		bool fullInventory();
		void addItem(std::string);
		void removeItem(std::string);
		void displayInventory();
};

#endif