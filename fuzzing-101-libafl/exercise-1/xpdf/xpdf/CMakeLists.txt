#========================================================================
#
# xpdf/cmake-xpdf.txt
#
# CMake script for the Xpdf tools.
#
# Modified by Ashutosh Varma <ashutoshvarma11@live.com>
# Copyright 2015 Glyph & Cog, LLC
#
#========================================================================

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/goo")
include_directories("${PROJECT_SOURCE_DIR}/fofi")
include_directories("${PROJECT_SOURCE_DIR}/splash")
if (PNG_FOUND)
  include_directories("${PNG_INCLUDE_DIRS}")
  add_definitions("${PNG_DEFINITIONS}")
endif ()
if (HAVE_LCMS)
  include_directories("${LCMS_INCLUDE_DIR}")
  set(COLOR_MANAGER_SOURCE "ColorManager.cc")
else ()
  set(COLOR_MANAGER_SOURCE "")
endif ()

add_library(xpdf_objs OBJECT
  # AcroForm.cc
  Annot.cc
  Array.cc
  BuiltinFont.cc
  BuiltinFontTables.cc
  Catalog.cc
  CharCodeToUnicode.cc
  CMap.cc
  ${COLOR_MANAGER_SOURCE}
  Decrypt.cc
  Dict.cc
  Error.cc
  FontEncodingTables.cc
  # Form.cc
  Function.cc
  Gfx.cc
  GfxFont.cc
  GfxState.cc
  GlobalParams.cc
  JArithmeticDecoder.cc
  JBIG2Stream.cc
  JPXStream.cc
  Lexer.cc
  Link.cc
  NameToCharCode.cc
  Object.cc
  # OptionalContent.cc
  Outline.cc
  OutputDev.cc
  Page.cc
  Parser.cc
  # PDF417Barcode.cc
  PDFDoc.cc
  PDFDocEncoding.cc
  PSTokenizer.cc
  SecurityHandler.cc
  Stream.cc
  # TextString.cc
  UnicodeMap.cc
  # UnicodeRemapping.cc
  UnicodeTypeTable.cc
  # UTF8.cc
  # XFAForm.cc
  XRef.cc
  # Zoox.cc
)

if (HAVE_SPLASH)
  set(SPLASH_LIB splash)
  set(SPLASH_OBECTS $<TARGET_OBJECTS:splash_objs>)
  set(SPLASH_OUTPUT_DEV_SRC "SplashOutputDev.cc")
else()
  set(SPLASH_LIB "")
  set(SPLASH_OBECTS "")
  set(SPLASH_OUTPUT_DEV_SRC "")
endif()

add_library(xpdf STATIC
  $<TARGET_OBJECTS:xpdf_objs>
  $<TARGET_OBJECTS:goo_objs>
  $<TARGET_OBJECTS:fofi_objs>
  ${SPLASH_OBECTS}
  # $<TARGET_OBJECTS:${PNG_LIBRARIES}>
  # $<TARGET_OBJECTS:${ZLIB_LIBRARIES}>
  # $<TARGET_OBJECTS:${FREETYPE_LIBRARY}>
  PreScanOutputDev.cc
  PSOutputDev.cc
  ${SPLASH_OUTPUT_DEV_SRC}
  TextOutputDev.cc
  # HTMLGen.cc
  # WebFont.cc
  ImageOutputDev.cc
)

target_include_directories(
  xpdf
  PUBLIC
  "${PNG_INCLUDE_DIRS}"
  "${ZLIB_INCLUDE_DIRS}"
  "${FREETYPE_INCLUDE_DIRS}"
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/goo"
  "${PROJECT_SOURCE_DIR}/fofi"
  "${PROJECT_SOURCE_DIR}/splash"
  "${CMAKE_CURRENT_SOURCE_DIR}"
)


