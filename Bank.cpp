
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

const string ClientsFileName = "clients.txt";
void ShowMainMenue();


struct  sClient
{
	string accountnumber;
	string pincode;
	string name;
	string phone;
	double AccountBalance;
	bool markfordelet = false;
};
enum Enmainscreen { showclient = 1, addcliient = 2, deleteclient = 3, updateclient = 4, findclient = 5, exitscreen = 6 };

void GoBackToMainMenueScrren()
{
	cout << "\n\nclique enter of the return to main menue screen";
	system("pause>0");
	ShowMainMenue();
}


short readnumber()
{
	int number = 0;
	cout << "Please Enter The Number [1} to [6] ?";
	cin >> number;

	return number;
}

vector <string> SplitString(string s1, string dilim)
{
	vector <string> vsplit;

	short pos = 0;
	string sword;

	while ((pos = s1.find(dilim)) != std::string::npos)
	{
		sword = s1.substr(0, pos);
		if (sword != "")
		{
			vsplit.push_back(sword);
		}

		s1.erase(0, pos + dilim.length());

	}

	if (s1 != "")
	{
		vsplit.push_back(s1);
	}

	return vsplit;

}

sClient ConvertLinetoRecord(string line, string Seperator = "#//#")
{
	vector <string> vstringline;
	sClient client;

	vstringline = SplitString(line, Seperator);

	client.accountnumber = vstringline[0];
	client.pincode = vstringline[1];
	client.name = vstringline[2];
	client.phone = vstringline[3];
	client.AccountBalance = stod(vstringline[4]);

	return client;


}

vector <sClient> LoadCleintsDataFromFile(string ClientsFileName)
{
	vector <sClient> vclients;
	fstream Myfile;

	Myfile.open(ClientsFileName, ios::in);
	if (Myfile.is_open())
	{
		string line;
		sClient client;
		while (getline(Myfile, line))
		{
			client = ConvertLinetoRecord(line);

			vclients.push_back(client);
		}


		Myfile.close();

	}



	return vclients;

}

void PrintClientRecord(sClient client)
{

	cout << "| " << setw(15) << left << client.accountnumber;
	cout << "| " << setw(10) << left << client.pincode;
	cout << "| " << setw(40) << left << client.name;
	cout << "| " << setw(20) << left << client.phone;
	cout << "| " << setw(15) << left << client.AccountBalance;

}

void showclientscreen()
{
	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\t\tclient (" << vclients.size() << ") client(s).";
	cout << "\n________________________________________________________";
	cout << "________________________________________________________\n" << endl;

	cout << "| " << setw(15) << left << "account number ";
	cout << "| " << setw(10) << left << "pin code ";
	cout << "| " << setw(40) << left << "name";
	cout << "| " << setw(20) << left << "phone ";
	cout << "| " << setw(15) << left << "account balance";

	cout << "\n________________________________________________________";
	cout << "________________________________________________________\n" << endl;

	for (sClient client : vclients)
	{
		PrintClientRecord(client);
		cout << endl;
	}


	cout << "\n________________________________________________________";
	cout << "________________________________________________________\n" << endl;



}





string ConvertRecordToLine(sClient clinet, string suplitr = "#//#")
{
	string stClientRecord = "";

	stClientRecord = stClientRecord + clinet.accountnumber + suplitr;
	stClientRecord = stClientRecord + clinet.pincode + suplitr;
	stClientRecord = stClientRecord + clinet.name + suplitr;
	stClientRecord = stClientRecord + clinet.phone + suplitr;
	stClientRecord = stClientRecord + to_string(clinet.AccountBalance) + suplitr;

	return stClientRecord;

}

bool ClientExistsByAccountNumber(string accountnumber, string FileName)
{
	vector <sClient> vclients;
	fstream Myfile;
	Myfile.open(FileName, ios::in);
	if (Myfile.is_open())
	{
		string line;
		sClient client;
		while (getline(Myfile, line))
		{
			client = ConvertLinetoRecord(line);
			if (client.accountnumber == accountnumber)
			{
				Myfile.close();
				return true;
			}
			vclients.push_back(client);
		}
		Myfile.close();
	}


	return false;
}

