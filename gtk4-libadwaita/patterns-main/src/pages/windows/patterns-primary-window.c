/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#include "patterns-config.h"
#include "patterns-primary-window.h"

#include <adwaita.h>
#include <glib/gi18n.h>

#include "patterns-utils.h"

struct _PatternsPrimaryWindow
{
  GtkWindow parent_instance;

  GtkWindow *secondary_window;
  GtkWindow *preferences_window;
};

G_DEFINE_TYPE (PatternsPrimaryWindow, patterns_primary_window, GTK_TYPE_WINDOW)

static void
secondary_activate_cb (PatternsPrimaryWindow *self,
                       const char            *action_name,
                       GVariant              *parameter)
{
  gtk_window_present (self->secondary_window);
}

static void
preferences_activate_cb (PatternsPrimaryWindow *self,
                         const char            *action_name,
                         GVariant              *parameter)
{
  gtk_window_present (self->preferences_window);
}

static void
about_activate_cb (PatternsPrimaryWindow *self,
                   const char            *action_name,
                   GVariant              *parameter)
{
  GtkWidget *about;

  const char *developers[] = {
    "Angela Avery <angela@example.org>",
    NULL
  };

  const char *artists[] = {
    "GNOME Design Team",
    NULL
 };

  const char *special_thanks[] = {
    "My cat",
    NULL
 };

  const char *release_notes = "\
<p>\
  This release adds the following features:\
</p>\
<ul>\
  <li>Added a way to export fonts.</li>\
  <li>Better support for <code>monospace</code> fonts.</li>\
  <li>Added a way to preview <em>italic</em> text.</li>\
  <li>Bug fixes and performance improvements.</li>\
  <li>Translation updates.</li>\
</ul>\
  ";

  about =
    g_object_new (ADW_TYPE_ABOUT_WINDOW,
                  "transient-for", self,
                  "application-icon", "org.example.Typeset",
                  "application-name", _("Typeset"),
                  "developer-name", _("Angela Avery"),
                  "version", "1.2.3",
                  "release-notes-version", "1.2.0",
                  "release-notes", release_notes,
                  "comments", _("Typeset is an app that doesn’t exist and is used as an example content for this about window."),
                  "website", "https://example.org",
                  "issue-url", "https://example.org",
                  "support-url", "https://example.org",
                  "copyright", "© 2022 Angela Avery",
                  "license-type", GTK_LICENSE_LGPL_2_1,
                  "developers", developers,
                  "artists", artists,
                  "translator-credits", _("translator-credits"),
                  NULL);

  adw_about_window_add_link (ADW_ABOUT_WINDOW (about),
                             _("_Documentation"),
                             "https://gnome.pages.gitlab.gnome.org/libadwaita/doc/main/class.AboutWindow.html");

  adw_about_window_add_legal_section (ADW_ABOUT_WINDOW (about),
                                      _("Fonts"),
                                      NULL,
                                      GTK_LICENSE_CUSTOM,
                                      "This application uses font data from <a href='https://example.org'>somewhere</a>.");

  adw_about_window_add_acknowledgement_section (ADW_ABOUT_WINDOW (about),
                                                _("Special thanks to"),
                                                special_thanks);

  gtk_window_present (GTK_WINDOW (about));
}

static void
patterns_primary_window_dispose (GObject *object)
{
  PatternsPrimaryWindow *self = PATTERNS_PRIMARY_WINDOW (object);

  patterns_clear_window (self->secondary_window);
  patterns_clear_window (self->preferences_window);

  G_OBJECT_CLASS (patterns_primary_window_parent_class)->dispose (object);
}

static void
patterns_primary_window_class_init (PatternsPrimaryWindowClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->dispose = patterns_primary_window_dispose;

  gtk_widget_class_install_action (widget_class, "demo.secondary", NULL,
                                   (GtkWidgetActionActivateFunc) secondary_activate_cb);
  gtk_widget_class_install_action (widget_class, "demo.preferences", NULL,
                                   (GtkWidgetActionActivateFunc) preferences_activate_cb);
  gtk_widget_class_install_action (widget_class, "demo.about", NULL,
                                   (GtkWidgetActionActivateFunc) about_activate_cb);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Patterns/pages/windows/patterns-primary-window.ui");
  gtk_widget_class_bind_template_child (widget_class, PatternsPrimaryWindow, secondary_window);
  gtk_widget_class_bind_template_child (widget_class, PatternsPrimaryWindow, preferences_window);
}

static void
patterns_primary_window_init (PatternsPrimaryWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}
