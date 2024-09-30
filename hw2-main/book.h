#ifndef BOOK_H
#define BOOK_H

#include "product.h"

class Book : public Product {
public:
    // constructor for books based on instructions
    Book(const std::string& name, double price, int quantity, const std::string& author, const std::string& isbn);
    // reading in key words from book information
    std::set<std::string> keywords() const override;
    // creating the display for when a user views cart
    std::string displayString() const override;
    // printing all information about the book as it was shown in input file
    void dump(std::ostream& os) const override;

private:
    // data members author and isbn needed for a product to be a book
    std::string author;
    std::string isbn;
};

#endif // BOOK_H
