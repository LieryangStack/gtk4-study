#include <gtk/gtk.h>

static void
click_cb (GtkButton *btn) {
  g_print ("Cliked.\n");
}

static void
app_activate (GApplication *app) {
  GtkWidget *win;
  GtkWidget *btn;

  win = gtk_application_window_new (GTK_APPLICATION (app));
  gtk_window_set_title (GTK_WINDOW (win), "lb2");
  gtk_window_set_default_size (GTK_WINDOW (win), 300, 400);
  
  btn = gtk_button_new_with_label ("hello");
  gtk_window_set_child (GTK_WINDOW (win), btn);
  g_signal_connect (btn, "clicked", G_CALLBACK (click_cb), NULL);

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

