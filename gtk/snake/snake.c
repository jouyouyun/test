/* 
   snake - snake.c 
   Copyright (c) 2003 by Linux_Lyb <linux_lyb@sohu.com> 
   ________________________________________________________________________________    
   This program is free software; you can redistribute it and/or modify 
   it under the terms of the GNU General Public License as published by 
   the Free Software Foundation; either version 2, or (at your option) 
   any later version. 

   This program is distributed in the hope that it will be useful, 
   but WITHOUT ANY WARRANTY; without even the implied warranty of 
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
   GNU General Public License for more details. 

   You should have received a copy of the GNU General Public License 
   along with this program; if not, write to the Free Software 
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. 

   See the file COPYING in the doc/ directory for more information. 
 */

#include <gdk/gdkkeysyms.h>
#include <time.h>
#include <stdlib.h>
#include "snake.h"

static GtkWidget *window = NULL;
static GtkWidget *draw_area = NULL;
static GdkPixmap *pixmap = NULL;
GtkWidget *label;
gchar text[64];
guint timer = 0;
gboolean playing = FALSE;
gboolean pauseing = FALSE;
Snake snake;
Food food;
   //游戏相关变量  
guint speed = 200;
guint level = 1;
guint foods = 35;
guint live = 3;

gboolean play_game(gpointer data);

gint my_rand(gint min, gint max)
{
      return rand() % max + min;
}

   //进行蛇身体（不包括头部）的走动  
void snake_run()
{
      gint i;
      for (i = snake.length; i > 0; i--) {
	    snake.body[i].x = snake.body[i - 1].x;
	    snake.body[i].y = snake.body[i - 1].y;
      }

}

   //设置标签的内容  
void set_label()
{
      sprintf(text, "egg: %d | live: %d | level: %d", foods, live, level);
      gtk_label_set_text(GTK_LABEL(label), text);
}

   //画游戏画面  
void draw()
{
      gint i;
      //clear all  
      gdk_draw_rectangle(pixmap, window->style->white_gc, TRUE, 0, 0,
			 draw_area->allocation.width,
			 draw_area->allocation.height);

      //draw snake  
      for (i = 0; i <= snake.length; i++) {
	    //g_print ("[%d]%d,%d->",i,snake.body[i].x,snake.body[i].y);  
	    gdk_draw_rectangle(pixmap, window->style->black_gc, TRUE,
			       snake.body[i].x * 10,
			       snake.body[i].y * 10, 10, 10);
      }


      //draw egg  
      gdk_draw_rectangle(pixmap, window->style->black_gc, TRUE, food.x * 10,
			 food.y * 10, 10, 10);

      gtk_widget_queue_draw(draw_area);
}

   //初始化游戏  
void init_game()
{
      gint i;
      //蛇的设定  
      snake.length = 5;
      snake.body[0].x = my_rand(5, 20);
      snake.body[0].y = my_rand(5, 20);
      snake.direction = my_rand(0, 4);
      snake.live = TRUE;

      for (i = 1; i <= snake.length; i++)
	    switch (snake.direction) {
	    case UP:
		  snake.body[i].x = snake.body[i - 1].x;
		  snake.body[i].y = snake.body[i - 1].y - 1;
		  break;
	    case DOWN:
		  snake.body[i].x = snake.body[i - 1].x;
		  snake.body[i].y = snake.body[i - 1].y + 1;;
		  break;
	    case LEFT:
		  snake.body[i].x = snake.body[i - 1].x - 1;
		  snake.body[i].y = snake.body[i - 1].y;
		  break;
	    case RIGHT:
		  snake.body[i].x = snake.body[i - 1].x + 1;
		  snake.body[i].y = snake.body[i - 1].y;
		  break;
	    default:
		  break;
	    }

      snake.live = TRUE;
      //蛋的设定  
      food.x = my_rand(0, 20);
      food.y = food.x;
      food.live = TRUE;
}

  //游戏开始  
