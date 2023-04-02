/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#pragma once

#include "patterns-page.h"

G_BEGIN_DECLS

#define PATTERNS_TYPE_PAGE_UTILITY_PANE (patterns_page_utility_pane_get_type())

G_DECLARE_FINAL_TYPE (PatternsPageUtilityPane, patterns_page_utility_pane, PATTERNS, PAGE_UTILITY_PANE, PatternsPage)

G_END_DECLS
