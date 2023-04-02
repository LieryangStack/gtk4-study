patterns_sources = [
  'pages/boxed-lists/patterns-page-boxed-lists.c',
  'pages/controls/patterns-page-controls.c',
  'pages/stub/patterns-page-stub.c',
  'pages/utility-pane/patterns-page-utility-pane.c',
  'pages/view-switcher/patterns-page-view-switcher.c',
  'pages/welcome/patterns-page-welcome.c',
  'pages/windows/patterns-page-windows.c',
  'pages/windows/patterns-primary-window.c',

  'main.c',
  'patterns-application.c',
  'patterns-page.c',
  'patterns-page-info.c',
  'patterns-utils.c',
  'patterns-window.c',
]

patterns_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk4', version: '>= 4.2.0'),
  dependency('libadwaita-1'),
]

gnome = import('gnome')

patterns_sources += gnome.compile_resources('patterns-resources',
  'patterns.gresource.xml',
  c_name: 'patterns'
)

executable('patterns', patterns_sources,
  dependencies: patterns_deps,
  gui_app: true,
  install: true,
)
