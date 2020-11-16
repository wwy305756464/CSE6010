Author: Wenyue Wang, Shushu Zhao
Created: Oct 17, 2020

# Description:
This program aims to use graph in C to generate maze by DFS and generate output files. Then use BFS to solve the maze

This program is built in macOS Catalina, and compiled through gcc. To compile, open terminal and type:
For maze generation:
>> gcc maze_generate.c maze.c –o output.out
>> ./output.out [numrow] [numcol] [file_name]
For maze solve:
>> gcc maze_solver.c maze.c queue.c –o output.out
>> ./output.out [file_name]
   
e.g:
gcc maze_generate.c maze.c -o output.out
./output.out 4 4 maze_generation.txt
gcc maze_solver.c maze.c queue.c -o output.out
./output.out maze_generation.txt
