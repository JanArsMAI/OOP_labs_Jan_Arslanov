#include "../include/figure.h"

std::ostream& operator<< (std::ostream& os, const Figure &figure) {
    return figure.output(os);
}

std::istream& operator>> (std::istream& is, Figure &figure) {
    return figure.input(is);
}