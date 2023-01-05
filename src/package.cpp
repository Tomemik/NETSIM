#include "package.hpp"
#include "types.hpp"

Package::Package() {
    ElementID id;
    if (!freed_IDs.empty()) {
        id = *freed_IDs.begin();
        freed_IDs.erase(id);
    } else {
        id = assigned_IDs.empty() ? 1 : *assigned_IDs.rbegin() + 1;
    }
    assigned_IDs.insert(id);
    m_id = id;
    }

Package::Package(ElementID id) : m_id(id) {
    assigned_IDs.insert(id);
}

Package::Package(const Package& other) : m_id(other.m_id) {}

Package::Package(Package&& other) : m_id(other.m_id) {}

Package::~Package() {freed_IDs.insert(m_id);}

ElementID Package::get_id() const {return m_id;}

Package& Package::operator=(const Package& other) {
    freed_IDs.insert(m_id);
    assigned_IDs.erase(m_id);
    m_id = other.m_id;
    assigned_IDs.insert(m_id);
    return *this;
}

Package& Package::operator=(Package&& other) {
    freed_IDs.insert(m_id);
    assigned_IDs.erase(m_id);
    m_id = other.m_id;
    assigned_IDs.insert(m_id);
    return *this;
}