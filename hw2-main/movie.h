#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"

class Movie : public Product {
public:
    // constructor that makes a movie based on requirements
    Movie(const std::string& name, double price, int quantity, const std::string& genre, const std::string& rating);
    // function to find keywords for a movie 
    std::set<std::string> keywords() const override;
    // function to display movie info for viewCart
    std::string displayString() const override;
    // function to display movie info in same layout as input file
    void dump(std::ostream& os) const override;

private:
    // data members that make a movie unique from a product
    std::string genre;
    std::string rating;
};

#endif // MOVIE_H
