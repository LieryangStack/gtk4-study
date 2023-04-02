/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PATTERNS_TYPE_PRIMARY_WINDOW (patterns_primary_window_get_type())

G_DECLARE_FINAL_TYPE (PatternsPrimaryWindow, patterns_primary_window, PATTERNS, PRIMARY_WINDOW, GtkWindow)

G_END_DECLS
