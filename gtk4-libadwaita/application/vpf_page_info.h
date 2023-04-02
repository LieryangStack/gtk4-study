/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define VPF_TYPE_PAGE_INFO (vpf_page_info_get_type())

G_DECLARE_FINAL_TYPE (VpfPageInfo, vpf_page_info, VPF, PAGE_INFO, GObject)

VpfPageInfo *vpf_page_info_new (const char *title,
                                     const char *icon_name,
                                     GType       type);

G_END_DECLS
