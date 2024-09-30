#include "mydatastore.h"
#include "util.h"
using namespace std;

MyDataStore::MyDataStore() {
    // No need to initialize
}

MyDataStore::~MyDataStore() {
    // deleting all the User* from the users map
    for(std::pair<std::string, User*> u_ : users){
        delete u_.second;
    }
    // deleting all the Product* from the products map
    for(std::pair<std::string, Product*> p_ : products){
        delete p_.second;
    }
    // clearing both maps
    users.clear();
    products.clear();
}

void MyDataStore::addProduct(Product* p) {
    // Add product to the products map
    products[p->getName()] = p;
    // getting the keywords for the product
    for(std::string key : p->keywords()){
        // making the keywords lowercased and added into keywords
        // this helps us later with the search function
        keywords[convToLower(key)].insert(p);
    }

}

void MyDataStore::addUser(User* u) {
    // Add user to the users map
    users[u->getName()] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    // creating the return vector
    std::vector<Product*> results;
    // Convert search terms to lower case for case-insensitive search
    std::set<std::string> termsLower;
    for (const std::string& term : terms) {
        termsLower.insert(convToLower(term));
    }
    // looping through the items
    for (const std::pair<const std::string, Product*>& kv : products) {
        // creating variables for the search
        Product* prod = kv.second;
        std::set<std::string> productKeywords = prod->keywords();
        
        bool match = false;
        for (const std::string& term : termsLower) { // looping through given terms
            bool termMatch = false;
            for (const std::string& keyword : productKeywords) { // looping through our specific product's keywords
                if (convToLower(keyword).find(term) != std::string::npos) {
                    termMatch = true; // we find a match
                    if (type != 0) { 
                        break;
                    }
                }
            }
            // based on the type and termMatch, we set match accordingly
            if (type == 0 && !termMatch) { 
                match = false;
                break;
            } else if (type != 0 && termMatch) { 
                match = true;
                break;
            }
            if (type == 0) { 
                match = true;
            }
        }
        // if we got a match, we add it to our results vector
        if (match) {
            results.push_back(prod);
        }
    }

    return results;
}

// Implement other member functions as needed

template <typename T>
std::set<T> MyDataStore::setIntersection(const std::set<T>& set1, const std::set<T>& set2) {
    std::set<T> result; // use the set intersection function to return the correct set
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(result, result.begin()));
    return result;
}

void MyDataStore::dump(std::ostream& ofile){
  // print the header for products
  ofile << "<products>" << endl;
  for(std::pair<std::string, Product*> currProduct : products){
    (currProduct.second)->dump(ofile); // for each product, dump correct info
  }
  // print the footer for products
  ofile << "</products>" << endl;
  // print the header for users
  ofile << "<users>" << endl;
  for(std::pair<std::string, User*> currUser : users){
    (currUser.second)->dump(ofile); // for each user, dump correct info
  }
  // print the footer for users
  ofile << "</users>" << endl;

}

void MyDataStore::addCart(const std::string& username, Product* product){
    // if a deque has not been made for username
    if(carts.find(username) == carts.end()){
        std::deque<Product*> userCart; // create a deque for the user
        userCart.push_back(product); // add the product to the deque
        carts[username] = userCart; // add the deque to the map
    }
    else{
        (carts[username]).push_back(product); // add the product to the existing deque
    }

}

void MyDataStore::viewCart(const std::string& username){
    const auto& userCart = carts[username];  // Get a reference to the deque

    // loop through items in cart
    for (size_t i = 0; i < userCart.size(); ++i) {
        cout << "Item " << i+1 << endl; // pring out item indication
        cout << userCart[i]->displayString() << endl; // diplay item info using displayString
    }

}

void MyDataStore::buyCart(const std::string& username){
    // create a user* for use in function
    User* user_ = users[username];
    // create new cart to replace old cart with
    std::deque<Product*> newCart;
    for(Product* item : carts[username]){ // loop through cart items
        if(item->getQty() == 0){ // if the item is sold out
            newCart.push_back(item); // add to new cart without buying and move on
            continue;
        }
        else if(item->getPrice() > user_->getBalance()){ // if item is too expensive
            newCart.push_back(item);// and to new cart without buying and move on
            continue;
        }
        user_->deductAmount(item->getPrice()); // deduct the payment from the user
        item->subtractQty(1); // deduct the quantity by 1
    }
    carts[username] = newCart; // set the user's cart to be newCart
}

bool MyDataStore::isAUser(const std::string& nm){
    // loop through the users
    for(std::pair<std::string, User*> person : users){
        if((person.second)->getName() == nm){
            return true; // if we find a username match, return true
        }
    }
    return false; // no match, so return false
}


