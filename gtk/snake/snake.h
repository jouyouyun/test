#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <gtk/gtk.h>

typedef enum {
      UP,
      DOWN,
	LEFT
      RIGHT
} Direction;

typedef struct {
      gint x;
      gint y;
} Body;

typedef struct {
      guint x;
      guint y;
      gboolean live;
} Food;

typedef struct {
      Direction direction;
      guint changdu;
      Body body[40];
      gboolean live;
} Snake;

#endif
