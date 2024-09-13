#include "../include/counter.h"
#include <sstream>

int to_binary(int a) {
    std::stringstream ans;
    int num = 0;
    while (a != 0) {
        ans << (a % 2);
        a /= 2;
    }
    char current;
    while (ans >> current) {
        if (current == '1') {
            ++num;
        }
    }
    return num;
}

int counter(int a, int b) {
    int answer = 0;
    for (int i = a; i <= b; ++i) {
        answer += to_binary(i);
    }
    return answer;
}