#include "./functions/functions.hpp"

int main() {

    std::cout << adv1First("./textfiles/in1.txt") << "\n";
    std::cout << adv1Last("./textfiles/in1.txt") << "\n";
    std::cout << adv2First("./textfiles/in2.txt") << "\n";
    std::cout << adv2Last("./textfiles/in2.txt") << "\n";
    std::cout << adv3First("./textfiles/in3.txt") << "\n";
    std::cout << adv3Last("./textfiles/in3.txt") << "\n";

    return 0;
}