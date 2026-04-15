# HXE
### A Work in progress Xbox (OG) emulator written in C

#### What Works
- Loading 64mb of main memory
- Loads .Xbe's and parses Section Headers, Thunk Table, and Entry points
- Runs the game code natively on your x64/x86 pc! (Until it crashes:P)
- Patching Thunk Table to load kernel functions
- Running homebrew built with nxdk (Kinda)

#### What doesn't work
- Running retail games
- All kernel functions



<img width="613.5" height="462.5" alt="pic" src="https://github.com/user-attachments/assets/58fe7f71-ec17-4e17-a37e-d9506ce7f0c4" />

HXE Running the nxdk triangle demo!


## Credits
- https://github.com/cxbx-reloaded/cxbx-reloaded Their source code is really good reference for how to pull of all this HLE-ing.
- https://xboxdevwiki.net/ Great source for Xbox specs!
- The cxbx team for the awesome XbSymbolDatabase!


## Notes

- This is my second emulator project ever (first being CHIP-8) so expect very bad code as i'm new to C.
- I know the second project in the solution is called "Xemu-dll" it has nothing to do with the Xemu emulator. It just stands for "Xbox Emulator dll"

