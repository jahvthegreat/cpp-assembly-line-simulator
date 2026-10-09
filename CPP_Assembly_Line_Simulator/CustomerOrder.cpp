// C++ assembly-line simulation — Seneca academic coursework
// Some test/starter materials may originate from course resources; review sharing permissions before publication.

#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>
#include <vector>

namespace seneca {
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder() : m_cntItem(0), m_lstItem(nullptr) {}

    CustomerOrder::CustomerOrder(const std::string& str) : m_cntItem(0), m_lstItem(nullptr) {
        Utilities util;
        size_t pos = 0;
        bool more = true;
        std::vector<std::string> items;
        
        // take customer name
        m_name = util.extractToken(str, pos, more);
        
        // take product name
        if (more) {
            m_product = util.extractToken(str, pos, more);
        }
        
        // take all items
        while (more) {
            std::string item = util.extractToken(str, pos, more);
            if (!item.empty()) {
                items.push_back(item);
            }
        }
        
        // allocate items
        m_cntItem = items.size();
        if (m_cntItem > 0) {
            m_lstItem = new Item*[m_cntItem];
            for (size_t i = 0; i < m_cntItem; i++) {
                m_lstItem[i] = new Item(items[i]);
            }
        }
        
        // update width field
        if (util.getFieldWidth() > m_widthField) {
            m_widthField = util.getFieldWidth();
        }
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept 
        : m_name(std::move(other.m_name)), 
          m_product(std::move(other.m_product)), 
          m_cntItem(other.m_cntItem), 
          m_lstItem(other.m_lstItem) {
        other.m_cntItem = 0;
        other.m_lstItem = nullptr;
    }
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other) {
            // clean up existing resources
            for (size_t i = 0; i < m_cntItem; i++) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
            m_name = std::move(other.m_name);
            m_product = std::move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;
            
            // reset other
            other.m_cntItem = 0;
            other.m_lstItem = nullptr;
        }
        return *this;
    }
    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }
    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (!m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }
    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == itemName) {
                if (!m_lstItem[i]->m_isFilled) {
                    return false;
                }
            }
        }
        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == station.getItemName() && 
                !m_lstItem[i]->m_isFilled) {
                
                if (station.getQuantity() > 0) {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();
                    os << "    Filled " << m_name << ", " << m_product 
                       << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    return;
                } else {
                    os << "    Unable to fill " << m_name << ", " << m_product 
                       << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }
    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;
        
        for (size_t i = 0; i < m_cntItem; i++) {
            os << "[" << std::setw(6) << std::setfill('0') << std::right 
               << m_lstItem[i]->m_serialNumber << "] "
               << std::setfill(' ') << std::left << std::setw(m_widthField) 
               << m_lstItem[i]->m_itemName << " - " 
               << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") 
               << std::endl;
        }
    }
}