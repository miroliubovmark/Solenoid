# CMake minimum required version
cmake_minimum_required(VERSION 3.5)

# Top level project
project(MagneticFieldModeling)

# Shared libraries
set(SHARED_LIBS
    MagneticField
    Tools
)

set(SUBPROJECTS
        ${SHARED_LIBS}
)

# Library subprojects
foreach(SUBPROJECT ${SUBPROJECTS})
        # Add subproject
	add_subdirectory(${SUBPROJECT})
endforeach(SUBPROJECT)
