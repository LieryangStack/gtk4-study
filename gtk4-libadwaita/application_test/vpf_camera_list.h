#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define VPF_TYPE_CAMERA_LIST (vpf_camera_list_get_type())

/**
 * FINAL定义类（类结构体内部由宏展开，类结构体没有自定义数据，实例结构体需要自己定义） 
 * 宏展开如下：
 * typedef struct _VpfApplication VpfApplication;
 * typedef struct _VpfApplicationClass VpfApplicationClass{
 *   AdwApplicationClass parent_class;   
 * };
*/
G_DECLARE_FINAL_TYPE (VpfCameraList, vpf_camera_list, VPF, CAMERA_LIST, GObject)

VpfCameraList *
vpf_camera_list_new ();

G_END_DECLS