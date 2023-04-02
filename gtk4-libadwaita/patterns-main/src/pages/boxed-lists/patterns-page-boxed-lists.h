/*
 * Copyright (C) 2021 Purism SPC
 * Copyright (C) 2021 Marco Melorio <marco.melorio@protonmail.com>
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#pragma once

#include "patterns-page.h"

G_BEGIN_DECLS

#define PATTERNS_TYPE_PAGE_BOXED_LISTS (patterns_page_boxed_lists_get_type())

G_DECLARE_FINAL_TYPE (PatternsPageBoxedLists, patterns_page_boxed_lists, PATTERNS, PAGE_BOXED_LISTS, PatternsPage)

G_END_DECLS
