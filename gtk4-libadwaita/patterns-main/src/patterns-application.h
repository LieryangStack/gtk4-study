/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define PATTERNS_TYPE_APPLICATION (patterns_application_get_type())

G_DECLARE_FINAL_TYPE (PatternsApplication, patterns_application, PATTERNS, APPLICATION, AdwApplication)

GApplication *patterns_application_new (void);

G_END_DECLS
