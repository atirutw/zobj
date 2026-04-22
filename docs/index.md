# ZObj
ZObj is a simple object and executable file format for 8-bit systems. It is designed to be easily handled on such systems.

## Overall Structure
| Element          | Description                                 |
| ---------------- | ------------------------------------------- |
| Header           | Contains metadata about the file            |
| Section 1 Header | Contains metadata about Section 1           |
| Section 2 Header | Contains metadata about Section 2           |
| ...              | Contains metadata about other sections      |
| Section 1 Data   | Contains the actual data for Section 1      |
| Section 2 Data   | Contains the actual data for Section 2      |
| ...              | Contains the actual data for other sections |

## Header
```c
typedef struct {
    uint8_t magic[2]; // "\x7fZ"
    uint8_t version; // Currently 0 (1)
    uint8_t flags; // (2)!
    uint8_t architecture; // (3)!
    uint8_t abi; // (4)!
    uint16_t entry_point; // (5)!
    uint16_t num_sections; // The number of sections in the file.
    char reserved[6];
} header_t;
```

1. Since the format is currently pre-1.0, the format specifications may change without a version bump. Be mindful of this when writing implementations.
2. See: [Flags](#flags).
3. See: [Architecture](#architecture).
4. See: [ABI](#abi).
5. Where the program pointer should be set to when executing the file. Unused if the executable flag is not set.

### Flags
- `0x01`: Executable. If set, the file is an executable and should be executed by jumping to the entry point.

### Architecture
- `0x00`: Unknown, invalid, or not applicable.
- `0x01`: Zilog Z80.

### ABI
- `0x00`: Unspecified or unknown.
- `0x01`: Zeal 8-bit OS.

## Section Header
```c
typedef struct {
    uint16_t name_offset;
    uint8_t type;
    uint8_t flags;
    uint16_t address;
    uint16_t size;
} section_header_t;
```

### Section Types
- `0x00`: Program data, or other non-metadata section.
- `0x01`: String table. Contains null-terminated strings, and is used for section and symbol names.
- `0x02`: Symbol table. Contains an array of symbol entries.
- `0x03`: Relocation table. Contains an array of relocation entries.

### Section Flags
- `0x01`: Allocate. If set, the section takes up space in memory when the file is loaded.
- `0x02`: Load. If set alongside the allocate flag, the section's data is loaded into memory when the file is loaded. If not set, the section is allocated but not loaded, and should be zero-initialized.
- `0x04`: Executable. If set, the section contains executable code. This flag is only informational on systems without memory protection.

## Symbol Table Entry
```c
typedef struct {
    uint16_t name_offset;
    uint16_t value;
    uint16_t section;
    uint8_t type;
    uint8_t other;
} symbol_entry_t;
```

### Symbol Types
- `0x00`: Undefined. The symbol is undefined and should be resolved by the linker.
- `0x01`: Absolute. The symbol is absolute and does not need to be relocated.
- `0x02`: Section-relative. The symbol's value is relative to the start of its section.

## Relocation Table Entry
```c
typedef struct {
    uint16_t address;
    uint16_t symbol;
    uint8_t length;
    uint8_t flags;
    char reserved[2];
} relocation_entry_t;
```

### Relocation Lengths
- `0x01`: 8-bit relocation.
- `0x02`: 16-bit relocation.
- `0x03`: 24-bit relocation.
- `0x04`: 32-bit relocation.

### Relocation Flags
- `0x01`: PC-relative. If set, the relocation is relative to the program counter.
