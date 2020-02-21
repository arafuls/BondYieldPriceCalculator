#pragma once

class BondCalculator
{
public:
	BondCalculator();
	~BondCalculator();

	bool Compare(double a, double b, double epsilon);
	double SummationPV(int a_years, double a_face, double a_rate, double a_cashflow);
	double CalcYield(double a_coupon, int a_years, double a_face, double a_price);
	double CalcPrice(double a_coupon, int a_years, double a_face, double a_rate);


private:

};

