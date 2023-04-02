/*
 * Copyright (C) 2021 Purism SPC
 * Copyright (C) 2021 Marco Melorio <marco.melorio@protonmail.com>
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#include "patterns-config.h"
#include "patterns-page-boxed-lists.h"

#include <glib/gi18n.h>

#include "patterns-utils.h"

struct _PatternsPageBoxedLists
{
  PatternsPage parent_instance;

  GtkWindow *sub_view;
};

G_DEFINE_TYPE (PatternsPageBoxedLists, patterns_page_boxed_lists, PATTERNS_TYPE_PAGE)

static void
sub_view_activate_cb (PatternsPageBoxedLists *self,
                      const char             *action_name,
                      GVariant               *parameter)
{
  GtkWindow *window = GTK_WINDOW (gtk_widget_get_root (GTK_WIDGET (self)));

  gtk_window_set_transient_for (self->sub_view, window);
  gtk_window_present (self->sub_view);
}

static void
external_link_activate_cb (PatternsPageBoxedLists *self,
                           const char             *action_name,
                           GVariant               *parameter)
{
  GtkWindow *window = GTK_WINDOW (gtk_widget_get_root (GTK_WIDGET (self)));

  gtk_show_uri (window, _("https://os.gnome.org"), GDK_CURRENT_TIME);
}

static void
patterns_page_boxed_lists_dispose (GObject *object)
{
  PatternsPageBoxedLists *self = PATTERNS_PAGE_BOXED_LISTS (object);

  patterns_clear_window (self->sub_view);

  G_OBJECT_CLASS (patterns_page_boxed_lists_parent_class)->dispose (object);
}

static void
patterns_page_boxed_lists_class_init (PatternsPageBoxedListsClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->dispose = patterns_page_boxed_lists_dispose;

  gtk_widget_class_install_action (widget_class, "page.sub-view", NULL,
                                   (GtkWidgetActionActivateFunc) sub_view_activate_cb);
  gtk_widget_class_install_action (widget_class, "page.external-link", NULL,
                                   (GtkWidgetActionActivateFunc) external_link_activate_cb);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Patterns/pages/boxed-lists/patterns-page-boxed-lists.ui");
  gtk_widget_class_bind_template_child (widget_class, PatternsPageBoxedLists, sub_view);
}

static void
patterns_page_boxed_lists_init (PatternsPageBoxedLists *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}
