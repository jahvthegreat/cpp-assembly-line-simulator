// C++ assembly-line simulation — Seneca academic coursework
// Some test/starter materials may originate from course resources; review sharing permissions before publication.

#include "Utilities.h"
#include <string>
#include <stdexcept>
#include <cctype>

namespace seneca {
    char Utilities::m_delimiter = '|';

    Utilities::Utilities() : m_widthField(1) {}
    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }
    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }
    std::string Utilities::trimWhitespace(const std::string& str) const {
        if (str.empty()) return str;
        auto begin = str.begin();
        auto end = str.end();
        // find first non-space char
        while (begin != end && std::isspace(static_cast<unsigned char>(*begin))) {
            ++begin;
        }
        // find last non-space char
        while (begin != end && std::isspace(static_cast<unsigned char>(*(end - 1)))) {
            --end;
        }
        return std::string(begin, end);
    }

    bool Utilities::validatePosition(size_t pos, const std::string& str) const {
        return pos < str.length();
    }

    size_t Utilities::findNextDelimiter(const std::string& str, size_t startFrom) const {
        for (size_t i = startFrom; i < str.length(); ++i) {
            if (str[i] == m_delimiter) {
                return i;}
        }
        return std::string::npos;
    }
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        // check if we at end of string
        if (!validatePosition(next_pos, str)) {
            more = false;
            return "";
        }
        
        // checkg for delimiter at curent position
        if (str[next_pos] == m_delimiter) {
            more = false;
            throw std::runtime_error("Delimiter found at current position");
        }
        
        size_t tokenStart = next_pos;
        size_t tokenEnd = findNextDelimiter(str, tokenStart);
        // determine if there's more tokens after this one
        if (tokenEnd == std::string::npos) {
            tokenEnd = str.length();
            more = false;
        } else {
            more = true;
        }
        size_t tokenLength = tokenEnd - tokenStart;
        std::string rawToken = str.substr(tokenStart, tokenLength);
        //clean up the token
        std::string cleanToken = trimWhitespace(rawToken);
        //update width of field
        size_t tokenSize = cleanToken.size();
        if (tokenSize > m_widthField) {
            m_widthField = tokenSize;
        }   
        // set next position for subsequent calls
        next_pos = tokenEnd + 1;
        
        return cleanToken;
    }
    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }
    char Utilities::getDelimiter() {
        return m_delimiter;
    }
}