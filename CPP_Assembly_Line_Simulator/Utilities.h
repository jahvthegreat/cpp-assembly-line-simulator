// C++ assembly-line simulation — Seneca academic coursework
// Some test/starter materials may originate from course resources; review sharing permissions before publication.

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>

namespace seneca {
    class Utilities {
        size_t m_widthField;
        static char m_delimiter;
        
        std::string trimWhitespace(const std::string& str) const;
        bool validatePosition(size_t pos, const std::string& str) const;
        size_t findNextDelimiter(const std::string& str, size_t startFrom) const;
        
    public:
        Utilities();
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };
}

#endif