void game_start()
{
      if (timer == 0)
	    timer = g_timeout_add(speed, play_game, NULL);
}

  //暂停游戏  
void game_pause(GtkWidget * widget)
{
      if (pauseing == FALSE) {
	    if (timer != 0)
		  g_source_remove(timer);

	    timer = 0;
	    gtk_button_set_label(GTK_BUTTON(widget), " Go ");
	    pauseing = TRUE;
      } else {
	    if (timer == 0)
		  timer = g_timeout_add(speed, play_game, NULL);
	    gtk_button_set_label(GTK_BUTTON(widget), "Pause");
	    pauseing = FALSE;
      }
}

  //停止游戏  
void game_stop()
{
      playing = FALSE;
      if (timer != 0)
	    g_source_remove(timer);
      timer = 0;
}

gboolean play_game(gpointer data)
{
      int i;
      if (playing == FALSE) {	//如果游戏还没开始，初始化游戏并开始  
	    init_game();
	    set_label();
	    playing = TRUE;
	    return TRUE;
      }

      snake_run();

      switch (snake.direction) {
      case UP:
	    snake.body[0].y = snake.body[0].y - 1;
	    //判断是否有向自己身体走的情况，如果有就改变方向  
	    //头部[0]和身体[2]的坐标(x或y)相同，就需要向反方向改变  
	    if (snake.body[0].y == snake.body[2].y) {
		  snake.direction = DOWN;
		  snake.body[0].y = snake.body[0].y + 2;
	    }
	    break;
      case DOWN:
	    snake.body[0].y = snake.body[0].y + 1;
	    if (snake.body[0].y == snake.body[2].y) {
		  snake.direction = UP;
		  snake.body[0].y = snake.body[0].y - 2;
	    }

	    break;
      case LEFT:
	    snake.body[0].x = snake.body[0].x - 1;
	    if (snake.body[0].x == snake.body[2].x) {
		  snake.direction = RIGHT;
		  snake.body[0].x = snake.body[0].x + 2;
	    }
	    break;
      case RIGHT:
	    snake.body[0].x = snake.body[0].x + 1;
	    if (snake.body[0].x == snake.body[2].x) {
		  snake.direction = LEFT;
		  snake.body[0].x = snake.body[0].x - 2;
	    }
	    break;
      default:
	    break;
      }
      //判断蛇的头部是否碰到了自己的身体，如果碰到了就去死！  
      for (i = 4; i <= snake.length; i++)
	    if (snake.body[0].x == snake.body[i].x
		&& snake.body[0].y == snake.body[i].y)
		  snake.live = FALSE;

      //判断蛇是否碰到边界，如果碰到了就去死！  
      if (snake.body[0].x < 0 || snake.body[0].y < 0
	  || snake.body[0].x > 40 || snake.body[0].y > 40) {
	    snake.live = FALSE;
      }
      //判断蛇是否死了  
      if (she.live == FALSE) {
	    live = live - 1;
	    if (live == 0) {	//没命就GAME OVER  
		  speed = 200;
		  level = 1;
		  foods = 20;
		  live = 3;
		  game_stop();
		  gtk_label_set_text(GTK_LABEL(label), " - Game Over -");
		  return FALSE;
	    }
	    //还有命就继续  
	    set_label();
	    init_game();
      }
      //判断蛇是否吃到了蛋，如果吃到了就变长！  
      if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
	    snake.length = snake.length + 1;
	    snake.body[snake.length].x = snake.body[snake.length - 1].x;
	    snake.body[snake.length].y = snake.body[snake.length - 1].y;
	    //重新生成一个蛋  
	    food.x = my_rand(0, 20);
	    food.y = food.x;
	    foods = foods - 1;	//减少一个蛋  
	    if (foods == 0) {	//如果吃完全部的蛋，进入下一局，速度加快  
		  level = level + 1;
		  foods = 20;
		  if (speed > 30)
			speed = speed - 20;
		  game_stop();
		  game_start();
	    }
	    set_label();
      }

      draw();
      return TRUE;
}

