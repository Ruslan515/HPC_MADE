# CMake generated Testfile for 
# Source directory: /media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy
# Build directory: /media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(blur_test_5 "/usr/bin/bash" "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/test/smoke_test.sh" "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/build/src/blur" "5%")
set_tests_properties(blur_test_5 PROPERTIES  WORKING_DIRECTORY "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/build/test" _BACKTRACE_TRIPLES "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/CMakeLists.txt;28;add_test;/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/CMakeLists.txt;0;")
add_test(blur_test_15 "/usr/bin/bash" "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/test/smoke_test.sh" "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/build/src/blur" "15%")
set_tests_properties(blur_test_15 PROPERTIES  WORKING_DIRECTORY "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/build/test" _BACKTRACE_TRIPLES "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/CMakeLists.txt;31;add_test;/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/CMakeLists.txt;0;")
add_test(blur_test_30 "/usr/bin/bash" "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/test/smoke_test.sh" "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/build/src/blur" "30%")
set_tests_properties(blur_test_30 PROPERTIES  WORKING_DIRECTORY "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/build/test" _BACKTRACE_TRIPLES "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/CMakeLists.txt;34;add_test;/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/CMakeLists.txt;0;")
add_test(blur_test_75 "/usr/bin/bash" "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/test/smoke_test.sh" "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/build/src/blur" "75%")
set_tests_properties(blur_test_75 PROPERTIES  WORKING_DIRECTORY "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/build/test" _BACKTRACE_TRIPLES "/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/CMakeLists.txt;37;add_test;/media/ruslan515/DATA_LINUX/ITMO/I_semestr/C++/hw_04_copy/CMakeLists.txt;0;")
subdirs("src")
