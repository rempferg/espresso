# CMake generated Testfile for 
# Source directory: /Users/bindgens2/Documents/espresso_dev/espresso/src/core/unit_tests
# Build directory: /Users/bindgens2/Documents/espresso_dev/espresso/build_default/src/core/unit_tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Vector_test "Vector_test")
add_test(RuntimeError_test "RuntimeError_test")
add_test(RunningAverage_test "RunningAverage_test")
add_test(RuntimeErrorCollector_test "RuntimeErrorCollector_test")
add_test(ScriptInterface_test "ScriptInterface_test")
add_test(Wall_test "Wall_test")
add_test(Factory_test "Factory_test")
add_test(NumeratedContainer_test "NumeratedContainer_test")
add_test(MpiCallbacks_test "/opt/local/bin/mpiexec" "-np" "2" "MpiCallbacks_test")
add_test(ParallelScriptInterface_test "/opt/local/bin/mpiexec" "-np" "2" "ParallelScriptInterface_test")
add_test(gather_buffer_test "/opt/local/bin/mpiexec" "-np" "4" "gather_buffer_test")
add_test(scatter_buffer_test "/opt/local/bin/mpiexec" "-np" "4" "scatter_buffer_test")
add_test(AutoParameters_test "AutoParameters_test")
add_test(make_function_test "make_function_test")
add_test(AutoParameter_test "AutoParameter_test")
add_test(Variant_test "Variant_test")
add_test(ParticleIterator_test "ParticleIterator_test")
add_test(Range_test "Range_test")
