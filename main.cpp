#include <iostream>
#include "package.hpp"
#include "storage_types.hpp"


int main() {

    PackageQueue fifo(PackageQueueType::FIFO);
    PackageQueue lifo(PackageQueueType::LIFO);

    fifo.push(Package(1));
    fifo.push(Package(2));
    fifo.push(Package(3));
    fifo.push(Package(4));

    lifo.push(Package(1));
    lifo.push(Package(2));
    lifo.push(Package(3));
    lifo.push(Package(4));

    if(fifo.pop().get_id() == 1 && fifo.pop().get_id() == 2 && fifo.pop().get_id() == 3 && fifo.pop().get_id() == 4){
        std::cout<<"fifo dziala poprawnie"<<std::endl;
    }
    if(lifo.pop().get_id() == 4 && lifo.pop().get_id() == 3 && lifo.pop().get_id() == 2 && lifo.pop().get_id() == 1){
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
