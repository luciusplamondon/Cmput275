#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"
struct Maze {
    char **grid;
    int width;
    int height;
    struct Pos player;
    struct Pos start;
};

struct Maze *readMaze() { //bug, when size is altered, everything else is alter must fix!!!!!!!
    struct Maze *m = malloc(sizeof(struct Maze));
    m->grid = NULL;
    m->height = 0;
    m->width = 0;

    char buffer[2001]; //according to the sample, max length is 2001
    int startCount = 0;
    int goalCount = 0;

    while (scanf("%s", buffer) == 1) {
        int len = strlen(buffer);
        m->width = len;

        m->grid = realloc(m->grid, sizeof(char *) * (m->height + 1)); //implement dynamically growing array !!!!!!
        m->grid[m->height] = malloc(len + 1); //allocate meory for the next line
        strcpy(m->grid[m->height], buffer);// copy the input value to the grid

        for (int i = 0; i < len; i++) { //scan through our copied input
            char c = m->grid[m->height][i];

            if (c == 'S') {
                m->start.x = i;
                m->start.y = m->height;
                m->player = m->start;
                startCount++;// make sure there are exactly 1 start location
            } else if (c == 'G') {
                goalCount++; //to make sure there are a goal in the maze
            } else if (c == 'O' || c == 'X' || c == 'I' || (c >= '0' && c <= '9')) {
                // These are valid characters, do nothing
                continue;
            } else {
                printf("Invalid character found when reading maze: %c - this is invalid input\n", c); //invalid characters, but not delete it, check sample
            }
        }
        m->height++;//increment height

        int ch = getchar(); 
        if (ch == '\n' || ch == '\r') {//since scanf skip whitespace, we have to check if /n is done twice
            int nextC = getchar();
            if (nextC == '\n' || nextC == '\r') break;
            ungetc(nextC, stdin); //find a way to not use this !!!!!!
        }
    }

    // Return NULL if: 
    // 1. Not exactly one start
    // 2. No goals
    if (startCount != 1 || goalCount < 1) {
        destroyMaze(m); 
        return NULL;
    }

    return m;
}
struct Pos find_other_teleporter(struct Maze *m, char digit, int curX, int curY, int oldX, int oldY) {
    for (int r = 0; r < m->height; r++) { //loop through row
        for (int c = 0; c < m->width; c++) { //lop through colum
            if (m->grid[r][c] == digit && (r != curY || c != curX)) { //check if digit are same
                return (struct Pos){c, r};//move position to that number
            }
        }
    }
    return (struct Pos){oldX, oldY}; // If nothing, return to original positon
}
struct Pos makeMove(struct Maze *m, char dir) {
    int dx = 0, dy = 0;
    if (dir == 'n') dy = -1;
    else if (dir == 's') dy = 1;
    else if (dir == 'e') dx = 1;
    else if (dir == 'w') dx = -1;

    int nextX = m->player.x + dx; //put newposition in a varibale to check if its viable
    int nextY = m->player.y + dy;

    // Boundary and Wall check
    if (nextY < 0 || nextY >= m->height || nextX < 0 || nextX >= m->width || m->grid[nextY][nextX] == 'X') {
        return m->player; //dont move, return to orginal spot
    }
    int oldX = m->player.x;
    int oldY = m->player.y;
    m->player.x = nextX; //its viable, update the position
    m->player.y = nextY;

    char tile = m->grid[m->player.y][m->player.x];

    // Goal Check
    if (tile == 'G') {
        return (struct Pos){-1, -1};//signal the win condition
    }

    // Teleporter Check
    if (tile >= '0' && tile <= '9') {
        m->player = find_other_teleporter(m, tile, m->player.x, m->player.y, oldX, oldY);// not really what i want, I want my character to not move if number isnt valid !!!!!
    } 
    // Icy Tile Logic
    else if (tile == 'I') {
        // Continue moving in same direction until non-ice or wall
        while (1) {
            int slipX = m->player.x + dx;
            int slipY = m->player.y + dy;

            if (slipY < 0 || slipY >= m->height || slipX < 0 || slipX >= m->width || m->grid[slipY][slipX] == 'X') {
                break; // Stop before wall/edge
            }
            int oldX = m->player.x; //hope this works, it makes non working teleporters as walls
            int oldY = m->player.y; //

            m->player.x = slipX;
            m->player.y = slipY;
            char nextTile = m->grid[m->player.y][m->player.x];
            
            if (nextTile == 'G') return (struct Pos){-1, -1};// if slid into goal, signal win
            if (nextTile >= '0' && nextTile <= '9') { //if slide into teleporter, teleport
                m->player = find_other_teleporter(m, nextTile, m->player.x, m->player.y, oldX, oldY);
                break; // Teleporting stops the "slide"
            }
            if (nextTile != 'I') break; // Landed on non-icy tile
        }
    }

    return m->player;//return position
}
void reset(struct Maze *m) { //reset the maze by simply setting the player to the start
    m->player = m->start;
}

void printMaze(struct Maze *m) {
    for (int i = 0; i < m->width + 2; i++) printf("="); //first line, print "="*width +2 because of the boarder
    printf("\n");

    for (int r = 0; r < m->height; r++) { //print each row
        printf("|"); // border
        for (int c = 0; c < m->width; c++) {// print each collon in that row
            if (r == m->player.y && c == m->player.x) printf("P"); //if the player is in that location, print P instead
            else printf("%c", m->grid[r][c]);// else, print the grid value at [r][c]
        }
        printf("|\n");
    }

    for (int i = 0; i < m->width + 2; i++) printf("=");// last line, print "="*width +2 because of the boarder
    printf("\n");
}
struct Maze *destroyMaze(struct Maze *m) {
    if (m) { //if maze is empty, do nothing
        for (int i = 0; i < m->height; i++) { //free each row one by one
            free(m->grid[i]);
        }
        free(m->grid);
        free(m);
    }
    return NULL;
}
// ************************************************************************************************************************************** DELETE AFTER USE
int whitespace(char c) {
  return c == ' ' || c == '\n' || c == '\n' || c == '\r';
}

char getNext() {
  char c = getchar();
  for (; whitespace(c); c = getchar());
  return c;
}

int main() {
  struct Maze *m = readMaze();
  if (m == NULL) {
    printf("Malformed maze.\n");
    return 0;
  }
  printf("Finished reading maze, enter commands\n");
  char cmd;
  char target;
  int done = 0;
  int win = 0;
  while (!done && !feof(stdin)) {
    cmd = getNext();
    if (cmd == EOF) break; // breaks loop
    switch (cmd) {
      case 'p':
        printMaze(m);
        break; // breaks switch
      case 'q':
        done = 1;
        break; // breaks switch
      case 'm':
        target = getNext();
        if (target == EOF) {
          done = 1;
          break; // breaks switch
        }
        if (target != 'n' && target != 'e' && target != 's' && target != 'w') {
          printf("Invalid move target: %c\n", target);
        } else {
          struct Pos p = makeMove(m, target);
          if (p.x == -1 && p.y == -1) {
            done = 1;
            win = 1;
          }
        }
        break;
      case 'r':
        reset(m);
        break;
      default:
        printf("Incorrect command: %c\n", cmd);
        break;
    }
  }
  if (win) {
    printf("Congrats you made it to the end of the maze!\n");
    printMaze(m);
  }
  m = destroyMaze(m);
  if (m != NULL) {
    printf("Error, your destroyMaze doesn't return NULL\n");
  }
}