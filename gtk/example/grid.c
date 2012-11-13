/*
 *	GtkGrid 网格
 */

#include <gtk/gtk.h>

static void print_hello ( GtkWidget *window, gpointer data )
{
	g_print( "Hello World\n" );
}

int main( int argc, char *argv[] )
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *button;

	gtk_init( &argc, &argv );

	window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	gtk_window_set_title( GTK_WINDOW(window), "Grid" );
	g_signal_connect( window, "destroy", G_CALLBACK(gtk_main_quit), NULL );
	gtk_container_set_border_width( GTK_CONTAINER(window), 10 );

	/* Here we construct the container that is going pack our buttons */
	grid = gtk_grid_new();

	/* Pack the container in the window */
	gtk_container_add( GTK_CONTAINER(window), grid );

	button = gtk_button_new_with_label( "Button 1" );
	g_signal_connect( button, "clicked", G_CALLBACK(print_hello), NULL );

	/*
	* Place the first button in the grid cell (0, 0), and make it fill
	* just 1 cell horizontally and vertically (ie no spanning)
	* 把 button 附加到 grid 里
	*/
	gtk_grid_attach( GTK_GRID(grid), button, 0, 0, 1, 1 );

	button = gtk_button_new_with_label( "Button 2" );
	g_signal_connect( button, "clicked", G_CALLBACK(print_hello), NULL );
	/*
	* Place the second button in the grid cell (1, 0), and make it fill
	* just 1 cell horizontally and vertically (ie no spanning)
	*/
	gtk_grid_attach( GTK_GRID(grid), button, 1, 0, 1, 1 );

	button = gtk_button_new_with_label( "Quit" );
	g_signal_connect( button, "clicked", G_CALLBACK(gtk_main_quit), NULL );

	/*
	* Place the Quit button in the grid cell (0, 1), and make it
	* span 2 columns.
	*/
	gtk_grid_attach( GTK_GRID(grid), button, 0, 1, 2, 1 );

	gtk_widget_show_all( window );
	gtk_main();

	return 0;
}
