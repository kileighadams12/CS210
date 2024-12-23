#include <iostream>  // For cin, cout
#include <iomanip>  // For setprecision and setw
#include <string>  // For string class
#include <limits>  // For numeric_limits
#include <cmath>  // For pow function
#include <vector>  // For vector container

using namespace std; // Using the standard namespace
const int MONTHS_IN_YEAR = 12;  // Number of months in a year

// Function to print details for each year
void printDetails(int year, double yearEndBalance, double interestEarned) {
    // Set widths to align columns properly
    cout << left << setw(12) << year;  // Year column: 10-width, left-aligned
    cout << left << "$" << setw(19) << fixed << setprecision(2) << yearEndBalance; // Balance: right-aligned with formatting
    cout << left << "$" << setw(18) << fixed << setprecision(2) << interestEarned << endl;  // Interest: right-aligned with formatting
	cout << endl;  // Move to the next line
}

// Function to print the section title (left-aligned)
void printSectionTitle(const string& title) {
    // Print the title
    cout << title << endl;
}
// Function to print the separators 
void printSeparator(const string& title) {
    // Print `=` separator based on the title length
    for (int i = 0; i < title.length(); ++i) { 
        cout << "=";
    }
	cout << endl;  // Move to the next line
}

// Function to print the headers
void printHeader() {
    cout << left << setw(8) << "YEAR";  // Year column
    cout << left << setw(20) << "YEAR END BALANCE";  // Balance column
    cout << left << setw(25) << "YEAR END EARNED INTEREST" << endl;  // Interest column

    // Print `-` separator based on the header width
    for (int i = 0; i < 8; ++i) cout << "-";  
    for (int i = 0; i < 20; ++i) cout << "-";  
    for (int i = 0; i < 25; ++i) cout << "-";  
    cout << endl;  
}

// Function to calculate balance without monthly deposit
double calculateBalanceWithoutMonthlyDeposit(double initialInvestment, double interestRate, int numberOfYears) {
    double balance = initialInvestment;
    double monthlyInterestRate = interestRate / 100.0 / MONTHS_IN_YEAR;

    // Print the section title
    printSectionTitle("Balance and Interest Without Additional Monthly Deposits");

    // Print the separators (based on title length)
    printSeparator("Balance and Interest Without Additional Monthly Deposits");

    // Print the table header
    printHeader();

	// Calculate the balance for each year
    for (int year = 1; year <= numberOfYears; ++year) {
        double startBalance = balance;

        // Apply monthly compounded interest
        for (int month = 1; month <= MONTHS_IN_YEAR; ++month) {
            balance += balance * monthlyInterestRate;  // Apply interest each month
        }

    // Print the details for the current year
    printDetails(year, balance, balance - startBalance);

    }
    return balance;
}

// Function to calculate balance with monthly deposit
double balanceWithMonthlyDeposit(double initialInvestment, double monthlyDeposit, double interestRate, int numberOfYears) {
	double balance = initialInvestment; // Initialize the balance
	double monthlyInterestRate = interestRate / 100.0 / MONTHS_IN_YEAR; // Calculate the monthly interest rate
	double yearlyInterest = 0.0; // Initialize the interest earned for the year
	double interest = 0.0; // Initialize the interest

    // Print the section title
    printSectionTitle("Balance and Interest With Additional Monthly Deposits");

    // Print the separators (based on title length)
    printSeparator("Balance and Interest With Additional Monthly Deposits");

    // Print the table header
    printHeader();

	// Calculate the balance and interest earned for each year
	for (int year = 1; year <= numberOfYears; ++year) { // Calculate the balance for each year
		yearlyInterest = 0.0;  // Reset the interest earned for the year

        // Apply monthly deposit and interest
        for (int month = 1; month <= MONTHS_IN_YEAR; ++month) {
            balance += monthlyDeposit;
            interest = balance * monthlyInterestRate;  // Calculate the interest for the month
			yearlyInterest += interest;  // Add the interest to the total interest earned

			balance += interest;  // Add the interest to the balance

        }

        // Print the details for the current year
        printDetails(year, balance, yearlyInterest);
    }

	return balance;  // Return the final balance
}

