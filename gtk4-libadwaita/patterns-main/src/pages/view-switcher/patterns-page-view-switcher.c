/*
 * Copyright (C) 2021 Marco Melorio <marco.melorio@protonmail.com>
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#include "patterns-config.h"
#include "patterns-page-view-switcher.h"

#include "patterns-utils.h"

struct _PatternsPageViewSwitcher
{
  PatternsPage parent_instance;

  GtkWindow *demo;
};

G_DEFINE_TYPE (PatternsPageViewSwitcher, patterns_page_view_switcher, PATTERNS_TYPE_PAGE)

static void
demo_activate_cb (PatternsPageViewSwitcher *self,
                  const char               *action_name,
                  GVariant                 *parameter)
{
  gtk_window_present (self->demo);
}

static void
patterns_page_view_switcher_dispose (GObject *object)
{
  PatternsPageViewSwitcher *self = PATTERNS_PAGE_VIEW_SWITCHER (object);

  patterns_clear_window (self->demo);

  G_OBJECT_CLASS (patterns_page_view_switcher_parent_class)->dispose (object);
}

static void
patterns_page_view_switcher_class_init (PatternsPageViewSwitcherClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->dispose = patterns_page_view_switcher_dispose;

  gtk_widget_class_install_action (widget_class, "demo.run", NULL,
                                   (GtkWidgetActionActivateFunc) demo_activate_cb);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Patterns/pages/view-switcher/patterns-page-view-switcher.ui");
  gtk_widget_class_bind_template_child (widget_class, PatternsPageViewSwitcher, demo);
}

static void
patterns_page_view_switcher_init (PatternsPageViewSwitcher *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}
