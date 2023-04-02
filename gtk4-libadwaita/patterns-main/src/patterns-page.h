/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PATTERNS_TYPE_PAGE (patterns_page_get_type())

G_DECLARE_DERIVABLE_TYPE (PatternsPage, patterns_page, PATTERNS, PAGE, GtkWidget)

struct _PatternsPageClass
{
  GtkWidgetClass parent_class;
};

G_END_DECLS
