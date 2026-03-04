#include <stdio.h>

typedef struct {
    int x, y;
} Point;

void move(Point *p, int dx, int dy) {
    p->x += dx;
    p->y += dy;
}

int main(void) {
    Point p1 = {10, 20};
    move(&p1, 5, -10);
    printf("Yeni koordinatlar: (%d, %d)\n", p1.x, p1.y);
    return 0;
}
