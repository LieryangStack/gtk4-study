#include <gtk/gtk.h>

static void 
app_activate (GApplication *app, gpointer *user_data) {
  GtkWidget *win;
  win = gtk_window_new ();
  gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));
  gtk_window_present (GTK_WINDOW (win));
}


int
main (int argc, char *argv[]) {
  GtkApplication *app;
  int state;

  app = gtk_application_new ("lieryang.pr2", G_APPLICATION_FLAGS_NONE);
  /* activate信息是在GApplication中定义的 */
  g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
  state = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return state;
}