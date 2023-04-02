/*
 * Copyright (C) 2021 Purism SPC
 * Copyright (C) 2021 Marco Melorio <marco.melorio@protonmail.com>
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#include "patterns-config.h"
#include "patterns-window.h"

#include <glib/gi18n.h>

#include "patterns-page-info.h"

#include "pages/boxed-lists/patterns-page-boxed-lists.h"
#include "pages/controls/patterns-page-controls.h"
#include "pages/stub/patterns-page-stub.h"
#include "pages/utility-pane/patterns-page-utility-pane.h"
#include "pages/view-switcher/patterns-page-view-switcher.h"
#include "pages/welcome/patterns-page-welcome.h"
#include "pages/windows/patterns-page-windows.h"

struct _PatternsWindow
{
  AdwApplicationWindow  parent_instance;

  AdwLeaflet *leaflet;
  GListStore *list;
};

G_DEFINE_TYPE (PatternsWindow, patterns_window, ADW_TYPE_APPLICATION_WINDOW)

static char *
get_results_page (PatternsWindow *self,
                  guint           selected)
{
  return g_strdup (selected == GTK_INVALID_LIST_POSITION ? "empty" : "list");
}

static GObject *
new_page_cb (PatternsWindow *self,
             GType           type)
{
  return g_object_ref (g_object_new (type, NULL));
}

static void
list_activate_cb (PatternsWindow *self)
{
  adw_leaflet_navigate (self->leaflet, ADW_NAVIGATION_DIRECTION_FORWARD);
}

static void
folded_notify_cb (PatternsWindow *self)
{
  gtk_widget_action_set_enabled (GTK_WIDGET (self), "leaflet.back",
                                 adw_leaflet_get_folded (self->leaflet));
}

static void
leaflet_back_activate_cb (PatternsWindow *self,
                          const char    *action_name,
                          GVariant      *parameter)
{
  adw_leaflet_navigate (self->leaflet, ADW_NAVIGATION_DIRECTION_BACK);
}

static void
patterns_window_class_init (PatternsWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  // TODO: these should be on the leaflet instead
  gtk_widget_class_install_action (widget_class, "leaflet.back", NULL,
                                   (GtkWidgetActionActivateFunc) leaflet_back_activate_cb);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Patterns/patterns-window.ui");
  gtk_widget_class_bind_template_child (widget_class, PatternsWindow, leaflet);
  gtk_widget_class_bind_template_child (widget_class, PatternsWindow, list);
  gtk_widget_class_bind_template_callback (widget_class, new_page_cb);
  gtk_widget_class_bind_template_callback (widget_class, list_activate_cb);
  gtk_widget_class_bind_template_callback (widget_class, folded_notify_cb);
  gtk_widget_class_bind_template_callback (widget_class, get_results_page);
}

#define ADD_PAGE(list, title, icon, type) g_list_store_append ((list), patterns_page_info_new ((title), (icon), (type)));
#define ADD_STUB(list, title, icon) ADD_PAGE ((list), (title), (icon), PATTERNS_TYPE_PAGE_STUB);

static void
patterns_window_init (PatternsWindow *self)
{
  g_type_ensure (PATTERNS_TYPE_PAGE_INFO);

  gtk_widget_init_template (GTK_WIDGET (self));

  ADD_PAGE (self->list, _("Welcome"), "page-welcome-symbolic", PATTERNS_TYPE_PAGE_WELCOME);

  ADD_PAGE (self->list, _("Windows"), "page-windows-symbolic", PATTERNS_TYPE_PAGE_WINDOWS);
  ADD_PAGE (self->list, _("Utility Pane"), "page-utility-pane-symbolic", PATTERNS_TYPE_PAGE_UTILITY_PANE);
  ADD_PAGE (self->list, _("Boxed Lists"), "page-boxed-lists-symbolic", PATTERNS_TYPE_PAGE_BOXED_LISTS);
  ADD_STUB (self->list, _("Grid View"), "page-grid-view-symbolic");
  ADD_STUB (self->list, _("List View"), "page-list-view-symbolic");
  ADD_STUB (self->list, _("Column View"), "page-column-view-symbolic");

  ADD_STUB (self->list, _("Sidebar"), "page-sidebar-symbolic");
  ADD_PAGE (self->list, _("View Switcher"), "page-view-switcher-symbolic", PATTERNS_TYPE_PAGE_VIEW_SWITCHER);
  ADD_STUB (self->list, _("Tabs"), "page-tabs-symbolic");

  ADD_PAGE (self->list, _("Controls"), "page-controls-symbolic", PATTERNS_TYPE_PAGE_CONTROLS);
  ADD_STUB (self->list, _("Feedback"), "page-feedback-symbolic");

  folded_notify_cb (self);
}

GtkWidget *
patterns_window_new (GtkApplication *app)
{
  g_return_val_if_fail (GTK_IS_APPLICATION (app), NULL);
  return g_object_new (PATTERNS_TYPE_WINDOW,
                       "application", app,
                       NULL);
}
