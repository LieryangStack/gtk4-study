/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: MIT or LGPL-2.1-or-later
 */

#include "patterns-config.h"

#include <glib/gi18n.h>

#include "patterns-application.h"

int
main (int    argc,
      char **argv)
{
  g_autoptr (GApplication) app = patterns_application_new ();

  return g_application_run (G_APPLICATION (app), argc, argv);
}
