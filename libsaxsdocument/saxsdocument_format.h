/*
 * Format handling of SAXS documents.
 * Copyright (C) 2009, 2010 Daniel Franke <dfranke@users.sourceforge.net>
 *
 * This file is part of libsaxsdocument.
 *
 * libsaxsdocument is free software: you can redistribute it 
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * libsaxsdocument is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with libsaxsdocument. If not,
 * see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBSAXSDOCUMENT_SAXSDOCUMENT_FORMAT_H
#define LIBSAXSDOCUMENT_SAXSDOCUMENT_FORMAT_H

#ifdef __cplusplus
extern "C" {
#endif

struct saxs_document;

/**
 * @brief File format descriptor.
 */
struct saxs_document_format {
  /**
   * The name of the format, most often the filename
   * extension, e.g. @a dat.
   */
  const char *name;

  /** Free form descriptive text. */
  const char *description;

  /**
   * @returns 1 if the @a filename or the @a formatname can be
   * handled by this descriptor, 0 otherwise.
   *
   * Aformat descriptor without a @a check function will never
   * be used.
   */
  int (*check)(const char *filename, const char *formatname);

  /**
   * @returns 0 if read successfully, -1 on error.
   */
  int (*read)(struct saxs_document *doc, const char *filename);

  /**
   * @returns 0 if written successfully, -1 on error.
   */
  int (*write)(struct saxs_document *doc, const char *filename);

  struct saxs_document_format *next;
};
typedef struct saxs_document_format saxs_document_format;


saxs_document_format*
saxs_document_format_create();

void
saxs_document_format_free(saxs_document_format*);

/**
 * Shall be called at by the user of libsaxsdocument at startup of the
 * application.
 *
 * Or, shall be called by one of @ref saxs_document_format_first,
 * @ref saxs_document_format_next or @ref saxs_document_format_find
 * if the list of formats is empty.
 */
void
saxs_document_format_init();

void
saxs_document_format_register(const saxs_document_format *format);

saxs_document_format*
saxs_document_format_first();


saxs_document_format*
saxs_document_format_next();


/**
 * @brief Find a specific format by name or by determined from file name.
 *
 * Convenience Function.
 *
 * @param filename    A filename, may be NULL.
 * @param formatname  The name of a format, may be NULL.
 * 
 * @returns A format description or NULL if no format could be found.
 */

saxs_document_format*
saxs_document_format_find(const char *filename,
                          const char *formatname);


/**
 * @brief Case-insensitive string comparison.
 * @returns 0 if the format identifiers are equal, 1 otherwise.
 */
int
compare_format(const char *a, const char *b);

/**
 * @brief Extract the suffix of a filename.
 * Example: 'bsa.dat' has suffix 'dat'.
 */
const char*
suffix(const char *filename);

#ifdef __cplusplus
}
#endif

#endif /* !LIBSAXSDOCUMENT_SAXSDOCUMENT_FORMAT_H */
