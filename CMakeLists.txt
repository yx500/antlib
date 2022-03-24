get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
add_library ( ${TARGET_NAME} ${SOURCES} ${HEADERS} )

# file(GLOB SOURCES
# "${CMAKE_CURRENT_SOURCE_DIR}/BGI/*.cpp"
# "${CMAKE_CURRENT_SOURCE_DIR}/BGI/*.h"
# "${CMAKE_CURRENT_SOURCE_DIR}/Comp/*.cpp"
# "${CMAKE_CURRENT_SOURCE_DIR}/Comp/*.h"
# "${CMAKE_CURRENT_SOURCE_DIR}/Ext/*.cpp"
# "${CMAKE_CURRENT_SOURCE_DIR}/Ext/*.h"
# "${CMAKE_CURRENT_SOURCE_DIR}/Gora/*.cpp"
# "${CMAKE_CURRENT_SOURCE_DIR}/Gora/*.h"
# )
# add_library ( ${TARGET_NAME} ${SOURCES} )


target_include_directories ( ${TARGET_NAME} PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR} 
${CMAKE_CURRENT_SOURCE_DIR}/Comp 
${CMAKE_CURRENT_SOURCE_DIR}/Ext 
${CMAKE_CURRENT_SOURCE_DIR}/Gora 
)



#install ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
install(TARGETS ${TARGET_NAME} DESTINATION lib)
install(FILES ${SOURCES} DESTINATION include/${TARGET_NAME})		  


