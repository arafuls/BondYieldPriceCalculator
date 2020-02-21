#include "stdafx.h"
#include "BondCalculator.h"

BondCalculator::BondCalculator()
{
}


BondCalculator::~BondCalculator()
{
}


/*
NAME
	bool Compare(double a, double b, double epsilon)

PARAMETERS
	double a		- The first double to compare.
	double b		- The second double to compare.
	double episilon	- The precision when comparing. Default (0.0000001).

DESCRIPTION
	Compares two doubles to see if they are within epsilon distance.

RETURNS
	Returns true if doubles are within epsilon distance, otherwise returns false.
*/
bool BondCalculator::Compare(double a, double b, double epsilon = 0.0000001)
{
	return abs(a - b) < epsilon;
}


/*
NAME
	double SummationPV(int a_years, double a_face, double a_rate, double a_cashflow)

PARAMETERS
	int a_years			- The number of years for bond maturity.
	double a_face		- The face value of the bond.
	double a_rate		- The yield rate of the bond.
	double a_cashflow	- The annual coupon payments to be made.

DESCRIPTION
	Sums total payments for a bond to calculate the current present value.

RETURNS
	Returns a double representing the total present value of the a bond.
*/
double BondCalculator::SummationPV(int a_years, double a_face, double a_rate, double a_cashflow)
{
	// Summation formula for present value
	double pv = 0;
	for (int i = 1; i < a_years + 1; i++)
	{
		pv += a_cashflow / pow(1 + a_rate, i);
	}
	pv += a_face / pow(1 + a_rate, a_years);	// Adding final payment to present value

	return pv;
}


/*
NAME
	double CalcYield(double a_coupon, int a_years, double a_face, double a_price)

PARAMETERS
	double a_coupon - The coupon rate percentage in decimal format (10% = 0.10).
	int a_years		- The number of years for bond maturity.
	double a_face	- The face value of the bond.
	double a_price	- The premium/discount rate of the bond.

DESCRIPTION
	Calculates the Yield to Maturity rate for a bond based on the bond's attributes.

RETURNS
	Returns a double representing the Yield to Maturity rate as a percentage.
	(ie. 15.4332% is returned as 0.154332)
*/
double BondCalculator::CalcYield(double a_coupon, int a_years, double a_face, double a_price)
{
	auto startTime = std::chrono::high_resolution_clock::now();
	//process to be timed

	double cashflow = a_coupon * a_face;	// Our annual coupon payments
	double r1 = 0;
	double r2 = 1;

	// Keep adjusting rate until we find exact number for the current premium/discount price
	while (true)
	{
		double rate = (r1 + r2) / 2;
		double pv = SummationPV(a_years, a_face, rate, cashflow);
		// If current rate gives us expected par value
		if (Compare(pv, a_price))
		{
			// Record processing time and timestamp
			auto endTime = std::chrono::high_resolution_clock::now();
			auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

			// Document calculation data to log file
			std::ofstream logfile;
			logfile.open("logs.txt", std::ios_base::app);
			if (logfile.is_open())
			{
				logfile << "Time " << std::chrono::seconds(std::time(NULL)).count() << "\n";
				logfile << "Calculated Bond Yield in " << time << " nanoseconds.\n";
				logfile << a_coupon*100 << "% Coupon, " << a_years << " Years, $" << a_face << " Face Value, $" << a_price << " Price\n\n";
				logfile.close();
			}

			return rate;
		}

		// Adjust rate accordingly to find exact pv
		if (pv < a_price)
		{
			// Estimated PV is too low
			r2 = rate;
		}
		else if (pv > a_price)
		{
			// Estimated PV is too high
			r1 = rate;
		}
	}
}


/*
NAME
	double CalcPrice(double a_coupon, int a_years, double a_face, double a_rate)

PARAMETERS
	double a_coupon - The coupon rate percentage in decimal format (10% = 0.10).
	int a_years		- The number of years for bond maturity.
	double a_face	- The face value of the bond.
	double a_rate	- The yield rate of the bond.

DESCRIPTION
	Calculates the price for a bond based on the bond's attributes.

RETURNS
	Returns a double representing the bond price.
*/
double BondCalculator::CalcPrice(double a_coupon, int a_years, double a_face, double a_rate)
{
	auto startTime = std::chrono::high_resolution_clock::now();

	double cashflow = a_coupon * a_face;	// Our annual coupon payments
	double pv = SummationPV(a_years, a_face, a_rate, cashflow);

	// Record processing time and timestamp
	auto endTime = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

	// Document calculation data to log file
	std::ofstream logfile;
	logfile.open("logs.txt", std::ios_base::app);
	if (logfile.is_open())
	{
		logfile << "Time " << std::chrono::seconds(std::time(NULL)).count() << "\n";
		logfile << "Calculated Bond Price in " << time << " nanoseconds.\n";
		logfile << a_coupon * 100 << "% Coupon, " << a_years << " Years, $" << a_face << " Face Value, " << a_rate*100 << "% Rate\n\n";
		logfile.close();
	}

	return pv;
}