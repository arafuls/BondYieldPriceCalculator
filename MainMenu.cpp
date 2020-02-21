#include "stdafx.h"

MainMenu::MainMenu()
{
	Prompt();
}

MainMenu::~MainMenu()
{
}


/*
NAME
	bool GetDouble(double& a_num)

PARAMETERS
	double& a_num	- An integer passed by reference to store user input.

DESCRIPTION
	Attempts to get a valid double from the user. User has 3 attempts to
	correctly enter a double before aborting and returning to main menu.
	Enter -1 to abort manually and return to main menu.

RETURNS
	Returns a boolen representing if the method completed successfully or
	was aborted.
*/
bool MainMenu::GetDouble(double& a_num)
{
	int count = 0;
	do
	{
		double num;
		std::cout << "    Input: ";
		std::cin >> num;

		if (num == -1)
		{
			return false;
		}

		if (std::cin.fail())
		{
			count++;
			std::cout << "    ERROR: Invalid character entered, try again!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			a_num = num;
			return true;
		}
	} while (count < 3);

	std::cout << "Too many failed attempts, returning to main menu.";
	return false;
}


/*
NAME
	bool GetInt(int& a_num)

PARAMETERS
	int& a_num	- An integer passed by reference to store user input.

DESCRIPTION
	Attempts to get a valid integer from the user. User has 3 attempts to 
	correctly enter an integer before aborting and returning to main menu.
	Enter -1 to abort manually and return to main menu.

RETURNS
	Returns a boolen representing if the method completed successfully or
	was aborted.
*/
bool MainMenu::GetInt(int& a_num)
{
	int count = 0;
	do
	{
		int num;
		std::cout << "    Input: ";
		std::cin >> num;

		if (num == -1)
		{
			return false;
		}

		if (std::cin.fail())
		{
			count++;
			std::cout << "    ERROR: Invalid character entered, try again!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			a_num = num;
			return true;
		}
	} while (count < 3);

	std::cout << "Too many failed attempts, returning to main menu.";
	return false;
}


/*
NAME
	double GetUserBondData(int a_type)

PARAMETERS
	int a_type	- Determines the type of data to collect from user input and
					the type of calculation to perform with collected data.
					* 1 is bond price to generate bond yield.
					* 2 is bond rate to generate bond price.

DESCRIPTION
	Prompts the user for input data, collects it, and calls the calculation
	method according based on the passed a_type. Enter -1 during data 
	collection to abort the process.

RETURNS
	Returns a double representing either the desired output or -99999 if aborted.
*/
double MainMenu::GetUserBondData(int a_type)
{
	double const ERROR_CODE = -99999;

	std::cout << " Bond Yield Calculator (-1 to stop)";
	std::cout << std::endl << std::endl;

	// Collect common data used by both calculations
	double coupon; 
	std::cout << " Enter Bond Coupon" << std::endl;
	if (!GetDouble(coupon)) { return ERROR_CODE; }
	std::cout << std::endl;

	int years;
	std::cout << " Enter Bond Years" << std::endl;
	if (!GetInt(years)) { return ERROR_CODE; }
	std::cout << std::endl;

	double face;
	std::cout << " Enter Bond Face Value" << std::endl;
	if (!GetDouble(face)) { return ERROR_CODE; }
	std::cout << std::endl;

	// Determine user data to collect and calculation to perform
	if (a_type == 1)
	{
		// Calculate Bond Yield 
		double price;
		std::cout << " Enter Bond Price" << std::endl;
		if (!GetDouble(price)) { return ERROR_CODE; }
		std::cout << "=========================" << std::endl;
		return m_BC.CalcYield(coupon, years, face, price);
	}
	else if (a_type == 2)
	{
		// Calculate Bond Price
		double rate;
		std::cout << " Enter Bond Rate" << std::endl;
		if (!GetDouble(rate)) { return ERROR_CODE; }
		std::cout << "=========================" << std::endl;
		return m_BC.CalcPrice(coupon, years, face, rate);
	}
	else
	{
		// Should not execute but allows for default code path
		return -99999;
	}
}


