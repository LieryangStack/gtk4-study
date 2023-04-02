/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define PATTERNS_TYPE_PAGE_INFO (patterns_page_info_get_type())

G_DECLARE_FINAL_TYPE (PatternsPageInfo, patterns_page_info, PATTERNS, PAGE_INFO, GObject)

PatternsPageInfo *patterns_page_info_new (const char *title,
                                         const char *icon_name,
                                          GType       type);

G_END_DECLS
