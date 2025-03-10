cmake_minimum_required(VERSION 3.5)

project(TP2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TP2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Documentos/documentosui.h Documentos/documentosui.cpp Documentos/documentosui.ui
        lectorarchivos.h lectorarchivos.cpp

        NPC/npc.h NPC/npc.cpp
        Documentos/pasaporte.h Documentos/pasaporte.cpp
        Documentos/estancia.h Documentos/estancia.cpp
        Documentos/documentacion.h Documentos/documentacion.cpp
        Reglas/reglasnivel1.h Reglas/reglasnivel1.cpp
        Generadores/generadornpc.h Generadores/generadornpc.cpp
        Generadores/generadordocumentacion.h Generadores/generadordocumentacion.cpp
        Generadores/colanpc.h Generadores/colanpc.cpp
        juego.h juego.cpp


        Resources.qrc
        GameScreen/gamescreen.h GameScreen/gamescreen.cpp GameScreen/gamescreen.ui
        NPC/npcui.h NPC/npcui.cpp NPC/npcui.ui
        Documentos/uaderpass.h Documentos/uaderpass.cpp Documentos/uaderpass.ui
        Reglas/reglas.h Reglas/reglas.cpp
        Reglas/reglasnivel2.h Reglas/reglasnivel2.cpp
        Reglas/reglasnivel3.h Reglas/reglasnivel3.cpp
        Reglas/reglasnivel4.h Reglas/reglasnivel4.cpp
        Reglas/reglasnivel5.h Reglas/reglasnivel5.cpp
        NPC/npcgenericoui.h NPC/npcgenericoui.cpp NPC/npcgenericoui.ui
        NPC/npccomun.h NPC/npccomun.cpp
        Gestores/gestordocumentosui.h Gestores/gestordocumentosui.cpp
        GameScreen/BotonesCustom.h GameScreen/BotonesCustom.cpp GameScreen/BotonesCustom.ui
        Gestores/gestornpcsui.h Gestores/gestornpcsui.cpp
        Generadores/generarestancia.h Generadores/generarestancia.cpp
        Documentos/estanciaui.h Documentos/estanciaui.cpp Documentos/estanciaui.ui
        Documentos/pasaporte.h
        Generadores/generador_pasaporte.h
        Generadores/generador_pasaporte.cpp
        Documentos/pasaporteui.h Documentos/pasaporteui.cpp Documentos/pasaporteui.ui
        Documentos/dni.h Documentos/dni.cpp Documentos/dni.ui
        NPC/globosdialogoui.h NPC/globosdialogoui.cpp NPC/globosdialogoui.ui
        PantallaPausa/pantallapausa.h PantallaPausa/pantallapausa.cpp PantallaPausa/pantallapausa.ui
        PantallaStats/pantallafinalnivel.cpp PantallaStats/pantallafinalnivel.h PantallaStats/pantallafinalnivel.ui
        GameScreen/pantallaperdiste.h GameScreen/pantallaperdiste.cpp GameScreen/pantallaperdiste.ui
        PantallaMenu/pantallamenu.cpp PantallaMenu/pantallamenu.h PantallaMenu/pantallamenu.ui
        Generadores/locuracaracteres.h Generadores/locuracaracteres.cpp
        PantallaTransicion/pantallatransicion.h PantallaTransicion/pantallatransicion.cpp PantallaTransicion/pantallatransicion.ui
        Documentos/docsiconui.h Documentos/docsiconui.cpp Documentos/docsiconui.ui
        Documentos/listaacompaniantes.cpp Documentos/listaacompaniantes.h
        Generadores/generadorlistaacompaniantes.cpp Generadores/generadorlistaacompaniantes.h
        Documentos/listaacompaniantesui.h Documentos/listaacompaniantesui.cpp Documentos/listaacompaniantesui.ui
        GameScreen/libroreglas.cpp GameScreen/libroreglas.h GameScreen/libroreglas.ui
        Documentos/transcriptordialogos.h Documentos/transcriptordialogos.cpp Documentos/transcriptordialogos.ui
        Generadores/generador_paisresidencia.h Generadores/generador_paisresidencia.cpp
        Documentos/paisresidencia.h Documentos/paisresidencia.cpp
        Documentos/paisresidenciaui.h Documentos/paisresidenciaui.cpp Documentos/paisresidenciaui.ui
        GameScreen/pantallatutorial.h GameScreen/pantallatutorial.cpp GameScreen/pantallatutorial.ui
        Generadores/generadorskin.h Generadores/generadorskin.cpp
        NPC/skin.h NPC/skin.cpp
        SaveSlots/PlayerStats.h
        GameScreen/intropantalla.h GameScreen/intropantalla.cpp GameScreen/intropantalla.ui
        GameScreen/notificacion.h GameScreen/notificacion.cpp GameScreen/notificacion.ui
        Generadores/generador_nuevaestancia.h Generadores/generador_nuevaestancia.cpp
        Documentos/nuevaestancia.h Documentos/nuevaestancia.cpp
        SaveSlots/guardarpartida.h SaveSlots/guardarpartida.cpp
        logs.h logs.cpp
        Niveles/lectorniveles.h Niveles/lectorniveles.cpp
        Documentos/nuevaestanciaui.h Documentos/nuevaestanciaui.cpp Documentos/nuevaestanciaui.ui
        Generadores/generador_radiografia.h Generadores/generador_radiografia.cpp
        Documentos/radiografia.h Documentos/radiografia.cpp
        Documentos/radiografiaui.h Documentos/radiografiaui.cpp Documentos/radiografiaui.ui
        NPC/npcfondo.h NPC/npcfondo.cpp NPC/npcfondo.ui
        Gestores/gestorfondonpcs.h Gestores/gestorfondonpcs.cpp

















    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TP2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TP2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TP2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TP2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(TP2 PRIVATE Qt6::Multimedia)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TP2)
endif()
set_target_properties(TP2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TP2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TP2)
endif()