if (BUILD_TOOLS)

  #--- pdftops

  if (HAVE_SPLASH)
    add_executable(pdftops
      $<TARGET_OBJECTS:xpdf_objs>
      PreScanOutputDev.cc
      PSOutputDev.cc
      SplashOutputDev.cc
      pdftops.cc
    )
    target_link_libraries(pdftops goo fofi splash
                          ${PAPER_LIBRARY}
                          ${FREETYPE_LIBRARY} ${FREETYPE_OTHER_LIBS}
                          ${DTYPE_LIBRARY}
                          ${LCMS_LIBRARY}
                          ${FONTCONFIG_LIBRARY}
                          ${CMAKE_THREAD_LIBS_INIT})
  else ()
    add_executable(pdftops
      $<TARGET_OBJECTS:xpdf_objs>
      PreScanOutputDev.cc
      PSOutputDev.cc
      pdftops.cc
    )
    target_link_libraries(pdftops goo fofi
                          ${PAPER_LIBRARY}
                          ${LCMS_LIBRARY}
                          ${FONTCONFIG_LIBRARY}
                          ${CMAKE_THREAD_LIBS_INIT})
  endif ()
  install(TARGETS pdftops RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  install(FILES ${PROJECT_SOURCE_DIR}/doc/pdftops.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

  #--- pdftotext

  add_executable(pdftotext
    $<TARGET_OBJECTS:xpdf_objs>
    TextOutputDev.cc
    pdftotext.cc
  )
  target_link_libraries(pdftotext goo fofi
                        ${PAPER_LIBRARY}
                        ${LCMS_LIBRARY}
                        ${FONTCONFIG_LIBRARY}
                        ${CMAKE_THREAD_LIBS_INIT})
  install(TARGETS pdftotext RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  install(FILES ${PROJECT_SOURCE_DIR}/doc/pdftotext.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

  #--- pdftohtml

  if (HAVE_SPLASH AND PNG_FOUND)
    add_executable(pdftohtml
      $<TARGET_OBJECTS:xpdf_objs>
      HTMLGen.cc
      SplashOutputDev.cc
      TextOutputDev.cc
      WebFont.cc
      pdftohtml.cc
    )
    target_link_libraries(pdftohtml goo fofi splash
                          ${PAPER_LIBRARY}
                          ${FREETYPE_LIBRARY} ${FREETYPE_OTHER_LIBS}
                          ${DTYPE_LIBRARY}
                          ${LCMS_LIBRARY}
                          ${PNG_LIBRARIES}
                          ${FONTCONFIG_LIBRARY}
                          ${CMAKE_THREAD_LIBS_INIT})
    install(TARGETS pdftohtml RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
    install(FILES ${PROJECT_SOURCE_DIR}/doc/pdftohtml.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
  endif ()

  #--- pdfinfo

  add_executable(pdfinfo
    $<TARGET_OBJECTS:xpdf_objs>
    pdfinfo.cc
  )
  target_link_libraries(pdfinfo goo fofi
                        ${PAPER_LIBRARY}
                        ${LCMS_LIBRARY}
                        ${FONTCONFIG_LIBRARY}
                        ${CMAKE_THREAD_LIBS_INIT})
  install(TARGETS pdfinfo RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  install(FILES ${PROJECT_SOURCE_DIR}/doc/pdfinfo.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

  #--- pdffonts

  add_executable(pdffonts
    $<TARGET_OBJECTS:xpdf_objs>
    pdffonts.cc
  )
  target_link_libraries(pdffonts goo fofi
                        ${PAPER_LIBRARY}
                        ${LCMS_LIBRARY}
                        ${FONTCONFIG_LIBRARY}
                        ${CMAKE_THREAD_LIBS_INIT})
  install(TARGETS pdffonts RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  install(FILES ${PROJECT_SOURCE_DIR}/doc/pdffonts.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

  #--- pdfdetach

  add_executable(pdfdetach
    $<TARGET_OBJECTS:xpdf_objs>
    pdfdetach.cc
  )
  target_link_libraries(pdfdetach goo fofi
                        ${PAPER_LIBRARY}
                        ${LCMS_LIBRARY}
                        ${FONTCONFIG_LIBRARY}
                        ${CMAKE_THREAD_LIBS_INIT})
  install(TARGETS pdfdetach RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  install(FILES ${PROJECT_SOURCE_DIR}/doc/pdfdetach.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

  #--- pdftoppm

  if (HAVE_SPLASH)
    add_executable(pdftoppm
      $<TARGET_OBJECTS:xpdf_objs>
      SplashOutputDev.cc
      pdftoppm.cc
    )
    target_link_libraries(pdftoppm goo fofi splash
                          ${PAPER_LIBRARY}
                          ${FREETYPE_LIBRARY} ${FREETYPE_OTHER_LIBS}
                          ${DTYPE_LIBRARY}
                          ${LCMS_LIBRARY}
                          ${FONTCONFIG_LIBRARY}
                          ${CMAKE_THREAD_LIBS_INIT})
    install(TARGETS pdftoppm RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
    install(FILES ${PROJECT_SOURCE_DIR}/doc/pdftoppm.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
  endif ()

  #--- pdftopng

  if (HAVE_SPLASH AND PNG_FOUND)
    add_executable(pdftopng
      $<TARGET_OBJECTS:xpdf_objs>
      SplashOutputDev.cc
      pdftopng.cc
    )
    target_link_libraries(pdftopng goo fofi splash
                          ${PAPER_LIBRARY}
                          ${FREETYPE_LIBRARY} ${FREETYPE_OTHER_LIBS}
                          ${DTYPE_LIBRARY}
                          ${LCMS_LIBRARY}
                          ${PNG_LIBRARIES}
                          ${FONTCONFIG_LIBRARY}
                          ${CMAKE_THREAD_LIBS_INIT})
    install(TARGETS pdftopng RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
    install(FILES ${PROJECT_SOURCE_DIR}/doc/pdftopng.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
  endif ()

  #--- pdfimages

  add_executable(pdfimages
    $<TARGET_OBJECTS:xpdf_objs>
    ImageOutputDev.cc
    pdfimages.cc
  )
  target_link_libraries(pdfimages goo fofi
                        ${PAPER_LIBRARY}
                        ${LCMS_LIBRARY}
                        ${FONTCONFIG_LIBRARY}
                        ${CMAKE_THREAD_LIBS_INIT})
  install(TARGETS pdfimages RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  install(FILES ${PROJECT_SOURCE_DIR}/doc/pdfimages.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

  #--- xpdfrc man page

  install(FILES ${PROJECT_SOURCE_DIR}/doc/xpdfrc.5 DESTINATION ${CMAKE_INSTALL_MANDIR}/man5)
endif()


INSTALL(TARGETS xpdf
    LIBRARY DESTINATION libxpdf/lib
    ARCHIVE DESTINATION libxpdf/lib
)

FILE(GLOB source_headers
    "${PROJECT_SOURCE_DIR}/*.h"
    "${PROJECT_BINARY_DIR}/*.h"
    "${PROJECT_SOURCE_DIR}/goo/*.h"
    "${PROJECT_SOURCE_DIR}/fofi/*.h"
    "${PROJECT_SOURCE_DIR}/splash/*.h"
    "${PROJECT_SOURCE_DIR}/xpdf/*.h"
)

INSTALL(FILES ${source_headers} DESTINATION libxpdf/include)
