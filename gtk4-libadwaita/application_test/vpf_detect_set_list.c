#include "vpf_detect_set_list.h"

struct _VpfDetectSetList {
  GObject parent;

  gchararray type;
  guint border_color;
  guint background_color;
  gboolean active;
};

enum {
  PROP_0,
  PROP_TYPE,
  PROP_BORDER_COLOR,
  PROP_BACKGROUND_COLOR,
  PROP_ACTIVE,

  N_PROPS
};

G_DEFINE_TYPE (VpfDetectSetList, vpf_detect_set_list, G_TYPE_OBJECT)
static GParamSpec *properties[N_PROPS] = { NULL, };

static void
vpf_detect_set_list_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec) {
  VpfDetectSetList *self = VPF_DETECT_SET_LIST (object);

  switch (property_id) {
    case PROP_TYPE :
      self->type = g_strdup (g_value_get_string (value));
      break;
    case PROP_BORDER_COLOR :
      self->border_color = g_value_get_uint (value);
      break;
    case PROP_BACKGROUND_COLOR :
      self->background_color = g_value_get_uint (value);
      break;
    case PROP_ACTIVE :
      self->active = g_value_get_boolean (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
  }

}

static void
vpf_detect_set_list_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec) {
  VpfDetectSetList *self = VPF_DETECT_SET_LIST (object);

  switch (property_id) {
    case PROP_TYPE :
      g_value_set_string (value, self->type);
      break;
    case PROP_BORDER_COLOR :
      g_value_set_uint (value, self->border_color);
      break;
    case PROP_BACKGROUND_COLOR :
      g_value_set_uint (value, self->background_color);
      break;
    case PROP_ACTIVE :
      g_value_set_boolean (value, self->active);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
  }
}

static void
vpf_detect_set_list_finalize (GObject *object) {
  VpfDetectSetList *self = VPF_DETECT_SET_LIST (object);
  if (self->type) {
    g_free (self->type);
    self->type = NULL;
  }
  G_OBJECT_CLASS (vpf_detect_set_list_parent_class)->finalize (object);
}

static void
vpf_detect_set_list_class_init (VpfDetectSetListClass *class) {
  GObjectClass *gobject_class = G_OBJECT_CLASS (class);

  gobject_class->finalize = vpf_detect_set_list_finalize;
  gobject_class->set_property = vpf_detect_set_list_set_property;
  gobject_class->get_property = vpf_detect_set_list_get_property;

  properties[PROP_TYPE] = g_param_spec_string ("type", NULL, NULL, NULL, G_PARAM_READWRITE);
  properties[PROP_BORDER_COLOR] = g_param_spec_uint ("border-color", NULL, NULL, 0, 10, 0, G_PARAM_READWRITE);
  properties[PROP_BACKGROUND_COLOR] = g_param_spec_uint ("background-color", NULL, NULL, 0, 10, 0, G_PARAM_READWRITE);
  properties[PROP_ACTIVE] = g_param_spec_boolean ("active", NULL, NULL, 0, G_PARAM_READWRITE);

  g_object_class_install_properties (gobject_class, N_PROPS, properties);
}

static void
vpf_detect_set_list_init (VpfDetectSetList *self) {

}

VpfDetectSetList *
vpf_detect_set_list_new () {
  return g_object_new (VPF_TYPE_DETECT_SET_LIST, NULL);
}




