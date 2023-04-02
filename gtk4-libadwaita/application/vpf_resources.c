#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.vpf"), aligned (8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[1969]; const double alignment; void * const ptr;}  vpf_resource_data = {
  "\107\126\141\162\151\141\156\164\000\000\000\000\000\000\000\000"
  "\030\000\000\000\254\000\000\000\000\000\000\050\005\000\000\000"
  "\000\000\000\000\002\000\000\000\004\000\000\000\004\000\000\000"
  "\005\000\000\000\324\265\002\000\377\377\377\377\254\000\000\000"
  "\001\000\114\000\260\000\000\000\264\000\000\000\113\120\220\013"
  "\000\000\000\000\264\000\000\000\004\000\114\000\270\000\000\000"
  "\274\000\000\000\055\305\376\341\003\000\000\000\274\000\000\000"
  "\031\000\166\000\330\000\000\000\231\007\000\000\053\256\133\236"
  "\004\000\000\000\231\007\000\000\004\000\114\000\240\007\000\000"
  "\244\007\000\000\260\267\044\060\001\000\000\000\244\007\000\000"
  "\006\000\114\000\254\007\000\000\260\007\000\000\057\000\000\000"
  "\001\000\000\000\157\162\147\057\004\000\000\000\166\160\146\137"
  "\141\160\160\154\151\143\141\164\151\157\156\137\167\151\156\144"
  "\157\167\056\165\151\000\000\000\261\006\000\000\000\000\000\000"
  "\074\077\170\155\154\040\166\145\162\163\151\157\156\075\042\061"
  "\056\060\042\040\145\156\143\157\144\151\156\147\075\042\125\124"
  "\106\055\070\042\077\076\012\074\151\156\164\145\162\146\141\143"
  "\145\076\074\041\055\055\040\344\276\235\350\265\226\345\272\223"
  "\347\211\210\346\234\254\055\055\076\074\162\145\161\165\151\162"
  "\145\163\040\154\151\142\075\042\147\164\153\042\040\166\145\162"
  "\163\151\157\156\075\042\064\056\060\042\057\076\074\162\145\161"
  "\165\151\162\145\163\040\154\151\142\075\042\154\151\142\141\144"
  "\167\141\151\164\141\042\040\166\145\162\163\151\157\156\075\042"
  "\061\056\060\042\057\076\074\164\145\155\160\154\141\164\145\040"
  "\143\154\141\163\163\075\042\126\160\146\101\160\160\154\151\143"
  "\141\164\151\157\156\127\151\156\144\157\167\042\040\160\141\162"
  "\145\156\164\075\042\101\144\167\101\160\160\154\151\143\141\164"
  "\151\157\156\127\151\156\144\157\167\042\076\074\160\162\157\160"
  "\145\162\164\171\040\156\141\155\145\075\042\144\145\146\141\165"
  "\154\164\055\167\151\144\164\150\042\076\061\060\060\060\074\057"
  "\160\162\157\160\145\162\164\171\076\074\160\162\157\160\145\162"
  "\164\171\040\156\141\155\145\075\042\144\145\146\141\165\154\164"
  "\055\150\145\151\147\150\164\042\076\067\062\060\074\057\160\162"
  "\157\160\145\162\164\171\076\074\160\162\157\160\145\162\164\171"
  "\040\156\141\155\145\075\042\143\157\156\164\145\156\164\042\076"
  "\074\157\142\152\145\143\164\040\143\154\141\163\163\075\042\107"
  "\164\153\102\157\170\042\076\074\041\055\055\345\236\202\347\233"
  "\264\142\157\170\357\274\210\346\240\207\351\242\230\346\240\217"
  "\357\274\214\103\154\141\155\160\357\274\211\055\055\076\074\160"
  "\162\157\160\145\162\164\171\040\156\141\155\145\075\042\157\162"
  "\151\145\156\164\141\164\151\157\156\042\076\166\145\162\164\151"
  "\143\141\154\074\057\160\162\157\160\145\162\164\171\076\074\041"
  "\055\055\346\240\207\351\242\230\346\240\217\055\055\076\074\143"
  "\150\151\154\144\076\074\157\142\152\145\143\164\040\143\154\141"
  "\163\163\075\042\101\144\167\110\145\141\144\145\162\102\141\162"
  "\042\076\074\160\162\157\160\145\162\164\171\040\156\141\155\145"
  "\075\042\164\151\164\154\145\055\167\151\144\147\145\164\042\076"
  "\074\157\142\152\145\143\164\040\143\154\141\163\163\075\042\101"
  "\144\167\127\151\156\144\157\167\124\151\164\154\145\042\076\074"
  "\160\162\157\160\145\162\164\171\040\156\141\155\145\075\042\164"
  "\151\164\154\145\042\040\164\162\141\156\163\154\141\164\141\142"
  "\154\145\075\042\171\145\163\042\076\351\200\211\351\241\271\346"
  "\240\217\074\057\160\162\157\160\145\162\164\171\076\074\057\157"
  "\142\152\145\143\164\076\074\057\160\162\157\160\145\162\164\171"
  "\076\074\057\157\142\152\145\143\164\076\074\057\143\150\151\154"
  "\144\076\074\143\150\151\154\144\076\074\157\142\152\145\143\164"
  "\040\143\154\141\163\163\075\042\101\144\167\103\154\141\155\160"
  "\042\076\074\160\162\157\160\145\162\164\171\040\156\141\155\145"
  "\075\042\143\150\151\154\144\042\076\074\157\142\152\145\143\164"
  "\040\143\154\141\163\163\075\042\107\164\153\102\157\170\042\076"
  "\074\160\162\157\160\145\162\164\171\040\156\141\155\145\075\042"
  "\157\162\151\145\156\164\141\164\151\157\156\042\076\166\145\162"
  "\164\151\143\141\154\074\057\160\162\157\160\145\162\164\171\076"
  "\074\160\162\157\160\145\162\164\171\040\156\141\155\145\075\042"
  "\155\141\162\147\151\156\055\164\157\160\042\076\062\064\074\057"
  "\160\162\157\160\145\162\164\171\076\074\160\162\157\160\145\162"
  "\164\171\040\156\141\155\145\075\042\155\141\162\147\151\156\055"
  "\142\157\164\164\157\155\042\076\062\064\074\057\160\162\157\160"
  "\145\162\164\171\076\074\160\162\157\160\145\162\164\171\040\156"
  "\141\155\145\075\042\155\141\162\147\151\156\055\163\164\141\162"
  "\164\042\076\061\062\074\057\160\162\157\160\145\162\164\171\076"
  "\074\160\162\157\160\145\162\164\171\040\156\141\155\145\075\042"
  "\155\141\162\147\151\156\055\145\156\144\042\076\061\062\074\057"
  "\160\162\157\160\145\162\164\171\076\074\160\162\157\160\145\162"
  "\164\171\040\156\141\155\145\075\042\163\160\141\143\151\156\147"
  "\042\076\062\064\074\057\160\162\157\160\145\162\164\171\076\074"
  "\143\150\151\154\144\076\074\157\142\152\145\143\164\040\143\154"
  "\141\163\163\075\042\101\144\167\120\162\145\146\145\162\145\156"
  "\143\145\163\107\162\157\165\160\042\076\074\143\150\151\154\144"
  "\076\074\157\142\152\145\143\164\040\143\154\141\163\163\075\042"
  "\101\144\167\101\143\164\151\157\156\122\157\167\042\076\074\160"
  "\162\157\160\145\162\164\171\040\156\141\155\145\075\042\151\143"
  "\157\156\055\156\141\155\145\042\076\162\157\167\055\160\162\145"
  "\146\145\162\145\156\143\145\163\055\163\171\155\142\157\154\151"
  "\143\074\057\160\162\157\160\145\162\164\171\076\074\160\162\157"
  "\160\145\162\164\171\040\156\141\155\145\075\042\163\165\142\164"
  "\151\164\154\145\042\040\164\162\141\156\163\154\141\164\141\142"
  "\154\145\075\042\171\145\163\042\076\124\150\145\171\040\141\154"
  "\163\157\040\150\141\166\145\040\141\040\163\165\142\164\151\164"
  "\154\145\040\141\156\144\040\141\156\040\151\143\157\156\074\057"
  "\160\162\157\160\145\162\164\171\076\074\160\162\157\160\145\162"
  "\164\171\040\156\141\155\145\075\042\164\151\164\154\145\042\040"
  "\164\162\141\156\163\154\141\164\141\142\154\145\075\042\171\145"
  "\163\042\076\122\157\167\163\040\150\141\166\145\040\141\040\164"
  "\151\164\154\145\074\057\160\162\157\160\145\162\164\171\076\074"
  "\057\157\142\152\145\143\164\076\074\057\143\150\151\154\144\076"
  "\074\143\150\151\154\144\076\074\157\142\152\145\143\164\040\143"
  "\154\141\163\163\075\042\101\144\167\101\143\164\151\157\156\122"
  "\157\167\042\076\074\160\162\157\160\145\162\164\171\040\156\141"
  "\155\145\075\042\164\151\164\154\145\042\040\164\162\141\156\163"
  "\154\141\164\141\142\154\145\075\042\171\145\163\042\076\122\157"
  "\167\163\040\143\141\156\040\150\141\166\145\040\163\165\146\146"
  "\151\170\040\167\151\144\147\145\164\163\074\057\160\162\157\160"
  "\145\162\164\171\076\074\143\150\151\154\144\076\074\157\142\152"
  "\145\143\164\040\143\154\141\163\163\075\042\107\164\153\102\165"
  "\164\164\157\156\042\076\074\160\162\157\160\145\162\164\171\040"
  "\156\141\155\145\075\042\154\141\142\145\154\042\040\164\162\141"
  "\156\163\154\141\164\141\142\154\145\075\042\171\145\163\042\076"
  "\101\143\164\151\157\156\074\057\160\162\157\160\145\162\164\171"
  "\076\074\160\162\157\160\145\162\164\171\040\156\141\155\145\075"
  "\042\166\141\154\151\147\156\042\076\143\145\156\164\145\162\074"
  "\057\160\162\157\160\145\162\164\171\076\074\057\157\142\152\145"
  "\143\164\076\074\057\143\150\151\154\144\076\074\057\157\142\152"
  "\145\143\164\076\074\057\143\150\151\154\144\076\074\057\157\142"
  "\152\145\143\164\076\074\057\143\150\151\154\144\076\074\041\055"
  "\055\040\155\157\162\145\040\154\151\163\164\163\040\055\055\076"
  "\074\057\157\142\152\145\143\164\076\074\057\160\162\157\160\145"
  "\162\164\171\076\074\057\157\142\152\145\143\164\076\074\057\143"
  "\150\151\154\144\076\074\057\157\142\152\145\143\164\076\074\057"
  "\160\162\157\160\145\162\164\171\076\074\057\164\145\155\160\154"
  "\141\164\145\076\074\057\151\156\164\145\162\146\141\143\145\076"
  "\012\000\000\050\165\165\141\171\051\166\160\146\057\000\000\000"
  "\002\000\000\000\147\156\157\155\145\057\000\000\003\000\000\000"
  "" };

