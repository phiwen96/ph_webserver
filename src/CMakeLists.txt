file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/../include/ph_file/*.hpp")


foreach(file ${HEADER_LIST})
    source_group (TREE ${CMAKE_CURRENT_LIST_DIR}/../include/ph_file
        PREFIX "include"               
        FILES  ${file}
    )
endforeach()


file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

foreach(file ${SOURCE_LIST})
    source_group (TREE ${CMAKE_CURRENT_LIST_DIR}
        PREFIX "src"               
        FILES  ${file}
    )
endforeach()



add_library (ph_file
	${SOURCE_LIST}  ${HEADER_LIST} 
	# ALIAS ph_file::ph_file
)

set_target_properties (
	ph_file 

	PROPERTIES
  		CXX_STANDARD 20
  		CXX_STANDARD_REQUIRED ON
  		CXX_EXTENSIONS OFF

	FOLDER
		""
)
# Make override a feature requirement only if available
target_compile_features (ph_file 
	PUBLIC
  		$<$<COMPILE_FEATURES:cxx_override>:cxx_override>
)
# Define the foo_OVERRIDE symbol so it provides the
# override keyword if available or empty otherwise
target_compile_definitions (ph_file 
	# PUBLIC
  	# 	$<$<COMPILE_FEATURES:cxx_override>:-Dph_file_OVERRIDE=override>
  	# 	$<$<NOT:$<COMPILE_FEATURES:cxx_override>>:-Dph_file_OVERRIDE>

	PRIVATE 
		"$<$<CONFIG:DEBUG>:DEBUG> $<$<CONFIG:RELEASE>:RELEASE>"
)


# target_compile_definitions (lib PRIVATE "$<$<CONFIG:DEBUG>:DEBUG> $<$<CONFIG:RELEASE>:RELEASE>")


# target_sources (ph_concepts PRIVATE in/platform.hpp)

set_target_properties (ph_file PROPERTIES CXX_STANDARD 20)
target_compile_features (ph_file PUBLIC cxx_std_20)

ph_precompile (TARGET ph_file PRIVATE PCH ${std_pch})

# add_library (ph_file ALIAS ph_file::ph_file)
# target_link_libraries (lib PRIVATE    ${Vulkan_LIBRARIES} glfw)
# target_link_libraries (lib PRIVATE ph_file)

target_include_directories (ph_file PUBLIC ${CMAKE_PROJECT_SOURCE_DIR}/include ph_concepts ph_proxy ph_optional)
target_link_libraries (ph_file PUBLIC ph_concepts ph_proxy ph_optional)

# target_include_directories (ph_concepts PRIVATE ${Boost_INCLUDE_DIRS})

target_compile_features (ph_file PUBLIC cxx_std_20)

# target_compile_options(ph_concepts PUBLIC "-ast-dump  -fsyntax-only")


target_include_directories(ph_file PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include/ph_file>
    $<INSTALL_INTERFACE:include/ph_file>
)

target_include_directories(ph_file PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

if (PROJECT_NAME STREQUAL PROJECT_NAME)
    # set_target_properties (lib PROPERTIES FOLDER "lib/")
else ()
    set_target_properties (ph_file PROPERTIES FOLDER "dependencies/ph_file")
endif ()



# IDE()