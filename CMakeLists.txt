cmake_minimum_required(VERSION 3.19)
project(Kwestions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Kwestions
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    addquestiondialog.h
    addquestiondialog.cpp
    addquestiondialog.ui
    questionnaireselectionmodel.h
    questionnaireselectionmodel.cpp
    questionmodel.h
    questionmodel.cpp
    responseoptionmodel.h
    responseoptionmodel.cpp
    business_logic/question.h
    business_logic/question.cpp
    business_logic/responseoption.h
    business_logic/responseoption.cpp
    business_logic/questionnaire.h
    business_logic/questionnaire.cpp
    newquestionnairedialog.h
    newquestionnairedialog.cpp
    newquestionnairedialog.ui
)

target_link_libraries(Kwestions
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Kwestions
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Kwestions
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
