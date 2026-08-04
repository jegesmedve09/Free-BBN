<div align="center">
  <h1>Free-BBN</h1>
  
  <p>
    <strong>Source-Available recreation of the PlayStation Broadband Navigator (PSBBN) dashboard</strong><br>
    built from scratch with <code>ps2sdk</code> + <code>gsKit</code>
  </p>

  <p>
    <em>No patches. No official Sony HDD or PSBBN installation required. Pure homebrew freedom.</em>
  </p>

  <br>

  <p style="font-size: 1.3em; color: #58a6ff; font-weight: bold; text-shadow: 0 0 8px rgba(88,166,255,0.4);">
    The glow is back — for every PS2
  </p>
</div>

---

# About
Works on **real PlayStation 2** hardware and **PCSX2**.
The original PSBBN required both japanese console,OEM network adapter, Sony approved HDD to function.
FreeBBN, just runs from whatever weird storage media you hacked onto your PS2.
It be an old USB you found in your grandparents addic, or a brand new shiny SSD you bought in the local store.
WARNING: Some files contain Eastereggs

**Free-BBN** brings back that **iconic blue glow**, flowing waves, smooth menu animations — but now for **every PS2 owner**:

- Fat models
- Slim models
- Official Sony HDD
- Modern ODE / adapter setups

This is **not** a patch of the original Sony binary.  
It's a complete from-scratch homebrew recreation, **source-available from day one**.

# Current Status (July 2026)

- ✓ Actual Music streaming and sound effects working
- ✓ Partial FMV playback
- ✓ Overengineered, but totally modular...
- Not-so-Early alpha — but it **boots and glows** ✨

# Credits

| Role                        | Who                                                                 |
|-----------------------------|---------------------------------------------------------------------|
| Idea & Vision               | Bögi Dániel (@jegesmedve09) [](https://github.com/jegesmedve09) — the madman who said: "Sony didn't give us open PSBBN, so I'll build it." |
| Special Thanks              | PS2 homebrew scene • CosmicScale's PSBBN English patch • sacred green screen • RCA cables that revealed what HDMI tried to hide • Quality ZlatyBazant beer that never let me down • the immense amount of self control needed not to throw my development suite out the WINDOW |


# Technical information
### Compatibility

#### FAT models
| Platform            | Status                                                                       |
|---------------------|------------------------------------------------------------------------------|
| SCPH-10000-00   JPN | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| SCPH-15000-00   JPN | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| SCPH-18000-00   JPN | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| SCHP-3000x          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| SCPH-3500x          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| SCPH-3700x          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| SCPH-3900x          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| SCPH-500xx          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB Tested on 50004   |
| SCPH-5500x          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |

#### SLIM models
| Platform            | Status                                                                       |
|---------------------|------------------------------------------------------------------------------|
| SCPH-70000          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| SCPH-75000          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| SCPH-77000          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| SCHP-7900x          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| SCPH-9000x          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB/Tuna ![Untested](https://img.shields.io/badge/Untested-orange) |

#### PSX models
| Platform            | Status                                                                       |
|---------------------|------------------------------------------------------------------------------|
| DESR-50000          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| DESR-51000          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| DESR-57000          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| DESR-7000x          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)  |
| DESR-7100x          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| DESR-7500x          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |
| DESR-7700x          | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via FMCB ![Untested](https://img.shields.io/badge/Untested-orange)   |

#### PS2 TV models
| Platform            | Status                                                                       |
|---------------------|------------------------------------------------------------------------------|
| PX300               | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via Tuna ![Untested](https://img.shields.io/badge/Untested-orange)   |
| PX300-1             | ![Supported](https://img.shields.io/badge/Supported-brightgreen) via Tuna ![Untested](https://img.shields.io/badge/Untested-orange)   |

### Storage Support
|Device           | Status                 |
|-----------------|------------------------|
| MemoryCard 0 (PlayStation 2) (8 MB Original) | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |
| MemoryCard 1 (PlayStation 2) (8 MB Original) | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |
| Dual MemoryCards (Playstation 2) (8 MB Original) | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |
| MemoryCard 0 (PlayStation 2) (8 MB+) | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |
| MemoryCard 1 (PlayStation 2) (8 MB+) | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |
| Dual MemoryCards (Playstation 2) (8 MB +) | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |
| MemoryCard 0 (PlayStation) | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |
| MemoryCard 1 (PlayStation) | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |
| Dual MemoryCards (PlayStation) | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |
| PS2 & PS Mismached MemoryCards | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |
| USB Mass (Single Drive + Single Partition) | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |
| USB Mass (Single Drive + Multiple Partitions) | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |
| USB Mass (Multiple Drives + Single Partition) | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |
| USB Mass (Multiple Drives + Multiple Partitions) | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |
| PS2 HDD (only FAT consoles) | ![Supported](https://img.shields.io/badge/Supported-brightgreen) |

### Intellectual Property & Assets
The "Curse" wallpaper/artwork featured in the free hobbyist version of this software is the property of **@shadydaone** on Instagram.
It is utilized within this non-commercial homebrew project with the creator's explicit permission. 

- **Artist Profile:** [@shadydaone on Instagram](https://instagram.com/shadydaone)
- *Note: This asset is strictly excluded from the software's codebase copyright and will not be included in any commercial licensing.*



### License

**Custom Source-Available License**  
Copyright © 2025–PRESENT Bögi Dániel (@jegesmedve09) [](https://github.com/jegesmedve09)

Read LICENSE file for more information.

---

<div align="center">

**More coming soon.**

<h2 style="color: #00d4ff; text-shadow: 0 0 12px rgba(0,212,255,0.6);">
  The glow is just beginning...
</h2>

</div>

<br>

### Developer Notes:

> **A word from the dev:** (2025-2026 Jan.)
> 
> before anyone starts ghossiping about the code having AI —  
> code that's 100% blind AI-slop **is** shit  
> (because humans didn't fuck around and find out what it actually does)
> 
> but when we use AI **as a guide** — like a brother who kills power at 99% kernel compile just to teach you patience —  
> to fix mistakes while we actually **understand** the code...  
> **that's not shit. That's smart load-sharing.**
> 
> don't cancel me on X pls... nor Grok. Grok did nothing wrong.

<br><br>

> **A word from the dev:** (2026 May 7)
> 
> FUCK

<br><br>

> **A word from the dev:** (2026 May 11)
> 
> me: U want pizza?
> swedes: *INHALES*
> (väldigt bra)

<br><br>

> **A word from the dev:** (2026 Jun 6)
> 
> meow~ :3
