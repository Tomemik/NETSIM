#ifndef NETSIM_STORAGE_TYPES_HPP
#define NETSIM_STORAGE_TYPES_HPP

#include "types.hpp"
#include "package.hpp"

enum class PackageQueueType
{
    FIFO,
    LIFO
};


class IPackageStockpile
{
public:
    using const_iterator = std::list<Package>::const_iterator;

    virtual void push(const Package& package) = 0;

    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;

    virtual size_t size() const = 0;
    virtual bool empty() const = 0;

    virtual ~IPackageStockpile() = default; //
};

class IPackageQueue : public IPackageStockpile
{
public:
    virtual Package pop() = 0;

    virtual PackageQueueType get_queue_type() const;
};

class PackageQueue : public IPackageQueue
{
public:
    PackageQueue(PackageQueueType queueType);

    void push(const Package& package) override;
    const_iterator cbegin() const override;
    const_iterator cend() const override;
    const_iterator begin() const override;
    const_iterator end() const override;
    size_t size() const override;
    bool empty() const override;

    Package pop() override;
    PackageQueueType get_queue_type() const override;

private:
    std::list<Package> queue_;
    PackageQueueType queueType_;
};
#endif
