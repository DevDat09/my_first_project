#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <fstream>
#include <cassert>
#include <iomanip>
#include <cctype>
using namespace std;

class Store
{
private:
	int numOfPhoneModels;
	int numOfCustomers;
	struct Phone
	{
		int phoneId;
		string brand;
		string phoneName;
		int quantity;
		int price;
		string availability;
		int RAM;
		int ROM;
		int productYear;
	};

	struct Customer
	{
		int customerId;
		string customerName;
		string customerPhone;
		Phone boughtPhone;
		string insuranceYear;
	};

	const char *inputFileName;
	ifstream inputFile;
	Phone *phone;
	Customer *customer;
	void getInput();
	int getNumberOfPhone();

public:
	Store(const char *inputFileName);
	~Store();

	void managePhoneInfo();
	void manageCustomInfo();
	void manageImport();
	void manageSale();

	int search(string name);
	void printPhone();
	void printFull();
	void updatePrice();

	void print1Customer();
	void printFullCustomer();
};

Store::Store(const char *ifn)
	: inputFileName(ifn)
{
	numOfPhoneModels = getNumberOfPhone();
	numOfCustomers = 0;
	inputFile.open(inputFileName);
	assert(inputFile);
	phone = new Phone[50];
	customer = new Customer[50];
	getInput();
}

Store::~Store()
{
	delete[] phone;
	delete[] customer;
	inputFile.close();
}

int Store::getNumberOfPhone()
{
	string line;
	int count = 0;
	inputFile.open(inputFileName);
	assert(inputFile);
	while (getline(inputFile, line))
		count++;
	inputFile.close();
	return count;
}

void Store::getInput()
{
	int count = 0;
	while (!inputFile.eof() && count < numOfPhoneModels)
	{
		inputFile >> phone[count].phoneId;
		inputFile >> phone[count].brand;
		inputFile >> phone[count].phoneName;
		inputFile >> phone[count].RAM;
		inputFile >> phone[count].ROM;
		inputFile >> phone[count].quantity;
		phone[count].availability = (phone[count].quantity == 0) ? "No" : "Yes";
		inputFile >> phone[count].price;
		inputFile >> phone[count++].productYear;
	}
	numOfPhoneModels = count;
}

void Store::printFull()
{
	system("cls");
	cout << "**************************************************************************************************************" << endl;
	cout << "**                                     MANAGE PHONE INFORMATION                                             **" << endl;
	cout << "**************************************************************************************************************" << endl
		 << endl;
	cout << "  +----------------+---------------+---------------+---------------------+----------------+----------------+  " << endl;
	cout << "  |    Phone Id    |    Brand      |      Name     |    Availability     |    Quantity    |    Price       |  " << endl;
	cout << "  +----------------+---------------+---------------+---------------------+----------------+----------------+  " << endl;
	for (int i = 0; i < numOfPhoneModels; ++i)
	{
		cout << "  |                                                                                                        |  " << endl;
		cout << "  |    " << setw(16) << left << phone[i].phoneId;
		cout << setw(17) << left << phone[i].brand;
		cout << setw(20) << left << phone[i].phoneName;
		phone[i].availability = (phone[i].quantity == 0) ? "No" : "Yes";
		cout << setw(21) << left << phone[i].availability;
		cout << setw(14) << left << phone[i].quantity;
		cout << setw(12) << left << phone[i].price << "|" << endl;
		cout << "  |                                                                                                        |  " << endl;
	}
	cout << "  +--------------------------------------------------------------------------------------------------------+  " << endl;
	cout << endl
		 << "    " << system("pause");
}

void Store::printFullCustomer()
{
	system("cls");
	cout << "**************************************************************************************************************" << endl;
	cout << "**                                 MANAGE CUSTOMER INFORMATION                                              **" << endl;
	cout << "**************************************************************************************************************" << endl
		 << endl;
	cout << "  +----------------+-----------------------+------------------------+-------------------+------------------+  " << endl;
	cout << "  |  Customer Id   |        Name           |      Phone Numer       |    Phone model    |  Insurance Year  |  " << endl;
	cout << "  +----------------+-----------------------+------------------------+-------------------+------------------+  " << endl;
	for (int i = 0; i < numOfCustomers; ++i)
	{
		cout << "  |                                                                                                        |  " << endl;
		cout << "  |  " << setw(20) << left << customer[i].customerId;
		cout << setw(25) << left << customer[i].customerName;
		cout << setw(23) << left << customer[i].customerPhone;
		cout << setw(25) << left << customer[i].boughtPhone.phoneName;
		cout << setw(9) << left << customer[i].insuranceYear << "|" << endl;
		cout << "  |                                                                                                        |  " << endl;
	}
	cout << "  +--------------------------------------------------------------------------------------------------------+  " << endl;
	cout << endl
		 << "    " << system("pause");
}

