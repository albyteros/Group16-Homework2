#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

using namespace std;

// pass in space-delimited arguments when you call the executable
// Example: ./a.out 1 2 3.3

int main(int argc, char *argv[])
{
    if (argc > 4)
    {
        cout << "Too many arguments. Cannot pass in more than three." << endl;
        return -1;
    }

    if (argc < 4)
    {
        cout << "Please provide loan amount, interest rate, and monthly payment." << endl;
        return -1;
    }

    int i = 1;

    double loan_amount, yearly_interest_rate, monthly_payment;
    double arguments[3] = {0, 0, 0};

    if (argc > 1)
    {
        while (i < argc)
        {
            try
            {
                arguments[i - 1] = stod(argv[i]);
            }
            catch(const invalid_argument&)
            {
                if(i == 1)
                    cout << "(Invalid loan amount): " << argv[i] << endl;
                else if(i == 2)
                    cout << "(Invalid interest rate): "
                         << argv[i-1] << " " << argv[i] << endl;
                else
                    cout << "(Invalid payment): "
                         << argv[i-2] << " " << argv[i-1] << " "
                         << argv[i] << endl;

                return -2;
            }
            catch(const out_of_range&)
            {
                if(i == 1)
                    cout << "(Invalid loan amount): " << argv[i] << endl;
                else if(i == 2)
                    cout << "(Invalid interest rate): "
                         << argv[i-1] << " " << argv[i] << endl;
                else
                    cout << "(Invalid payment): "
                         << argv[i-2] << " " << argv[i-1] << " "
                         << argv[i] << endl;

                return -2;
            }

            i++;
        }
    }

    loan_amount = arguments[0];
    yearly_interest_rate = arguments[1];
    monthly_payment = arguments[2];

    // Check for invalid loan amount
    if (loan_amount <= 0)
    {
        cout << "(Invalid loan amount): " << argv[1] << endl;
        return -2;
    }

    // Check for invalid interest rate
    if (yearly_interest_rate < 0)
    {
        cout << "(Invalid interest rate): "
             << argv[1] << " " << argv[2] << endl;
        return -2;
    }

    // Check for invalid monthly payment
    if (monthly_payment <= 0)
    {
        cout << "(Invalid payment): "
             << argv[1] << " " << argv[2] << " "
             << argv[3] << endl;
        return -2;
    }

    // Convert yearly interest rate to monthly rate
    double monthly_interest_rate = yearly_interest_rate / 12.0;

    // Convert percentage to decimal
    double interest_rate_decimal = monthly_interest_rate / 100.0;

    // Check if payment is large enough to pay off the loan
    double first_month_interest =
        loan_amount * interest_rate_decimal;

    if (monthly_payment <= first_month_interest)
    {
        cout << "You will never pay off your debt." << endl;
        return 0;
    }

    // Currency formatting
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "\nLoan Amount: " << loan_amount << endl;
    cout << "Interest Rate (% per year): "
         << yearly_interest_rate << endl;
    cout << "Monthly Payments: " << monthly_payment << endl;
    cout << endl;

    // AMORTIZATION TABLE
    cout << "*****************************************************************" << endl;
    cout << "\tAmortization Table" << endl;
    cout << "*****************************************************************" << endl;

    cout << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal"
         << endl;

    double balance = loan_amount;
    double interest_total = 0.0;
    int currentMonth = 0;

    // Month 0
    cout << currentMonth
         << "\t$" << balance
         << "\tN/A\tN/A\tN/A\tN/A"
         << endl;

    // Calculate each month
    while (balance > 0)
    {
        // Monthly interest
        double interest = balance * interest_rate_decimal;

        // Regular payment
        double payment = monthly_payment;

        // Handle final payment
        if (balance + interest < monthly_payment)
        {
            payment = balance + interest;
        }

        // Principal paid
        double principal = payment - interest;

        // Update balance
        balance = balance - principal;

        // Avoid tiny floating-point remainder
        if (balance < 0.005)
        {
            balance = 0.00;
        }

        // Add interest to total
        interest_total += interest;

        currentMonth++;

        // Display monthly information
        cout << currentMonth
             << "\t$" << balance
             << "\t$" << payment
             << "\t" << monthly_interest_rate
             << "\t$" << interest
             << "\t$" << principal
             << endl;
    }

    cout << "****************************************************************" << endl;

    cout << "\nIt takes " << currentMonth
         << " months to pay off the loan." << endl;

    cout << "Total interest paid is: $"
         << interest_total << endl;

    cout << endl;

    return 0;
}
