#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"


/*======== void parse_file () ==========
Inputs:   char * filename 
          struct matrix * transform, 
          struct matrix * pm,
          screen s
Returns: 

Goes through the file named filename and performs all of the actions listed in that file.
The file follows the following format:
     Every command is a single character that takes up a line
     Any command that requires arguments must have those arguments in the second line.
     The commands are as follows:
         line: add a line to the edge matrix - 
	    takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
	 ident: set the transform matrix to the identity matrix - 
	 scale: create a scale matrix, 
	    then multiply the transform matrix by the scale matrix - 
	    takes 3 arguments (sx, sy, sz)
	 translate: create a translation matrix, 
	    then multiply the transform matrix by the translation matrix - 
	    takes 3 arguments (tx, ty, tz)
	 rotate: create an rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 2 arguments (axis, theta) axis should be x y or z
	 apply: apply the current transformation matrix to the 
	    edge matrix
	 display: draw the lines of the edge matrix to the screen
	    display the screen
	 save: draw the lines of the edge matrix to the screen
	    save the screen to a file -
	    takes 1 argument (file name)
	 quit: end parsing

See the file script for an example of the file format


IMPORTANT MATH NOTE:
the trig functions int math.h use radian mesure, but us normal
humans use degrees, so the file will contain degrees for rotations,
be sure to conver those degrees to radians (M_PI is the constant
for PI)
====================*/
void parse_file ( char * filename, 
                  struct matrix * transform, 
                  struct matrix * edges,
                  screen s) {

  FILE *f;
  char line[256];
  char axis;
  float sx, sy, sz;
  int x, y, z, x1, y1, z1, deg;

  color c;
  
  clear_screen(s);

  if ( strcmp(filename, "stdin") == 0 ) 
    f = stdin;
  else
    f = fopen(filename, "r");
  
  while ( fgets(line, 255, f) != NULL ) {
    line[strlen(line)-1]='\0';


    if (strcmp(line, "line") == 0) {
      printf("time to line\n");
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      sscanf(line, "%d %d %d %d %d %d", &x, &y, &z, &x1, &y1, &z1);
      printf("%d %d %d %d %d %d\n", x, y, z, x1, y1, z1);
      add_edge( edges, x, y, z, x1, y1, z1);
    }


    else if (strcmp(line, "ident") == 0) {
      printf("time to ident\n");
      //resets transform matrix
      ident(transform);
    }
    else if (strcmp(line, "scale") == 0) {
      printf("time to scale\n");
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      sscanf(line, "%f %f %f", &sx, &sy, &sz);
      printf("%f %f %f\n", sx, sy, sz);
      struct matrix * sc = make_scale(sx, sy, sz);
      matrix_mult(sc, transform);
      free_matrix(sc);
    }
    else if (strcmp(line, "move") == 0) {
      printf("time to move\n");
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      sscanf(line, "%d %d %d", &x, &y, &z);
      printf("%d %d %d\n", x, y, z);
      struct matrix * m = make_translate(x, y, z);
      matrix_mult(m, transform);
      free_matrix(m);
    }
    else if (strcmp(line, "rotate") == 0) {
      printf("time to rotate\n");
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      sscanf(line, "%c %d", &axis, &deg);
      printf("%c %d\n", axis, deg);

      //convert to radians
      float rad = deg * M_PI / 180;

      struct matrix * rot;
      
      if (axis == 'x') {
	rot = make_rotX(rad);
      } else if (axis == 'y') {
	rot = make_rotY(rad);
      } else if (axis == 'z') {
	printf("THIS IS THE RADIANS: %f\n", rad);
	rot = make_rotZ(rad);
      } else {
	printf("NOTHING");
      }

      matrix_mult(rot, transform);
      print_matrix(rot);
      rot = make_translate(70+deg, 0, 0);
      matrix_mult(rot, transform);
      free_matrix(rot);
    }

    else if (strcmp(line, "apply") == 0) {
      printf("time to apply\n");
      matrix_mult(transform, edges);
    }
    else if (strcmp(line, "display") == 0) {
      printf("time to display\n");
      clear_screen( s );
      draw_lines(edges, s, c);
      display( s );
    }
    else if (strcmp(line, "save") == 0) {
      printf("time to save\n");
      fgets(line, 255, f);
      line[strlen(line)]='\0';
      printf("Save in %s\n", line);
    }
    else {
      printf("ERROR :%s:\n",line);
    }
  }
}
  
