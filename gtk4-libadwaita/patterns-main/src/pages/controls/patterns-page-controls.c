/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#include "patterns-config.h"
#include "patterns-page-controls.h"

struct _PatternsPageControls
{
  PatternsPage parent_instance;
};

G_DEFINE_TYPE (PatternsPageControls, patterns_page_controls, PATTERNS_TYPE_PAGE)

static double
progress_to_level (PatternsPageControls *self G_GNUC_UNUSED,
                   double                progress)
{
  return progress * 5;
}

static void
patterns_page_controls_class_init (PatternsPageControlsClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Patterns/pages/controls/patterns-page-controls.ui");
  gtk_widget_class_bind_template_callback (widget_class, progress_to_level);
}

static void
patterns_page_controls_init (PatternsPageControls *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}
