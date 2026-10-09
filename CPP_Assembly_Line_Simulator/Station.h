// C++ assembly-line simulation — Seneca academic coursework
// Some test/starter materials may originate from course resources; review sharing permissions before publication.

#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <string>
#include <iostream>

namespace seneca {

    // forward declaration
    class Utilities;

    class Station {
        int m_id;
        std::string m_name;
        std::string m_description;
        size_t m_serialNumber;
        size_t m_quantity;
        
        static size_t m_widthField;
        static int id_generator;
        
        void initializeFromRecord(const std::string& record);
        void parseTokens(class Utilities& util, const std::string& record); // Use class keyword
        
    public:
        Station(const std::string& record);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };

} // namespace seneca

#endif