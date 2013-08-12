if (NOT PNDMAN_LIBRARY)
    message("Building libpndman with qtpndman")
    ADD_SUBDIRECTORY(libpndman)
    list(APPEND QTPNDMAN_INCL ${libpndman_SOURCE_DIR}/include)
    list(APPEND QTPNDMAN_LINK pndman)
endif ()

SET(QTPNDMAN_STATIC_INCL ${QTPNDMAN_INCL} CACHE STRING "(internal) qtpndman static includes")
SET(QTPNDMAN_STATIC_LINK ${QTPNDMAN_LINK} CACHE STRING "(internal) qtpndman static linkage")
