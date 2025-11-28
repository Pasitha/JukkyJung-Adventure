#pragma once
#include "Item.h"
#include <vector>
#include <memory>

class Inventory {
public:
    void addItem(std::unique_ptr<Item> item);
    void removeItem(const std::string& itemName);
    void useItem(const std::string& itemName, Character& character);

private:
    std::vector<std::unique_ptr<Item>> items;
};
