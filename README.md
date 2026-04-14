# HXE
### A Work in progress Xbox (OG) emulator written in C

#### What Works
- Loading 64mb of main memory
- Loads .Xbe's and parses Section Headers, Thunk Table, and Entry points
- Runs the game code natively on your x64/x86 pc! (Until it crashes:P)
- Patching Thunk Table to load kernel functions
- Can run a simple hello world program!

#### What doesn't work
- Running actual games
- All kernel functions
- Graphics

## Credits
- https://github.com/cxbx-reloaded/cxbx-reloaded Their source code is really good reference for how to pull of all this HLE-ing.
- https://xboxdevwiki.net/ Great source for Xbox specs!


## Notes

- This is my second emulator project ever (first being CHIP-8) so expect very bad code as i'm new to C.
- I know the second project in the solution is called "Xemu-dll" it has nothing to do with the Xemu emulator. It just stands for "Xbox Emulator dll"

