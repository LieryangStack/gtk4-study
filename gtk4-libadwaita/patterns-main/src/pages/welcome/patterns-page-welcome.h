/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#pragma once

#include "patterns-page.h"

G_BEGIN_DECLS

#define PATTERNS_TYPE_PAGE_WELCOME (patterns_page_welcome_get_type())

G_DECLARE_FINAL_TYPE (PatternsPageWelcome, patterns_page_welcome, PATTERNS, PAGE_WELCOME, PatternsPage)

G_END_DECLS
