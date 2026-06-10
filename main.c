#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 50
#define HEIGHT 20
#define MAX_SHAPES 50

typedef enum { SHAPE_LINE = 1, SHAPE_RECT, SHAPE_CIRCLE, SHAPE_TRIANGLE } ShapeType;

typedef struct {
    int id;
    int active;
    ShapeType type;
    char draw_char;
    int x1, y1;
    int x2, y2;
    int x3, y3; // For triangle
    int w, h;   // For rectangle
    int r;      // For circle
} Shape;

char grid[HEIGHT][WIDTH];
Shape shapes[MAX_SHAPES];
int shape_count = 0;
int next_id = 1;
char bg_char = '_';

void clear_grid() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            grid[y][x] = bg_char;
        }
    }
}

void set_pixel(int x, int y, char ch) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        grid[y][x] = ch;
    }
}

void draw_line(int x1, int y1, int x2, int y2, char ch) {
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1) {
        set_pixel(x1, y1, ch);
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void draw_rect(int x, int y, int w, int h, char ch) {
    if (w <= 0 || h <= 0) return;
    for (int i = 0; i < w; ++i) {
        set_pixel(x + i, y, ch);
        set_pixel(x + i, y + h - 1, ch);
    }
    for (int j = 0; j < h; ++j) {
        set_pixel(x, y + j, ch);
        set_pixel(x + w - 1, y + j, ch);
    }
}

void draw_circle(int cx, int cy, int r, char ch) {
    if (r < 0) return;
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    
    while (y >= x) {
        set_pixel(cx + x, cy + y, ch);
        set_pixel(cx - x, cy + y, ch);
        set_pixel(cx + x, cy - y, ch);
        set_pixel(cx - x, cy - y, ch);
        set_pixel(cx + y, cy + x, ch);
        set_pixel(cx - y, cy + x, ch);
        set_pixel(cx + y, cy - x, ch);
        set_pixel(cx - y, cy - x, ch);
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, char ch) {
    draw_line(x1, y1, x2, y2, ch);
    draw_line(x2, y2, x3, y3, ch);
    draw_line(x3, y3, x1, y1, ch);
}

void render_all() {
    clear_grid();
    for (int i = 0; i < shape_count; ++i) {
        if (!shapes[i].active) continue;
        char ch = shapes[i].draw_char;
        switch (shapes[i].type) {
            case SHAPE_LINE:
                draw_line(shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2, ch);
                break;
            case SHAPE_RECT:
                draw_rect(shapes[i].x1, shapes[i].y1, shapes[i].w, shapes[i].h, ch);
                break;
            case SHAPE_CIRCLE:
                draw_circle(shapes[i].x1, shapes[i].y1, shapes[i].r, ch);
                break;
            case SHAPE_TRIANGLE:
                draw_triangle(shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2, shapes[i].x3, shapes[i].y3, ch);
                break;
        }
    }
}

void display_grid() {
    printf(" +");
    for (int x = 0; x < WIDTH; ++x) printf("-");
    printf("+\n");

    for (int y = 0; y < HEIGHT; ++y) {
        printf(" |");
        for (int x = 0; x < WIDTH; ++x) {
            printf("%c", grid[y][x]);
        }
        printf("|\n");
    }

    printf(" +");
    for (int x = 0; x < WIDTH; ++x) printf("-");
    printf("+\n");
}

void print_shapes() {
    printf("\n--- Active Objects ---\n");
    int active_found = 0;
    for (int i = 0; i < shape_count; ++i) {
        if (!shapes[i].active) continue;
        active_found = 1;
        printf("  [ID: %d] ", shapes[i].id);
        switch (shapes[i].type) {
            case SHAPE_LINE:
                printf("Line from (%d, %d) to (%d, %d) using '%c'\n", shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2, shapes[i].draw_char);
                break;
            case SHAPE_RECT:
                printf("Rectangle at (%d, %d), size %dx%d using '%c'\n", shapes[i].x1, shapes[i].y1, shapes[i].w, shapes[i].h, shapes[i].draw_char);
                break;
            case SHAPE_CIRCLE:
                printf("Circle centered at (%d, %d), radius %d using '%c'\n", shapes[i].x1, shapes[i].y1, shapes[i].r, shapes[i].draw_char);
                break;
            case SHAPE_TRIANGLE:
                printf("Triangle vertices (%d, %d), (%d, %d), (%d, %d) using '%c'\n", shapes[i].x1, shapes[i].y1, shapes[i].x2, shapes[i].y2, shapes[i].x3, shapes[i].y3, shapes[i].draw_char);
                break;
        }
    }
    if (!active_found) {
        printf("  (No objects in the picture)\n");
    }
}

int get_int(const char *prompt, int *val) {
    char buf[128];
    printf("%s", prompt);
    if (!fgets(buf, sizeof(buf), stdin)) return 0;
    return sscanf(buf, "%d", val) == 1;
}

void get_char(const char *prompt, char *val, char def) {
    char buf[128];
    printf("%s", prompt);
    if (!fgets(buf, sizeof(buf), stdin)) {
        *val = def;
        return;
    }
    int idx = 0;
    while (buf[idx] == ' ' || buf[idx] == '\t') idx++;
    if (buf[idx] == '\n' || buf[idx] == '\0') {
        *val = def;
    } else {
        *val = buf[idx];
    }
}

int main() {
    int choice;
    while (1) {
        // Clear terminal screen using ANSI escape code
        printf("\033[H\033[J");
        
        printf("==================================================\n");
        printf("               2D GRAPHICS EDITOR                 \n");
        printf("==================================================\n\n");
        
        render_all();
        display_grid();
        print_shapes();
        
        printf("\nMENU:\n");
        printf(" 1. Add Shape\n");
        printf(" 2. Modify Shape\n");
        printf(" 3. Delete Shape\n");
        printf(" 4. Exit\n");
        
        if (!get_int("\nEnter choice (1-4): ", &choice)) {
            continue;
        }
        
        if (choice == 4) {
            printf("\nExiting editor. Goodbye!\n");
            break;
        }
        
        if (choice == 1) {
            int stype;
            printf("\nShape Types: 1.Line | 2.Rectangle | 3.Circle | 4.Triangle\n");
            if (!get_int("Select shape type (1-4): ", &stype) || stype < 1 || stype > 4) {
                printf("Invalid type! Press Enter to continue...");
                getchar();
                continue;
            }
            if (shape_count >= MAX_SHAPES) {
                printf("Maximum shape limit reached! Press Enter to continue...");
                getchar();
                continue;
            }
            
            Shape s;
            s.id = next_id++;
            s.active = 1;
            s.type = (ShapeType)stype;
            s.draw_char = '*';
            
            if (stype == 1) {
                printf("Line coordinates:\n");
                get_int("  x1: ", &s.x1);
                get_int("  y1: ", &s.y1);
                get_int("  x2: ", &s.x2);
                get_int("  y2: ", &s.y2);
            } else if (stype == 2) {
                printf("Rectangle coordinates:\n");
                get_int("  Top-Left x: ", &s.x1);
                get_int("  Top-Left y: ", &s.y1);
                get_int("  Width: ", &s.w);
                get_int("  Height: ", &s.h);
            } else if (stype == 3) {
                printf("Circle coordinates:\n");
                get_int("  Center x: ", &s.x1);
                get_int("  Center y: ", &s.y1);
                get_int("  Radius: ", &s.r);
            } else if (stype == 4) {
                printf("Triangle coordinates:\n");
                get_int("  x1: ", &s.x1);
                get_int("  y1: ", &s.y1);
                get_int("  x2: ", &s.x2);
                get_int("  y2: ", &s.y2);
                get_int("  x3: ", &s.x3);
                get_int("  y3: ", &s.y3);
            }
            get_char("  Draw character (default '*'): ", &s.draw_char, '*');
            shapes[shape_count++] = s;
        } 
        else if (choice == 2) {
            int id, found = -1;
            if (!get_int("Enter shape ID to modify: ", &id)) continue;
            for (int i = 0; i < shape_count; ++i) {
                if (shapes[i].active && shapes[i].id == id) {
                    found = i;
                    break;
                }
            }
            if (found == -1) {
                printf("Shape not found! Press Enter to continue...");
                getchar();
                continue;
            }
            
            Shape *s = &shapes[found];
            printf("Modifying shape ID %d. Enter new parameters:\n", id);
            if (s->type == SHAPE_LINE) {
                get_int("  x1: ", &s->x1); get_int("  y1: ", &s->y1);
                get_int("  x2: ", &s->x2); get_int("  y2: ", &s->y2);
            } else if (s->type == SHAPE_RECT) {
                get_int("  Top-Left x: ", &s->x1); get_int("  Top-Left y: ", &s->y1);
                get_int("  Width: ", &s->w); get_int("  Height: ", &s->h);
            } else if (s->type == SHAPE_CIRCLE) {
                get_int("  Center x: ", &s->x1); get_int("  Center y: ", &s->y1);
                get_int("  Radius: ", &s->r);
            } else if (s->type == SHAPE_TRIANGLE) {
                get_int("  x1: ", &s->x1); get_int("  y1: ", &s->y1);
                get_int("  x2: ", &s->x2); get_int("  y2: ", &s->y2);
                get_int("  x3: ", &s->x3); get_int("  y3: ", &s->y3);
            }
            get_char("  Draw character (default '*'): ", &s->draw_char, '*');
        } 
        else if (choice == 3) {
            int id, found = -1;
            if (!get_int("Enter shape ID to delete: ", &id)) continue;
            for (int i = 0; i < shape_count; ++i) {
                if (shapes[i].active && shapes[i].id == id) {
                    found = i;
                    break;
                }
            }
            if (found == -1) {
                printf("Shape not found!\n");
            } else {
                shapes[found].active = 0;
                printf("Shape successfully deleted!\n");
            }
            printf("Press Enter to continue...");
            getchar();
        }
    }
    return 0;
}