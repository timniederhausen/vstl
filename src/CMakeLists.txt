set(SOURCE_FILES
  string.cpp
  string_view.cpp
)

add_library(vstl STATIC ${SOURCE_FILES})

target_include_directories(vstl PUBLIC
  ${vstl_SOURCE_DIR}/include
)

target_link_libraries(vstl boost)
