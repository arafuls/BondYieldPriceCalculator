#pragma once
class MainMenu
{
public:
	MainMenu();
	~MainMenu();


private:
	BondCalculator m_BC;

	bool GetDouble(double& a_num);
	bool GetInt(int& a_num);
	double GetUserBondData(int a_type);
	void PromptText();
	void Prompt();
	void Selection(int a_selection);

};

