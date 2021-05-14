# 42CodinGameArena
<h1> minishell_unit_test </h1>

Local arena to test your code against everyone else

</br>

<h2> Prerequisites </h2>

The arena was made to compile on Mac.

<h2> Installation </h2>

+ Clone the repository and Make, and executable `arena` will be created and player object files in `playerObject/` will be turned into executables

<h2> Usage </h2>

`./arena <your_executable> <opponent_executable1> <opponent_executable2> ... 2> /dev/null` to confront your executable against all other executables passed as parameter, as many times as specified on the `PLAYOUT define` of arena.cpp (`2> /dev/null` to get rid of the stderr output

<img  src="https://github.com/martingarcialopez/42CodinGameArena/.images/arena2.png" width="50%"/>

`./arena <your_executable>` to confront your executable against all other executables in `opponent/`

+ <h3> Options </h3>

  `--no-error` or `-n` Does not test the stderr output, which is tested by default

  </br>
  
  You can run tests of a given section by doing:

  `--<test_section_name>` e.g. `--builtins` Only errors in these tests will be written in the log file. Note that you can combine them

  > ./unit_test.sh --n --builtins --quotes

  will only run the builtins and quotes tests and won't test the stderr output

  </br>
  
  `--help` or `-h` Shows the script usage, mainly the names of each test section and its abreviation
  
  
<h2> Behaviour </h2>

+ For each test, stdout and stderr of your minishell and real bash will be compared, along with their return codes.
For a test to be passed, you need to have the same return code of bash, as well as the same output in the stdout.

+ If the stderr differs, you will see [FAIL] on the stderr column, but that won't affect the previous result of the test. If the stderr is empty or if it doesn't differs, stderr column will be empty.