// Function to calculate the number of years to reach a savings goal
int calculateYearsToGoal(double initialInvestment, double monthlyDeposit, double interestRate, double savingsGoal) {
    double balance = initialInvestment;
    double monthlyInterestRate = interestRate / 100.0 / MONTHS_IN_YEAR;
    int years = 0;

	// Print the section title
    cout << "\nSavings Goal\n"
         << "===========================================\n"
         << left << setw(8) << "YEAR"
         << left << setw(20) << "YEAR END BALANCE"
	     << endl;
;
    // Calculate the number of years to reach the savings goal
    while (balance < savingsGoal) {
		double startBalance = balance;
  

		for (int month = 1; month <= MONTHS_IN_YEAR; ++month) { // Apply monthly deposit and interest
            balance += monthlyDeposit;
            balance += balance * monthlyInterestRate;
        }
		++years; // Increment the number of years
        
		// Print the details for the current year
        cout << left << setw(8) << years
             << left << "$" << setw(19) << fixed << setprecision(2) << balance
             << endl;
           
            
    }
	return years; // Return the number of years to reach the savings goal
}

// Function to get positive input for a double value
double getPositiveDouble(string prompt) { 
	double value;    // Variable to store the input
	while (true) {  // Loop until valid input is received
		cout << prompt;  // Print the received prompt

		cin >> value;   // Get the input

        // Check for valid input and positive value
		if (cin.fail() || value < 0) { // Check for invalid input
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the invalid input

			cout << "Invalid input. Please enter a positive number." << endl;  // Print error message
        } 

		
        else {
            return value; // Return the validated zero or positive number
        }
    }
}

// Function to get positive input for an integer value
int getPositiveInt(string prompt) { 
	int value;  // Variable to store the input
    while (true) {
        cout << prompt; 
        cin >> value;

        // Check for valid input and positive value
        if (cin.fail() || value <= 0) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the invalid input

            cout << "Invalid input. Please enter a positive integer." << endl;
        }
        else {
			return value; // Return the valid positive integer
        }
    }
}

// Function to validate the the user's input when yes or no questions are asked
string yesOrNoValidation(string choice) {
	while (choice != "y" && choice != "Y" && choice != "n" && choice != "N") {  // Check if the input is not y/Y or n/N
		cout << "Invalid input. Please enter 'y' or 'n': ";  // Print error message if input is invalid
		cin >> choice;  // Retrieve the input again
	}
	return choice;  // Return the validated input
}

// Main function to run the investment calculator
int main() {
	double initialInvestment, monthlyDeposit, interestRate, savingsGoal; // Variables for user input
	int numberOfYears;     // Number of years for the investment
    string continueChoice, goalChoice;   // User's choice to continue

    do {
        cout << "****************************************************\n";
        cout << "******************* Data Input *********************\n";
        cout << endl;

        // Get valid positive input for each variable
        initialInvestment = getPositiveDouble("Initial Investment Amount: $");
        monthlyDeposit = getPositiveDouble("Monthly Deposit: $");
        interestRate = getPositiveDouble("Annual Interest: %");
        numberOfYears = getPositiveInt("Number of Years: ");

        cout << "\nPress enter to continue. . ." << endl;
        cin.ignore(); // To clear the newline character
        cin.get();  // Wait for user to press Enter

        // Calculate and print balance without monthly deposit
        calculateBalanceWithoutMonthlyDeposit(initialInvestment, interestRate, numberOfYears);

		cout << endl; // Move to the next line

        // Calculate and print balance with monthly deposit
        balanceWithMonthlyDeposit(initialInvestment, monthlyDeposit, interestRate, numberOfYears);
         
        cout << "\nWould you like to set a savings goal? (y/n): "; 
		cin >> goalChoice; // Get user choice to set a savings goal
		goalChoice = yesOrNoValidation(goalChoice); // Validate the user's choice to ensure it is 'y' or 'n'

		if (goalChoice == "y" || goalChoice == "Y") { // Check if user wants to set a savings goal
			savingsGoal = getPositiveDouble("Enter your savings goal amount: $ "); // Get the savings goal amount
			int yearsToGoal = calculateYearsToGoal(initialInvestment, monthlyDeposit, interestRate, savingsGoal); // Calculate the number of years to reach the goal
            cout << "\nIt will take approximately " << yearsToGoal << " years to reach your savings goal of $" << fixed
				<< setprecision(2) << savingsGoal << "." << endl; // Print the number of years to reach the goal
        }

        cout << "\nWould you like to test with different values? (y/n): ";
		cin >> continueChoice; // Get user's choice to continue
		continueChoice = yesOrNoValidation(continueChoice); // Validate the user's choice to ensure it is 'y' or 'n'

    // Continue if user wants to test with different values
    } while (continueChoice == "y" || continueChoice == "Y");

	// Exit message
    cout << "Thank you for banking with Airgead!" << endl;
    return 0;
}

