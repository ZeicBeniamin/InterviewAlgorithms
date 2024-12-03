#include <string.h>

#include <fstream>
#include <iostream>
#include <iterator>
#include <set>

using namespace std;

ifstream f("market_cap.in");

struct Stock {
   public:
    // Default
    Stock(string name, unsigned int price, unsigned int shares,
          float mCap)
        : name(name), price(price), shares(shares), mCap(mCap) {
        cout << "Default constructor called" << "\n";
        Stock::totalMcap += mCap;
    }
    // Copy : Stock a = b;
    Stock(const Stock& o)
        : price(o.price),
          shares(o.shares),
          mCap(o.mCap),
          name(o.name) {
        cout << "Copy constructor called" << "\n";

        // Stock::totalMcap += mCap;
    }
    // Copy assign operator : Stock a; a = b;
    Stock& operator=(Stock& other) {
        if (this != &other) {
            price = other.price;
            shares = other.shares;
            mCap = other.mCap;
            name = other.name;
            // Stock::totalMcap += mCap;
        }
        cout << "Copy assignmnet constructor called\n";

        return *this;
    }
    // Move : Stock a = std::move(b)
    Stock(Stock&& o)
        : price(o.price),
          shares(o.shares),
          mCap(o.mCap),
          name(o.name) {
        cout << "Move constructor called\n";

        // Stock::totalMcap += mCap;
    }
    // Move operator : Stock a; a = std::move(b)
    Stock& operator=(Stock&& other) {
        if (this != &other) {
            // *this = other;
            price = other.price;
            shares = other.shares;
            mCap = other.mCap;
            name = other.name;

            // Stock::totalMcap += mCap;
        }
        cout << "Move assignment operator called\n";

        return *this;
    }

    ~Stock() {
        Stock::totalMcap -= mCap;
        cout << "Destructor called\n";
    }

    float calculate_weight() const {
        // return thiprice * shares / totalMCap;
        return (price * shares) / Stock::totalMcap;
    }

    float calcIdxContrib() const {
        cout << "Weight of " << name << " " << calculate_weight() << "\n";
        return calculate_weight() * price;
    }

   public:
    string getName() const { return name; }
    float getMarketCap() const { return mCap; }
    float getTotalMarketCap() { return totalMcap; }
    unsigned int getPrice() const {return price;}
    unsigned int getShares() const {return shares;}

   private:
    string name;
    unsigned int price;
    unsigned int shares;
    float mCap;
    static float totalMcap;
};

float Stock::totalMcap;

struct CustomCompare {
    bool operator()(const Stock& lhs, const Stock& rhs) const {
        if (lhs.getName() == rhs.getName()) {
            // lhs < rhs or lhs > rhs would both return "false", thus indicating
            // equality between stocks As such, std::set will consider both to
            // be the sem set element, i.e. will replace lhs
            return false;
        } else {
            if (lhs.getMarketCap() == rhs.getMarketCap()) {
                // If we have two stocks with the same market cap, we do
                // lexicographical sorting
                return lhs.getName() < rhs.getName();
            } else {
                return lhs.getMarketCap() > rhs.getMarketCap();
            }
        }
    }
};

set<Stock, CustomCompare> market;

void see(const set<Stock, CustomCompare>& market) {
    // for (Stock stock: market) {
    //     cout << stock.name << " " << stock.mCap << "\n";
    //     // cout << stock.name << "\n";
    // }
    std::set<Stock, CustomCompare>::iterator it;
    for (it = market.cbegin(); it != market.cend(); ++it) {
        // auto n = *it;
        // cout << it -> name;
        // cout << it->getName() << " " << it->getMarketCap() << "\n";
        cout << it->getName() << " " << it->getPrice() << " " << it->getShares() << "\n";
    }
    cout << "\n";
}



float calculate_idx(set<Stock, CustomCompare> &market) {
    int counter = 0;
    float indexVal = 0; 

    for (set<Stock,CustomCompare>::iterator it = market.begin(); it != market.end(); ++it) {
        if (counter == 10) {
            break;
        } 
        ++counter;

        indexVal += it -> calcIdxContrib();
    }

    return indexVal;
}

void read() {
    string name;
    unsigned int price;
    unsigned int shares;
    float mCap;
    while (!f.eof()) {
        f >> name;
        f >> price;
        f >> shares;
        mCap = price * shares;
        Stock stock(name, price, shares, mCap);

        market.insert(stock);
        cout << "Sum: " << stock.getTotalMarketCap() - stock.getMarketCap() << "\n";
        cout << "Mkt idx " << (int)calculate_idx(market) << "\n";
        see(market);
        // cout << "In while loop\n";
        // cout << "Name: " << stock.name << "\n";
        // cout << "Price: " << stock.price << "\n";
        // cout << "Shares: " << stock.shares << "\n";
    }
}

int main() {
    read();
    // process();

    return 0;
}