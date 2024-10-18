#include "../include/triangle.h"
#include "../include/point.h"

Triangle::Triangle(const Point list_of_points[3]){
    for (size_t i=0; i <= 2; ++i){
        this->points[i] = list_of_points[i];
    }
    is_valid_or_not();
}
bool Triangle::is_valid_or_not() const{
    const Point first_point = this->points[0];
    const Point second_point = this->points[1];
    const Point third_point = this->points[2];
    if ((first_point.x == second_point.x && second_point.x == third_point.x && first_point.x == third_point.x) || (first_point.y == second_point.y && second_point.y == third_point.y && first_point.y == third_point.y)){
        throw std::invalid_argument("all points are on the one line, impossible to make a triangle");
    }

    check_for_equal_points(first_point, second_point, third_point);

    double first_side = sqrt(pow(abs(first_point.x - second_point.x), 2) + pow(abs(first_point.y - second_point.y), 2));
    double second_side = sqrt(pow(abs(first_point.x - third_point.x), 2) + pow(abs(first_point.y - third_point.y), 2));
    double third_side = sqrt(pow(abs(second_point.x - third_point.x), 2) + pow(abs(second_point.y - third_point.y), 2));
    if ((first_side >= second_side + third_side) || (second_side >= first_side + third_side) || (third_side >= first_side + second_side)){
        throw std::invalid_argument("it's impossible to make a triangle from this points");
    }
    return true;
}

bool Triangle::check_for_equal_points(const Point& point_1, const Point& point_2, const Point& point_3) const{
    if ((point_1.x == point_2.x && point_1.y == point_2.y) || (point_1.x == point_3.x && point_1.y == point_3.y) || (point_3.x == point_2.x && point_3.y == point_2.y)){
        throw std::invalid_argument("you are trying to make a triangle from the same points. it's impossible");
    }
    return true;
}

Triangle &Triangle::operator=(const Triangle& other_triangle){
    if (this != &other_triangle){
        for (size_t i = 0; i <= 2; ++i){
            this->points[i] = other_triangle.points[i];
        }
    }
    return *this;
}

Triangle &Triangle::operator=(Triangle&& other_triangle) noexcept{
    if (this != &other_triangle)
    {
        for (int i = 0; i < 3; ++i)
        {
            points[i] = std::move(other_triangle.points[i]);
        }
    }
    return *this;
}


bool Triangle::operator==(const Figure &other) const{
    const Triangle* other_triangle = dynamic_cast<const Triangle *>(&other);
    if (!other_triangle) {
        return false;
    }
    for (size_t i = 0; i < 3; ++i){
        if ((this->points[i].x != other_triangle->points[i].x) || (this->points[i].y != other_triangle->points[i].y)) {
            return false;
        }
    }
    return true;
}

Point Triangle::center() const{
    double x = 0.0;
    double y = 0.0;
    for (size_t i = 0; i <= 2; ++i){
        x += this->points[i].x;
        y += this->points[i].y;
    }
    x = x / 3;
    y = y / 3;
    const Point answer_point(x, y);
    return answer_point;
}

void Triangle::get_data() const
{
    std::cout << *this << std::endl;
}

Triangle::operator double() const
{
    const Point first_point = this->points[0];
    const Point second_point = this->points[1];
    const Point third_point = this->points[2];
    double first_side = sqrt((first_point.x - second_point.x) * (first_point.x - second_point.x) +
                             (first_point.y - second_point.y) * (first_point.y - second_point.y));
    double second_side = sqrt((first_point.x - third_point.x) * (first_point.x - third_point.x) +
                              (first_point.y - third_point.y) * (first_point.y - third_point.y));
    double third_side = sqrt((second_point.x - third_point.x) * (second_point.x - third_point.x) +
                             (second_point.y - third_point.y) * (second_point.y - third_point.y));
    double half_perimeter = (first_side + second_side + third_side) / 2;
    double area = sqrt(half_perimeter * (half_perimeter - first_side) * 
                       (half_perimeter - second_side) * 
                       (half_perimeter - third_side));

    return area;
}

std::ostream &Triangle::output(std::ostream &os) const {
    os << "Triangle points :";
    for (const auto &point : points) {
        os << point << " ";
    }
    return os;
}

std::istream &Triangle::input(std::istream &is) {
    Point temp_points[3];
    for (int i = 0; i < 3; ++i) {
        is >> temp_points[i];
    }
    if (is.fail()) {
        throw std::invalid_argument("Error. Expected 3 points.");
    }
    for (int i = 0; i < 3; ++i) {
        points[i] = temp_points[i];
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Triangle &object) {
    return object.output(os);
}

std::istream &operator>>(std::istream &is, Triangle &object) {
    return object.input(is);
}