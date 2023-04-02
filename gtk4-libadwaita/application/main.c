#include "vpf_application.h"
#include "vpf_application_window.h"

static void 
app_activate (GApplication *app, gpointer *user_data) {
  GtkWidget *win;
  win = vpf_application_window_new (GTK_APPLICATION (app));
  gtk_window_set_title (GTK_WINDOW (win), "pr4");
  gtk_window_set_default_size (GTK_WINDOW (win), 500, 400);
  gtk_window_present (GTK_WINDOW (win));

}

int
main (int argc, char *argv[])
{
  g_autoptr (GApplication) app = vpf_application_new ("vpf.application", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
  return g_application_run (G_APPLICATION (app), argc, argv);
}