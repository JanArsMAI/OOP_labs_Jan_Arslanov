#include <iostream>
#include "./src/rectangle.cpp"
#include "./src/square.cpp"
#include "./src/triangle.cpp"

int main()
{
    Point triangle_pt[3] = {
        {0.0, 1.0},
        {1.0, 0.0},
        {0.0, -1.0}};
    Triangle triangle_1(triangle_pt);
    std::cout << "center of triangle " << triangle_1.center() << std::endl;
    std::cout << "area of triangle " << static_cast<double>(triangle_1) << std::endl;
    Point triangle_pt_2[3] = {
        {0.0, 1.0},
        {1.0, 0.0},
        {0.0, -1.0}};
    Triangle triangle_2(triangle_pt_2);
    if (triangle_2 == triangle_1){
        std::cout << "these triangles are equal" << std::endl;
    }
    else{
        std::cout << "they are not equal" << std::endl;
    }
    std::cout << "---------------------------------------------------------------------" << std::endl;
    Point square_pt[4] = {
        {1.0, 0.0},
        {1.0, 1.0},
        {2.0, 1.0},
        {2.0, 0.0},
        };
    Square square_1(square_pt);
    std::cout << "center of triangle " << square_1.center() << std::endl;
    std::cout << "area of triangle " << static_cast<double>(square_1) << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;
    Point rectangle_pt[4] = {
        {1.0, 0.0},
        {1.0, 5.0},
        {3.0, 5.0},
        {3.0, 0.0}};
    Rectangle rectangle_1(rectangle_pt);
    std::cout << "center of triangle " << rectangle_1.center() << std::endl;
    std::cout << "area of triangle " << static_cast<double>(rectangle_1) << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;

    Figure *arr[] = {&triangle_1,&square_1,&rectangle_1,};

    for (auto value : arr)
    {
        value->get_data();
    }

    return 0;
}