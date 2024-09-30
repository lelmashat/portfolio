#include "book.h"
#include "util.h"
#include <iomanip>
#include <sstream>
using namespace std;

// constructor for books takes in the arguments and makes assignments accordingly
Book::Book(const std::string& name, double price, int quantity, const std::string& author, const std::string& isbn)
    : Product("book", name, price, quantity), author(author), isbn(isbn) {}


std::set<std::string> Book::keywords() const {
    // parse through the book name and author to get a set of keywords
    std::set<std::string> keys = parseStringToWords(getName());
    std::set<std::string> authorset = parseStringToWords(author);
    // insert the set of words from the author set to keys
    keys.insert(authorset.begin(), authorset.end());
    // insert the isbn to keys and return keys
    keys.insert(isbn);
    return keys;
}

std::string Book::displayString() const {
    // useing an ostrinstream to help in creating our display string
    std::ostringstream oss;
    // setting the precision for the price to avoid too many decimal places
    oss << std::fixed << std::setprecision(2) << getPrice();
    // creating a string using the book info in the required formatting
    std::string displayStr = getName() + "\nAuthor: " + author + " ISBN: " 
                                + isbn + "\n" + oss.str() 
                                + " " + std::to_string(getQty()) + " left.";
    // returning our string
    return displayStr;
}

void Book::dump(std::ostream& os) const {
    // dump the book information that is inherited from product
    Product::dump(os);
    // print out book related info
    os << isbn << std::endl;
    os << author << std::endl;
}