sClient ReadNewClient()
{
	sClient client;

	cout << "enter account number ? ";
	getline(cin >> ws, client.accountnumber);

	while (ClientExistsByAccountNumber(client.accountnumber, ClientsFileName))
	{
		cout << "\nclient with[" << client.AccountBalance << "] already exits, enter another account ";
		getline(cin >> ws, client.accountnumber);
	}


	cout << "enter pin code ? ";
	getline(cin, client.pincode);

	cout << "enter name ? ";
	getline(cin, client.name);

	cout << "enter phone ? ";
	getline(cin, client.phone);

	cout << "enter account balance ? ";
	cin >> client.AccountBalance;

	return client;

}

void AddDataLineToFile(string filename, string stDataLine)
{
	fstream Myfile;
	Myfile.open(filename, ios::out | ios::app);
	if (Myfile.is_open())
	{
		Myfile << stDataLine << endl;
		Myfile.close();
	}


}

void AddNewClient()
{
	sClient client;
	client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(client));

}

void ShowAddClientsScreen()
{
	char addmore = 'Y';
	do
	{
		system("cls");
		cout << "=================================================\n";
		cout << "\t\tadd new clients screen \n";
		cout << "=================================================\n";

		cout << "Adding New Client:\n\n";

		AddNewClient();


		cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
		cin >> addmore;
	} while (toupper(addmore) == 'Y');




}



string ReadString()
{
	string s1;
	cout << "\nPlease enter AccountNumber? ";
	getline(cin >> ws, s1);

	return s1;

}

bool FindClientByAccountNumber(string accounetnumber, vector <sClient> vclients, sClient& client)
{

	for (sClient c : vclients)
	{
		if (c.accountnumber == accounetnumber)
		{
			client = c;
			return true;
		}

	}


	return false;
}

void PrintClientCard(sClient client)
{
	cout << "the following are the client delails:\n\n";
	cout << "=================================================\n";
	cout << "account number : " << client.accountnumber << endl;
	cout << "pin code       : " << client.pincode << endl;
	cout << "name           : " << client.name << endl;
	cout << "phone          : " << client.phone << endl;
	cout << "account balance : " << client.AccountBalance << endl;
	cout << "=================================================\n";

}

bool MarkClientForDeleteByAccountNumber(string accounetnumber, vector <sClient>& vclients)
{
	for (sClient& c : vclients)
	{
		if (c.accountnumber == accounetnumber)
		{
			c.markfordelet = true;
			return true;
		}

	}
	return false;

}

vector <sClient> SaveCleintsDataToFile(string accounetnumber, vector <sClient>& vclients)
{
	fstream Myfile;
	string dataline;
	Myfile.open(ClientsFileName, ios::out);

	if (Myfile.is_open())
	{
		for (sClient& c : vclients)
		{
			if (c.markfordelet == false)
			{
				dataline = ConvertRecordToLine(c);
				Myfile << dataline << endl;
			}


		}

		Myfile.close();
	}

	return vclients;

}

bool DeleteClientByAccountNumber(string accounetnumber, vector <sClient>& vclients)
{
	sClient client;
	char anwser = 'n';

	if (FindClientByAccountNumber(accounetnumber, vclients, client))
	{
		PrintClientCard(client);
		char anwser = 'n';

		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> anwser;
		if (anwser == 'Y' || anwser == 'y')
		{
			MarkClientForDeleteByAccountNumber(accounetnumber, vclients);
			SaveCleintsDataToFile(accounetnumber, vclients);


			//Refresh Clients
			vclients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}

	}
	else
	{
		cout << "client with account number (" << accounetnumber << ") not found!";
		return false;
	}
	return false;

}

void ShowDeleteClientsScreen()
{
	cout << "=================================================\n";
	cout << "\t\tDelete clients screen \n";
	cout << "=================================================\n";
	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);
	string accounetnumber = ReadString();
	DeleteClientByAccountNumber(accounetnumber, vclients);
}



