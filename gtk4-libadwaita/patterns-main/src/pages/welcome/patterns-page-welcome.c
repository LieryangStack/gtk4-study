/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#include "patterns-config.h"
#include "patterns-page-welcome.h"

struct _PatternsPageWelcome
{
  PatternsPage parent_instance;
};

G_DEFINE_TYPE (PatternsPageWelcome, patterns_page_welcome, PATTERNS_TYPE_PAGE)

static gboolean
activate_link_cb (PatternsPageWelcome *self,
                  const char          *uri)
{
  if (!g_strcmp0 (uri, "patterns://inspector")) {
    gtk_window_set_interactive_debugging (TRUE);
    return GDK_EVENT_STOP;
  }

  return GDK_EVENT_PROPAGATE;
}

static void
patterns_page_welcome_class_init (PatternsPageWelcomeClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Patterns/pages/welcome/patterns-page-welcome.ui");
  gtk_widget_class_bind_template_callback (widget_class, activate_link_cb);
}

static void
patterns_page_welcome_init (PatternsPageWelcome *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}
