#include <gtk/gtk.h>

int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);

    //Janela
    GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(janela), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(janela), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(janela);
    gtk_main();
}