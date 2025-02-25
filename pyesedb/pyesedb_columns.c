/*
 * Python object definition of the sequence and iterator object of columns
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

#include "pyesedb_column.h"
#include "pyesedb_columns.h"
#include "pyesedb_libcerror.h"
#include "pyesedb_libesedb.h"
#include "pyesedb_python.h"

PySequenceMethods pyesedb_columns_sequence_methods = {
	/* sq_length */
	(lenfunc) pyesedb_columns_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pyesedb_columns_getitem,
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

PyTypeObject pyesedb_columns_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyesedb._columns",
	/* tp_basicsize */
	sizeof( pyesedb_columns_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyesedb_columns_free,
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
	&pyesedb_columns_sequence_methods,
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
	"pyesedb internal sequence and iterator object of columns",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pyesedb_columns_iter,
	/* tp_iternext */
	(iternextfunc) pyesedb_columns_iternext,
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
	(initproc) pyesedb_columns_init,
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

/* Creates a new columns object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyesedb_columns_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items )
{
	pyesedb_columns_t *columns_object = NULL;
	static char *function             = "pyesedb_columns_new";

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
	/* Make sure the columns values are initialized
	 */
	columns_object = PyObject_New(
	                  struct pyesedb_columns,
	                  &pyesedb_columns_type_object );

	if( columns_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create columns object.",
		 function );

		goto on_error;
	}
	if( pyesedb_columns_init(
	     columns_object ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize columns object.",
		 function );

		goto on_error;
	}
	columns_object->parent_object     = parent_object;
	columns_object->get_item_by_index = get_item_by_index;
	columns_object->number_of_items   = number_of_items;

	Py_IncRef(
	 (PyObject *) columns_object->parent_object );

	return( (PyObject *) columns_object );

on_error:
	if( columns_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) columns_object );
	}
	return( NULL );
}

/* Intializes a columns object
 * Returns 0 if successful or -1 on error
 */
int pyesedb_columns_init(
     pyesedb_columns_t *columns_object )
{
	static char *function = "pyesedb_columns_init";

	if( columns_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid columns object.",
		 function );

		return( -1 );
	}
	/* Make sure the columns values are initialized
	 */
	columns_object->parent_object     = NULL;
	columns_object->get_item_by_index = NULL;
	columns_object->current_index     = 0;
	columns_object->number_of_items   = 0;

	return( 0 );
}

/* Frees a columns object
 */
void pyesedb_columns_free(
      pyesedb_columns_t *columns_object )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyesedb_columns_free";

	if( columns_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid columns object.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           columns_object );

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
	if( columns_object->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) columns_object->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) columns_object );
}

/* The columns len() function
 */
Py_ssize_t pyesedb_columns_len(
            pyesedb_columns_t *columns_object )
{
	static char *function = "pyesedb_columns_len";

	if( columns_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid columns object.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) columns_object->number_of_items );
}

/* The columns getitem() function
 */
PyObject *pyesedb_columns_getitem(
           pyesedb_columns_t *columns_object,
           Py_ssize_t item_index )
{
	PyObject *column_object = NULL;
	static char *function   = "pyesedb_columns_getitem";

	if( columns_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid columns object.",
		 function );

		return( NULL );
	}
	if( columns_object->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid columns object - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( columns_object->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid columns object - invalid number of items.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) columns_object->number_of_items ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	column_object = columns_object->get_item_by_index(
	                 columns_object->parent_object,
	                 (int) item_index );

	return( column_object );
}

/* The columns iter() function
 */
PyObject *pyesedb_columns_iter(
           pyesedb_columns_t *columns_object )
{
	static char *function = "pyesedb_columns_iter";

	if( columns_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid columns object.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) columns_object );

	return( (PyObject *) columns_object );
}

/* The columns iternext() function
 */
PyObject *pyesedb_columns_iternext(
           pyesedb_columns_t *columns_object )
{
	PyObject *column_object = NULL;
	static char *function   = "pyesedb_columns_iternext";

	if( columns_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid columns object.",
		 function );

		return( NULL );
	}
	if( columns_object->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid columns object - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( columns_object->current_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid columns object - invalid current index.",
		 function );

		return( NULL );
	}
	if( columns_object->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid columns object - invalid number of items.",
		 function );

		return( NULL );
	}
	if( columns_object->current_index >= columns_object->number_of_items )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	column_object = columns_object->get_item_by_index(
	                 columns_object->parent_object,
	                 columns_object->current_index );

	if( column_object != NULL )
	{
		columns_object->current_index++;
	}
	return( column_object );
}

