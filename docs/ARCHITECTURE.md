# DOVE OS Architecture

## Design rule

DOVE is built as a layered system. Each layer exposes a small, stable interface to the layer above it. Hardware-specific code stays below the kernel abstractions.

## Kernel roadmap

### 0.1 Boot foundation
- Multiboot2 entry
- Protected-mode C environment
- VGA console
- deterministic build
- QEMU smoke test

### 0.2 CPU and interrupts
- GDT
- IDT
- exception handlers
- PIC/APIC strategy
- timer
- keyboard driver

### 0.3 Memory
- physical memory manager
- paging
- kernel heap
- virtual memory abstraction

### 0.4 Execution
- process/thread model
- scheduler
- system-call boundary
- user/kernel separation
- IPC

### 0.5 Storage
- block-device interface
- VFS
- initial filesystem
- persistent configuration

### 0.6 Device and network foundations
- PCI enumeration
- framebuffer/graphics abstraction
- USB strategy
- Ethernet/Wi-Fi driver strategy
- sockets/network stack

### 0.7 DOVE userland
- init/system manager
- service supervisor
- permissions
- native application ABI
- package manager
- shell

### 0.8 DOVE Shell
- compositor/window manager
- desktop
- settings
- notifications
- accessibility

### 0.9 Jelon integration
Jelon becomes a privileged-but-sandboxed OS agent through explicit system capabilities rather than unrestricted kernel access.

Initial capabilities:
- launch/close applications
- inspect permitted files
- system settings
- notifications
- automation
- speech input/output
- device control

Sensitive capabilities such as calls, messaging, credentials, and destructive filesystem actions require explicit permissions and auditable user consent.

### 1.x Compatibility
Windows and Android applications are separate runtime targets. DOVE will use compatibility technologies instead of pretending they are native binaries.

The compatibility architecture must isolate runtimes from the kernel and DOVE security model.

## Long-term hardware model

The first target is x86. The kernel interfaces should avoid unnecessary x86 assumptions so an ARM64 port can be introduced later for phones and tablets.

## Security model

Security is a core architecture concern, not a post-release feature:
- least privilege
- capability-oriented service access
- process isolation
- signed packages
- verified update path
- recoverable system updates
- auditable Jelon permissions
