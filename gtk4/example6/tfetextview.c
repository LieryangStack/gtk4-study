#include <string.h>
#include "tfetextview.h"

struct _TfeTextView {
  GtkTextView parent;
  GFile *file;
};

G_DEFINE_TYPE (TfeTextView, tfe_text_view, GTK_TYPE_TEXT_VIEW);

enum {
  CHANGE_FILE,
  OPEN_RESPONSE,
  NUMBER_OF_SINGALS
};

static guint tfe_text_view_signals[NUMBER_OF_SINGALS];

static void
tfe_text_view_dispose (GObject *gobject) {
  TfeTextView *tv = TFE_TEXT_VIEW (gobject);

  if (G_IS_FILE (tv->file)) 
    g_clear_object (&tv->file);
  
  G_OBJECT_CLASS (tfe_text_view_parent_class)->dispose (gobject);
}

static void
tfe_text_view_init (TfeTextView *tv) {
  tv->file = NULL;
}

/**
 * @brief: 主要进行了信号注册
 *         "change-file"
 *         "open-response"
*/
static void
tfe_text_view_class_init (TfeTextViewClass *class) {
  GObjectClass *object_class = G_OBJECT_CLASS (class);

  object_class->dispose = tfe_text_view_dispose;
  tfe_text_view_signals[CHANGE_FILE] = g_signal_new ("change-file",
                                 G_TYPE_FROM_CLASS (class),
                                 G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                                 0 /* class offset */,
                                 NULL /* accumulator */,
                                 NULL /* accumulator data */,
                                 NULL /* C marshaller */,
                                 G_TYPE_NONE /* return_type */,
                                 0     /* n_params */
                                 );
  tfe_text_view_signals[OPEN_RESPONSE] = g_signal_new ("open-response",
                                 G_TYPE_FROM_CLASS (class),
                                 G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                                 0 /* class offset */,
                                 NULL /* accumulator */,
                                 NULL /* accumulator data */,
                                 NULL /* C marshaller */,
                                 G_TYPE_NONE /* return_type */,
                                 1     /* n_params */,
                                 G_TYPE_INT
                                 );
}

static void
open_dialog_response (GtkWidget *dialog, gint response, TfeTextView *tv) {
  GtkTextBuffer *tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tv));
  GFile *file;
  char *contents;
  gsize length;
  GtkWidget *message_dialog;
  GError *err = NULL;
  
  /* 如果打开文件成功 response = GTK_RESPONSE_ACCEPT */
  if (response != GTK_RESPONSE_ACCEPT)
    g_signal_emit (tv, tfe_text_view_signals[OPEN_RESPONSE], 0, TFE_OPEN_RESPONSE_CANCEL);
  else if (! G_IS_FILE (file = gtk_file_chooser_get_file (GTK_FILE_CHOOSER (dialog)))) {
    g_warning ("TfeTextView: gtk_file_chooser_get_file returns non GFile.\n");
    g_signal_emit (tv, tfe_text_view_signals[OPEN_RESPONSE], 0, TFE_OPEN_RESPONSE_ERROR);
  } else if (! g_file_load_contents (file, NULL, &contents, &length, NULL, &err)) {
    message_dialog = gtk_message_dialog_new (GTK_WINDOW (dialog), GTK_DIALOG_MODAL,
                        GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", err->message);
    g_signal_connect (message_dialog, "response", G_CALLBACK (gtk_window_destroy), NULL);
    gtk_widget_show (message_dialog);
    g_error_free (err);
    g_signal_emit (tv, tfe_text_view_signals[OPEN_RESPONSE], 0, TFE_OPEN_RESPONSE_ERROR);
  } else {
    gtk_text_buffer_set_text (tb, contents, length);
    g_free (contents);
    gtk_text_buffer_set_modified (tb, FALSE);
    if (! (G_IS_FILE (tv->file) && g_file_equal (tv->file, file)))
      g_signal_emit (tv, tfe_text_view_signals[CHANGE_FILE], 0);
    if (G_IS_FILE (tv->file))
      g_object_unref (tv->file);
    tv->file = file; // The ownership of 'file' moves to TfeTextView
    g_signal_emit (tv, tfe_text_view_signals[OPEN_RESPONSE], 0, TFE_OPEN_RESPONSE_SUCCESS);
  }
  gtk_window_destroy (GTK_WINDOW (dialog));
}