static GStaticResource static_resource = { vpf_resource_data.data, sizeof (vpf_resource_data.data) - 1 /* nul terminator */, NULL, NULL, NULL };

G_MODULE_EXPORT
GResource *vpf_get_resource (void);
GResource *vpf_get_resource (void)
{
  return g_static_resource_get_resource (&static_resource);
}
/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __G_CONSTRUCTOR_H__
#define __G_CONSTRUCTOR_H__

/*
  If G_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a usable way, including e.g. on library unload. If not you're on
  your own.

  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):

  #ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  G_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }

*/

#ifndef __GTK_DOC_IGNORE__

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define G_DEFINE_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);

#elif defined (_MSC_VER) && (_MSC_VER >= 1500)
/* Visual studio 2008 and later has _Pragma */

/*
 * Only try to include gslist.h if not already included via glib.h,
 * so that items using gconstructor.h outside of GLib (such as
 * GResources) continue to build properly.
 */
#ifndef __G_LIB_H__
#include "gslist.h"
#endif

#include <stdlib.h>

#define G_HAS_CONSTRUCTORS 1

/* We do some weird things to avoid the constructors being optimized
 * away on VS2015 if WholeProgramOptimization is enabled. First we
 * make a reference to the array from the wrapper to make sure its
 * references. Then we use a pragma to make sure the wrapper function
 * symbol is always included at the link stage. Also, the symbols
 * need to be extern (but not dllexport), even though they are not
 * really used from another object file.
 */

