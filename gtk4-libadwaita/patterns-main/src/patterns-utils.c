/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#include "patterns-config.h"
#include "patterns-utils.h"

void
patterns_clear_window (GtkWindow *window)
{
  if (!window)
    return;

  if (gtk_widget_get_visible (GTK_WIDGET (window)))
    gtk_window_set_hide_on_close (window, FALSE);
  else
    gtk_window_destroy (window);
}
