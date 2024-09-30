#include "clothing.h"
#include "util.h"
#include <iomanip>
#include <sstream>

// constructor sets the data members based on function inputs
Clothing::Clothing(const std::string& name, double price, int quantity, const std::string& size, const std::string& brand)
    : Product("clothing", name, price, quantity), size(size), brand(brand) {}

std::set<std::string> Clothing::keywords() const {
    // parsing the words from the item name and brand to sets
    std::set<std::string> keys = parseStringToWords(getName());
    std::set<std::string> brandset = parseStringToWords(brand);
    // adding the keywords from the second set to the first
    keys.insert(brandset.begin(), brandset.end());
    // adding the size to the first set and returning that set as total keywords
    keys.insert(size);
    return keys;
}

std::string Clothing::displayString() const {
    // using an ostringstream to help with string creation
    std::ostringstream oss;
    // fixing the price so that it does not have too many decimal places
    oss << std::fixed << std::setprecision(2) << getPrice();
    // creating the display string based on required formatting
    std::string displayStr = getName() + "\nSize: " + size + " Brand: " 
                                + brand + "\n" + oss.str() 
                                + " " + std::to_string(getQty()) + " left.";
    // returning the display string
    return displayStr;
}

void Clothing::dump(std::ostream& os) const {
    // dump (print) the info about the clothing item inherited from profit
    Product::dump(os);
    // print the unique clothing info
    os << size << std::endl;
    os << brand << std::endl;
}

