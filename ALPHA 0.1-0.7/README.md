## Project Evolution – From Monolithic Mess to Proper Homebrew

### v0.x – The "All-in-one ELF of Pain" era (late 2025, eraly 2026 (january 14) )

The very first versions were one giant ELF file containing literally everything:

- Splash screen code
- Startup chime (optional)
- Basic rendering loop
- Early menu stubs
- Random debug printf hell
- Approximately 5000 lines of beautiful disaster (that somehow compiled)

**What was wrong with it?**
Pretty much everything long-term:

- Impossible to read or debug after ~2000 LOC
- Adding one new menu item felt like open-heart surgery (another C file)
- Black screens everywhere because of one wrong gsKit call deep inside
- Toolchain upgrades broke half the file for no reason, then reverted to the old one just to be safe)
- Felt more like a proof-of-concept than a real dashboard
- Loading times? Yeah… it was quick as fuck, but buggy as fuck also

It booted. It glowed (sometimes).
But it was **not** sustainable. Not even close.

### The Big Rewrite – Modular Edition (January 2026 – current)

We threw the whole monolith into the trash (metaphorically) and started over with a proper structure. Read the README file in other versions of the project to find out more
