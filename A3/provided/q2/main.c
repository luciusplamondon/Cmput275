#include "maze.h"
#include <stdio.h>
/*
 * This is the main that will use your main ADT.
 * It begins by calling your readMaze function to read
 * the maze in, and then continues by reading commands
 * from standard input from the user. The command
 * the user can give are as follows;
 *    p - to print the maze.
 *    q - to end the program.
 *    m - to make a move, the m must be followed by n, e, s, or w.
 *    r - to reset the maze by calling your reset function.
 * After reading all commands from the user your 
 * destroyMaze function is then called to clean up the maze.
*/
struct Maze {
    char **grid;
    int width;
    int height;
    struct Pos player;
    struct Pos start;
};



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
}

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