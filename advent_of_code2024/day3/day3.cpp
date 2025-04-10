#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

std::ifstream f("input.in");
std::ofstream g("output.out");

int reverse_number(int);
void process_line(std::string);

class BigInt {
public:
    BigInt();
    BigInt(int number);
    void operator+= (BigInt rhs);
    // void operator += (int rhs);
    void operator+ (BigInt rhs);
    // void operator + (int rhs);
    friend std::ostream & operator<< (std::ostream & os, const BigInt & bigInt) {
        for (int k = bigInt.numberOfDigits() - 1; k >= 0 ; --k) {
            os << bigInt._digits[k];
        }
        return os;
    }
    
private:
    std::vector<int> _digits;

    int getDigit(int position);
    // We know std::vector returns size via a function call, so we just create a wrapper function.
    // In the more complicated case where we would have addition *and* subtraction, the size of the
    // number could decrease, a case in which we should've either reallocated a smaller vector (so 
    // as to obtain the correct number of digits) or we could've had a an additional variable in
    // which to store the number of digits. But then we should've changed the number of digits 
    // based on the operation performed.
    int numberOfDigits() const; 
    void changeDigit(int position, int value);
};

BigInt::BigInt() {
    // Create a one-element number
    _digits.push_back(0);
}

BigInt::BigInt(int number) {
    int digit;
    
    while (number != 0) {
        _digits.push_back(number % 10);
        number = number / 10;
    }
}

void BigInt::operator+= (BigInt rhs) {
    int carry = 0;
    int intermediaryResult = 0;
    int sum = 0;
    
    // Get lenghth of longest number
    int length = this->numberOfDigits();
    if (length < rhs.numberOfDigits()) {
        length = rhs.numberOfDigits();
    }

    // Add each digit together
    for (int k = 0; k < length; ++k) {
        intermediaryResult = this->getDigit(k) + rhs.getDigit(k) + carry;
        sum = intermediaryResult % 10;
        carry = intermediaryResult / 10;
        
        this->changeDigit(k, sum);
    }

    // Add carry as MSB, if there is a final carry out of the addition operation
    if (carry) {
        this->changeDigit(this->numberOfDigits() + 1, carry);
    }
}


int BigInt::numberOfDigits() const{
    return _digits.size();
}

void BigInt::changeDigit(int position, int value) {
    if (position < this->numberOfDigits()) {
        _digits[position] = value;
    } else {
        _digits.push_back(value);
    }
}

int BigInt::getDigit(int position) {
    if (position < this->numberOfDigits()) {
        return _digits[position];
    } else {
        return 0;
    } 
}

// Main *******************************************************************************************

int main() {
    std::string line;
    while (!f.eof()) {
        getline(f, line);
        process_line(line);
    }
}

// Functions **************************************************************************************
void process_line(std::string str) {
    std::regex pattern("mul\\(\\d*,\\d*\\)");
    std::string result;
    std::string number;

    static unsigned long long sum = 0;

    std::sregex_iterator end = std::sregex_iterator();
    static BigInt sum2;

    for(std::sregex_iterator it(str.begin(), str.end(), pattern);
        it != end;
        ++it) {
            // std::cout << "Match: " << it -> str() << "\n";
            result = it -> str();
            
            std::string::iterator start = result.begin() + 4;
            std::string::iterator end = result.end() - 1;
            std::string::iterator coma = std::find(start, end, ',');

            std::string number1(start, coma);
            std::string number2(coma + 1, end);

            // std::cout << std::stoi(number1) << " ";
            // std::cout << std::stoi(number2);

            // Add to bigint instead of sum
            int mul_result = std::stoi(number1) * std::stoi(number2);
            sum += mul_result;
            sum2 += mul_result;
            std::cout << sum << "\n";
            std::cout << sum2 << "\n";
        }
}

int reverse_number(int number) {
    int reversed = 0;
    while (number != 0) {
        reversed = number % 10 + reversed * 10;
        number = number / 10;
    }

    return reversed;
}