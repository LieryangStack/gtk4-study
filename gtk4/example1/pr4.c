#include <gtk/gtk.h>
#include <gdk/x11/gdkx.h>
#include <X11/X.h>

static void 
app_activate (GApplication *app, gpointer *user_data) {
  GtkWidget *win;
  win = gtk_application_window_new (GTK_APPLICATION (app));
  gtk_window_set_title (GTK_WINDOW (win), "pr4");
  gtk_window_set_default_size (GTK_WINDOW (win), 500, 400);
  gtk_window_present (GTK_WINDOW (win));

  GtkWidget *btn;
  btn = gtk_button_new_with_label ("Test Button");

  GtkWidget *img;
  img = gtk_image_new_from_file ("/home/lieryang/Pictures/lieryang.jpg");

  gtk_window_set_child (GTK_WINDOW(win), img);

  XID win_id = GDK_SURFACE_XID (gtk_native_get_surface(gtk_widget_get_native(win)));
  XID btn_id = GDK_SURFACE_XID (gtk_native_get_surface(gtk_widget_get_native(img)));

  g_print ("win_id = 0x%lx\n", win_id);
  g_print ("btn_id = 0x%lx\n", btn_id);
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