#include "zobj.h"

int zobj_header_read(FILE *file, ZObjHeader *header) {
  if (fread(header->magic, sizeof(header->magic), 1, file) != 1)
    return 1;

  if (header->magic[0] != ZOBJ_MAGIC[0] || header->magic[1] != ZOBJ_MAGIC[1])
    return 1;

  if (fread(&header->version, sizeof(header->version), 1, file) != 1)
    return 1;
  if (fread(&header->flags, sizeof(header->flags), 1, file) != 1)
    return 1;
  if (fread(&header->architecture, sizeof(header->architecture), 1, file) != 1)
    return 1;
  if (fread(&header->abi, sizeof(header->abi), 1, file) != 1)
    return 1;
  if (fread(&header->entry, sizeof(header->entry), 1, file) != 1)
    return 1;
  if (fread(&header->sections, sizeof(header->sections), 1, file) != 1)
    return 1;
  if (fread(header->reserved, sizeof(header->reserved), 1, file) != 1)
    return 1;

  return 0;
}

int zobj_header_write(FILE *file, const ZObjHeader *header) {
  if (fwrite(header->magic, sizeof(header->magic), 1, file) != 1)
    return 1;
  if (fwrite(&header->version, sizeof(header->version), 1, file) != 1)
    return 1;
  if (fwrite(&header->flags, sizeof(header->flags), 1, file) != 1)
    return 1;
  if (fwrite(&header->architecture, sizeof(header->architecture), 1, file) != 1)
    return 1;
  if (fwrite(&header->abi, sizeof(header->abi), 1, file) != 1)
    return 1;
  if (fwrite(&header->entry, sizeof(header->entry), 1, file) != 1)
    return 1;
  if (fwrite(&header->sections, sizeof(header->sections), 1, file) != 1)
    return 1;
  if (fwrite(header->reserved, sizeof(header->reserved), 1, file) != 1)
    return 1;

  return 0;
}

int zobj_section_header_read(FILE *file, ZObjSectionHeader *header) {
  if (fread(&header->name_offset, sizeof(header->name_offset), 1, file) != 1)
    return 1;
  if (fread(&header->type, sizeof(header->type), 1, file) != 1)
    return 1;
  if (fread(&header->flags, sizeof(header->flags), 1, file) != 1)
    return 1;
  if (fread(&header->address, sizeof(header->address), 1, file) != 1)
    return 1;
  if (fread(&header->size, sizeof(header->size), 1, file) != 1)
    return 1;

  return 0;
}

int zobj_section_header_write(FILE *file, const ZObjSectionHeader *header) {
  if (fwrite(&header->name_offset, sizeof(header->name_offset), 1, file) != 1)
    return 1;
  if (fwrite(&header->type, sizeof(header->type), 1, file) != 1)
    return 1;
  if (fwrite(&header->flags, sizeof(header->flags), 1, file) != 1)
    return 1;
  if (fwrite(&header->address, sizeof(header->address), 1, file) != 1)
    return 1;
  if (fwrite(&header->size, sizeof(header->size), 1, file) != 1)
    return 1;

  return 0;
}

int zobj_symbol_read(FILE *file, ZObjSymbol *symbol) {
  if (fread(&symbol->name_offset, sizeof(symbol->name_offset), 1, file) != 1)
    return 1;
  if (fread(&symbol->value, sizeof(symbol->value), 1, file) != 1)
    return 1;
  if (fread(&symbol->size, sizeof(symbol->size), 1, file) != 1)
    return 1;
  if (fread(&symbol->type, sizeof(symbol->type), 1, file) != 1)
    return 1;
  if (fread(&symbol->other, sizeof(symbol->other), 1, file) != 1)
    return 1;

  return 0;
}

int zobj_symbol_write(FILE *file, const ZObjSymbol *symbol) {
  if (fwrite(&symbol->name_offset, sizeof(symbol->name_offset), 1, file) != 1)
    return 1;
  if (fwrite(&symbol->value, sizeof(symbol->value), 1, file) != 1)
    return 1;
  if (fwrite(&symbol->size, sizeof(symbol->size), 1, file) != 1)
    return 1;
  if (fwrite(&symbol->type, sizeof(symbol->type), 1, file) != 1)
    return 1;
  if (fwrite(&symbol->other, sizeof(symbol->other), 1, file) != 1)
    return 1;

  return 0;
}

int zobj_relocation_read(FILE *file, ZObjRelocation *reloc) {
  if (fread(&reloc->address, sizeof(reloc->address), 1, file) != 1)
    return 1;
  if (fread(&reloc->symbol_index, sizeof(reloc->symbol_index), 1, file) != 1)
    return 1;
  if (fread(&reloc->length, sizeof(reloc->length), 1, file) != 1)
    return 1;
  if (fread(&reloc->flags, sizeof(reloc->flags), 1, file) != 1)
    return 1;
  if (fread(reloc->reserved, sizeof(reloc->reserved), 1, file) != 1)
    return 1;

  return 0;
}

int zobj_relocation_write(FILE *file, const ZObjRelocation *reloc) {
  if (fwrite(&reloc->address, sizeof(reloc->address), 1, file) != 1)
    return 1;
  if (fwrite(&reloc->symbol_index, sizeof(reloc->symbol_index), 1, file) != 1)
    return 1;
  if (fwrite(&reloc->length, sizeof(reloc->length), 1, file) != 1)
    return 1;
  if (fwrite(&reloc->flags, sizeof(reloc->flags), 1, file) != 1)
    return 1;
  if (fwrite(reloc->reserved, sizeof(reloc->reserved), 1, file) != 1)
    return 1;

  return 0;
}
