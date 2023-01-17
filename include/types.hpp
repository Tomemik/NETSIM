#ifndef NETSIM_TYPES_HPP
#define NETSIM_TYPES_HPP

#include <iostream>
#include <functional>
using ElementID = int;

using ProbabilityGenerator= std::function<double()>;
using Time=unsigned int;
using TimeOffset= unsigned int;

#endif //NETSIM_TYPES_HPP
