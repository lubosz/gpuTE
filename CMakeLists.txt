project(minimalTemplate)

cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
find_package(Grantlee REQUIRED)

set(QT_USE_QTSQL true)
INCLUDE(${QT_USE_FILE})

include_directories(
	include
  ${QT_INCLUDES}
  ${Grantlee_INCLUDE_DIRS}
)

ADD_DEFINITIONS(-DGRANTLEE_TEMPLATE_PATH="templates")

file(GLOB_RECURSE books_example_SRCS src/*.cpp)

QT4_WRAP_CPP(MOC_INCS include/bookwrapper.h)

add_executable(
	minimalTemplate
	${MOC_INCS}
	${books_example_SRCS}
)

target_link_libraries(
	minimalTemplate
	${QT_LIBRARIES}
	${Grantlee_CORE_LIBRARIES}
)

