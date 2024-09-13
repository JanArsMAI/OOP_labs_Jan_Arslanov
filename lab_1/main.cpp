#include <iostream>
#include "include/counter.h"

int main(){
    int a=0, b=0;
    std::cin >> a >> b;
    if ((a > 0) && (a > b)){
        std::cout << "Incorrect numbers, try to input first number greater than the second(0 <= a <= b)";
    }
    else{
        std::cout << counter(a, b) << std::endl;
    }
    
    return 0;
}