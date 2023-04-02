/*
 * Copyright (C) 2021 Marco Melorio <marco.melorio@protonmail.com>
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#pragma once

#include "patterns-page.h"

G_BEGIN_DECLS

#define PATTERNS_TYPE_PAGE_VIEW_SWITCHER (patterns_page_view_switcher_get_type())

G_DECLARE_FINAL_TYPE (PatternsPageViewSwitcher, patterns_page_view_switcher, PATTERNS, PAGE_VIEW_SWITCHER, PatternsPage)

G_END_DECLS
