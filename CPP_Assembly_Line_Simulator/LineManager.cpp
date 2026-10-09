// C++ assembly-line simulation — Seneca academic coursework
// Some test/starter materials may originate from course resources; review sharing permissions before publication.

#include "LineManager.h"
#include <fstream>
#include <algorithm>

namespace seneca {

LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
    std::ifstream infile(file);
    if (!infile) {
        throw std::string("Unable to open file");
    }
    
    std::string line;
    while (std::getline(infile, line)) {
        size_t delimPos = line.find('|');
        std::string current = line.substr(0, delimPos);
        std::string next = (delimPos != std::string::npos) ? line.substr(delimPos + 1) : "";
        
        // Locate the current station using find_if
        auto currentIt = std::find_if(stations.begin(), stations.end(), 
            [&current](Workstation* ws) { return ws->getItemName() == current; });
        
        if (currentIt == stations.end()) continue;
        
        m_activeLine.push_back(*currentIt);
        
        // Link to next station when available
        if (next.empty()) continue;
        
        auto nextIt = std::find_if(stations.begin(), stations.end(),
            [&next](Workstation* ws) { return ws->getItemName() == next; });
        
        if (nextIt != stations.end()) {
            (*currentIt)->setNextStation(*nextIt);
        }
    }
    
    // Identify the first station (one with no predecessors)
    for (auto station : stations) {
        bool hasIncoming = false;
        
        for (auto other : stations) {
            if (other->getNextStation() != station) continue;
            hasIncoming = true;
            break;
        }
        
        if (hasIncoming) continue;
        
        m_firstStation = station;
        break;
    }
    
    m_cntCustomerOrder = g_pending.size();
}

void LineManager::reorderStations() {
    std::vector<Workstation*> reordered;
    Workstation* current = m_firstStation;
    
    while (current != nullptr) {
        reordered.push_back(current);
        current = current->getNextStation();
    }
    
    m_activeLine = reordered;
}

bool LineManager::run(std::ostream& os) {
    static size_t iteration = 0;
    iteration++;
    os << "Line Manager Iteration: " << iteration << std::endl;
    
    // Transfer pending order to first station if available
    if (!g_pending.empty()) {
        *m_firstStation += std::move(g_pending.front());
        g_pending.pop_front();
    }
    
    // Process filling at all stations
    for (auto station : m_activeLine) {
        station->fill(os);
    }
    
    // Attempt order movement at all stations
    for (auto station : m_activeLine) {
        station->attemptToMoveOrder();
    }
    
    return (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
}

void LineManager::display(std::ostream& os) const {
    for (auto station : m_activeLine) {
        station->display(os);
    }
}

}