/*
NAME
	void PromptText()

DESCRIPTION
	Displays the main menu prompt to the user via stdout.
*/
void MainMenu::PromptText()
{
	std::cout << "Chimera Investment Corporation | Bond Yield Calculator" << std::endl << std::endl;

	std::cout << "    0: Exit Calculator" << std::endl;
	std::cout << "    1: Calculate Bond Yield" << std::endl;
	std::cout << "    2: Calculate Bond Price" << std::endl;
	std::cout << "    3: Demonstration Showcase" << std::endl << std::endl;
}


/*
NAME
	void Prompt()

DESCRIPTION
	Loops the Main Menu class so the user can continuously make calculations.
*/
void MainMenu::Prompt()
{
	do
	{
		int decision = 0;

		do
		{
			// Display options and record response
			PromptText();
			std::cout << "  Option: ";
			std::cin >> decision;

			// Ignore invalid entires
			if (std::cin.fail()) { decision = -99999; }
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << std::endl << std::endl << std::endl << std::endl;
		} while (decision < 0 || decision > 3);

		// Valid menu entry
		std::cout << std::endl;
		Selection(decision);
	} while (true);
}


/*
NAME
	void Selection(int a_selection)

PARAMETERS
	int a_selection	- An integer representing a selection from the main menu prompt.

DESCRIPTION
	Determines the appropriate code path based on the user's selection from the main
	menu.
*/
void MainMenu::Selection(int a_selection)
{
	m_BC = BondCalculator();
	std::cout << std::fixed << std::setprecision(7);

	switch (a_selection)
	{
	case 0:
		exit(EXIT_SUCCESS);
	case 1:
		std::cout << "Bond Yield: " << GetUserBondData(1) << std::endl;
		break;
	case 2:
		std::cout << "Bond Price: " << GetUserBondData(2) << std::endl;
		break;
	case 3:
		std::cout << " Demonstration Showcase" << std::endl;
		std::cout << " $1000 Bond w/ 10% Coupon, 832.4       Discount,  5 Years returns: " << m_BC.CalcYield(0.10, 5, 1000, 832.4) << std::endl;
		std::cout << " $1000 Bond w/ 10% Coupon, 15%             Rate,  5 Years returns: " << m_BC.CalcPrice(0.10, 5, 1000, 0.15) << std::endl << std::endl;

		std::cout << " $1000 Bond w/ 10% Coupon, 1000        Discount,  5 Years returns: " << m_BC.CalcYield(0.10, 5, 1000, 1000) << std::endl;
		std::cout << " $1000 Bond w/ 15% Coupon, 15%             Rate,  5 Years returns: " << m_BC.CalcPrice(0.15, 5, 1000, 0.15) << std::endl << std::endl;

		std::cout << " $1000 Bond w/ 10% Coupon, 1079.85      Premium,  5 Years returns: " << m_BC.CalcYield(0.10, 5, 1000, 1079.85) << std::endl;
		std::cout << " $1000 Bond w/ 10% Coupon, 8%              Rate,  5 Years returns: " << m_BC.CalcPrice(0.10, 5, 1000, 0.08) << std::endl << std::endl;

		std::cout << " $1000 Bond w/ 10% Coupon, 528.8807463 Discount, 30 Years returns: " << m_BC.CalcYield(0.10, 30, 1000, 528.8807463) << std::endl;
		std::cout << " $1000 Bond w/ 10% Coupon, 19%             Rate, 30 Years returns: " << m_BC.CalcPrice(0.10, 30, 1000, 0.19) << std::endl << std::endl;
		break;
	default:
		exit(EXIT_FAILURE);
	}
	std::cout << std::endl << std::endl << std::endl << std::endl;
}