/* 本例的主要目的是在主窗口中旋转一个box控件，再在box控件中
 * 放置一个单行编辑框和一个按钮
 * 并且单击按钮退出程序
 */

#include <gtk/gtk.h>

/* "button" 的回调函数i */
void cb_button( GtkWidget *widget, gpointer data )
{
	g_print( "你单击了按钮\n" );
	gtk_main_quit();
}

int main( int argc, char* argv[] )
{
	GtkWidget *main_window;
	GtkWidget *button, *editor, *hbox;

	gtk_init( &argc, &argv );

	main_window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	g_signal_connect( G_OBJECT( main_window ), "destroy", 
			G_CALLBACK( gtk_main_quit ), NULL );
	gtk_window_set_title( GTK_WINDOW( main_window ), "Hello Arch" );
	gtk_window_set_default_size( GTK_WINDOW( main_window ), 200, 150 );

	button = gtk_button_new_with_label( "退出程序" );
	g_signal_connect( G_OBJECT( button ), "clicked", 
			G_CALLBACK( cb_button ), NULL );

	editor = gtk_entry_new();

	hbox = gtk_box_new( FALSE, 10 );

	gtk_box_pack_start( GTK_BOX( hbox ), editor, TRUE, TRUE, 10 );
	gtk_box_pack_start( GTK_BOX( hbox ), button, FALSE, FALSE, 10 );
	
	gtk_container_add( GTK_CONTAINER( main_window ), hbox );

	gtk_widget_show_all( main_window );
	gtk_main();

	return 0;
}
