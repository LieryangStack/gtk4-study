#include "vpf_application.h"

static void show_about (GSimpleAction *action, GVariant *state, gpointer user_data);

static GActionEntry app_entries[] = {
  { "about", show_about },
};

struct _VpfApplication {
  AdwApplication parent;
};

G_DEFINE_TYPE (VpfApplication, vpf_application, ADW_TYPE_APPLICATION)

static void
vpf_application_class_init (VpfApplicationClass *class) {

}

static void
vpf_application_init (VpfApplication *self) {
  g_action_map_add_action_entries (G_ACTION_MAP (self), 
                                   app_entries, 
                                   G_N_ELEMENTS (app_entries), self);
}

GApplication *
vpf_application_new (const char *application_id, GApplicationFlags  flags) {
  return g_object_new (VPF_TYPE_APPLICATION,
                       "application-id", application_id,
                       "flags", flags, NULL);
}

static void 
show_about (GSimpleAction *action, GVariant *state, gpointer user_data) {

}