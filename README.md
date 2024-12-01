Compile with `mingw32-make.exe` in project directory. Then you can use `sdpt` in the project directory to run! It has to be run with a command, currently only `render` does anything though.

All functions have a little description on them. This comes in the form:
``` C
/*
 *   INPUT  : A basic explanation of each parameter of the function, the 
 *            prototype may well elaborate on this. Each parameter is in a
 *            separate sentence.
 *   OUTPUT : What the function returns, this is almost always an integer which
 *            will be TRUE or FALSE (see 'util/global.h' for definitions) to 
 *            indicate the success of the operation. This description generally
 *            indicates what it is that will succeed or fail.
 * 
 *   DESC   : A basic description of what the function does. This will be a 
 *            high-level and abstract explanation.
 *   NOTE   : Any further notes. Not all prototypes have this section.
 */
int function(int *arg1, char arg2); 
```

They are no wider than 80 characters.