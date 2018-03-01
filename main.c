#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"

int main(int argc, char **argv) {

  screen s;
  struct matrix * edges;
  struct matrix * transform;

  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);


  struct matrix * t = make_translate(3, 3, 3);
  print_matrix(t);
  free_matrix(t);
  struct matrix * sc = make_scale(2, 2, 2);
  print_matrix(sc);
  free_matrix(sc);
  struct matrix * x = make_rotX(60);
  print_matrix(x);
  free_matrix(x);
  struct matrix * y = make_rotY(60);
  print_matrix(y);
  free_matrix(y);
  struct matrix * z = make_rotZ(60);
  print_matrix(z);
  free_matrix(z);


  /*
  if ( argc == 2 )
    parse_file( argv[1], transform, edges, s );
  else
    parse_file( "stdin", transform, edges, s );
  */
  
  free_matrix( edges );
  free_matrix( transform );
}  
