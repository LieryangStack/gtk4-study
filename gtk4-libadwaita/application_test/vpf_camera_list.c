#include "vpf_camera_list.h"

struct _VpfCameraList {
  GObject parent;

  gchararray type;
  guint out1;
  guint out2;

  gchararray link_param;
  gchararray serial_number;
  gchararray user;
  gchararray password;

  gchararray active_status;
  gchararray add_status;
  gchararray network_status;

  gboolean view1_select_status;
  gboolean view2_select_status;
  
};

enum {
  PROP_0,
  PROP_TYPE,
  PROP_LINK_PARAM,
  PROP_SERIAL_NUMBER,
  PROP_USER,
  PROP_PASSWORD,
  PROP_ACTIVE_STATUS,
  PROP_ADD_STATUS,
  PROP_NETWORK_STATUS,
  PROP_OUT1,
  PROP_OUT2,
  PROP_VIEW1_SELECT_STATUS,
  PROP_VIEW2_SELECT_STATUS,

  N_PROPS
};

G_DEFINE_TYPE (VpfCameraList, vpf_camera_list, G_TYPE_OBJECT)
static GParamSpec *properties[N_PROPS] = { NULL, };

static void
vpf_camera_list_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec) {
  VpfCameraList *self = VPF_CAMERA_LIST (object);

  switch (property_id) {
    case PROP_TYPE :
      self->type = g_strdup (g_value_get_string (value));
      break;
    case PROP_LINK_PARAM :
      self->link_param = g_strdup (g_value_get_string (value));
      break;
    case PROP_SERIAL_NUMBER :
      self->serial_number = g_strdup (g_value_get_string (value));
      break;
    case PROP_USER :
      self->user = g_strdup (g_value_get_string (value));
      break;
    case PROP_PASSWORD :
      self->password = g_strdup (g_value_get_string (value));
      break;
    case PROP_ACTIVE_STATUS :
      self->active_status = g_strdup (g_value_get_string (value));
      break;
    case PROP_ADD_STATUS :
      self->add_status = g_strdup (g_value_get_string (value));
      break;
    case PROP_NETWORK_STATUS :
      self->network_status = g_strdup (g_value_get_string (value));
      break;
    case PROP_OUT1 :
      self->out1 = g_value_get_uint (value);
      break;
    case PROP_OUT2 :
      self->out2 = g_value_get_uint (value);
      break;
    case PROP_VIEW1_SELECT_STATUS :
      self->view1_select_status = g_value_get_boolean (value);
      break;
    case PROP_VIEW2_SELECT_STATUS :
      self->view2_select_status = g_value_get_boolean (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
  }

}

static void
vpf_camera_list_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec) {
  VpfCameraList *self = VPF_CAMERA_LIST (object);

  switch (property_id) {
    case PROP_TYPE :
      g_value_set_string (value, self->type);
      break;
    case PROP_LINK_PARAM :
      g_value_set_string (value, self->link_param);
      break;
    case PROP_SERIAL_NUMBER :
      g_value_set_string (value, self->serial_number);
      break;
    case PROP_USER :
      g_value_set_string (value, self->user);
      break;
    case PROP_PASSWORD :
      g_value_set_string (value, self->password);
      break;
    case PROP_ACTIVE_STATUS :
      g_value_set_string (value, self->active_status);
      break;
    case PROP_ADD_STATUS :
      g_value_set_string (value, self->add_status);
      break;
    case PROP_NETWORK_STATUS :
      g_value_set_string (value, self->network_status);
      break;
    case PROP_OUT1 :
      g_value_set_uint (value, self->out1);
      break;
    case PROP_OUT2 :
      g_value_set_uint (value, self->out2);
      break;
    case PROP_VIEW1_SELECT_STATUS :
      g_value_set_boolean (value, self->view1_select_status);
      break;
    case PROP_VIEW2_SELECT_STATUS :
      g_value_set_boolean (value, self->view2_select_status);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
  }
}

static void
vpf_camera_list_finalize (GObject *object)
{
  VpfCameraList *self = VPF_CAMERA_LIST (object);
  if (self->type) {
    g_free (self->type);
    self->type = NULL;
  }
  if (self->link_param) {
    g_free (self->link_param);
    self->link_param = NULL;
  }
  if (self->serial_number) {
    g_free (self->serial_number);
    self->serial_number = NULL;
  }
  if (self->user) {
    g_free (self->user);
    self->user = NULL;
  }
  if (self->password) {
    g_free (self->password);
    self->password = NULL;
  }
  if (self->active_status) {
    g_free (self->active_status);
    self->active_status = NULL;
  }
  if (self->add_status) {
    g_free (self->add_status);
    self->add_status = NULL;
  }
  if (self->network_status) {
    g_free (self->network_status);
    self->network_status = NULL;
  }
  G_OBJECT_CLASS (vpf_camera_list_parent_class)->finalize (object);
}

static void
vpf_camera_list_class_init (VpfCameraListClass *class) {
  GObjectClass *gobject_class = G_OBJECT_CLASS (class);

  gobject_class->finalize = vpf_camera_list_finalize;
  gobject_class->set_property = vpf_camera_list_set_property;
  gobject_class->get_property = vpf_camera_list_get_property;

  properties[PROP_TYPE] = g_param_spec_string ("type", NULL, NULL, NULL, G_PARAM_READWRITE);
  properties[PROP_LINK_PARAM] = g_param_spec_string ("link-param", NULL, NULL, NULL, G_PARAM_READWRITE);
  properties[PROP_SERIAL_NUMBER] = g_param_spec_string ("serial-number", NULL, NULL, NULL, G_PARAM_READWRITE);
  properties[PROP_USER] = g_param_spec_string ("user", NULL, NULL, NULL, G_PARAM_READWRITE);
  properties[PROP_PASSWORD] = g_param_spec_string ("password", NULL, NULL, NULL, G_PARAM_READWRITE);
  properties[PROP_ACTIVE_STATUS] = g_param_spec_string ("active-status", NULL, NULL, NULL, G_PARAM_READWRITE);
  properties[PROP_ADD_STATUS] = g_param_spec_string ("add-status", NULL, NULL, NULL, G_PARAM_READWRITE);
  properties[PROP_NETWORK_STATUS] = g_param_spec_string ("network-status", NULL, NULL, NULL, G_PARAM_READWRITE);
  properties[PROP_OUT1] = g_param_spec_uint ("out1", NULL, NULL, 0, 10, 0, G_PARAM_READWRITE);
  properties[PROP_OUT2] = g_param_spec_uint ("out2", NULL, NULL, 0, 10, 0, G_PARAM_READWRITE);
  properties[PROP_VIEW1_SELECT_STATUS] = g_param_spec_boolean ("view1-select-status", NULL, NULL, 0, G_PARAM_READWRITE);
  properties[PROP_VIEW2_SELECT_STATUS] = g_param_spec_boolean ("view2-select-status", NULL, NULL, 0, G_PARAM_READWRITE);

  g_object_class_install_properties (gobject_class, N_PROPS, properties);
}

static void
vpf_camera_list_init (VpfCameraList *self) {

}

VpfCameraList *
vpf_camera_list_new () {
  return g_object_new (VPF_TYPE_CAMERA_LIST, NULL);
}




