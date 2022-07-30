//Include statements
#include <iostream>
#include <string>
#include <iomanip>

#include <fstream>

using namespace std;

//Global declarations
struct MenuItemType {
	string menuItem;
	double price;
	bool ordered{ false };
};

//Function prototypes
void wait();

void getData(MenuItemType mList[], int listSize);
void showMenu(MenuItemType mList[], int listSize, char& choice);
void printCheck(MenuItemType mList[], int listSize);

int main()
{
	MenuItemType mList[8];
	int listSize = 8;
	char choice;

	//Program logic	
	getData(mList, listSize);

	cout << "Welcome to Zaden's Resturant" << endl;
	cout << "---- Today's Menu ----" << endl;

	do {
		showMenu(mList, listSize, choice);
	} while (choice != 'N');
	printCheck(mList, listSize);

	return 0;
}

void getData(MenuItemType mList[], int listSize) {
	ifstream inFile;
	inFile.open("menu.txt");

	if (inFile.fail()) {
		cout << "Could not open file..." << endl;
		exit(1);
	}
	else {
		for (int i = 0; i < listSize; i++) {
			getline(inFile, mList[i].menuItem);
			inFile >> mList[i].price;
			inFile.ignore(1, '\n');
		}
	}
	inFile.close();
}

void showMenu(MenuItemType mList[], int listSize, char& selectionChoice) {
	int itemNumber, itemCounter{ 1 };

	for (int i = 0; i < listSize; i++) {
		cout << left << itemCounter << ": " << setw(15) << mList[i].menuItem << setw(5) << right << "$" << fixed << setprecision(2) << mList[i].price << endl;
		itemCounter++;
	}
	cout << endl;
	cout << "You can make up to 8 single order selections" << endl;
	cout << "Do you want to make a selection? (Y/y) or (N/n): ";
	cin >> selectionChoice;
	selectionChoice = toupper(selectionChoice);

	while (selectionChoice != 'N') {
		cout << endl;
		cout << "Enter item number: ";
		cin >> itemNumber;

		if (itemNumber > 0 && itemNumber <= listSize) {
			mList[itemNumber - 1].ordered = true;
		}
		else {
			cout << "Invalid item number" << endl;
		}

		cout << endl;
		cout << "Select another item (Y/y) or (N/n): ";
		cin >> selectionChoice;
		selectionChoice = toupper(selectionChoice);
	}
}

void printCheck(MenuItemType mList[], int listSize) {
	double subTotal{ 0 }, tax{ 0 }, total{ 0 };

	cout << endl;
	cout << "Welcome to Zaden's Resturant" << endl;

	for (int i = 0; i < listSize; i++) {
		if (mList[i].ordered) {
			cout << setw(15) << left << mList[i].menuItem << setw(5) << right << "$" << fixed << setprecision(2) << mList[i].price << endl;
			subTotal += mList[i].price;
		}
	}

	tax = (subTotal * 5) / 100;
	total = subTotal + tax;

	cout << setw(15) << left << "Subtotal: " << setw(5) << right << "$" << fixed << setprecision(2) << subTotal << endl;
	cout << setw(15) << left << "Tax: " << setw(5) << right << "$" << fixed << setprecision(2) << tax << endl;
	cout << setw(15) << left << "Total: " << setw(5) << right << "$" << fixed << setprecision(2) << total << endl;
	cout << endl;
}