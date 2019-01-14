/********************************************************************************************************************
** Name: Thomas Lem																								   **
** Date: 12/04/2018																								   **
** Description: Source code for class Player.																	   **
********************************************************************************************************************/

#include "player.hpp"
#include "space.hpp"

/********************************************************************************************************************
**												Player::Player										     		   **
** Default constructor initializes the Player's health points and sets the atticOpen to false.					   **
********************************************************************************************************************/
Player::Player()
{
	set_healthPoints(125);
	set_atticOpen(false);
}

/********************************************************************************************************************
**												Player::~Player										     		   **
** Default destructor																							   **
********************************************************************************************************************/
Player::~Player() {}

/********************************************************************************************************************
**												Player::moveTop										     		   **
** This function allows the player to move from the current space it is occupying to the space that the current    **
** space's top pointer points to by setting the Player's currentSpace value to equal to the currentSpace's top     **
** top pointer. If the space is keySpace (locked), check user inventory for key. Deduct 5 from current health for  **
** each function call.																							   **
********************************************************************************************************************/
void Player::moveTop()
{
	// Make sure space player can move to space
	if (currentSpace->get_topSpace() != nullptr)
	{
		// If no key is required, move to next space and set current space of player
		if (!currentSpace->get_topSpace()->get_keySpace())
		{
			set_currentSpace(currentSpace->get_topSpace());
			std::cout << "You are now in the " << this->currentSpace->get_nameSpace() << "." << std::endl;

			// Player loses 5HP for every move due to poison
			this->healthPoints -= 5;

			// Display current health
			std::cout << "Current health points: " << this->get_healthPoints() << std::endl << std::endl;
		}
		else
		{
			// If moving top to front porch, player must have key to Front Porch, no health loss for win
			if (checkItem("Key to Front Porch"))
			{
				set_currentSpace(currentSpace->get_topSpace());
				std::cout << "Unlocked the door. You are now in the " << currentSpace->get_nameSpace() << "." << std::endl << std::endl;
			}
			else
			{
				std::cout << "The door is locked. Looks like you need a key." << std::endl << std::endl;
			}
		}
	}
	else
	{
		std::cout << "There is nothing there." << std::endl << std::endl;
	}

}

/********************************************************************************************************************
**												Player::moveRight										     	   **
** This function allows the player to move from the current space it is occupying to the space that the current    **
** space's right pointer points to by setting the Player's currentSpace value equal to the currentSpace's right    **
** pointer. If the space is keySpace (locked), check user inventory for key. Deduct 5 from current health for each **
** function call.																								   **
********************************************************************************************************************/
void Player::moveRight()
{
	// Make sure player can move to space
	if (currentSpace->get_rightSpace() != nullptr)
	{
		// If no key is required, move to next space and set current space of player
		if (!(currentSpace->get_rightSpace()->get_keySpace()))
		{
			set_currentSpace(currentSpace->get_rightSpace());
			std::cout << "You are now in the " << this->currentSpace->get_nameSpace() << "." << std::endl;

			// Player loses 5HP for every move due to poison
			this->healthPoints -= 5;

			// Display current health
			std::cout << "Current health points: " << this->get_healthPoints() << std::endl << std::endl;
		}
		else
		{
			// If moving right to attic, player must have key to attic
			if (checkItem("Key to Attic"))
			{
				set_currentSpace(currentSpace->get_rightSpace());
				std::cout << "Unlocked the door. You are now in the " << currentSpace->get_nameSpace() << "." << std::endl;

				// Player loses 5HP for every move due to poison
				this->healthPoints -= 5;

				// Remove key from inventory, display current health, and set atticOpen to true
				removeItem("Key to Attic");
				displayInventory();
				set_atticOpen(true);
				currentSpace->set_keySpace(false);
				std::cout << "Current health points: " << this->get_healthPoints() << std::endl << std::endl;
			}
			else
			{
				std::cout << "The door is locked. Looks like you need a key." << std::endl << std::endl;
			}
		}
	}
	else
	{
		std::cout << "There is nothing there." << std::endl << std::endl;
	}
}

/********************************************************************************************************************
**												Player::moveBottom										     	   **
** This function allows the player to move from the current space it is occupying to the space that the current    **
** space's bottom pointer points to by setting the Player's currentSpace value equal to the currentSpace's bottom  **
** pointer. Deduct 5 from current health for each function call.												   **
********************************************************************************************************************/
void Player::moveBottom()
{
	// Make sure space player can move to space
	if (currentSpace->get_bottomSpace() != nullptr)
	{
		set_currentSpace(currentSpace->get_bottomSpace());
		std::cout << "You are now in the " << this->currentSpace->get_nameSpace() << "." << std::endl;

		// Player loses 5HP for every move due to poison
		this->healthPoints -= 5;

		// Display current health
		std::cout << "Current health points: " << this->get_healthPoints() << std::endl << std::endl;
	}
	else
	{
		std::cout << "There is nothing there." << std::endl << std::endl << std::endl;
	}
}

