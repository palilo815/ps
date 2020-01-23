class Rectangle {
private:
    int width;
    int height;
public:
    Rectangle(int width, int height) {
        this->width = width;
        this->height = height;
    }
    int get_width() const {
        return this->width;
    }
    int get_height() const {
        return this->height;
    }
    void set_width(int width) {
        if (width > 0 && width <= 1000)
            this->width = width;
    }
    void set_height(int height) {
        if (height > 0 && height <= 2000)
            this->height = height;
    }
    int area() const {
        return this->width * this->height;
    }
    int perimeter() const {
        return 2 * (this->width + this->height);
    }
    bool is_square() const {
        return this->width == this->height;
    }
};