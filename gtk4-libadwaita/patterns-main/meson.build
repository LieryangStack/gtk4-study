project('patterns', 'c',
          version: '0.1.0',
          license: ['MIT', 'LGPL-2.1-or-later'],
    meson_version: '>= 0.50.0',
  default_options: [ 'warning_level=2',
                     'c_std=gnu11',
                   ],
)

i18n = import('i18n')

config_h = configuration_data()
config_h.set_quoted('PACKAGE_VERSION', meson.project_version())
config_h.set_quoted('GETTEXT_PACKAGE', 'patterns')
config_h.set_quoted('LOCALEDIR', join_paths(get_option('prefix'), get_option('localedir')))
config_h.set_quoted('APPLICATION_ID', 'org.gnome.Patterns')
configure_file(
  output: 'patterns-config.h',
  configuration: config_h,
)

add_project_arguments([
  '-I' + meson.build_root(),
  '-Wno-missing-field-initializers',
  '-Wno-unused-parameter',
], language: 'c')

subdir('data')
subdir('src')
subdir('po')

meson.add_install_script('build-aux/meson/postinstall.py')
