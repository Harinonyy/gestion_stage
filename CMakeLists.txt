 cmake_minimum_required(VERSION 3.16)

project(Gestion_Stage VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        form_etudiant.cpp
        form_etudiant.h
        form_etudiant.ui
        form_groupe.cpp
        form_groupe.h
        form_groupe.ui
        form_enseignant.cpp
        form_enseignant.h
        form_enseignant.ui
        form_theme.cpp
        form_theme.h
        form_theme.ui
        modif_etudiant.cpp
        modif_etudiant.ui
        modif_etudiant.h
        icones.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Gestion_Stage
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        connexionbd.h connexionbd.cpp
        modif_etudiant.h modif_etudiant.cpp modif_etudiant.ui
        modif_groupe.h modif_groupe.cpp modif_groupe.ui
        modif_enseignant.h modif_enseignant.cpp modif_enseignant.ui
        modif_theme.h modif_theme.cpp modif_theme.ui


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Gestion_Stage APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Gestion_Stage SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Gestion_Stage
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Gestion_Stage PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Gestion_Stage)
endif()
set_target_properties(Gestion_Stage PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Gestion_Stage
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Gestion_Stage)
endif()

