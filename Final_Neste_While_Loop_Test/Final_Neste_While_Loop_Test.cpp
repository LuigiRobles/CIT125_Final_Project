// CIT125 Intro to C++ Luigi Robles
// 08-20-20 Summer Term
// End of Term Programming Project
// @VinylDesignsLA Order Form Program
// Takes users order for Mugs or Decals
// Writes a Receipt to a sequential access file

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//function prototypes
void displayMenu();
int getTotal(int a, int b);
void mugMenu();

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
	string itemAdded = " ";
	ofstream outFile;
	bool mugsOrderedYes = false;
	bool decalsOrderedYes = false;

	//Welcome message and display menu
	cout << "Welcome to the @VinylDesignsLA order program." << endl;
	cout << "Please select from the following menu: " << endl;
	displayMenu();
	cout << endl;

	cin >> selection; // input for menu selection

	while (toupper(selection) != 'Q') { //while loop for menu selection

		if (toupper(selection) == 'M') //if Menu selection is M for Mugs
		{	
			//Mug Selection Menu
			mugMenu();

			cin >> orderQuantity; //input for quantity of mugs ordered

			//checking for quantity discount
			if (orderQuantity > 0 && orderQuantity <= 9) 
			{
				mugPrice = 20;
				total = getTotal(mugPrice, orderQuantity);
				cout << "Current Total for this item: " << total << endl;
			}
			else if (orderQuantity >= 10 && orderQuantity < 20)
			{
				mugPrice = 15;
				total = getTotal(mugPrice, orderQuantity);
				cout << "Current Total for this item: " << total << endl;
			}
			else if (orderQuantity >= 20)
			{
				mugPrice = 10;
				total = getTotal(mugPrice, orderQuantity);
				cout << "Current Total for this item: " << total << endl;
			} //end if

			//nested loop to force a positive quantity ordered
			while (orderQuantity < 0) {

				cout << "Please enter a positive order quantity" << endl;
				cin >> orderQuantity;
				cout << endl;

			} //end while loop

			//check to see if customer would like to add another item
			cout << "Would you like to order something else? (Y/N)";
			cin >> addMore;
			cout << endl;

			//If customer wants to add more, display selection menu again
			//and add current quantity ordered to addMoreQuantity variable
			if (toupper(addMore) == 'Y') 
			{
				displayMenu();
				cin >> selection;
				cout << endl;
				if (selection == 'M' and orderQuantity > 0)
				{
					addMoreQuantity = orderQuantity + addMoreQuantity;
					itemAdded = "Mugs";
				}
				else if (selection == 'D')
					itemAdded = "Decals";

				//check if addMoreQuantity is discount eligible 
				if (addMoreQuantity > 0 && addMoreQuantity <= 9)
				{
					mugPrice = 20;
					subTotal = getTotal(mugPrice, addMoreQuantity); //calculate subtotal @ regular price
					cout << "Current Total for this item: " << subTotal << endl;
				}
				else if (addMoreQuantity >= 10 && addMoreQuantity < 20)
				{
					mugPrice = 15;
					subTotal = getTotal(mugPrice, addMoreQuantity); //calculate subtotal with level 1 discount
					cout << "Current Total for this item: " << subTotal << endl;
				}
				else if (addMoreQuantity >= 20)
				{
					mugPrice = 10;
					subTotal = getTotal(mugPrice, addMoreQuantity); //calculate subtotal with level 2 discount
					cout << "Current Total for this item: " << subTotal << endl;
				}//end if

			}
			//break out of loop is customer does not want to add more
			else if (toupper(addMore) == 'N')
				break;
		}
		else if (toupper(selection) == 'D')
		{	
			//if customer wants to order Vinyl Decals
			//display Decal Size options and save their selection
			// to vinylSize variable
			cout << "Vinyl Decals are sold in packs of 10" << endl;
			cout << "Please select a Vinyl Decal Size from the following menu: " << endl;
			cout << " Enter 4 for (4 x 4), 5 for (5 x 5) or 6 for (6 x 6 )" << endl;
			cin >> vinylSize;
			cout << endl;

			//switch for decal size selection and to assign correct
			//pricing based on size of decal
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

		}
		else
		{
			//if customer does not select M , D or Q 
			cout << "Invalid selection." << endl;
			cout << "Please enter M for Mugs, D for Vinyl Decals, or Q for Quit" << endl;
			cin >> selection;

		} //end if for Menu Selection

	} //end while
	
	//checking to see if Vinyl Decals were ordered
	//and display Vinyl Decals Price
	if (vinylPrice >= 0)
		cout << "Your total for Vinyl Decals is: $ " << vinylPrice << endl;

	//checking to see if customer added more items to order
	//and adding together both totals for initial order and add more total
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
	
	//if customer answer yes to finalize order
	//a reciept will be saved to reciept.txt 
	//with item ordered# quantity # and price
	cout << "Would you like to finalize your order? (Y/N)" << endl;
	cin >> finalizeOrder;
	if (toupper(finalizeOrder) == 'Y')
	{
		//checking to see what should be saved to reciept
		if (orderQuantity > 0)
		{
			mugsOrderedYes = true;
			itemOrdered = "Mugs";
		}
		if (addMoreQuantity > 0)
		{
			itemOrdered = "Mugs";
			mugsOrderedYes = true;
		}
		if (vinylPrice > 0)
		{
			itemOrdered = "Decals";
			decalsOrderedYes = true;
		}
			

		//checking to see if mugs were added after placing initial order
		//and adding both quantity together before saving to reciept
		if (itemOrdered == "Mugs")
			total = orderQuantity + addMoreQuantity;

		outFile.open("receipt.txt", ios::out); //open reciept.txt for output

		if (outFile.is_open()) //checking to see if file was opened successfully
		{
			if (mugsOrderedYes == true && decalsOrderedYes == false) //checking to see if only mugs should be saved to receipt
			{
				outFile << "Item Ordered"<< '#'<< "Quantity" <<'#'<<"Price"<< endl;
				outFile << "Mugs" << '#' << total << '#' << grandTotal << endl;
			}
			else if (decalsOrderedYes == true && mugsOrderedYes == false) //checking to see if only Vinyl Decals should be saved to receipt
			{
				outFile << "Item Ordered"<< '#' << "Size" << '#'<< "Price" << endl;
				outFile << "Decals" << '#' << vinylSize << '#' << vinylPrice << endl;
			}
			
			if ((decalsOrderedYes == true) && (mugsOrderedYes == true)) //checking to see if both Mugs and Decals should be saved to receipt
			{
				outFile << "Item Ordered" << '#' << "Size" << '#' << "Price" << endl;
				outFile << "Decals" << '#' << vinylSize << '#' << vinylPrice << endl;
				outFile << "Item Ordered" << '#' << "Quantity" << '#' << "Price" << endl;
				outFile << "Mugs" << '#' << orderQuantity + addMoreQuantity << '#' << total << endl;
			}


		} //end if for checking if file was opened correctly
		else
			cout << "reciept.txt file could not be opened" << endl;

		outFile.close(); //close file after writting to it.

	} //end if for checking if customer wants to finalize receipt
	else
	{
		cout << "Order was not finalized and no receipt was saved" << endl;
		cout << "Please restart program if you would like to place an order." << endl;

	}
		
	return 0;
} // end of main function

//***Function Definitions***
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

void mugMenu() 
{
	cout << "How many mugs would you like to order?" << endl;
	cout << "Orders with 10 or more of the same mug qualify for discounted pricing" << endl;
	cout << "1 - 9 Mugs are $20 each" << endl;
	cout << "10 - 19 Mugs are $15 each" << endl;
	cout << "20 or more are $10 each" << endl;
	cout << endl;
} //end of mugMenu function

