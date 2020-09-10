#!/bin/sh

doxygen

/home/user/Qt/5.15.0/gcc_64/bin/qhelpgenerator ./html/index.qhp -o ./klibcore.qch
