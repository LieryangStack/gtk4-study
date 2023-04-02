#include <adwaita.h>

static void 
app_activate (GApplication *app, gpointer *user_data) {
  GtkBuilder *build = gtk_builder_new_from_file ("application.ui");
  GtkWidget *win = GTK_WIDGET (gtk_builder_get_object (build, "win"));
    GtkWidget *leaflet = GTK_WIDGET (gtk_builder_get_object (build, "leaflet"));
  gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));
  //adw_style_manager_set_color_scheme(adw_style_manager_get_default(), ADW_COLOR_SCHEME_PREFER_DARK);
  g_print ("%d\n", adw_leaflet_get_folded (ADW_LEAFLET (leaflet)));
  gtk_window_present (GTK_WINDOW (win));
}

int
main (int argc, char *argv[]) {
  g_autoptr (AdwApplication) app = adw_application_new ("test.application", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
  return g_application_run (G_APPLICATION (app), argc, argv);
}

