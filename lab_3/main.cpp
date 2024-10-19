#include <iostream>
#include "./src/rectangle.cpp"
#include "./src/square.cpp"
#include "./src/triangle.cpp"
#include <string>

void add_figure(Figure **list_of_figures, int &size, int &capacity);
void delete_figure(Figure **list_of_figures, int &size, const int &capacity);
void print_info(Figure **list_of_figures, int &size, const int &capacity);
void get_area(Figure **list_of_figures, int &size, const int &capacity);
void destruct_list(Figure **list_of_figures, int &size, int &capacity) noexcept;

int main() {
    int current_size = 0;
    int capacity = 0;
    std::cout << "Enter capacity value: ";
    std::cin >> capacity;
    while (capacity <= 0) {
        std::cout << "Capacity must be more than 0: ";
        std::cin >> capacity;
    }

    Figure **list_of_figures = new Figure*[capacity];

    bool working_now = true;
    while (working_now) {
        std::cout << "Commands: exit, add_figure, delete_figure, print_info, get_area" << std::endl;
        std::string command;
        std::cin >> command;

        if (command == "exit") {
            std::cout << "Finishing executing..." << std::endl;
            working_now = false;
        } else if (command == "add_figure") {
            add_figure(list_of_figures, current_size, capacity);
        } else if (command == "delete_figure") {
            delete_figure(list_of_figures, current_size, capacity);
        } else if (command == "print_info") {
            print_info(list_of_figures, current_size, capacity);
        } else if (command == "get_area") {
            get_area(list_of_figures, current_size, capacity);
        } else {
            std::cout << "Wrong command, try again." << std::endl;
        }
    }

    destruct_list(list_of_figures, current_size, capacity);
}

void add_figure(Figure **list_of_figures, int &size, int &capacity) {
    if (size >= capacity) {
        std::cout << "Unable to add figure, list is full." << std::endl;
        return;
    }

    Figure *current_figure = nullptr;
    std::string type_of_figure;

    while (true) {
        std::cout << "Choose figure type: t (triangle), r (rectangle), s (square)" << std::endl;
        std::cin >> type_of_figure;

        if (type_of_figure == "t") {
            current_figure = new Triangle();
            break;
        } else if (type_of_figure == "r") {
            current_figure = new Rectangle();
            break;
        } else if (type_of_figure == "s") {
            current_figure = new Square();
            break;
        } else {
            std::cout << "Invalid input, please try again." << std::endl;
        }
    }

    try {
        std::cin >> *current_figure;
        list_of_figures[size++] = current_figure; // Increment size after adding
        std::cout << "Figure added successfully!" << std::endl;
    } catch (const std::exception &e) {
        delete current_figure; // Ensure we clean up on failure
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void delete_figure(Figure **list_of_figures, int &size, const int &capacity) {
    if (size <= 0) {
        std::cout << "List is empty, unable to delete." << std::endl;
        return;
    }

    int index = -1;
    while (index < 0 || index >= size) {
        std::cout << "Enter index to delete (0-" << size - 1 << "): ";
        std::cin >> index;
    }

    delete list_of_figures[index];
    for (int i = index; i < size - 1; ++i) {
        list_of_figures[i] = list_of_figures[i + 1];
    }
    list_of_figures[--size] = nullptr; // Clear last element

    std::cout << "Figure deleted successfully!" << std::endl;
}

void print_info(Figure **list_of_figures, int &size, const int &capacity) {
    for (int i = 0; i < size; ++i) {
        std::cout << "Figure at index " << i << ":" << std::endl;
        std::cout << *list_of_figures[i] << std::endl;
        std::cout << "Center: " << list_of_figures[i]->center() << std::endl;
        std::cout << "Area: " << static_cast<double>(*list_of_figures[i]) << std::endl << std::endl;
    }
}

void get_area(Figure **list_of_figures, int &size, const int &capacity) {
    double total_area = 0;
    for (int i = 0; i < size; ++i) {
        total_area += static_cast<double>(*list_of_figures[i]);
    }
    std::cout << "Total area: " << total_area << std::endl;
}

void destruct_list(Figure **list_of_figures, int &size, int &capacity) noexcept {
    for (int i = 0; i < size; ++i) {
        delete list_of_figures[i];
    }
    delete[] list_of_figures;
    size = 0;
    capacity = 0;
}
