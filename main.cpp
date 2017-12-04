#include <iostream>

const float DEPOSIT_FEE = 1.00;
const float BALANCE_FEE = 0.50;
const float WITHDRAWAL_FEE = 1.50;
const float OVERDRAWN_FEE = 5.00;
const int MAX_TRANSACT = 30;

struct Transaction
{
    char type;
    float amount;
};

class Account {
public:
    Account();
    void deposit(float a);
    float balanceEnquiry();
    void withdrawal(float a);
    void displayStatement() const;

private:
    float balance;
    Transaction transacts[MAX_TRANSACT];
    int numTransacts;
    float feeTotal;
};

Account::Account() {
    balance = 0;
    numTransacts = 0;
    feeTotal = 0;
}

void Account::deposit(float a) {

    balance += a;
    feeTotal += DEPOSIT_FEE;
    balance -= DEPOSIT_FEE;
    transacts[numTransacts].type = 'D';
    transacts[numTransacts].amount = a;
    numTransacts++;
};

float Account::balanceEnquiry() {

    feeTotal += BALANCE_FEE;
    balance -= BALANCE_FEE;
    transacts[numTransacts].type = 'B';
    transacts[numTransacts].amount = 0;
    numTransacts++;

    return balance;
}

void Account::withdrawal(float a) {

    balance -= a;

    if (balance >= 0) {
        feeTotal += WITHDRAWAL_FEE;
        balance -= WITHDRAWAL_FEE;
    }

    else {
        feeTotal += OVERDRAWN_FEE;
        balance -= OVERDRAWN_FEE;
    }

    transacts[numTransacts].type = 'W';
    transacts[numTransacts].amount = a;
    numTransacts++;
}

void Account::displayStatement() const {
    std::cout << std::endl << "Monthly Statement" << std::endl;
    std::cout << "=======================" << std::endl;

    for (int i = 0; i < numTransacts; i++) {
        switch (transacts[i].type) {
            case 'D':
                std::cout << "Deposit\tR" << transacts[i].amount << std::endl;
                break;
            case 'B':
                std::cout << "Balance enquiry" << std::endl;
                break;
            case 'W':
                std::cout << "Withdrawal\tR" << transacts[i].amount << std::endl;
                break;
            default:
                std::cout << "**Invalid transaction code**" << std::endl;
        }
    }

    std::cout << "Total Fee\tR" << feeTotal << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << "Closing balance\tR" << balance << std::endl;
}

int main() {

    Account account1;
    char type;
    float amount;

    std::cout << "Enter the transactions for the month" << std::endl;
    std::cout << "(D)eposit, (B)alance, (W)ithdrawal, E(X)it: " << std::endl;
    std::cin >> type;

    while (toupper(type) != 'X') {
        switch (toupper(type)) {
            case 'D':
                std::cin >> amount;
                account1.deposit(amount);
                break;
            case 'B':
                account1.balanceEnquiry();
                break;
            case 'W':
                std::cin >> amount;
                account1.withdrawal(amount);
        }
        std::cin >> type;
    }

    std::cout << std::endl;

    account1.displayStatement();

    return 0;
}