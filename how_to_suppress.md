valgrind --tool=memcheck --leak-check=full --show-reachable=yes --trace-children=yes --track-fds=yes --track-origins=yes --gen-suppressions=all --suppressions=./valgrind/memcheck.supp --suppressions=./valgrind/qt.supp --suppressions=./valgrind/sdl.supp --log-file=2 ./build/client

grep -v '^==4402==' ./2 >>  ss 