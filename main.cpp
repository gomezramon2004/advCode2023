#include "./functions/functions.hpp"
#include <iostream>

int main() {

    // Disable synchronization between C and C++ standard streams
    std::ios_base::sync_with_stdio(false);

    //std::cout << adv1First("./textfiles/in1.txt") << "\n";
    //std::cout << adv1Last("./textfiles/in1.txt") << "\n";
    //std::cout << adv2First("./textfiles/in2.txt") << "\n";
    //std::cout << adv2Last("./textfiles/in2.txt") << "\n";
    //std::cout << adv3First("./textfiles/in3.txt") << "\n";
    //std::cout << adv3Last("./textfiles/in3.txt") << "\n";
    //std::cout << adv4First("./textfiles/in4.txt") << "\n";
    //std::cout << adv4Last("./textfiles/in4.txt") << "\n";
    //std::cout << adv5First("./textfiles/in5.txt") << "\n";
    //std::cout << adv5Last("./textfiles/in5.txt") << "\n";
    //std::cout << adv6First("./textfiles/in6.txt") << "\n";
    //std::cout << adv6Last("./textfiles/in6.txt") << "\n";
    //std::cout << adv7First("./textfiles/in7.txt") << "\n";
    std::cout << adv7Last("./textfiles/in7.txt") << "\n";

    return 0;
}