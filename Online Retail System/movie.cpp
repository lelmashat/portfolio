#include "movie.h"
#include "util.h"
#include <iomanip>
#include <sstream>

using namespace std;

// constructor to make a movie based on given data
Movie::Movie(const std::string& name, double price, int quantity, const std::string& genre, const std::string& rating)
    : Product("movie", name, price, quantity), genre(genre), rating(rating) {}

std::set<std::string> Movie::keywords() const {
    // creating a set that we input all of the words from the movie title into
    std::set<std::string> keys = parseStringToWords(getName());
    // adding in the genre and rating to this set
    keys.insert(genre);
    keys.insert(rating);
    // returning set (has all keys for this movie)
    return keys;
}

std::string Movie::displayString() const {
    // using an ostringstream to help with creating return string
    std::ostringstream oss;
    // using set precision to avoid too many decimal places for the price
    oss << std::fixed << std::setprecision(2) << getPrice();
    // creating a string based on given formatting requirements
    std::string displayStr = getName() + "\nGenre: " + genre + " Rating: " 
                                + rating + "\n" + oss.str() 
                                + " " + std::to_string(getQty()) + " left.";
    // returning our string
    return displayStr;
}

void Movie::dump(std::ostream& os) const {
    // dump (print out) all movie info whose data members are inherited from product
    Product::dump(os);
    // print out unique movie data members
    os << genre << endl;
    os << rating << endl;
}

