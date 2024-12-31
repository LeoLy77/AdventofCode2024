#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int NUM_COLS = 130;
const int NUM_ROWS = 130;

typedef struct Position {
    int x;
    int y;
} Position;

typedef enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT,
} Direction;

typedef struct Guard {
    Position pos;
    Direction dir;
    bool game_over;
} Guard;

void loadFile(char** matrix, Guard* g) {
    FILE* file = fopen("input.txt", "r");
    for (int line_cnt = 0; line_cnt < NUM_ROWS; line_cnt++) {
        if (fgets(matrix[line_cnt], NUM_COLS + 2, file) == NULL) {
            fclose(file);
            for (int j = 0; j <= line_cnt; j++) {
                free(matrix[j]);
            }
            free(matrix);
        }

        matrix[line_cnt][strcspn(matrix[line_cnt], "\n")] = '\0';
        char* found_pos = strchr(matrix[line_cnt], '^') ;
        if (found_pos != NULL) {
            size_t index = found_pos - matrix[line_cnt];
            g->pos.x = (int) index;
            g->pos.y = line_cnt;
        }
    }
    fclose(file);
}

void cleanUp(char** matrix) {
    for (int i = 0; i < NUM_ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void reverseString(char *str) {
    size_t len = strlen(str);
    size_t start = 0, end = len - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}

int getCoverage(char** matrix, Guard* g) {
    int step_cnt = 0;
    int y = g->pos.x;
    int x = g->pos.y;

    if (x < 0 || x >= NUM_ROWS || y < 0 || y >= NUM_COLS) {
        g->game_over = true;
        printf("GAME OVER\n");
        return step_cnt;
    }

    if (matrix[x][y] == '#') {
        printf("BONG %d %d @ %c \n", x, y, matrix[x][y]);
        // printf("%s\n", matrix[x]);
        switch (g->dir) {
            case UP:
                g->pos.y++;
                break;
            case RIGHT:
                g->pos.x--;
                break;
            case DOWN:
                g->pos.y--;
                break;
            case LEFT:
                g->pos.x++;
                break;
        }
        g->dir = (g->dir + 1) % 4; 
    } else {
        if (matrix[x][y] != 'X') {
            matrix[x][y] = 'X';
            step_cnt++;
        }
    }
    switch (g->dir) {
        case UP:
            g->pos.y--;
            break;
        case RIGHT:
            g->pos.x++;
            break;
        case DOWN:
            g->pos.y++;
            break;
        case LEFT:
            g->pos.x--;
            break;
    }

    return step_cnt;
}

int main(char argc, char** argv) {
    bool do_part1 = false;
    char** matrix = (char**) malloc(sizeof(char*) * NUM_ROWS);
    for (int i = 0; i < NUM_ROWS; i++) {
        matrix[i] = (char*) malloc(sizeof(char) * (NUM_COLS + 1));
    }

    Guard g;
    g.dir = UP;
    g.game_over = false;

    loadFile(matrix, &g);
    printf("Guard pos %d %d\n", g.pos.x, g.pos.y);
    if (do_part1) {
        int sum = 0;
        while(!g.game_over) {
            printf("Guard pos (%d %d) | Dir = %d | Sum = %d\n", g.pos.x, g.pos.y, g.dir, sum);
            sum += getCoverage(matrix, &g);
        }

        printf("Sum = %d\n", sum);
    }
    
    cleanUp(matrix);

    return 0;
}