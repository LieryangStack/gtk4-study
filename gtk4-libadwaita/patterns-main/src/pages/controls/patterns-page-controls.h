/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#pragma once

#include "patterns-page.h"

G_BEGIN_DECLS

#define PATTERNS_TYPE_PAGE_CONTROLS (patterns_page_controls_get_type())

G_DECLARE_FINAL_TYPE (PatternsPageControls, patterns_page_controls, PATTERNS, PAGE_CONTROLS, PatternsPage)

G_END_DECLS
