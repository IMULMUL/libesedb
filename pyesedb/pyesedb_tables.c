/*
 * Python object definition of the sequence and iterator object of tables
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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyesedb_libcerror.h"
#include "pyesedb_libesedb.h"
#include "pyesedb_python.h"
#include "pyesedb_table.h"
#include "pyesedb_tables.h"

PySequenceMethods pyesedb_tables_sequence_methods = {
	/* sq_length */
	(lenfunc) pyesedb_tables_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pyesedb_tables_getitem,
	/* sq_slice */
	0,
	/* sq_ass_item */
	0,
	/* sq_ass_slice */
	0,
	/* sq_contains */
	0,
	/* sq_inplace_concat */
	0,
	/* sq_inplace_repeat */
	0
};

PyTypeObject pyesedb_tables_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyesedb._tables",
	/* tp_basicsize */
	sizeof( pyesedb_tables_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyesedb_tables_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	&pyesedb_tables_sequence_methods,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_ITER,
	/* tp_doc */
	"pyesedb internal sequence and iterator object of tables",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pyesedb_tables_iter,
	/* tp_iternext */
	(iternextfunc) pyesedb_tables_iternext,
	/* tp_methods */
	0,
	/* tp_members */
	0,
	/* tp_getset */
	0,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyesedb_tables_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Creates a new tables object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyesedb_tables_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items )
{
	pyesedb_tables_t *tables_object = NULL;
	static char *function           = "pyesedb_tables_new";

	if( parent_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid parent object.",
		 function );

		return( NULL );
	}
	if( get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get item by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the tables values are initialized
	 */
	tables_object = PyObject_New(
	                 struct pyesedb_tables,
	                 &pyesedb_tables_type_object );

	if( tables_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create tables object.",
		 function );

		goto on_error;
	}
	if( pyesedb_tables_init(
	     tables_object ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize tables object.",
		 function );

		goto on_error;
	}
	tables_object->parent_object     = parent_object;
	tables_object->get_item_by_index = get_item_by_index;
	tables_object->number_of_items   = number_of_items;

	Py_IncRef(
	 (PyObject *) tables_object->parent_object );

	return( (PyObject *) tables_object );

on_error:
	if( tables_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) tables_object );
	}
	return( NULL );
}

/* Intializes a tables object
 * Returns 0 if successful or -1 on error
 */
int pyesedb_tables_init(
     pyesedb_tables_t *tables_object )
{
	static char *function = "pyesedb_tables_init";

	if( tables_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid tables object.",
		 function );

		return( -1 );
	}
	/* Make sure the tables values are initialized
	 */
	tables_object->parent_object     = NULL;
	tables_object->get_item_by_index = NULL;
	tables_object->current_index     = 0;
	tables_object->number_of_items   = 0;

	return( 0 );
}

/* Frees a tables object
 */
void pyesedb_tables_free(
      pyesedb_tables_t *tables_object )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyesedb_tables_free";

	if( tables_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid tables object.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           tables_object );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( tables_object->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) tables_object->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) tables_object );
}

/* The tables len() function
 */
Py_ssize_t pyesedb_tables_len(
            pyesedb_tables_t *tables_object )
{
	static char *function = "pyesedb_tables_len";

	if( tables_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid tables object.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) tables_object->number_of_items );
}

/* The tables getitem() function
 */
PyObject *pyesedb_tables_getitem(
           pyesedb_tables_t *tables_object,
           Py_ssize_t item_index )
{
	PyObject *table_object = NULL;
	static char *function  = "pyesedb_tables_getitem";

	if( tables_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid tables object.",
		 function );

		return( NULL );
	}
	if( tables_object->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid tables object - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( tables_object->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid tables object - invalid number of items.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) tables_object->number_of_items ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	table_object = tables_object->get_item_by_index(
	                tables_object->parent_object,
	                (int) item_index );

	return( table_object );
}

/* The tables iter() function
 */
PyObject *pyesedb_tables_iter(
           pyesedb_tables_t *tables_object )
{
	static char *function = "pyesedb_tables_iter";

	if( tables_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid tables object.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) tables_object );

	return( (PyObject *) tables_object );
}

/* The tables iternext() function
 */
PyObject *pyesedb_tables_iternext(
           pyesedb_tables_t *tables_object )
{
	PyObject *table_object = NULL;
	static char *function  = "pyesedb_tables_iternext";

	if( tables_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid tables object.",
		 function );

		return( NULL );
	}
	if( tables_object->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid tables object - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( tables_object->current_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid tables object - invalid current index.",
		 function );

		return( NULL );
	}
	if( tables_object->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid tables object - invalid number of items.",
		 function );

		return( NULL );
	}
	if( tables_object->current_index >= tables_object->number_of_items )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	table_object = tables_object->get_item_by_index(
	                tables_object->parent_object,
	                tables_object->current_index );

	if( table_object != NULL )
	{
		tables_object->current_index++;
	}
	return( table_object );
}

