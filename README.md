# KLibCore


# update instruction (in root folder of your project)

```
git submodule init
git submodule update --remote 
```

# including KLibCore to your project

```
git submodule add git@github.com:burbokop/klibcore.git
```

## in .pro file

```
include(klibcore/klibcore.pro)
DEFINES += KLIBCORE_USE_LIBRARY
```

## in CMakteLists.txt file
```
include(klibcore/klibcore.cmake)
```

## building script example

```
#!/bin/sh

git clone https://github.com/burbokop/klibcore.git
cd ./klibcore
mkdir build
cd build
cmake .. \
	-DCMAKE_PREFIX_PATH=/home/user/Qt/5.15.2/gcc_64/lib/cmake
make
```

# additional defines

klib allow using extended meta system.
You can create instances by string names.
example:

```
QStringList classNames = kAvailableClasses();
QObject *newInstance = kInstantinate(classNames[0]);

```

for this you need add some text to .pro file:

```
DEFINES += KLIBCORE_USE_EXTENDED_META_SYSTEM
```
or to cmake
```
add_definitions(-DKLIBCORE_USE_EXTENDED_META_SYSTEM)
```
