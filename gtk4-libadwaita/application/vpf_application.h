#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define VPF_TYPE_APPLICATION (vpf_application_get_type())

/**
 * FINAL定义类（类结构体内部由宏展开，类结构体没有自定义数据，实例结构体需要自己定义） 
 * 宏展开如下：
 * typedef struct _VpfApplication VpfApplication;
 * typedef struct _VpfApplicationClass VpfApplicationClass{
 *   AdwApplicationClass parent_class;   
 * };
*/
G_DECLARE_FINAL_TYPE (VpfApplication, vpf_application, VPF, APPLICATION, AdwApplication)

GApplication *vpf_application_new (const char *application_id,
                                   GApplicationFlags  flags);

G_END_DECLS
