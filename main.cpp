#include <iostream>
#include "package.hpp"
#include "storage_types.hpp"


int main() {
    Package p1(1);
    Package p2;
    Package p3;
    Package p4;
    p2 = 5;
    Package p5;

    std::cout<<p1.get_id()<<std::endl;
    std::cout<<p2.get_id()<<std::endl;
    std::cout<<p5.get_id()<<std::endl;

    PackageQueue fifo(PackageQueueType::FIFO);
    PackageQueue lifo(PackageQueueType::LIFO);

    fifo.push(p1);
    fifo.push(p2);
    fifo.push(p3);
    fifo.push(p4);

    lifo.push(p1);
    lifo.push(p2);
    lifo.push(p3);
    lifo.push(p4);

    if(fifo.pop().get_id() == p1.get_id() && fifo.pop().get_id() == p2.get_id() && fifo.pop().get_id() == p3.get_id() && fifo.pop().get_id() == p4.get_id()){
        std::cout<<"fifo dziala poprawnie"<<std::endl;
    }
    if(lifo.pop().get_id() == p4.get_id() && lifo.pop().get_id() == p3.get_id() && lifo.pop().get_id() == p2.get_id() && lifo.pop().get_id() == p1.get_id()){
        std::cout<<"lifo dziala poprawnie"<<std::endl;
    }

    PackageQueueType t1 = fifo.get_queue_type();
    PackageQueueType t2 = lifo.get_queue_type();
    if(t1 == PackageQueueType::FIFO){
        std::cout<<"FIFO"<<std::endl;
    }
    if(t2 == PackageQueueType::LIFO){
        std::cout<<"LIFO"<<std::endl;
    }

}
