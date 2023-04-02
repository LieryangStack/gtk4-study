/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#include "patterns-config.h"
#include "patterns-page-utility-pane.h"

#include "patterns-utils.h"

struct _PatternsPageUtilityPane
{
  PatternsPage parent_instance;

  GtkWindow *demo;
};

G_DEFINE_TYPE (PatternsPageUtilityPane, patterns_page_utility_pane, PATTERNS_TYPE_PAGE)

static void
demo_activate_cb (PatternsPageUtilityPane *self,
                  const char              *action_name,
                  GVariant                *parameter)
{
  gtk_window_present (self->demo);
}

static GtkPackType
get_flap_position (PatternsPageUtilityPane *self,
                   gboolean                 is_start)
{
  return is_start ? GTK_PACK_START : GTK_PACK_END;
}

static void
patterns_page_utility_pane_dispose (GObject *object)
{
  PatternsPageUtilityPane *self = PATTERNS_PAGE_UTILITY_PANE (object);

  patterns_clear_window (self->demo);

  G_OBJECT_CLASS (patterns_page_utility_pane_parent_class)->dispose (object);
}

static void
patterns_page_utility_pane_class_init (PatternsPageUtilityPaneClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->dispose = patterns_page_utility_pane_dispose;

  gtk_widget_class_install_action (widget_class, "demo.run", NULL,
                                   (GtkWidgetActionActivateFunc) demo_activate_cb);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Patterns/pages/utility-pane/patterns-page-utility-pane.ui");
  gtk_widget_class_bind_template_child (widget_class, PatternsPageUtilityPane, demo);
  gtk_widget_class_bind_template_callback (widget_class, get_flap_position);
}

static void
patterns_page_utility_pane_init (PatternsPageUtilityPane *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}
