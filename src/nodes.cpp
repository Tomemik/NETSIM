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
        IPackageReceiver* receiver = receiver_preferences_.choose_receiver();
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

IPackageReceiver *ReceiverPreferences::choose_receiver(){
    double number = pg_();
    double sum = 0;
    for (const auto &item: preferences_)
    {
        sum += item.second;
        if(number <= sum)
            return item.first;
    }
    return preferences_.end()->first;
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r){
    if(preferences_.find(r) != preferences_.end())
    {
        preferences_.erase(r);
        if (preferences_.empty()) return;
        for(auto &i : preferences_) {i.second = 1;}
        for(auto &i : preferences_){ i.second /= static_cast<double>(preferences_.size());}
    }
}
