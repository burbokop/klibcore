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
