/* Installation Info */
static const char qt_configure_prefix_path_str  [12+256] = "qt_prfxpath=C:/Dev/Qt5-build/qtbase";
#ifdef QT_BUILD_QMAKE
static const char qt_configure_ext_prefix_path_str   [12+256] = "qt_epfxpath=C:/Dev/Qt5-build/qtbase";
static const char qt_configure_host_prefix_path_str  [12+256] = "qt_hpfxpath=C:/Dev/Qt5-build/qtbase";
#endif
static const short qt_configure_str_offsets[] = {
    0,
    4,
    12,
    16,
    20,
    24,
    32,
    40,
    44,
    46,
    48,
    61,
    70,
#ifdef QT_BUILD_QMAKE
    76,
    77,
    83,
    87,
    91,
    93,
    104,
#endif
};
static const char qt_configure_strs[] =
    "doc\0"
    "include\0"
    "lib\0"
    "bin\0"
    "bin\0"
    "plugins\0"
    "imports\0"
    "qml\0"
    ".\0"
    ".\0"
    "translations\0"
    "examples\0"
    "tests\0"
#ifdef QT_BUILD_QMAKE
    "\0"
    "false\0"
    "bin\0"
    "lib\0"
    ".\0"
    "win32-msvc\0"
    "win32-msvc\0"
#endif
;
#define QT_CONFIGURE_SETTINGS_PATH "etc/xdg"
#define QT_CONFIGURE_LIBLOCATION_TO_PREFIX_PATH "../"
#define QT_CONFIGURE_HOSTBINDIR_TO_EXTPREFIX_PATH "../"
#define QT_CONFIGURE_HOSTBINDIR_TO_HOSTPREFIX_PATH "../"
#ifdef QT_BUILD_QMAKE
# define QT_CONFIGURE_SYSROOTIFY_PREFIX false
# define QT_CONFIGURE_CROSSBUILD false
#endif
#define QT_CONFIGURE_PREFIX_PATH qt_configure_prefix_path_str + 12
#ifdef QT_BUILD_QMAKE
# define QT_CONFIGURE_EXT_PREFIX_PATH qt_configure_ext_prefix_path_str + 12
# define QT_CONFIGURE_HOST_PREFIX_PATH qt_configure_host_prefix_path_str + 12
#endif
