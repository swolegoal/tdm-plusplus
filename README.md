# Thy Dungeonman++
A lovingly-crafted C++ conversion/ripoff of Videlectrix' smash hit
[**Thy Dungeonman**](http://homestarrunner.com/dungeonman.html).

```
 "#" # # # #   #"= # # #"# #"" #"" #"# #"# #=# #"# #"#  .   .
  #  #"#  #    # # # # # # # # #"" # # # # # # #"# # # =#= =#=
  "  " "  "    ""  """ " " """ """ """ " " " " " " " "  "   "

                    /\      /\      /\
                    ||/----\||      ||
                    \_------_/      ||
                     / o  o \       ||
                     /  ||  \    o__||__o
                     / ---- \     \____/
                     /\/\/\/\       ||
                                    oo

         ~=Press the ENTER key to enter yon dungeon=~
```

## STATUS
Working, but not yet 100% accurate to the original.

## DEPENDENCIES
- A fairly recent C++ compiler and standard library
- GNU Autotools and a Borne shell (for building).

## BUILDING
```
$ autoreconf --install  # Barfs a bunch of Bash and M4 shit in your tree
```

```
$ ./configure  # Barfs out your Makefiles
```

```
$ make  # Actually builds the tdm binary.
```

## PLAYING
```
$ src/tdm
```

## SPOILERS
More info about the game [here](http://www.hrwiki.org/wiki/Thy_Dungeonman) (*spoilers*).
