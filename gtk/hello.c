#include <gtk/gtk.h>

/* 按钮"button"的回调函数 */
void quit( GtkWidget *wdget, gpointer data ) 
{
	gtk_main_quit();
}

int main( int argc, char *argv[] )
{
	//GtkWidget 是绝大部分可视组件的的基类
	//GtkWidget *window;

	/* 主窗口对象 */
	GtkWidget *main_window;
	/* 将要放置到主窗口中的按钮对象 */
	GtkWidget *button;

	//对程序传入的命令行参数进行标准化处理
	gtk_init( &argc, &argv );

	//创建窗口(200x200大小)
	main_window = gtk_window_new( GTK_WINDOW_TOPLEVEL );

	//设置窗口标题
	gtk_window_set_title( GTK_WINDOW( main_window ), "Hello Arch!" );
	//设置窗口的默认大小
	gtk_window_set_default_size( GTK_WINDOW( main_window ), 200, 100 );
	
	button = gtk_button_new_with_label( "退出程序" );
	gtk_container_add( GTK_CONTAINER( main_window ), button );
	/* 为"button"连接"单击事件"要调用的函数 */
	g_signal_connect( G_OBJECT( button ), "clicked", 
			G_CALLBACK( quit ), NULL );
	/* 单击右上角的“关闭按钮”关闭程序，会产生“destroy”信号 */
	g_signal_connect( G_OBJECT( main_window ), "destroy", 
			G_CALLBACK( quit ), NULL );

	//显示窗口
	gtk_widget_show( main_window );
	gtk_widget_show( button );
	/* 上边的两句可以合为 gtk_widget_show_all(window) */
	
	//Gtk程序主循环
	gtk_main();

	return 0;
}