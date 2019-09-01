#include "../include/intf.hpp"

int main()
{
    intf intf_instance = "2099999999";
    int int_instance = intf_instance;
    double double_instance_1 = intf_instance;
    double double_instance_2 = int(intf_instance);
    std::cout<<"intf_instance: "<<intf_instance<<std::endl
             <<"int_instance: "<<int_instance<<std::endl
             <<"double_instance_1: "<<double_instance_1<<std::endl
             <<"double_instance_2: "<<double_instance_2<<std::endl;
    intf intf_instance_2 = "20999999990";
    int int_instance_2 = intf_instance_2;
}
