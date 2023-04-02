#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define VPF_TYPE_APPLICATION_WINDOW (vpf_application_window_get_type())

/**
 * FINAL定义类（类结构体内部由宏展开，类结构体没有自定义数据，实例结构体需要自己定义） 
 * 宏展开如下：
 * typedef struct _VpfApplication VpfApplication;
 * typedef struct _VpfApplicationClass VpfApplicationClass{
 *   AdwApplicationClass parent_class;   
 * };
*/
G_DECLARE_FINAL_TYPE (VpfApplicationWindow, vpf_application_window, VPF, APPLICATION_WINDOW, AdwApplicationWindow)

GtkWidget *vpf_application_window_new (GtkApplication *app);


G_END_DECLS
