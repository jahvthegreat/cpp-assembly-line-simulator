// C++ assembly-line simulation — Seneca academic coursework
// Some test/starter materials may originate from course resources; review sharing permissions before publication.

#include "Station.h"
#include "Utilities.h"
#include <iomanip>
#include <sstream>

namespace seneca {
    size_t Station::m_widthField = 0;
    int Station::id_generator = 0;

    Station::Station(const std::string& record) 
        : m_id(0), m_serialNumber(0), m_quantity(0) {
        
        Utilities util;
        size_t pos = 0;
        bool more = true;
        
        //  take all tokens
        m_name = util.extractToken(record, pos, more);
        
        if (more) {
            std::string serialStr = util.extractToken(record, pos, more);
            // use stringstream for guaranteed correct parsing
            std::stringstream ss(serialStr);
            ss >> m_serialNumber;
        }
        
        if (more) {
            std::string qtyStr = util.extractToken(record, pos, more);
            // use stringstream for guaranteed correct parsing
            std::stringstream ss(qtyStr);
            ss >> m_quantity;
        }
        
        if (more) {
            m_description = util.extractToken(record, pos, more);
        }
        
        // generate ID
        m_id = ++id_generator;
        
        // update width
        if (m_name.length() > m_widthField) {
            m_widthField = m_name.length();
        }
    }

    const std::string& Station::getItemName() const {
        return m_name;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0) {
            --m_quantity;
        }
    }

    void Station::display(std::ostream& os, bool full) const {
        os << std::setw(3) << std::setfill('0') << std::right << m_id << " | ";
        os << std::left << std::setw(m_widthField) << std::setfill(' ') << m_name << " | ";
        os << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << " | ";
        
        if (full) {
            os << std::right << std::setw(4) << std::setfill(' ') << m_quantity << " | ";
            os << m_description;
        }
        
        os << std::endl;
    }
}