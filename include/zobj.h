/**
 * TODO: Thoroughly document this file format.
 * WARNING: WIP. Format can change without version bump!
 * NOTE: Keep *all* structs size multiples of 8 bytes!
 */

#ifndef ZOBJ_H
#define ZOBJ_H

#include <stdint.h>
#include <stdio.h>

#define ZOBJ_MAGIC "\x7fZ"

typedef enum {
  // Plain non-executable object file.
  ZOBJ_FLAG_NONE = 0,
  // Executable file. The entry point is specified in the header.
  ZOBJ_FLAG_EXECUTABLE = 1 << 0,
} ZObjFlags;

typedef enum {
  // Unknown/invalid architecture.
  ZOBJ_ARCH_UNKNOWN,
  // Zilog Z80.
  ZOBJ_ARCH_Z80,
} ZObjArchitecture;

typedef enum {
  // No specific ABI.
  ZOBJ_ABI_NONE,
  // Zeal 8-bit OS ABI.
  ZOBJ_ABI_ZEAL8,
} ZObjABI;

/**
 * The header of a ZObj file.
 */
typedef struct {
  char magic[2];
  uint8_t version;
  uint8_t flags;
  uint8_t architecture;
  uint8_t abi;
  uint16_t entry;
  uint16_t sections;
  char reserved[6];
} ZObjHeader;

int zobj_header_read(FILE *file, ZObjHeader *header);
int zobj_header_write(FILE *file, const ZObjHeader *header);

typedef enum {
  // Program data.
  ZOBJ_SECTION_PROGBITS,
  // String table. An object file is required to contain exactly one string
  // table section.
  ZOBJ_SECTION_STRTAB,
  // Symbol table. An object file may contain zero or one symbol table sections.
  // A symbol table section is required to be present if the file contains a
  // relocation table section.
  ZOBJ_SECTION_SYMTAB,
  // Relocation table. An object file may contain zero or one relocation table
  // sections.
  ZOBJ_SECTION_RELOC,
} ZObjSectionType;

typedef enum {
  // This section takes up memory space. If set without ZOBJ_SECTION_FLAG_LOAD,
  // this section is zero-initialized in memory.
  ZOBJ_SECTION_FLAG_ALLOC = 1 << 0,
  // The data immediately following this section header is loaded into memory at
  // the specified address when the file is loaded.
  ZOBJ_SECTION_FLAG_LOAD = 1 << 1,
  // This section contains executable code.
  ZOBJ_SECTION_FLAG_EXEC = 1 << 2,
} ZObjSectionFlags;

/**
 * The header of a ZObj section.
 */
typedef struct {
  uint16_t name_offset;
  uint8_t type;
  uint8_t flags;
  uint16_t address;
  uint16_t size;
} ZObjSectionHeader;

int zobj_section_header_read(FILE *file, ZObjSectionHeader *header);
int zobj_section_header_write(FILE *file, const ZObjSectionHeader *header);

typedef enum {
  // Undefined symbol. The value field is ignored.
  ZOBJ_SYMBOL_UNDEFINED,
  // Absolute symbol. The value field specifies the symbol's absolute value.
  ZOBJ_SYMBOL_ABSOLUTE,
  // Section symbol. The value field specifies the index of the section this
  // symbol is defined in.
  ZOBJ_SYMBOL_SECTION,
} ZObjSymbolType;

typedef struct {
  uint16_t name_offset;
  uint16_t value;
  uint16_t size;
  uint8_t type;
  // Reserved for future use.
  uint8_t other;
} ZObjSymbol;

int zobj_symbol_read(FILE *file, ZObjSymbol *symbol);
int zobj_symbol_write(FILE *file, const ZObjSymbol *symbol);

typedef enum {
  ZOBJ_RELOC_8,
  ZOBJ_RELOC_16,
  ZOBJ_RELOC_32,
} ZObjRelocationLength;

typedef enum {
  // No special flags.
  ZOBJ_RELOC_FLAG_NONE = 0,
  // This relocation is relative to the address of the relocation itself.
  ZOBJ_RELOC_FLAG_PCREL = 1 << 0,
  // This relocation requires an external reference. The symbol index must refer
  // to a symbol with an undefined type, and the symbol must be resolved by the
  // linker.
  ZOBJ_RELOC_FLAG_EXTERN = 1 << 1,
} ZObjRelocationFlags;

typedef struct {
  uint16_t address;
  uint16_t symbol_index;
  uint8_t length;
  uint8_t flags;
  char reserved[2];
} ZObjRelocation;

int zobj_relocation_read(FILE *file, ZObjRelocation *reloc);
int zobj_relocation_write(FILE *file, const ZObjRelocation *reloc);

#endif // ZOBJ_H
