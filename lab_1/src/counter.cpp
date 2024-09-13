#include "../include/counter.h"
#include <string>

int to_binary(int a) {
    std::string ans = "";
    int num = 0;
    while (a != 0) {
        ans += std::to_string(a % 2);
        a = a / 2;
    }
    for (auto i = ans.end() - 1; i != ans.begin() - 1; i--) {
        if (*(i) == '1') {
            ++num;
        }
    }
    return num;
}

int counter(int a, int b){
    int answer = 0;
    for (int i = a; i <= b; ++i){
        answer += to_binary(i);
    }
    return answer;
}