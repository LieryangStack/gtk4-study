#include <gtk/gtk.h>
#include "tfetextview.h"

/**
 * @brief: 在堆区开辟空间，格式化拷贝一份字符串，给notebook的label使用
 *         如果返回的字符串不再使用，一定要使用 g_free() 释放内存
*/
static char*
get_untitled () {
  static int c = -1;
  if (++c == 0) 
    return g_strdup_printf("Untitled");
  else
    return g_strdup_printf ("Untitled%u", c);
}

static TfeTextView *
get_current_textview (GtkNotebook *nb) {
  int i;
  GtkWidget *scr;
  GtkWidget *tv;

  i = gtk_notebook_get_current_page (nb);
  scr = gtk_notebook_get_nth_page (nb, i);
  tv = gtk_scrolled_window_get_child (GTK_SCROLLED_WINDOW (scr));
  return TFE_TEXT_VIEW (tv);
}

/**
 * @brief: 新建一个notebook页面
*/
static void
notebook_page_build (GtkNotebook *nb, GtkWidget *tv, const char *filename) {
  GtkWidget *scr = gtk_scrolled_window_new ();
  GtkNotebookPage *nbp;
  GtkWidget *lab;
  int i;

  gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scr), tv);
  lab = gtk_label_new (filename);
  i = gtk_notebook_append_page (nb, scr, lab);
  nbp = gtk_notebook_get_page (nb, scr);
  g_object_set (nbp, "tab-expand", TRUE, NULL);
  gtk_notebook_set_current_page (nb, i);
  g_signal_connect (GTK_TEXT_VIEW (tv), "change-file", G_CALLBACK (file_changed_cb), nb);
}

/**
 * @brief: 改变GtkNotebook实例标签的名称
 *         该函数被连接到 "change-file" 信号
 *         “ change-file ” 信号由TfeTextView实例发出
*/
static void
file_changed_cb (TfeTextView *tv, GtkNotebook *nb) {
  GtkWidget *scr;
  GtkWidget *label;
  GFile *file;
  char *filename;

  /* tfe_text_view_get_file 函数中的GFile 拷贝了一份，所以用完需要解引用 */
  file = tfe_text_view_get_file (tv);
  scr = gtk_widget_get_parent (GTK_WIDGET (tv));
  if (G_IS_FILE (file)) {
    filename = g_file_get_basename (file);
    g_object_unref (file);
  } else
    filename = get_untitled ();
  label = gtk_label_new (filename);
  g_free (filename);
  gtk_notebook_set_tab_label (nb, scr, label);
}

/**
 * @brief: "open-response" 信号的回调函数
 *         新建notebook页面
*/
static void
open_response (TfeTextView *tv, int response, GtkNotebook *nb) {
  GFile *file;
  char *filename;

  if (response != TFE_OPEN_RESPONSE_SUCCESS) {
    g_object_ref_sink (tv);
    g_object_unref (tv);
  }else {
    file = tfe_text_view_get_file (tv);
    filename = g_file_get_basename (file);
    g_object_unref (file);
    notebook_page_build (nb, GTK_WIDGET (tv), filename);
    g_free (filename);
  }
}

/**
 * 将当前页面保存到选项卡中指定的文件中。
 * 如果名称是untitled或untitled后跟数字，则会出现FileChooserDialog，
 * 用户可以选择或指定文件名 
*/
void
notebook_page_save (GtkNotebook *nb) {
  g_return_if_fail(GTK_IS_NOTEBOOK (nb));

  TfeTextView *tv;

  tv = get_current_textview (nb);
  tfe_text_view_save (TFE_TEXT_VIEW (tv));
}

/**
 * 关闭当前页面
*/
void
notebook_page_close (GtkNotebook *nb) {
  g_return_if_fail(GTK_IS_NOTEBOOK (nb));

  GtkWidget *win;
  int i;

  if (gtk_notebook_get_n_pages (nb) == 1) {
    win = gtk_widget_get_ancestor (GTK_WIDGET (nb), GTK_TYPE_WINDOW);
    gtk_window_destroy(GTK_WINDOW (win));
  } else {
    i = gtk_notebook_get_current_page (nb);
    gtk_notebook_remove_page (GTK_NOTEBOOK (nb), i);
  }
}

/**
 * 显示一个文件选择器对话框，用户可以选择一个文件。
 * 该文件被插入到一个新页。
*/
void
notebook_page_open (GtkNotebook *nb) {
  g_return_if_fail(GTK_IS_NOTEBOOK (nb));

  GtkWidget *tv;

  if ((tv = tfe_text_view_new ()) == NULL)
    return;
  g_signal_connect (TFE_TEXT_VIEW (tv), "open-response", G_CALLBACK (open_response), nb);
  tfe_text_view_open (TFE_TEXT_VIEW (tv), GTK_WINDOW (gtk_widget_get_ancestor (GTK_WIDGET (nb), GTK_TYPE_WINDOW)));
}

/**
 * 创建一个新页，读取一个文件并将其作为参数插入到该页中。
*/
void
notebook_page_new_with_file (GtkNotebook *nb, GFile *file) {
  g_return_if_fail(GTK_IS_NOTEBOOK (nb));
  g_return_if_fail(G_IS_FILE (file));

  GtkWidget *tv;
  char *filename;

  if ((tv = tfe_text_view_new_with_file (file)) == NULL)
    return; /* read error */
  filename = g_file_get_basename (file);
  notebook_page_build (nb, tv, filename);
  g_free (filename);
}

/**
 * 创建一个新的空页
*/
void
notebook_page_new (GtkNotebook *nb) {
  g_return_if_fail(GTK_IS_NOTEBOOK (nb));

  GtkWidget *tv;
  char *filename;

  if ((tv = tfe_text_view_new ()) == NULL)
    return;
  filename = get_untitled ();
  notebook_page_build (nb, tv, filename);
  g_free (filename);
}
