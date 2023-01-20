#ifndef NETSIM_NODES_HPP
#define NETSIM_NODES_HPP

#include "types.hpp"
#include "storage_types.hpp"
#include "config.hpp"
#include "helpers.hpp"

#include <iostream>
#include <memory>
#include <optional>
#include <map>
#include <functional>

enum ReceiverType{
    WORKER,
    STOREHOUSE
};

class IPackageReceiver{
public:
    using const_it= IPackageStockpile::const_iterator;

    virtual ElementID get_id() const = 0;
    virtual void receive_package(Package&& p) = 0;
#if (EXERCISE_ID > EXERCISE_ID_NODES)
    virtual ReceiverType get_receiver_type () const = 0;
#endif
    virtual const_it begin() const = 0;
    virtual const_it end() const = 0;
    virtual const_it cbegin() const = 0;
    virtual const_it cend() const = 0;
};

class Storehouse : public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueueType::LIFO)) : _id(id), _d(std::move(d)) {}

#if (EXERCISE_ID > EXERCISE_ID_NODES)
    ReceiverType get_receiver_type() const {return ReceiverType::STOREHOUSE;};
#endif

    ElementID get_id() const { return _id; }
    void receive_package(Package&& pack) { _d->push(std::move(pack)); }

    // iteratory
    const_it begin() const {return _d -> begin();};
    const_it end() const {return _d -> end();};
    const_it cbegin() const {return _d -> cbegin();};
    const_it cend() const {return _d -> cend();};

private:
    ElementID _id;
    std::unique_ptr<IPackageStockpile> _d;
};


//Najrozsądniej jest przekazać w parametrze konstruktora klasy ReceiverPreferences uchwyt do funkcji zwracającej
// (tj. argumentem konstruktora będzie obiekt funkcyjny odpowiedniego typu) – uchwyt ten zostanie
// zapamiętany w odpowiednim polu klasy ReceiverPreferences i to pole będzie wykorzystywane
// do uzyskania wartości (pseudo)losowej wewnątrz metody służącej do wyboru losowego odbiorcy.

class ReceiverPreferences{
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator pg = probability_generator):pg_(std::move(pg)){}
    const preferences_t& get_preferences() const{return preferences_;};
    void add_receiver(IPackageReceiver* receiver_ptr);
    void remove_receiver(IPackageReceiver* receiver_ptr);
    IPackageReceiver* choose_receiver();

    const_iterator begin() const {return preferences_.begin();};
    const_iterator end() const {return preferences_.end();};
    const_iterator cbegin() const {return preferences_.cbegin();};
    const_iterator cend() const {return preferences_.cend();};

private:
    ProbabilityGenerator pg_;
    preferences_t preferences_;
};

class PackageSender{
public:
    void send_package();
    const std::optional<Package>& get_sending_buffer() const {return bufor;}
    ReceiverPreferences receiver_preferences_;

protected:
    void push_package(Package&& pack) {bufor = std::move(pack);};

private:
    std::optional<Package> bufor;
};

class Ramp: public PackageSender{
public:
    Ramp(ElementID id, TimeOffset di): id_(id), di_(di){}
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const {return di_;};
    ElementID get_id() const {return id_;}
private:
    ElementID id_;
    TimeOffset di_;
};

class Worker: public PackageSender, public IPackageReceiver {
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : _id(id), _pd(pd), _q(std::move(q)) {}
    void do_work(Time t);
    TimeOffset get_processing_duration() const {return _pd;}
    Time get_package_processing_start_time() const {return _t;}

#if (EXERCISE_ID > EXERCISE_ID_NODES)
    ReceiverType get_receiver_type() const override {return ReceiverType::WORKER;}
#endif

    void receive_package(Package&& p) override {_q->push(std::move(p));}
    ElementID get_id() const override { return _id; }

    IPackageStockpile::const_iterator begin() const override {return _q->begin();}
    IPackageStockpile::const_iterator end() const override {return _q->end();}
    IPackageStockpile::const_iterator cbegin() const override {return _q->cbegin();}
    IPackageStockpile::const_iterator cend() const override {return _q->cend();}

private:
    ElementID _id;
    TimeOffset _pd;
    std::unique_ptr<IPackageQueue> _q;
    Time _t = 0;
    std::optional<Package> _processing_buffer;
};

#endif //NETSIM_NODES_HPP
