/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define PATTERNS_TYPE_WINDOW (patterns_window_get_type())

G_DECLARE_FINAL_TYPE (PatternsWindow, patterns_window, PATTERNS, WINDOW, AdwApplicationWindow)

GtkWidget *patterns_window_new (GtkApplication *app);

G_END_DECLS
