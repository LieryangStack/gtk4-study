#include <glib/gi18n.h>
#include "vpf_page_info.h"

struct _VpfPageInfo
{
  GObject parent_instance;

  char *icon_name;
  char *title;
  GType gtype;
};

G_DEFINE_TYPE (VpfPageInfo, vpf_page_info, G_TYPE_OBJECT)

enum {
  PROP_0,
  PROP_ICON_NAME,
  PROP_TITLE,
  PROP_GTYPE,
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
vpf_page_info_finalize (GObject *object)
{
  VpfPageInfo *self = VPF_PAGE_INFO (object);

  g_clear_pointer (&self->title, g_free);
  g_clear_pointer (&self->icon_name, g_free);

  G_OBJECT_CLASS (vpf_page_info_parent_class)->finalize (object);
}

static void
vpf_page_info_get_property (GObject    *object,
                                 guint       prop_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
  VpfPageInfo *self = VPF_PAGE_INFO (object);

  switch (prop_id) {
  case PROP_ICON_NAME:
    g_value_set_string (value, self->icon_name);
    break;
  case PROP_TITLE:
    g_value_set_string (value, self->title);
    break;
  case PROP_GTYPE:
    g_value_set_gtype (value, self->gtype);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
  }
}

static void
vpf_page_info_set_property (GObject      *object,
                                 guint         prop_id,
                                 const GValue *value,
                                 GParamSpec   *pspec)
{
  VpfPageInfo *self = VPF_PAGE_INFO (object);

  switch (prop_id) {
  case PROP_ICON_NAME:
    set_string (&self->icon_name, g_value_get_string (value));
    break;
  case PROP_TITLE:
    set_string (&self->title, g_value_get_string (value));
    break;
  case PROP_GTYPE:
    self->gtype = g_value_get_gtype (value);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
  }
}

static void
vpf_page_info_class_init (VpfPageInfoClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = vpf_page_info_finalize;
  object_class->get_property = vpf_page_info_get_property;
  object_class->set_property = vpf_page_info_set_property;

  props[PROP_ICON_NAME] =
    g_param_spec_string ("icon-name",
                         "Icon Name",
                         "Icon Name",
                         NULL,
                         G_PARAM_READWRITE);

  props[PROP_TITLE] =
    g_param_spec_string ("title",
                         "Title",
                         "Title",
                         NULL,
                         G_PARAM_READWRITE);

  props[PROP_GTYPE] =
    g_param_spec_gtype ("gtype",
                        "Type",
                        "Type",
                        VPF_TYPE_PAGE_INFO,
                        G_PARAM_READWRITE);

  g_object_class_install_properties (object_class, LAST_PROP, props);
}

static void
vpf_page_info_init (VpfPageInfo *self)
{
}

VpfPageInfo *
vpf_page_info_new (const char *title,
                        const char *icon_name,
                        GType       type)
{
  return g_object_new (VPF_TYPE_PAGE_INFO,
                       "title", title,
                       "icon-name", icon_name,
                       "gtype", type,
                       NULL);
}