/**
 * @brief: 函数save_file是由saveas_dialog_response和tfe_text_view_save调用的。
 *         该函数将缓冲区的内容保存到作为参数给出的文件中。
 *         如果发生错误，就显示错误消息。因此，这个函数的调用者不需要处理错误
*/
static gboolean
save_file (GFile *file, GtkTextBuffer *tb, GtkWindow *win) {
  GtkTextIter start_iter;
  GtkTextIter end_iter;
  char *contents;
  gboolean stat;
  GtkWidget *message_dialog;
  GError *err = NULL;

  gtk_text_buffer_get_bounds (tb, &start_iter, &end_iter);
  contents = gtk_text_buffer_get_text (tb, &start_iter, &end_iter, FALSE);
  stat = g_file_replace_contents (file, contents, strlen (contents), NULL, TRUE, \
                                  G_FILE_CREATE_NONE, NULL, NULL, &err);
  if (stat)
    /* FALSE表示文件缓冲区已经被修改 */
    gtk_text_buffer_set_modified (tb, FALSE);
  else {
    message_dialog = gtk_message_dialog_new (win, GTK_DIALOG_MODAL,
                                          GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s.", err->message);
    g_signal_connect (message_dialog, "response", G_CALLBACK (gtk_window_destroy), NULL);
    gtk_widget_show (message_dialog);
    g_error_free (err);
  }
  g_free (contents);
  return stat;
}

static void
saveas_dialog_response (GtkWidget *dialog, gint response, TfeTextView *tv) {
  GtkTextBuffer *tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tv));
  GFile *file;
  GtkWidget *win = gtk_widget_get_ancestor (GTK_WIDGET (tv), GTK_TYPE_WINDOW);

  if (response == GTK_RESPONSE_ACCEPT) {
    file = gtk_file_chooser_get_file (GTK_FILE_CHOOSER (dialog));
    if (! G_IS_FILE (file))
      g_warning ("TfeTextView: gtk_file_chooser_get_file returns non GFile.\n");
    else if (save_file (file, tb, GTK_WINDOW (win))) {
      /* 构件中的file 与 dialog中的file 不相等的情况下， 释放构件中的file */
      if (G_IS_FILE (tv->file) && (! g_file_equal (tv->file, file)))
        g_object_unref (tv->file);
      /* 如果 构件中的file=NULL 或者 两个file不相等*/
      if (! (G_IS_FILE (tv->file) && g_file_equal (tv->file, file))) {
        tv->file = file;
        /* 发射一个"change-file"信号 */
        g_signal_emit (tv, tfe_text_view_signals[CHANGE_FILE], 0);
      }
      g_object_unref (file);
    } else 
      g_object_unref (file);
  }
  gtk_window_destroy (GTK_WINDOW (dialog));
}

/**
 * @brief: 公有函数一定要检查参数
 *         这里的 GFile 拷贝了一份，用完一定要解引用
*/
GFile *
tfe_text_view_get_file (TfeTextView *tv) {
  g_return_val_if_fail (TFE_IS_TEXT_VIEW (tv), NULL);

  if (G_IS_FILE (tv->file))
    return g_file_dup (tv->file);
  else  
    return NULL;
}

