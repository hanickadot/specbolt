if (MSVC)
  # not supported
else()
  option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." ON)
  if (${FORCE_COLORED_OUTPUT})
  	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  		add_compile_options ($<$<COMPILE_LANGUAGE:C>:-fdiagnostics-color=always>)
  		add_compile_options ($<$<COMPILE_LANGUAGE:CXX>:-fdiagnostics-color=always>)
  	elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  		add_compile_options ($<$<COMPILE_LANGUAGE:C>:-fcolor-diagnostics>)
  		add_compile_options ($<$<COMPILE_LANGUAGE:CXX>:-fcolor-diagnostics>)
  	endif ()
  endif ()
endif ()