/* We need to account for differences between the mangling of symbols
 * for x86 and x64/ARM/ARM64 programs, as symbols on x86 are prefixed
 * with an underscore but symbols on x64/ARM/ARM64 are not.
 */
#ifdef _M_IX86
#define G_MSVC_SYMBOL_PREFIX "_"
#else
#define G_MSVC_SYMBOL_PREFIX ""
#endif

#define G_DEFINE_CONSTRUCTOR(_func) G_MSVC_CTOR (_func, G_MSVC_SYMBOL_PREFIX)
#define G_DEFINE_DESTRUCTOR(_func) G_MSVC_DTOR (_func, G_MSVC_SYMBOL_PREFIX)

#define G_MSVC_CTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _wrapper(void) { _func(); g_slist_find (NULL,  _array ## _func); return 0; } \
  __pragma(comment(linker,"/include:" _sym_prefix # _func "_wrapper")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _wrapper;

#define G_MSVC_DTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _constructor(void) { atexit (_func); g_slist_find (NULL,  _array ## _func); return 0; } \
   __pragma(comment(linker,"/include:" _sym_prefix # _func "_constructor")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _constructor;

#elif defined (_MSC_VER)

#define G_HAS_CONSTRUCTORS 1

/* Pre Visual studio 2008 must use #pragma section */
#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _wrapper(void) { _func(); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (*p)(void) = _func ## _wrapper;

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _constructor(void) { atexit (_func); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  init(_func)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void);

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  fini(_func)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void);

#else

/* constructors not supported for this compiler */

#endif

#endif /* __GTK_DOC_IGNORE__ */
#endif /* __G_CONSTRUCTOR_H__ */

#ifdef G_HAS_CONSTRUCTORS

#ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(vpfresource_constructor)
#endif
G_DEFINE_CONSTRUCTOR(vpfresource_constructor)
#ifdef G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(vpfresource_destructor)
#endif
G_DEFINE_DESTRUCTOR(vpfresource_destructor)

#else
#warning "Constructor not supported on this compiler, linking in resources will not work"
#endif

static void vpfresource_constructor (void)
{
  g_static_resource_init (&static_resource);
}

static void vpfresource_destructor (void)
{
  g_static_resource_fini (&static_resource);
}
