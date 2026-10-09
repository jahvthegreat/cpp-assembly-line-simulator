// C++ assembly-line simulation — Seneca academic coursework
// Some test/starter materials may originate from course resources; review sharing permissions before publication.

#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <string>
#include <iostream>
#include <vector>
#include "Station.h"

namespace seneca {
    class CustomerOrder {
        struct Item {
            std::string m_itemName;
            size_t m_serialNumber;
            bool m_isFilled;
            Item(const std::string& src) : m_itemName(src), m_serialNumber(0), m_isFilled(false) {};
        };
        
        std::string m_name;
        std::string m_product;
        size_t m_cntItem;
        Item** m_lstItem;
        static size_t m_widthField;
        
        void parseOrderData(const std::string& str);
        void allocateItems(const std::vector<std::string>& items);
        void cleanupResources();
        
    public:
        CustomerOrder();
        CustomerOrder(const std::string& str);
        CustomerOrder(const CustomerOrder&) { throw "ERROR: Cannot make copies."; }
        CustomerOrder(CustomerOrder&& other) noexcept;
        CustomerOrder& operator=(CustomerOrder&& other) noexcept;
        ~CustomerOrder();
        
        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };
}

#endif