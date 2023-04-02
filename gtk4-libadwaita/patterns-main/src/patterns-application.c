/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#include "patterns-config.h"
#include "patterns-application.h"

#include <glib/gi18n.h>

#include "patterns-window.h"

struct _PatternsApplication
{
  AdwApplication parent_instance;
};

G_DEFINE_TYPE (PatternsApplication, patterns_application, ADW_TYPE_APPLICATION)

static void
show_about (GSimpleAction *action,
            GVariant      *state,
            gpointer       user_data)
{
  GtkApplication *app = user_data;
  GtkWindow *window = gtk_application_get_active_window (app);
  GtkWidget *about;

  const char *developers[] = {
    "Alexander Mikhaylenko",
    "Christopher Davis",
    "Marco Melorio",
    NULL,
  };

  const char *designers[] = {
    "Allan Day",
    "Jakub Steiner",
    "Tobias Bernard",
    NULL,
  };

  about = g_object_new (ADW_TYPE_ABOUT_WINDOW,
                        "transient-for", window,
                        "application-name", _("Patterns"),
                        "application-icon", APPLICATION_ID,
                        "developer-name", _("The GNOME Project"),
                        "copyright", _("Copyright © 2021 Purism SPC"),
                        "license", _("This project is dual-licensed as MIT and LGPLv2+."),
                        "version", PACKAGE_VERSION,
                        "website", "https://developer.gnome.org/hig/",
                        "issue-url", "https://gitlab.gnome.org/exalm/patterns/-/issues/new",
                        "developers", developers,
                        "designers", designers,
                        "translator-credits", _("translator-credits"),
                        NULL);

  adw_about_window_add_legal_section (ADW_ABOUT_WINDOW (about),
                                      "MIT", NULL,
                                      GTK_LICENSE_MIT_X11, NULL);
  adw_about_window_add_legal_section (ADW_ABOUT_WINDOW (about),
                                      "LGPLv2+", NULL,
                                      GTK_LICENSE_LGPL_2_1, NULL);

  gtk_window_present (GTK_WINDOW (about));
}

static GActionEntry app_entries[] = {
  { "about", show_about },
};

static void
patterns_application_activate (GApplication *app)
{
  GtkWindow *window = gtk_application_get_active_window (GTK_APPLICATION (app));

  if (!window)
    window = GTK_WINDOW (patterns_window_new (GTK_APPLICATION (app)));

  gtk_window_present (window);
}

static void
patterns_application_class_init (PatternsApplicationClass *klass)
{
  GApplicationClass *application_class = G_APPLICATION_CLASS (klass);

  application_class->activate = patterns_application_activate;
}

static void
patterns_application_init (PatternsApplication *self)
{
  g_action_map_add_action_entries (G_ACTION_MAP (self),
                                   app_entries,
                                   G_N_ELEMENTS (app_entries),
                                   self);
}

GApplication *
patterns_application_new (void)
{
  return g_object_new (PATTERNS_TYPE_APPLICATION,
                       "application-id", "org.gnome.Patterns",
                       "flags", G_APPLICATION_FLAGS_NONE,
                       NULL);
}
