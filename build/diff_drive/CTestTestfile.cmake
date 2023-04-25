# CMake generated Testfile for 
# Source directory: /home/josue/Desktop/Reto_ws/src/diff_drive
# Build directory: /home/josue/Desktop/Reto_ws/build/diff_drive
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_diff_drive_nosetests_tests "/home/josue/Desktop/Reto_ws/build/diff_drive/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/josue/Desktop/Reto_ws/build/diff_drive/test_results/diff_drive/nosetests-tests.xml" "--return-code" "\"/usr/bin/cmake\" -E make_directory /home/josue/Desktop/Reto_ws/build/diff_drive/test_results/diff_drive" "/usr/bin/nosetests-2.7 -P --process-timeout=60 --where=/home/josue/Desktop/Reto_ws/src/diff_drive/tests --with-xunit --xunit-file=/home/josue/Desktop/Reto_ws/build/diff_drive/test_results/diff_drive/nosetests-tests.xml")
subdirs("gtest")
