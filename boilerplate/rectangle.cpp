
struct rect {
    int x1, y1, x2, y2;
    
    rect(int x1, int y1, int x2, int y2) : x1{x1}, y1{y1}, x2{x2}, y2{y2} {};
    
    int area() {
        return (y2 - y1) * (x2 - x1);
    }
};

int main() {
    rect r(0, 1, 1, 0);
}