# DOVE OS 🕊️

DOVE is an AI-native operating system project designed around a custom kernel, a modern system architecture, application compatibility, and Jelon—the built-in DOVE AI agent.

## Current milestone: DOVE 0.1

The first milestone establishes a real, reproducible boot path:

- Multiboot2-compatible x86 kernel
- 32-bit protected-mode C kernel foundation
- VGA text output
- Serial diagnostics
- Freestanding build with no host OS dependencies at runtime
- GRUB ISO generation
- QEMU smoke test
- GitHub Actions build

The architecture is deliberately layered so later work can add memory management, interrupts, processes, drivers, graphics, networking, security, application runtimes, and Jelon without rewriting the boot foundation.

## Repository layout

```
boot/       CPU entry point and Multiboot2 header
kernel/     Kernel source and public kernel interfaces
linker/     Kernel linker script
grub/       Bootloader configuration
scripts/    Local build/test helpers
docs/       Architecture documentation
```

## Build on Debian/Ubuntu

Install the build dependencies:

```bash
sudo apt update
sudo apt install build-essential gcc-multilib grub-pc-bin xorriso qemu-system-x86
```

Build:

```bash
make
```

Run:

```bash
make run
```

Clean:

```bash
make clean
```

The generated ISO is `build/dove.iso`.

## Project direction

DOVE is intended to evolve toward:

```
DOVE Kernel
   ├── Memory + Processes
   ├── Interrupts + Drivers
   ├── Storage + Filesystem
   ├── Networking
   ├── Security + Permissions
   ├── Graphics + DOVE Shell
   ├── Native Applications
   ├── Compatibility Runtimes
   │     ├── Windows
   │     └── Android
   └── Jelon AI
         ├── Voice
         ├── OS tools
         ├── Automation
         └── Telephony integrations
```

Compatibility layers will be implemented through mature open-source/runtime technology where appropriate; DOVE does not assume that every Windows or Android application can be supported.

## Status

**DOVE 0.1 — bootable kernel foundation in progress.**
