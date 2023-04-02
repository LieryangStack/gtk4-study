/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#include "patterns-config.h"
#include "patterns-page-windows.h"

#include "patterns-primary-window.h"
#include "patterns-utils.h"

struct _PatternsPageWindows
{
  PatternsPage parent_instance;

  GtkWindow *primary_window;
};

G_DEFINE_TYPE (PatternsPageWindows, patterns_page_windows, PATTERNS_TYPE_PAGE)

static void
primary_activate_cb (PatternsPageWindows *self,
                     const char          *action_name,
                     GVariant            *parameter)
{
  gtk_window_present (self->primary_window);
}

static void
patterns_page_windows_dispose (GObject *object)
{
  PatternsPageWindows *self = PATTERNS_PAGE_WINDOWS (object);

  patterns_clear_window (self->primary_window);

  G_OBJECT_CLASS (patterns_page_windows_parent_class)->dispose (object);
}

static void
patterns_page_windows_class_init (PatternsPageWindowsClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->dispose = patterns_page_windows_dispose;

  gtk_widget_class_install_action (widget_class, "demo.primary", NULL,
                                   (GtkWidgetActionActivateFunc) primary_activate_cb);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Patterns/pages/windows/patterns-page-windows.ui");
  gtk_widget_class_bind_template_child (widget_class, PatternsPageWindows, primary_window);
}

static void
patterns_page_windows_init (PatternsPageWindows *self)
{
  g_type_ensure (PATTERNS_TYPE_PRIMARY_WINDOW);

  gtk_widget_init_template (GTK_WIDGET (self));
}
