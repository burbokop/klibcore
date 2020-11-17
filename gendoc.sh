#!/bin/bash

WORKING_DIR=`pwd`

REPO_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

cd $REPO_ROOT_DIR
doxygen
mv ./html $WORKING_DIR/html
mv ./latex $WORKING_DIR/latex
cd $WORKING_DIR
qhelpgenerator ./html/index.qhp -o ./klibcore.qch
