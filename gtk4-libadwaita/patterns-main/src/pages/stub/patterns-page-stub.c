/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#include "patterns-config.h"
#include "patterns-page-stub.h"

struct _PatternsPageStub
{
  PatternsPage parent_instance;
};

G_DEFINE_TYPE (PatternsPageStub, patterns_page_stub, PATTERNS_TYPE_PAGE)

static void
patterns_page_stub_class_init (PatternsPageStubClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Patterns/pages/stub/patterns-page-stub.ui");
}

static void
patterns_page_stub_init (PatternsPageStub *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}
