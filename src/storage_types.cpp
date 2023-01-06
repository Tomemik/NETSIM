#include "package.hpp"
#include "types.hpp"
#include "storage_types.hpp"

PackageQueue::PackageQueue(PackageQueueType queueType) : queueType_(queueType){}

void PackageQueue::push(const Package& package){
    queue_.emplace_back(std::move(package));
}

PackageQueue::const_iterator PackageQueue::cbegin() const{
    return queue_.cbegin();

}
PackageQueue::const_iterator PackageQueue::cend() const{
    return queue_.cend();
}

PackageQueue::const_iterator PackageQueue::begin() const{
    return queue_.begin();
}

PackageQueue::const_iterator PackageQueue::end() const{
    return queue_.end();
}

size_t PackageQueue::size() const{
    return queue_.size();
}

bool PackageQueue::empty() const {
    return queue_.empty();
}

Package PackageQueue::pop()
{
    if (queueType_ == PackageQueueType::LIFO)
    {
        Package package = std::move(queue_.back());)
        m_queue.pop_back();
        return package;
    }
    else
    {
        Package package = std::move(queue_.front());
        queue_.pop_front();
        return package;
    }
}

PackageQueueType PackageQueue::get_queue_type() const
{
    return queueType_;
}