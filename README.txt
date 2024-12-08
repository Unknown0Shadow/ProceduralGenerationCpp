ProceduralGenerationCpp

A procedural generator build in C++ which generates a random N x M enclosed layout akin to a dungeon or maze.

COMPILATION
-For Windows, simply run compile.bat OR execute the following command in the command prompt: g++ -std=c++11 *.cpp -o proceduralGenerator.exe OR use an IDE (Integrated Development Environment)
-For other OS's (Operating Systems): no method provided in this project; you will have to do it yourself

RUN
method 1: double click on the compiled executable
method 2: from the command prompt opened in the project directory type FILE.exe, where FILE is the name of the executable which you have compiled
method 3: via an IDE (Eclipse, CodeBlocks, Visual Studio, BloodShed Dev-C, etc...)

ABOUT
Running the application with an IDE or via the executable will prompt the user for the following inputs:
Wall symbol -> the character that will be drawn in place of walls
Path symbol -> the character that will be drawn in place of paths
Uncharted symbol -> the character that will be drawn in unmapped surroundings
Merged walls (y/n) -> whether or not to display a compressed version of the map where the double walls have been merged together
Continuous generation (y/n) -> whether or not to generate one continuous path (y), or to fill all adjacent tiles (n) (certain tiles will still not be filled if they are surrounded by walls from all directions)
Map width -> a natural number in the range [4,50] representing the number of tiles arranged horizontally
Map Height -> a natural number in the range [4,50] representing the number of tiles arranged vertically

If you want to display whitespace for any of the symbols, leave the field empty
Special symbols can be displayed as well, hold left alt while typing the ASCII code for the symbol using the numpad (ex (HOLD) LEFT_ALT + 176) - this ability is specific to Windows, it may or may not exist in other OS's.

Running the application in the command prompt grants the user more control over the application. The user can simply run FILE.exe as is, or add launch option afterwards.
example: proceduralGenerator.exe -w 20 -h 10 -c -b # -p . -u " "
Possible launch flags:
-w [width]	(sets the width)
-h [height]	(sets the height)
-b [block]	(sets the symbol used for walls)
-p [path]	(sets the symbol used for paths)
-u [uncharted]	(sets the symbol used for unmapped areas)
-m		(enables merged generation)
-c		(enables continuous path generation)
-d		(enables debug mode)
These flags can be set in any order and combination (-w [width] -d -p [char] -h [height]). However the additional argument must be placed next to the relevant flag (bad example: -w -d 20 will not work). If there is no flag, the program will request input from the user. If there is at least one flag, inputs corresponding to -b through -d will be set to default values. Should any flag (with numeric argument) have improper arguments, it will be disregarded and the program will prompt the user for input to cover for those improper arguments.
Left Alt + numpad numbers seems to have unexpected output when the program has been launched through the command prompt, in spite of it working just fine when the program has been launched via the executable file.

Debug mode allows a step by step execution of the program, printing to the console the "thoughts" of the program at each significant decision point. It's also a neat way to watch the map being built tile by tile.

FOR DEVELOPERS
If you want to use this generator for your project, you might be interested in "generateMap" function (in main.cpp), for this alone is repsonsible for the generation of the tile map. The output is a std::vector<char>, on which you can implement navigation, collision, or whatever your heart desires. If you wish to work on the printed map instead, you will have to modify "displayMap" (in display_utility.cpp) to return the buffer (std::vector<char>).

TECHNICAL INFO
Made in Visual Studio 2022.
Compiler version c++98
OS: Windows 10

