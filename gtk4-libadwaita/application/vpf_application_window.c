#include "vpf_application_window.h"
#include "vpf_page_info.h"
#include "vpf_resources.c"

struct _VpfApplicationWindow {
  AdwApplication parent;

  AdwLeaflet *leaflet;
  GListStore *list;
};

G_DEFINE_TYPE (VpfApplicationWindow, vpf_application_window, ADW_TYPE_APPLICATION_WINDOW)

static void
leaflet_back_activate_cb (VpfApplicationWindow *self,
                          const char    *action_name,
                          GVariant      *parameter) {
  adw_leaflet_navigate (self->leaflet, ADW_NAVIGATION_DIRECTION_BACK);
}

static void
vpf_application_window_init (VpfApplicationWindow *self) {
  g_print ("%s\n", __func__);
  gtk_widget_init_template (GTK_WIDGET (self));
  g_print ("%s\n", __func__);
} 

static void
vpf_application_window_class_init (VpfApplicationWindowClass *class) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (class);

  // TODO: these should be on the leaflet instead
  gtk_widget_class_install_action (widget_class, "leaflet.back", NULL,
                                   (GtkWidgetActionActivateFunc) leaflet_back_activate_cb);
  
  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/vpf/vpf_application_window.ui");
  // gtk_widget_class_bind_template_child (widget_class, VpfApplicationWindow, leaflet);
  // gtk_widget_class_bind_template_child (widget_class, VpfApplicationWindow, list);
  // gtk_widget_class_bind_template_callback (widget_class, new_page_cb);
  // gtk_widget_class_bind_template_callback (widget_class, list_activate_cb);
  // gtk_widget_class_bind_template_callback (widget_class, folded_notify_cb);
  // gtk_widget_class_bind_template_callback (widget_class, get_results_page);
}

GtkWidget *
vpf_application_window_new (GtkApplication *app) {
  g_return_val_if_fail (GTK_IS_APPLICATION (app), NULL);
  return g_object_new (VPF_TYPE_APPLICATION_WINDOW,
                       "application", app, NULL);
}