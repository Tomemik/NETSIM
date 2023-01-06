#include "package.hpp"

std::set<ElementID> Package::assigned_IDs;
std::set<ElementID> Package::freed_IDs;

Package::Package() {
    ElementID id;
    if (!freed_IDs.empty()) {
        id = *freed_IDs.begin();
        freed_IDs.erase(id);
    } else {
        id = assigned_IDs.empty() ? 1 : *assigned_IDs.rbegin() + 1;
    }
    assigned_IDs.insert(id);
    id_ = id;
    }

Package::Package(ElementID id) : id_(id) {
    assigned_IDs.insert(id);
}

Package::Package(const Package& other) : id_(other.id_) {}

Package::Package(Package&& other) : id_(other.id_) {}

Package::~Package() {freed_IDs.insert(id_);}

ElementID Package::get_id() const {return id_;}

Package& Package::operator=(const Package& other) {
    freed_IDs.insert(id_);
    assigned_IDs.erase(id_);
    id_ = other.id_;
    assigned_IDs.insert(id_);
    return *this;
}

Package& Package::operator=(Package&& other) {
    freed_IDs.insert(id_);
    assigned_IDs.erase(id_);
    id_ = other.id_;
    assigned_IDs.insert(id_);
    return *this;
}