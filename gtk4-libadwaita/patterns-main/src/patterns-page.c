/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#include "patterns-config.h"
#include "patterns-page.h"

typedef struct
{
  gboolean show_back_button;
  char *title;
  GtkWidget *child;

  GtkWidget *header_bar;
  GtkWidget *child_bin;
} PatternsPagePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (PatternsPage, patterns_page, GTK_TYPE_WIDGET)

enum {
  PROP_0,
  PROP_SHOW_BACK_BUTTON,
  PROP_TITLE,
  PROP_CHILD,
  LAST_PROP
};

static GParamSpec *props[LAST_PROP];

static inline void
set_string (char       **dest,
            const char  *source)
{
  if (*dest)
    g_free (*dest);

  *dest = g_strdup (source);
}

static void
patterns_page_dispose (GObject *object)
{
  PatternsPage *self = PATTERNS_PAGE (object);
  PatternsPagePrivate *priv = patterns_page_get_instance_private (self);

  gtk_widget_unparent (priv->header_bar);
  gtk_widget_unparent (priv->child_bin);
  g_clear_object (&priv->child);

  G_OBJECT_CLASS (patterns_page_parent_class)->dispose (object);
}

static void
patterns_page_finalize (GObject *object)
{
  PatternsPage *self = PATTERNS_PAGE (object);
  PatternsPagePrivate *priv = patterns_page_get_instance_private (self);

  g_clear_pointer (&priv->title, g_free);

  G_OBJECT_CLASS (patterns_page_parent_class)->finalize (object);
}

static void
patterns_page_get_property (GObject    *object,
                            guint       prop_id,
                            GValue     *value,
                            GParamSpec *pspec)
{
  PatternsPage *self = PATTERNS_PAGE (object);
  PatternsPagePrivate *priv = patterns_page_get_instance_private (self);

  switch (prop_id) {
  case PROP_SHOW_BACK_BUTTON:
    g_value_set_boolean (value, priv->show_back_button);
    break;
  case PROP_TITLE:
    g_value_set_string (value, priv->title);
    break;
  case PROP_CHILD:
    g_value_set_object (value, priv->child);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
  }
}

static void
patterns_page_set_property (GObject      *object,
                            guint         prop_id,
                            const GValue *value,
                            GParamSpec   *pspec)
{
  PatternsPage *self = PATTERNS_PAGE (object);
  PatternsPagePrivate *priv = patterns_page_get_instance_private (self);

  switch (prop_id) {
  case PROP_SHOW_BACK_BUTTON:
    priv->show_back_button = g_value_get_boolean (value);
    break;
  case PROP_TITLE:
    set_string (&priv->title, g_value_get_string (value));
    break;
  case PROP_CHILD:
    g_set_object (&priv->child, g_value_get_object (value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
  }
}

static void
patterns_page_class_init (PatternsPageClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->dispose = patterns_page_dispose;
  object_class->finalize = patterns_page_finalize;
  object_class->get_property = patterns_page_get_property;
  object_class->set_property = patterns_page_set_property;

  props[PROP_SHOW_BACK_BUTTON] =
    g_param_spec_boolean ("show-back-button",
                          "Show Back Button",
                          "Show Back Button",
                          FALSE,
                          G_PARAM_READWRITE);

  props[PROP_TITLE] =
    g_param_spec_string ("title",
                         "Title",
                         "Title",
                         NULL,
                         G_PARAM_READWRITE);

  props[PROP_CHILD] =
    g_param_spec_object ("child",
                         "Child",
                         "Child",
                         GTK_TYPE_WIDGET,
                         G_PARAM_READWRITE);

  g_object_class_install_properties (object_class, LAST_PROP, props);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Patterns/patterns-page.ui");
  gtk_widget_class_bind_template_child_private (widget_class, PatternsPage, header_bar);
  gtk_widget_class_bind_template_child_private (widget_class, PatternsPage, child_bin);
}

static void
patterns_page_init (PatternsPage *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}