static gboolean configure_event(GtkWidget * widget,
				GdkEventConfigure * event, gpointer data)
{
      if (pixmap)
	    g_object_unref(pixmap);
      pixmap = gdk_pixmap_new(widget->window,
			      widget->allocation.width,
			      widget->allocation.height, -1);

      gdk_draw_rectangle(pixmap, widget->style->white_gc, TRUE, 0, 0,
			 widget->allocation.width,
			 widget->allocation.height);
      return TRUE;
}

static gboolean expose_event(GtkWidget * widget, GdkEventExpose * event,
			     gpointer data)
{
      gdk_draw_drawable(widget->window,
			widget->style->fg_gc[GTK_WIDGET_STATE(widget)],
			pixmap,
			event->area.x, event->area.y,
			event->area.x, event->area.y,
			event->area.width, event->area.height);
      return TRUE;
}

  //处理按钮事件  
void key_press(GtkWidget * widget, GdkEventKey * event)
{
      if (playing == TRUE && event->type == GDK_KEY_PRESS) {

	    switch (event->keyval) {
	    case GDK_Up:
		  snake.direction = UP;
		  break;
	    case GDK_Down:
		  snake.direction = DOWN;
		  break;
	    case GDK_Left:
		  snake.direction = LEFT;
		  break;
	    case GDK_Right:
		  snake.direction = RIGHT;
		  break;
	    default:
		  break;
	    }

      }
}

  //退出游戏  
void quit_game()
{
      game_stop();
      gtk_main_quit();
      g_object_unref(pixmap);
}

void create_window()
{
      GtkWidget *vbox, *hbox;
      GtkWidget *b_start, *b_pause;

      window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
      gtk_window_set_title(GTK_WINDOW(window), "TanChiShe Ver 0.3");
      //gtk_window_set_resizable (GTK_WINDOW(window),FALSE);  
      gtk_widget_set_usize(window, 408, 448);
      gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
      //gtk_widget_realize (window);  
      gtk_container_set_border_width(GTK_CONTAINER(window), 0);

      g_signal_connect(GTK_OBJECT(window), "destroy",
		       G_CALLBACK(quit_game), &window);
      g_signal_connect(GTK_OBJECT(window), "key_press_event",
		       G_CALLBACK(key_press), NULL);

      vbox = gtk_vbox_new(FALSE, 0);
      gtk_container_add(GTK_CONTAINER(window), vbox);

      draw_area = gtk_drawing_area_new();
      gtk_widget_set_usize(draw_area, 400, 400);
      //gtk_widget_set_size_request (draw_area,400,400);  

      g_signal_connect(draw_area, "expose_event",
		       G_CALLBACK(expose_event), NULL);
      g_signal_connect(draw_area, "configure_event",
		       G_CALLBACK(configure_event), NULL);

      gtk_box_pack_start(GTK_BOX(vbox), draw_area, TRUE, TRUE, 0);

      hbox = gtk_hbox_new(FALSE, 0);
      gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);

      b_start = gtk_button_new_with_label("Start");
      gtk_box_pack_start(GTK_BOX(hbox), b_start, FALSE, FALSE, 0);
      g_signal_connect(b_start, "clicked", G_CALLBACK(game_start), NULL);

      b_pause = gtk_button_new_with_label("Pause");
      gtk_box_pack_start(GTK_BOX(hbox), b_pause, FALSE, FALSE, 0);
      g_signal_connect(b_pause, "clicked",
		       G_CALLBACK(game_pause), b_pause);

      label = gtk_label_new(" - By Linux_Lyb ( linux_lyb@sohu.com )");
      gtk_box_pack_start(GTK_BOX(hbox), label, TRUE, TRUE, 0);

      gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
      srand(time(NULL));
      gtk_init(&argc, &argv);
      create_window();
      gtk_main();

      return 0;
}
