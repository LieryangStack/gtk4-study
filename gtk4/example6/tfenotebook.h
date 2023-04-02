#ifndef __TFE_NOTEBOOK_H__
#define __TFE_NOTEBOOK_H__

/**
 * 将当前页面保存到选项卡中指定的文件中。
 * 如果名称是untitled或untitled后跟数字，则会出现FileChooserDialog，
 * 用户可以选择或指定文件名 
*/
void
notebook_page_save(GtkNotebook *nb);

/**
 * 关闭当前页面
*/
void
notebook_page_close (GtkNotebook *nb);

/**
 * 显示一个文件选择器对话框，用户可以选择一个文件。
 * 该文件被插入到一个新页。
*/
void
notebook_page_open (GtkNotebook *nb);

/**
 * 创建一个新页，读取一个文件并将其作为参数插入到该页中。
*/
void
notebook_page_new_with_file (GtkNotebook *nb, GFile *file);

/**
 * 创建一个新的空页
*/
void
notebook_page_new (GtkNotebook *nb);

#endif