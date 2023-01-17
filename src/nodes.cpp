#include "nodes.hpp"
#include "helpers.hpp"


void Ramp::deliver_goods(Time t)
{
    if (t % di_ == 1)
    {
        Package pack;
        push_package(std::move(pack));
    }
}


void Worker::do_work(Time t) {
    if (!_processing_buffer)
    {
        if (!_q->empty())
        {
            _processing_buffer.emplace(_q->pop());
            _t = t;
        }
    }

    if (_processing_buffer)
    {
        if ((t - _t) == _pd - 1)
        {
            push_package(std::move(_processing_buffer.value()));
            _processing_buffer.reset();
        }
    }
}


void PackageSender::send_package()
{
    if (bufor)
    {
        IPackageReceiver* receiver = receiver_preferences_.get_receiver();
        receiver->receive_package(std::move(*bufor));
        bufor.reset();
    }
}


void ReceiverPreferences::add_receiver(IPackageReceiver* r)
{
    double preference = 1;
    preferences_[r] = preference;
    for(auto &i : preferences_) {i.second = 1;}
    for(auto &i : preferences_){ i.second /= static_cast<double>(preferences_.size());}
}


IPackageReceiver *ReceiverPreferences::get_receiver ()
{
    double p = pg_();
    double distributor_value = 0.0;
    for (auto& item: preferences_) {
        distributor_value = distributor_value + item.second;
        if (p<=distributor_value) {
            return item.first;
        }
    }
    throw std::runtime_error("Error has occurred in ReceiverPreferences::choose_receiver()");
}


void ReceiverPreferences::delete_receiver(IPackageReceiver* r){
    if(preferences_.find(r) != preferences_.end())
    {
        preferences_.erase(r);
        if (preferences_.empty()) return;
        for(auto &i : preferences_) {i.second = 1;}
        for(auto &i : preferences_){ i.second /= static_cast<double>(preferences_.size());}
    }
}
