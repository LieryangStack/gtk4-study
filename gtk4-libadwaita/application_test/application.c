#include <adwaita.h>
#include "vpf_camera_list.h"
#include "vpf_detect_set_list.h"
//#include "resource.c"

static GListModel *
create_cameral_list_model () {
  /**
   * 新建GListStore对象增加一个引用计数，
   * 添加到store里面会增加一个引用基数（仅是地址存储）
   * 用完最后需要从store移除对象
  */
  GListStore *store = g_list_store_new (VPF_TYPE_CAMERA_LIST);
  VpfCameraList *l1, *l2, *l3;
  guint p = 0;
 
  l1 = vpf_camera_list_new ();
  g_object_set (l1,"view1-select-status", 1, "view2-select-status", 1, "type", "网络摄像头", "link-param", "/usr/dec", "serial-number", "Sx86ki", 
                    "user", "admin", "password", "lieryang", "active-status", "未激活", "add-status", "未添加", "network-status", "在线", "out1", 0, "out2", 2, NULL);
  g_list_store_append (store, l1);
  g_object_unref (l1);

  l2 = vpf_camera_list_new ();
  g_object_set (l2,"view1-select-status", 1, "view2-select-status", 1, "type", "VEYE摄像头", "link-param", "/usr/dec", "serial-number", "Sx86ki", 
                    "user", "admin", "password", "lieryang", "active-status", "未激活", "add-status", "未添加", "network-status", "在线", "out1", 1, "out2", 1, NULL);
  g_list_store_append (store, l2);
  g_object_unref (l2);

  l3 = vpf_camera_list_new ();
  g_object_set (l3,"view1-select-status", 1, "view2-select-status", 1, "type", "网络摄像头", "link-param", "/usr/dec", "serial-number", "Sx86ki", 
                    "user", "admin", "password", "lieryang", "active-status", "未激活", "add-status", "未添加", "network-status", "在线", "out1", 2, "out2", 0, NULL);
  g_list_store_append (store, l3);
  g_object_unref (l3);

  return G_LIST_MODEL (store);
}

static GListModel *
create_detect_set_list_model () {
  /**
   * 新建GListStore对象增加一个引用计数，
   * 添加到store里面会增加一个引用基数（仅是地址存储）
   * 用完最后需要从store移除对象
  */
  GListStore *store = g_list_store_new (VPF_TYPE_DETECT_SET_LIST);
  VpfDetectSetList *l1, *l2, *l3;
  guint p = 0;
 
  l1 = vpf_detect_set_list_new ();
  g_object_set (l1, "type", "行人", NULL);
  g_list_store_append (store, l1);
  g_object_unref (l1);

  l2 = vpf_detect_set_list_new ();
  g_object_set (l2, "type", "车辆", NULL);
  g_list_store_append (store, l2);
  g_object_unref (l2);

  l3 = vpf_detect_set_list_new ();
  g_object_set (l3, "type", "动物", NULL);
  g_list_store_append (store, l3);
  g_object_unref (l3);

  return G_LIST_MODEL (store);
}


static void 
app_activate (GApplication *app, gpointer *user_data) {
  // GtkIconTheme *theme = gtk_icon_theme_get_for_display (gdk_display_get_default ());
  // gtk_icon_theme_add_resource_path (theme, "/test/icons");
  GListModel *model = create_cameral_list_model();
  GListModel *detect_set_list_model = create_detect_set_list_model();
  GtkBuilder *build = gtk_builder_new_from_file ("application_bck.ui");
  GtkWidget *win = GTK_WIDGET (gtk_builder_get_object (build, "main_win"));
  GtkWidget *picture = GTK_WIDGET (gtk_builder_get_object (build, "picture"));

  GtkSingleSelection *selection1 = gtk_single_selection_new (G_LIST_MODEL (model));
  GtkSingleSelection *selection2 = gtk_single_selection_new (G_LIST_MODEL (model));
  GtkSingleSelection *selection3 = gtk_single_selection_new (G_LIST_MODEL (detect_set_list_model));
  GtkWidget *set_detect_column_view = GTK_WIDGET (gtk_builder_get_object (build, "set_detect_column_view"));
  GtkWidget *set_add_camera_column_view = GTK_WIDGET (gtk_builder_get_object (build, "set_add_camera_column_view"));
  GtkWidget *set_all_camera_column_view = GTK_WIDGET (gtk_builder_get_object (build, "set_all_camera_column_view"));

  gtk_column_view_set_model (GTK_COLUMN_VIEW (set_detect_column_view), GTK_SELECTION_MODEL (selection3));
  gtk_column_view_set_model (GTK_COLUMN_VIEW (set_add_camera_column_view), GTK_SELECTION_MODEL (selection1));
  gtk_column_view_set_model (GTK_COLUMN_VIEW (set_all_camera_column_view), GTK_SELECTION_MODEL (selection2));

  gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));
  //adw_style_manager_set_color_scheme(adw_style_manager_get_default(), ADW_COLOR_SCHEME_PREFER_DARK);
  gtk_picture_set_filename (GTK_PICTURE (picture), "/home/lieryang/Pictures/300x200.jpg");

  gtk_window_present (GTK_WINDOW (win));
}

int
main (int argc, char *argv[]) {
  g_autoptr (AdwApplication) app = adw_application_new ("test.application", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
  return g_application_run (G_APPLICATION (app), argc, argv);
}