void Store::print1Customer()
{
	system("cls");
	int id;
	int pos = -1;

	cout << "**************************************************************************************************************" << endl;
	cout << "**                                 MANAGE CUSTOMER INFORMATION                                              **" << endl;
	cout << "**************************************************************************************************************" << endl;
	cout << endl
		 << "  Enter customer id: ";
	cin >> id;
	cout << endl;
	for (int i = 0; i < numOfCustomers; ++i)
	{
		if (customer[i].customerId == id)
		{
			pos = i;
			break;
		}
	}

	if (pos != -1)
	{
		cout << "    - Customer Id: " << id << endl
			 << endl;
		cout << "    - Customer Name: " << customer[pos].customerName << endl
			 << endl;
		cout << "    - Customer phone's number: " << customer[pos].customerPhone << endl
			 << endl;
		cout << "    - Phone model bought:" << endl
			 << endl;
		cout << "          + Phone name: " << customer[pos].boughtPhone.phoneName << endl
			 << endl;
		cout << "          + Brand: " << customer[pos].boughtPhone.brand << endl
			 << endl;
		;
		cout << "          + RAM: " << customer[pos].boughtPhone.RAM << endl
			 << endl;
		cout << "          + ROM: " << customer[pos].boughtPhone.ROM << endl
			 << endl;
		cout << "          + Price: " << customer[pos].boughtPhone.price << " VND" << endl
			 << endl;
		cout << "          + Insurance year: " << customer[pos].insuranceYear << endl
			 << endl;
	}
	else
		cout << "    No customer FOUND." << endl;
	cout << endl
		 << "    " << system("pause");
}

void lowerCase(string &str)
{
	for (int i = 0; i < str.size(); ++i)
		str[i] = tolower(str[i]);
}

int Store::search(string name)
{
	string temp1, temp2;
	temp1 = name;
	lowerCase(temp1);
	for (int i = 0; i < numOfPhoneModels; ++i)
	{
		temp2 = phone[i].phoneName;
		lowerCase(temp2);
		if (temp1.compare(temp2) == 0)
			return i;
	}
	return -1;
}
void Store::printPhone()
{
	int pos;
	string model;

	do
	{
		system("cls");
		cout << "**************************************************************************************************" << endl;
		cout << "**                                 MANAGE PHONE INFORMATION                                     **" << endl;
		cout << "**************************************************************************************************" << endl;
		cout << endl
			 << "    Please enter phone model you want to check: ";
		cin >> model;
		cout << endl;
		if ((pos = search(model)) != -1)
		{
			cout << "      - Phone name: " << phone[pos].phoneName << endl
				 << endl;
			cout << "      - Brand: " << phone[pos].brand << endl
				 << endl;
			cout << "      - RAM: " << phone[pos].RAM << endl
				 << endl;
			cout << "      - ROM: " << phone[pos].ROM << endl
				 << endl;
			cout << "      - Quantity: " << phone[pos].quantity << endl
				 << endl;
			cout << "      - Price: " << phone[pos].price << " VND" << endl
				 << endl;
		}
		else
			cout << "    Phone not FOUND!!!" << endl
				 << "    Please enter again." << endl;
	} while (pos == -1);
	cout << endl
		 << "    " << system("pause");
}

void Store::updatePrice()
{
	system("cls");
	int pos;
	string model;
	do
	{
		cout << "**************************************************************************************************************" << endl;
		cout << "**                                     MANAGE PHONE INFORMATION                                             **" << endl;
		cout << "**************************************************************************************************************" << endl;
		cout << endl
			 << "  Please enter phone model you want to update price: ";
		cin >> model;
		if ((pos = search(model)) != -1)
		{
			cout << endl
				 << "    Model: " << phone[pos].phoneName << endl;
			cout << endl
				 << "    Enter new price: ";
			cin >> phone[pos].price;
		}
		else
			cout << "    Phone not Found!!!" << endl
				 << "Please enter again." << endl;
	} while (pos == -1);
	cout << endl
		 << "    PRICE UPDATE SUCCESS!" << endl;
	cout << endl
		 << "    " << system("pause");
}

void Store::managePhoneInfo()
{
	int choice = 0;
	cout << endl;
	do
	{
		system("cls");
		cout << "**************************************************************************************************************" << endl;
		cout << "**                                     MANAGE PHONE INFORMATION                                             **" << endl;
		cout << "**************************************************************************************************************" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**  1. Display list phone.                                                                                  **" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**  2. Search phone information.                                                                            **" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**  3. Update Price.                                                                                        **" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**  4. Back.                                                                                                **" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**************************************************************************************************************" << endl;
		cout << endl
			 << "    Enter your option: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			printFull();
			break;
		case 2:
			printPhone();
			break;
		case 3:
			updatePrice();
			break;
		case 4:
			break;
		default:
			cout << "    Invalid option!!!" << endl
				 << "    Please enter again." << endl;
			break;
		}
	} while (choice != 4);
}

