/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#pragma once

#include "patterns-page.h"

G_BEGIN_DECLS

#define PATTERNS_TYPE_PAGE_WINDOWS (patterns_page_windows_get_type())

G_DECLARE_FINAL_TYPE (PatternsPageWindows, patterns_page_windows, PATTERNS, PAGE_WINDOWS, PatternsPage)

G_END_DECLS
