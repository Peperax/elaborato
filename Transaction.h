

#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include <iostream>


class Transaction {

private:
    std::string data;
    double import;
    std::string type;
    std::string description;

public:
    Transaction(const std::string& data, double import, const std::string& type, const std::string& description);

    std::string getData() const;
    double getImport() const;
    std::string getType() const;
    std::string getDescription() const;

};



#endif //TRANSACTION_H