void Store::manageImport()
{
	system("cls");
	string brand;
	string model;
	string temp1, temp2;
	int num;
	int pos = 0;

	cout << "**************************************************************************************************************" << endl;
	cout << "**                                     MANAGE PHONE INFORMATION                                             **" << endl;
	cout << "**************************************************************************************************************" << endl;
	cout << endl
		 << "    Enter brand of imported phone: ";
	cin >> brand;
	cout << endl
		 << "    Enter phone model: ";
	cin >> model;
	cout << endl
		 << "    Enter number of imported phone: ";
	cin >> num;

	temp1 = brand;
	lowerCase(temp1);
	if ((pos = search(model)) != -1)
	{
		temp2 = phone[pos].brand;
		lowerCase(temp2);
		if (temp1.compare(temp2) == 0)
			phone[pos].quantity += num;
	}
	else
	{
		cout << endl
			 << "    This model is not existed in your store!" << endl;
		cout << "    Please enter its information:" << endl;
		pos = numOfPhoneModels;
		phone[pos].brand = brand;
		phone[pos].phoneName = model;
		phone[pos].quantity = num;
		cout << "    Brand: " << phone[pos].brand << endl
			 << endl;
		cout << "    Phone name: " << phone[pos].phoneName << endl
			 << endl;
		cout << "    Quantity: " << phone[pos].quantity << endl
			 << endl;
		cout << "    Phone Id: " << flush;
		cin >> phone[pos].phoneId;
		cout << endl
			 << "    RAM: " << flush;
		cin >> phone[pos].RAM;
		cout << endl
			 << "    ROM: " << flush;
		cin >> phone[pos].ROM;
		cout << endl
			 << "    Price: " << flush;
		cin >> phone[pos].price;
		cout << endl
			 << "    Product year: " << flush;
		cin >> phone[pos].productYear;
		phone[pos].availability = (phone[pos].quantity == 0) ? "No" : "Yes";
		numOfPhoneModels++;
	}
	cout << endl
		 << "    IMPORT SUCCESS." << endl
		 << endl;
	cout << endl
		 << "    " << system("pause");
}
void Store::manageSale()
{
	system("cls");
	string model;
	string temp = "Yes";
	int pos;

	cout << "**************************************************************************************************************" << endl;
	cout << "**                                     MANAGE SALE INFORMATION                                              **" << endl;
	cout << "**************************************************************************************************************" << endl;
	cout << endl
		 << "    Enter customer's phone model: ";
	cin >> model;
	cin.ignore();
	cout << endl;
	if ((pos = search(model)) != -1 && temp.compare(phone[pos].availability) == 0)
	{
		cout << "    There is stock available of this model." << endl
			 << endl;
		customer[numOfCustomers].customerId = 123456 + numOfCustomers;
		cout << "    Enter customer name: ";
		getline(cin, customer[numOfCustomers].customerName);
		cout << endl
			 << "    Enter customer's phone number: " << flush;
		cin >> customer[numOfCustomers].customerPhone;
		cout << endl
			 << "    Enter year of insurance: " << flush;
		cin >> customer[numOfCustomers].insuranceYear;
		phone[pos].quantity -= 1;
		phone[pos].availability = (phone[pos].quantity == 0) ? "No" : "Yes";
		customer[numOfCustomers].boughtPhone = phone[pos];
		cout << endl
			 << "    SALE SUCCESS." << endl;
		numOfCustomers++;
	}
	else
	{
		cout << "This model is currently unavailable!!!" << endl;
	}
	cout << endl
		 << "    " << system("pause");
}

void Store::manageCustomInfo()
{
	int choice;
	do
	{
		system("cls");
		cout << "**************************************************************************************************************" << endl;
		cout << "**                                 MANAGE CUSTOMER INFORMATION                                              **" << endl;
		cout << "**************************************************************************************************************" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**  1. Display full customer list.                                                                          **" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**  2. Check customer information.                                                                          **" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**  3. Back.                                                                                                **" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**************************************************************************************************************" << endl;
		cout << endl
			 << "    Enter your option: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			printFullCustomer();
			break;
		case 2:
			print1Customer();
			break;
		case 3:
			break;
		default:
			cout << "Invalid option!!!" << endl
				 << "Please enter again." << endl;
			break;
		}
	} while (choice != 3);
}

int main()
{
	Store store("inFile.dat");
	int choice = 0;

	do
	{
		system("cls");
		cout << "**************************************************************************************************************" << endl;
		cout << "**                              WELCOM TO PHONE STORE MANAGEMENT SYSTEM                                     **" << endl;
		cout << "**************************************************************************************************************" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**  1. Manage phone information.                                                                            **" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**  2. Manage customer information.                                                                         **" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**  3. Manage sale information.                                                                             **" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**  4. Manage import information.                                                                           **" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**  5. Exit.                                                                                                **" << endl;
		cout << "**                                                                                                          **" << endl;
		cout << "**************************************************************************************************************" << endl;
		cout << endl
			 << "    Enter your option: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			store.managePhoneInfo();
			break;
		case 2:
			store.manageCustomInfo();
			break;
		case 3:
			store.manageSale();
			break;
		case 4:
			store.manageImport();
			break;
		case 5:
			cout << "Goodbye!!!" << endl
				 << "Have a nice day." << endl;
			break;
		default:
			break;
		}
	} while (choice != 5);

	return 0;
}