/********************************************************************************************************************
**												Player::moveLeft										     	   **
** This function allows the player to move from the current space it is occupying to the space that the current    **
** space's left pointer points to by setting the Player's currentSpace value equal to the currentSpace's left      **
** pointer. If the space is keySpace (locked), check user inventory for items. Deduct 5 from current health for    **
** each function call.																							   **
********************************************************************************************************************/
void Player::moveLeft()
{
	// Make sure space player can move to space
	if (currentSpace->get_leftSpace() != nullptr)
	{
		// If no key is required, move to next space and set space
		if (!currentSpace->get_leftSpace()->get_keySpace())
		{
			set_currentSpace(currentSpace->get_leftSpace());
			std::cout << "You are now in the " << this->currentSpace->get_nameSpace() << "." << std::endl;

			// Player loses 5HP for every move due to poison
			this->healthPoints -= 5;

			// Display current health
			std::cout << "Current health points: " << this->get_healthPoints() << std::endl << std::endl;
		}
		else
		{
			// If moving left to front porch, player must have garage door opener and AA batteries
			if (checkItem("Garage Door Opener") && checkItem("AA Batteries"))
			{
				set_currentSpace(currentSpace->get_leftSpace());
				std::cout << "Opened the garage door! You are now in the " << currentSpace->get_nameSpace() << "." << std::endl;

				// Display current health
				std::cout << "Current health points: " << this->get_healthPoints() << std::endl << std::endl;
			}
			else
			{
				if (checkItem("Garage Door Opener") && !checkItem("AA Batteries"))
				{
					std::cout << "The garage door doesn't budge. If only you had some AA Batteries for the Garage Door Opener." << std::endl << std::endl;
				}
				else
				{
					std::cout << "The garage door doesn't budge." << std::endl << std::endl;
				}
			}
		}
	}
	else
	{
		std::cout << "There is nothing there." << std::endl << std::endl;
	}
}

/********************************************************************************************************************
**												Player::set_currentSpace										   **
** This function takes in a pointer to a Space object as a parameter to set the Player's currentSpace to the       **
** pointer to the Space object being passed.																	   **
********************************************************************************************************************/
void Player::set_currentSpace(Space *space)
{
	this->currentSpace = space;
}

/********************************************************************************************************************
**												Player::get_currentSpace										   **
** Returns a pointer to the space the Player is occupying.														   **
********************************************************************************************************************/
Space* Player::get_currentSpace()
{
	return this->currentSpace;
}

/********************************************************************************************************************
**												Player::set_healthPoints										   **
** This function takes in an integer and sets it as the Player's health points.									   **
********************************************************************************************************************/
void Player::set_healthPoints(int hp)
{
	this->healthPoints = hp;
}

/********************************************************************************************************************
**												Player::get_healthPoints										   **
** Returns an integer value of the Player's health points.														   **
********************************************************************************************************************/
int Player::get_healthPoints()
{
	return this->healthPoints;
}

/********************************************************************************************************************
**												Player::playerDeath												   **
** This function returns true if the Player's health drops below 0.												   **
********************************************************************************************************************/
bool Player::playerDeath()
{
	if (this->get_healthPoints() <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/********************************************************************************************************************
**												Player::set_atticOpen											   **
** This function takes in a bool to set the atticOpen flag after the Player has visited the Attic once.			   **
********************************************************************************************************************/
void Player::set_atticOpen(bool open)
{
	this->atticOpen = open;
}

/********************************************************************************************************************
**												Player::get_atticOpen											   **
** Returns the bool value of the atticOpen flag.																   **
********************************************************************************************************************/
bool Player::get_atticOpen()
{
	return this->atticOpen;
}

/********************************************************************************************************************
**												Player::checkItem												   **
** If vector charInventory is not empty, returns true if the string being passed is found in the vector.		   **
********************************************************************************************************************/
bool Player::checkItem(std::string inInventory)
{
	if (!charInventory.empty())
	{
		for (size_t i = 0; i < this->charInventory.size(); i++)
		{
			if (charInventory[i] == inInventory)
			{
				return true;
			}
		}
	}
	return false;
}

/********************************************************************************************************************
**												Player::fullInventory											   **
** Returns true if the charInventory vector capacity reaches three.												   **
********************************************************************************************************************/
bool Player::fullInventory()
{
	// Player can hold up to 3 items at a time
	if (this->charInventory.size() > 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/********************************************************************************************************************
**												Player::addItem													   **
** Passes in a string to be added to the vector charInventory. If fullInvetory flag is set, does not add. Display  **
** the inventory in either case by calling displayInventory().													   **
********************************************************************************************************************/
void Player::addItem(std::string item)
{
	if (!fullInventory())
	{
		this->charInventory.push_back(item);
		std::cout << item << " has been added to your inventory." << std::endl;
		displayInventory();
	}
	else
	{
		std::cout << "Inventory at max capacity!" << std::endl;
		displayInventory();
	}
}

/********************************************************************************************************************
**												Player::removeItem												   **
** Passes in a string to be removed from the charInventory vector. Requires "algorithm" to use std::remove on      **
** vector.																										   **
********************************************************************************************************************/
void Player::removeItem(std::string toRemove)
{
	this->charInventory.erase(std::remove(charInventory.begin(), charInventory.end(), toRemove), charInventory.end());
	std::cout << toRemove << " removed from inventory." << std::endl << std::endl;
}

/********************************************************************************************************************
**												Player::displayInventory										   **
** Prints out the users vector charInventory to the console by printing out the element at each position.          **
********************************************************************************************************************/
void Player::displayInventory()
{
	if (!charInventory.empty())
	{
		std::cout << "Items in inventory: ";
		for (size_t i = 0; i < this->charInventory.size(); i++)
		{
			if ((i+1) != charInventory.size())
			{
				std::cout << charInventory[i] << ", ";
			}

			// In the case of the last item in the inventory (no comma, endl)
			else
			{
				std::cout << charInventory[i] << std::endl;
			}
		}
	}
	else
	{
		std::cout << "There are no items in your inventory. " << std::endl;
	}
}
