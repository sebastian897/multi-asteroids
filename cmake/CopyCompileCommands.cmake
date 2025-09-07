file(COPY "${CMAKE_BINARY_DIR}/compile_commands.json"
     DESTINATION "${CMAKE_SOURCE_DIR}"
     FILES_MATCHING PATTERN "compile_commands.json")

message(STATUS "Copied compile_commands.json to project root")
