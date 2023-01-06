#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP

#include "types.hpp"
#include <list>
#include <algorithm>
#include <set>
#include <iostream>

#pragma once

#include <set>

class Package {
public:
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;

    Package();
    Package(ElementID id);
    Package(const Package& other);
    Package(Package&& other);
    ~Package();

    ElementID get_id() const;

    Package& operator=(const Package& other);
    Package& operator=(Package&& other);

private:
    ElementID m_id;
};
#endif //NETSIM_PACKAGE_HPP
