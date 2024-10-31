#include <iostream>
#include "./src/rectangle.cpp"
#include "./src/triangle.cpp"
#include "./src/square.cpp"
#include "./src/array.cpp"

void add_rectangle(Array<Figure<double>>& figures) {
    Rectangle<double> rect;
    std::cout << "Enter the points of rectangle:\n";
    std::cin >> rect;
    figures.push_back(std::make_shared<Rectangle<double>>(rect));
}
void add_triangle(Array<Figure<double>>& figures) {
    Triangle<double> tr;
    std::cout << "Enter the points of triangle:\n";
    std::cin >> tr;
    figures.push_back(std::make_shared<Triangle<double>>(tr));
}
void add_square(Array<Figure<double>>& figures) {
    Square<double> square;
    std::cout << "Enter the points of triangle:\n";
    std::cin >> square;
    figures.push_back(std::make_shared<Square<double>>(square));
}

void remove_figure(Array<Figure<double>>& figures) {
    size_t index;
    std::cout << "Enter the index of deleting: ";
    if (!(std::cin >> index) || index >= figures.get_size()) {
        std::cout << "Error. No element on this index.\n";
        return;
    }
    figures.remove(index);
}

void print_all_figures(const Array<Figure<double>>& figures) {
    for (size_t i = 0; i < figures.get_size(); ++i) {
        figures[i]->get_data();
    }
}

void calculate_total_area(const Array<Figure<double>>& figures) {
    double totalArea = 0;
    for (size_t i = 0; i < figures.get_size(); ++i) {
        totalArea += static_cast<double>(*figures[i]);
    }
    std::cout << "Area of Array: " << totalArea << std::endl;
}

int main() {
    Array<Figure<double>> figures;

    while (true) {
        std::cout << "\ncommand <1> - Add triangle\n"
                  << "command <2> - Add rectangle\n"
                  << "command <3> - Add square\n"
                  << "command <4> -Print area of array\n"
                  << "command <5> - Get info of array\n"
                  << "command <6> - Delete figure\n"
                  << "command <7> - exit\n"
                  << "Choose option: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Try again, incorrect option.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                add_triangle(figures);
                break;
            case 2:
                add_rectangle(figures);
                break;
            case 3:
                add_square(figures);
                break;
            case 4:
                calculate_total_area(figures);
                break;
            case 5:
                print_all_figures(figures);
                break;
            case 6:
                remove_figure(figures);
                break;
            case 7:
                return 0;
            default:
                std::cout << "Incorrect option, try again.\n";
                break;
        }
    }

    return 0;
}