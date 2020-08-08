// Final_Neste_While_Loop_Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//function prototypes
void displayMenu();
int getTotal(int a, int b);

int main()
{
	//Declare and initialize variables
	char selection = ' ';
	char addMore = ' ';
	char finalizeOrder = ' ';
	int vinylSize = 0;
	int vinylPrice = 0;
	int orderQuantity = 0;
	int addMoreQuantity = 0;
	int mugPrice = 0;
	int subTotal = 0;
	int total = 0;
	int grandTotal = 0;
	string itemOrdered = " ";
	ofstream outFile;

	cout << "Welcome to the @VinylDesignsLA order program." << endl;
	cout << "Please select from the following menu: " << endl;

	displayMenu();
	cout << endl;
	cin >> selection;

	while (toupper(selection) != 'Q') {

		if (toupper(selection) == 'M')
		{
			cout << "How many mugs would you like to order?" << endl;
			cout << "Orders with 10 or more of the same mug qualify for discounted pricing" << endl;
			cout << "1 - 9 Mugs are $20 each" << endl;
			cout << "10 - 19 Mugs are $15 each" << endl;
			cout << "20 or more are $10 each" << endl;
			cout << endl;

			cin >> orderQuantity;

			if (orderQuantity > 0 && orderQuantity <= 9)
			{
				mugPrice = 20;
				total = getTotal(mugPrice, orderQuantity);
				cout << "Current Total: " << total << endl;
			}
			else if (orderQuantity >= 10 && orderQuantity < 20)
			{
				mugPrice = 15;
				total = getTotal(mugPrice, orderQuantity);
				cout << "Current Total: " << total << endl;
			}
			else if (orderQuantity >= 20)
			{
				mugPrice = 10;
				total = getTotal(mugPrice, orderQuantity);
				cout << "Current Total: " << total << endl;
			}

			while (orderQuantity < 0) {

				//inside loop
				cout << "Please enter a positive order quantity" << endl;
				cin >> orderQuantity;
				cout << endl;
			}

			// outer loop
			cout << "Would you like to order something else? (Y/N)";
			cin >> addMore;
			cout << endl;

			if (toupper(addMore) == 'Y')
			{
				displayMenu();
				cin >> selection;
				cout << endl;
				addMoreQuantity = orderQuantity + addMoreQuantity;

				if (addMoreQuantity > 0 && addMoreQuantity <= 9)
				{
					mugPrice = 20;
					subTotal = getTotal(mugPrice, addMoreQuantity);
					cout << "Current Total: " << subTotal << endl;
				}
				else if (addMoreQuantity >= 10 && addMoreQuantity < 20)
				{
					mugPrice = 15;
					subTotal = getTotal(mugPrice, addMoreQuantity);
					cout << "Current Total: " << subTotal << endl;
				}
				else if (addMoreQuantity >= 20)
				{
					mugPrice = 10;
					subTotal = getTotal(mugPrice, addMoreQuantity);
					cout << "Current Total: " << subTotal << endl;
				}

			}
			else if (toupper(addMore) == 'N')
				break;
		}
		else if (toupper(selection) == 'D')
		{
			cout << "Vinyl Decals are sold in packs of 10" << endl;
			cout << "Please select a Vinyl Decal Size from the following menu: " << endl;
			cout << " Enter 4 for (4 x 4), 5 for (5 x 5) or 6 for (6 x 6 )" << endl;
			cin >> vinylSize;
			cout << endl;

			switch (vinylSize)
			{
			case 4:
				vinylPrice = 39;
				break;
			case 5:
				vinylPrice = 45;
				break;
			case 6:
				vinylPrice = 52;
				break;
			default:
				cout << "Invalid size selected." << endl;
				break;
			} // end switch

			if (vinylPrice > 0)
				break;

		} //end if
		else
		{
			cout << "Invalid selection." << endl;
			cout << "Please enter M for Mugs, D for Vinyl Decals, or Q for Quit" << endl;
			cin >> selection;
		}


	} //end while
	
	if (vinylPrice >= 0)
		cout << "Your total for Vinyl Decals is: $ " << vinylPrice << endl;
	
	if (addMoreQuantity > 0)
	{
		grandTotal = subTotal + total + vinylPrice;
		cout << "Your grand total is $ " << grandTotal << endl;
	}
	else
	{
		grandTotal = total + vinylPrice;
		cout << "Your grand total is $ " << grandTotal << endl;
	}
	
	cout << "Would you like to finalize your order? (Y/N)" << endl;
	cin >> finalizeOrder;
	if (toupper(finalizeOrder) == 'Y')
	{
		if (orderQuantity > 0)
			itemOrdered = "Mugs";
		if (addMoreQuantity > 0)
			itemOrdered = "Mugs";
		else if (vinylPrice > 0)
			itemOrdered = "Decals";

		if (itemOrdered == "Mugs")
			total = orderQuantity + addMoreQuantity;
		
		outFile.open("receipt.txt", ios::out);
		
		if (outFile.is_open())
		{
			if (itemOrdered == "Mugs")
			{
				outFile << "Item Ordered: " << endl;
				outFile << itemOrdered << '#' << total << '#' << grandTotal << endl;
			}
			else if (itemOrdered == "Decals")
			{
				outFile << "Item Ordered: " << endl;
				outFile << itemOrdered << '#' << vinylSize << '#' << vinylPrice << endl;
			}
		}
		outFile.close();
	}

	return 0;
} // end of main function

//***Function Definitions
void displayMenu()
{
	cout << "Enter M to order Custom Mugs" << endl;
	cout << "Enter D to order Vinyl Decals" << endl;
	cout << "Or Enter Q to Quit" << endl;
} //end of displayMenu function

int getTotal(int a, int b)
{
	int total = 0;
	total = (a * b);
	return total;
} //end of getTotal function


//note to self need to add comments and move around display of current totals
//double check outputfile contents are correct when order has both mugs and decals
