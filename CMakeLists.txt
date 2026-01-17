cmake_minimum_required(VERSION 3.19)
project(Qwestions LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Qwestions
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    addquestiondialog.h
    addquestiondialog.cpp
    addquestiondialog.ui
)

target_link_libraries(Qwestions
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Qwestions
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Qwestions
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
