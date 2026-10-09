// C++ assembly-line simulation — Seneca academic coursework
// Some test/starter materials may originate from course resources; review sharing permissions before publication.

#include "Workstation.h"
#include <iostream>

namespace seneca {

std::deque<CustomerOrder> g_pending;
std::deque<CustomerOrder> g_completed;
std::deque<CustomerOrder> g_incomplete;

void Workstation::fill(std::ostream& os) {
    if (m_orders.empty()) return;
    m_orders.front().fillItem(*this, os);
}

bool Workstation::attemptToMoveOrder() {
    if (m_orders.empty()) return false;
    
    CustomerOrder& order = m_orders.front();
    
    // Check if item is already filled or no inventory available
    bool itemFilled = order.isItemFilled(getItemName());
    bool noStock = (getQuantity() == 0);
    
    if (!itemFilled && !noStock) return false;
    
    // Determine destination for the order
    if (m_pNextStation != nullptr) {
        *m_pNextStation += std::move(order);
    } else {
        // Route to appropriate completion queue
        auto& destination = order.isOrderFilled() ? g_completed : g_incomplete;
        destination.push_back(std::move(order));
    }
    
    m_orders.pop_front();
    return true;
}

void Workstation::setNextStation(Workstation* station) {
    m_pNextStation = station;
}

Workstation* Workstation::getNextStation() const {
    return m_pNextStation;
}

void Workstation::display(std::ostream& os) const {
    os << getItemName() << " --> ";
    os << (m_pNextStation ? m_pNextStation->getItemName() : "End of Line");
    os << std::endl;
}

Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
    m_orders.push_back(std::move(newOrder));
    return *this;
}

}