void 
tfe_text_view_open (TfeTextView *tv, GtkWindow *win) {
  g_return_if_fail (TFE_IS_TEXT_VIEW (tv));
  // 'win' is used for a transient window of the GtkFileChooserDialog.
  // It can be NULL.
  g_return_if_fail (GTK_IS_WINDOW (win) || win == NULL);

  GtkWidget *dialog;

  dialog = gtk_file_chooser_dialog_new ("Open file", win, GTK_FILE_CHOOSER_ACTION_OPEN,
            "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
  g_signal_connect (dialog, "response", G_CALLBACK (open_dialog_response), tv);
  gtk_widget_show (dialog);
}


/**
 * @brief: 函数tfe_text_view_save将GtkTextBuffer中的内容，
 *         写入到tv->file指定的文件中。如果tv->file为NULL，
 *         那么它将显示GtkFileChooserDialog并提示用户选择要保存的文件。
 *         然后它将内容保存到文件中，并设置tv->file为该文件指向GFile实例。
*/
void
tfe_text_view_save (TfeTextView *tv) {
  g_return_if_fail (TFE_IS_TEXT_VIEW (tv));

  GtkTextBuffer *tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tv));
  GtkWidget *win = gtk_widget_get_ancestor (GTK_WIDGET (tv), GTK_TYPE_WINDOW);

  if (! gtk_text_buffer_get_modified (tb))
    return; /* no need to save it */
  else if (tv->file == NULL)
    tfe_text_view_saveas (tv);
  else if (! G_IS_FILE (tv->file)) // Unexpected error
    g_error ("TfeTextView: The pointer tv->file isn't NULL nor GFile.\n");
  else 
    save_file (tv->file, tb, GTK_WINDOW (win));
}

/**
 * @brief: 该函数使用GtkFileChooserDialog并提示用户选择一个已存在的文件或指定一个新文件来保存。
 *         然后，该函数修改tv->file，并将内容保存到指定文件中。
 *         如果发生错误，将通过消息对话框显示给用户。
 *         该错误仅在TfeTextView中进行管理，没有任何信息被通知给调用方。
*/
void 
tfe_text_view_saveas (TfeTextView *tv) {
  g_return_if_fail (TFE_IS_TEXT_VIEW (tv));

  GtkWidget *dialog;
  GtkWidget *win = gtk_widget_get_ancestor (GTK_WIDGET (tv), GTK_TYPE_WINDOW);

  dialog = gtk_file_chooser_dialog_new ("Save file", GTK_WINDOW (win), GTK_FILE_CHOOSER_ACTION_SAVE,
                                      "Cancel", GTK_RESPONSE_CANCEL,
                                      "Save", GTK_RESPONSE_ACCEPT,
                                      NULL);
  g_signal_connect (dialog, "response", G_CALLBACK (saveas_dialog_response), tv);
  gtk_widget_show (dialog);
}

/**
 * @brief: 只是创建一个新的TfeTextView实例并返回指向新实例的指针
*/
GtkWidget *
tfe_text_view_new (void) {
   return GTK_WIDGET (g_object_new (TFE_TYPE_TEXT_VIEW, "wrap-mode", GTK_WRAP_WORD_CHAR, NULL));
}

/**
 * @brief: tfe_text_view_new_with_file是一个Gfile对象作为参数
 *         它将文件加载到GtkTextBuffer实例中，然后返回指向新实例的指针。
 *         如果在创建过程中发生错误，则返回NULL
*/
GtkWidget *
tfe_text_view_new_with_file (GFile *file) {
  g_return_val_if_fail (G_IS_FILE (file), NULL);

  GtkWidget *tv;
  GtkTextBuffer *tb;
  char *contents;
  gsize length;

  if (! g_file_load_contents (file, NULL, &contents, &length, NULL, NULL))
    return NULL;
  
  if ((tv = tfe_text_view_new()) != NULL) {
    tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tv));
    gtk_text_buffer_set_text (tb, contents, length);
    TFE_TEXT_VIEW (tv)->file = g_file_dup (file);
    /* FALSE表示buffer中内容已经修改 */
    gtk_text_buffer_set_modified (tb, FALSE);
  }
  g_free (contents);
  return tv;
}