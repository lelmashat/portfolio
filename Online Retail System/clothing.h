#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"

class Clothing : public Product {
public:
    // constructor created given clothing requirements
    Clothing(const std::string& name, double price, int quantity, const std::string& size, const std::string& brand);
    // function to get keywords from a clothing item
    std::set<std::string> keywords() const override;
    // function to display the clothing info for viewCart calls
    std::string displayString() const override;
    // function to display the clothing info in same layout as input file
    void dump(std::ostream& os) const override;

private:
    // data members that make a clothing item unique from a product
    std::string size;
    std::string brand;
};

#endif // CLOTHING_H
