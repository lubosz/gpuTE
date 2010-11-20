project(books_grantlee)

cmake_minimum_required(VERSION 2.6)

find_package(Qt4 REQUIRED)
find_package(Grantlee REQUIRED)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_GUI_LIB)
ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

include_directories(
	include
  ${QT_INCLUDES}
  ${QT_QTGUI_INCLUDE_DIR}
  ${QT_QTSQL_INCLUDE_DIR}
  ${Grantlee_INCLUDE_DIRS}
  ${PROJECT_BINARY_DIR}
)

configure_file(res/grantlee_paths.h.cmake ${PROJECT_BINARY_DIR}/grantlee_paths.h)

file(GLOB_RECURSE books_example_SRCS src/*.cpp)

set(books_example_RCSS
  res/books.qrc
)

set(books_example_UI
  res/bookwindow.ui
)

qt4_automoc( books_example_MOC_SRCS ${books_example_SRCS} )

QT4_WRAP_UI(books_example_UI_SRCS ${books_example_UI})

qt4_add_resources(
  books_example_RCS_SRCS
  ${books_example_RCSS}
)

add_executable(books
  ${books_example_SRCS}
  ${books_example_RCS_SRCS}
  ${books_example_UI_SRCS}
)

target_link_libraries(
  books
  ${QT_QTGUI_LIBRARIES}
  ${QT_QTSQL_LIBRARIES}
  ${Grantlee_CORE_LIBRARIES}
)



