#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <unordered_map>
#include <deque>
#include <set>

class MyDataStore : public DataStore {
public:
    // constructor and destructor for the data store
    MyDataStore();
    ~MyDataStore();

    // fuction for adding a product to the store
    void addProduct(Product* p) override;
    // function for adding a user to the store
    void addUser(User* u) override;
    // function for searching the store for any AND or OR matches
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    // function to add items to card
    void addCart(const std::string& username, Product* product);
    // function to display the cart
    void viewCart(const std::string& username);
    // function to buy the cart
    void buyCart(const std::string& username);
    // function to print all info into ofile
    void dump(std::ostream& ofile) override;
    // check if a string is a valid user
    bool isAUser(const std::string& nm);

private:
    // maps to store the users, products, carts, and keywords for the store
    std::unordered_map<std::string, User*> users;
    std::unordered_map<std::string, Product*> products;
    std::unordered_map<std::string, std::deque<Product*>> carts;
    std::unordered_map<std::string, std::set<Product*>> keywords;

    // Helper function to perform set intersection
    template <typename T>
    std::set<T> setIntersection(const std::set<T>& set1, const std::set<T>& set2);


};

#endif // MYDATASTORE_H
