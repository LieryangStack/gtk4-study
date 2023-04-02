/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#pragma once

#include "patterns-page.h"

G_BEGIN_DECLS

#define PATTERNS_TYPE_PAGE_STUB (patterns_page_stub_get_type())

G_DECLARE_FINAL_TYPE (PatternsPageStub, patterns_page_stub, PATTERNS, PAGE_STUB, PatternsPage)

G_END_DECLS