sClient ChangeClientRecord(string accounetnumber)
{
	sClient client;

	client.accountnumber = accounetnumber;

	cout << "pelase enter pin code ? ";
	getline(cin >> ws, client.pincode);

	cout << "pelase enter name ? ";
	getline(cin, client.name);

	cout << "pelase enter the phone ? ";
	getline(cin, client.phone);

	cout << "pelase enter the account balance ? ";
	cin >> client.AccountBalance;

	return client;

}

bool UpdateClientByAccountNumber(string accounetnumber, vector <sClient>& vclients)
{
	sClient client;
	char anwser = 'n';

	if (FindClientByAccountNumber(accounetnumber, vclients, client))
	{
		PrintClientCard(client);
		char anwser = 'n';

		cout << "\n\nAre you sure you want update this client? y/n?";
		cin >> anwser;
		if (anwser == 'Y' || anwser == 'y')
		{
			for (sClient& c : vclients)
			{
				c = ChangeClientRecord(accounetnumber);
				break;

			}

			SaveCleintsDataToFile(accounetnumber, vclients);

			cout << "\n\nClient Updated Successfully.";
			return true;
		}

	}
	else
	{
		cout << "client with account number (" << accounetnumber << ") not found!";
		return false;
	}



	return false;

}

void ShowUpDateClientsScreen()
{
	cout << "=================================================\n";
	cout << "\t\t Up Date clients screen \n";
	cout << "=================================================\n";
	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);
	string accounetnumber = ReadString();
	UpdateClientByAccountNumber(accounetnumber, vclients);

}



void ShowFindClientsScreen()
{
	cout << "=================================================\n";
	cout << "\t\tFind clients screen \n";
	cout << "=================================================\n";

	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);
	string accounetnumber = ReadString();
	sClient client;

	if (FindClientByAccountNumber(accounetnumber, vclients, client))
	{
		PrintClientCard(client);
	}
	else
	{
		cout << "\nclient with account number (" << accounetnumber << ") not found!";
	}



}


void ShowExitClientsScreen()
{
	cout << "=================================================\n";
	cout << "\t\tProgram ends :-) \n";
	cout << "=================================================\n";

}


void PerfromMainMenueOption(Enmainscreen mainscreen)
{
	switch (mainscreen)
	{
	case Enmainscreen::showclient:
	{
		system("cls");
		showclientscreen();
		GoBackToMainMenueScrren();
		break;
	}

	case Enmainscreen::addcliient:
	{
		system("cls");
		ShowAddClientsScreen();
		GoBackToMainMenueScrren();
		break;
	}


	case Enmainscreen::deleteclient:
	{
		system("cls");
		ShowDeleteClientsScreen();
		GoBackToMainMenueScrren();
		break;
	}
	case Enmainscreen::updateclient:
	{
		system("cls");
		ShowUpDateClientsScreen();
		GoBackToMainMenueScrren();
		break;

	}
	case Enmainscreen::findclient:
	{
		system("cls");
		ShowFindClientsScreen();
		GoBackToMainMenueScrren();
		break;
	}
	case Enmainscreen::exitscreen:
	{
		system("cls");
		ShowExitClientsScreen();
		break;
	}

	}


}


void ShowMainMenue()
{
	system("cls");
	cout << "=================================================\n";
	cout << "\t\tmaine menue screen \n";
	cout << "=================================================\n";
	cout << "\t\t[1] show client list.\n";
	cout << "\t\t[2] add client list.\n";
	cout << "\t\t[3] delete client list.\n";
	cout << "\t\t[4] update client list.\n";
	cout << "\t\t[5] find client list.\n";
	cout << "\t\t[6] exit.\n";
	cout << "=================================================\n";

	PerfromMainMenueOption((Enmainscreen)readnumber());

}

int main()
{

	
	ShowMainMenue();
	

	system("pause>0");
	return 0;
}
