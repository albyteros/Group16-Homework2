#include <iostream>

using namespace std;

//pass in space-delimited arguments when you call the executable
//Example: ./a.out 1 2 3.3
int main( int argc, char * argv[] )
{
	if (argc > 4) 
	{
		cout << "Too many arguments. Cannot pass in more than three." << endl;
		return -1;
	}

	int i = 1;
	double loan_amount, yearly_interest_rate, monthly_payment;

	double arguments [3];

	if (argc > 1)
	{
		while ( i < argc )
		{

			try
			{
				arguments[i-1] = stod(argv[i]);
			}
			catch(const std::invalid_argument&)
			{
				if(i==1)
					cout << "(Invalid loan amount): " << argv[i] << endl;
				else if (i==2)
					cout << "(Invalid interest rate): " << argv[i-1] << " " << argv[i] << endl;
				else
					cout << "(Invalid payment): " << argv[i-2] << " " << argv[i-1] << " " << argv[i] << endl;
				return -2;
			}
			i++;
		}
	}

	loan_amount = arguments[0];
	yearly_interest_rate = arguments[1];
	monthly_payment = arguments[2];
	cout << "Loan Amount -> " << loan_amount << endl;
	cout << "Yearly Interest Rate % -> " << yearly_interest_rate << endl;
	cout << "Monthly Payment -> " << monthly_payment << endl;

	int month = 1;
	double monthly_interest_rate = (yearly_interest_rate / 12);


	//checking if payment <= interest so program does not run infinitely
    if (monthly_payment <= loan_amount * (yearly_interest_rate / 1200)){
    std::cout << "You will never pay off your debt." << std::endl;
    return 0;
    }

    double balance = loan_amount;
    double interest;
    double total_interest = 0;

	// main loop of printing
	while (balance > 0){
	interest = balance * (monthly_interest_rate / 100);
    balance += interest;
    balance -= monthly_payment;
    total_interest += interest;
    
	// print block- we may need a better alignment than 5 whitespaces
    std::cout << month << "     ";
    std::cout << balance << "     ";
    std::cout << monthly_payment << "     ";
    std::cout << monthly_interest_rate << "     ";
    std::cout << interest << "     ";
    std::cout << (monthly_payment - interest) << std::endl;
    month++;
	}

    std::cout << "It takes " << month << " months to pay off the loan" << std::endl;
    std::cout << "total interest paid is: " << total_interest;

	return 0;
}
