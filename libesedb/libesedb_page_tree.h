/*
 * Page tree functions
 *
 * Copyright (C) 2009-2019, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBESEDB_PAGE_TREE_H )
#define _LIBESEDB_PAGE_TREE_H

#include <common.h>
#include <types.h>

#include "libesedb_io_handle.h"
#include "libesedb_key.h"
#include "libesedb_libbfio.h"
#include "libesedb_libcerror.h"
#include "libesedb_libfcache.h"
#include "libesedb_libfdata.h"
#include "libesedb_page.h"
#include "libesedb_page_tree_value.h"
#include "libesedb_page_value.h"
#include "libesedb_table_definition.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libesedb_page_tree libesedb_page_tree_t;

struct libesedb_page_tree
{
	/* The IO handle
	 */
	libesedb_io_handle_t *io_handle;

	/* The root page number
	 */
	uint32_t root_page_number;

	/* The object identifier
	 */
	uint32_t object_identifier;

	/* The table definition
	 */
	libesedb_table_definition_t *table_definition;

	/* The template table definition
	 */
	libesedb_table_definition_t *template_table_definition;

	/* The pages vector
	 */
	libfdata_vector_t *pages_vector;

	/* The pages cache
	 */
	libfcache_cache_t *pages_cache;
};

int libesedb_page_tree_initialize(
     libesedb_page_tree_t **page_tree,
     libesedb_io_handle_t *io_handle,
     libfdata_vector_t *pages_vector,
     libfcache_cache_t *pages_cache,
     uint32_t object_identifier,
     libesedb_table_definition_t *table_definition,
     libesedb_table_definition_t *template_table_definition,
     libcerror_error_t **error );

int libesedb_page_tree_free(
     libesedb_page_tree_t **page_tree,
     libcerror_error_t **error );

int libesedb_page_tree_read_root_page(
     libesedb_page_tree_t *page_tree,
     libbfio_handle_t *file_io_handle,
     off64_t page_offset,
     uint32_t page_number,
     libcerror_error_t **error );

int libesedb_page_tree_read_space_tree_page(
     libesedb_page_tree_t *page_tree,
     libbfio_handle_t *file_io_handle,
     uint32_t page_number,
     libcerror_error_t **error );

int libesedb_page_tree_read_page(
     libesedb_page_tree_t *page_tree,
     libbfio_handle_t *file_io_handle,
     off64_t page_offset,
     uint32_t page_number,
     libfdata_btree_node_t *node,
     libcerror_error_t **error );

int libesedb_page_tree_get_key_and_value(
     libesedb_page_tree_t *page_tree,
     libesedb_page_t *page,
     uint16_t page_value_index,
     libesedb_page_value_t *page_value,
     libesedb_key_t **key,
     libesedb_page_tree_value_t **page_tree_value,
     libcerror_error_t **error );

int libesedb_page_tree_get_number_of_leaf_values_from_page(
     libesedb_page_tree_t *page_tree,
     libbfio_handle_t *file_io_handle,
     libesedb_page_t *page,
     int *number_of_leaf_values,
     int recursion_depth,
     libcerror_error_t **error );

int libesedb_page_tree_get_number_of_leaf_values(
     libesedb_page_tree_t *page_tree,
     libbfio_handle_t *file_io_handle,
     uint32_t root_page_number,
     int *number_of_leaf_values,
     libcerror_error_t **error );

/* TODO deprecate */

int libesedb_page_tree_read_node(
     libesedb_page_tree_t *page_tree,
     libbfio_handle_t *file_io_handle,
     libfdata_btree_node_t *node,
     int node_data_file_index,
     off64_t node_data_offset,
     size64_t node_data_size,
     uint32_t node_data_flags,
     intptr_t *key_value,
     uint8_t read_flags,
     libcerror_error_t **error );

int libesedb_page_tree_read_leaf_value(
     libesedb_page_tree_t *page_tree,
     libbfio_handle_t *file_io_handle,
     libfdata_btree_t *tree,
     libfdata_cache_t *cache,
     int leaf_value_index,
     int leaf_value_data_file_index,
     off64_t leaf_value_data_offset,
     size64_t leaf_value_data_size,
     uint32_t leaf_value_data_flags,
     intptr_t *key_value,
     uint8_t read_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBESEDB_PAGE_TREE_H ) */

