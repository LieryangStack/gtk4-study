#include <adwaita.h>

static void 
app_activate (GApplication *app, gpointer *user_data) {
  GtkBuilder *build = gtk_builder_new_from_file ("app.ui");
  GtkWidget *win = GTK_WIDGET (gtk_builder_get_object (build, "window"));
  gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));
  gtk_window_present (GTK_WINDOW (win));
}

int
main (int argc, char *argv[]) {
  g_autoptr (AdwApplication) app = adw_application_new ("test.application", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
  return g_application_run (G_APPLICATION (app), argc, argv);
}
