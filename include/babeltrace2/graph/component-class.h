#ifndef BABELTRACE2_GRAPH_COMPONENT_CLASS_H
#define BABELTRACE2_GRAPH_COMPONENT_CLASS_H

/*
 * Copyright 2017-2018 Philippe Proulx <pproulx@efficios.com>
 * Copyright 2016 Jérémie Galarneau <jeremie.galarneau@efficios.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* For bt_component_class */
#include <babeltrace2/types.h>

/* For __BT_FUNC_STATUS_* */
#define __BT_FUNC_STATUS_ENABLE
#include <babeltrace2/func-status.h>
#undef __BT_FUNC_STATUS_ENABLE

#ifdef __cplusplus
extern "C" {
#endif

typedef enum bt_component_class_init_method_status {
	BT_COMPONENT_CLASS_INIT_METHOD_STATUS_OK		= __BT_FUNC_STATUS_OK,
	BT_COMPONENT_CLASS_INIT_METHOD_STATUS_ERROR		= __BT_FUNC_STATUS_ERROR,
	BT_COMPONENT_CLASS_INIT_METHOD_STATUS_MEMORY_ERROR	= __BT_FUNC_STATUS_MEMORY_ERROR,
} bt_component_class_init_method_status;

typedef enum bt_component_class_port_connected_method_status {
	BT_COMPONENT_CLASS_PORT_CONNECTED_METHOD_STATUS_OK		= __BT_FUNC_STATUS_OK,
	BT_COMPONENT_CLASS_PORT_CONNECTED_METHOD_STATUS_ERROR		= __BT_FUNC_STATUS_ERROR,
	BT_COMPONENT_CLASS_PORT_CONNECTED_METHOD_STATUS_MEMORY_ERROR	= __BT_FUNC_STATUS_MEMORY_ERROR,
} bt_component_class_port_connected_method_status;

typedef enum bt_component_class_query_method_status {
	BT_COMPONENT_CLASS_QUERY_METHOD_STATUS_OK		= __BT_FUNC_STATUS_OK,
	BT_COMPONENT_CLASS_QUERY_METHOD_STATUS_AGAIN		= __BT_FUNC_STATUS_AGAIN,
	BT_COMPONENT_CLASS_QUERY_METHOD_STATUS_ERROR		= __BT_FUNC_STATUS_ERROR,
	BT_COMPONENT_CLASS_QUERY_METHOD_STATUS_MEMORY_ERROR	= __BT_FUNC_STATUS_MEMORY_ERROR,
	BT_COMPONENT_CLASS_QUERY_METHOD_STATUS_INVALID_OBJECT	= __BT_FUNC_STATUS_INVALID_OBJECT,
	BT_COMPONENT_CLASS_QUERY_METHOD_STATUS_INVALID_PARAMS	= __BT_FUNC_STATUS_INVALID_PARAMS,
} bt_component_class_query_method_status;

typedef enum bt_component_class_message_iterator_init_method_status {
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_INIT_METHOD_STATUS_OK		= __BT_FUNC_STATUS_OK,
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_INIT_METHOD_STATUS_ERROR		= __BT_FUNC_STATUS_ERROR,
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_INIT_METHOD_STATUS_MEMORY_ERROR	= __BT_FUNC_STATUS_MEMORY_ERROR,
} bt_component_class_message_iterator_init_method_status;

typedef enum bt_component_class_message_iterator_next_method_status {
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_NEXT_METHOD_STATUS_OK		= __BT_FUNC_STATUS_OK,
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_NEXT_METHOD_STATUS_AGAIN		= __BT_FUNC_STATUS_AGAIN,
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_NEXT_METHOD_STATUS_ERROR		= __BT_FUNC_STATUS_ERROR,
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_NEXT_METHOD_STATUS_MEMORY_ERROR	= __BT_FUNC_STATUS_MEMORY_ERROR,
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_NEXT_METHOD_STATUS_END		= __BT_FUNC_STATUS_END,
} bt_component_class_message_iterator_next_method_status;

typedef enum bt_component_class_message_iterator_seek_beginning_method_status {
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_SEEK_BEGINNING_METHOD_STATUS_OK		= __BT_FUNC_STATUS_OK,
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_SEEK_BEGINNING_METHOD_STATUS_AGAIN		= __BT_FUNC_STATUS_AGAIN,
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_SEEK_BEGINNING_METHOD_STATUS_ERROR		= __BT_FUNC_STATUS_ERROR,
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_SEEK_BEGINNING_METHOD_STATUS_MEMORY_ERROR	= __BT_FUNC_STATUS_MEMORY_ERROR,
} bt_component_class_message_iterator_seek_beginning_method_status;

typedef enum bt_component_class_message_iterator_seek_ns_from_origin_method_status {
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_SEEK_NS_FROM_ORIGIN_METHOD_STATUS_OK		= __BT_FUNC_STATUS_OK,
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_SEEK_NS_FROM_ORIGIN_METHOD_STATUS_AGAIN		= __BT_FUNC_STATUS_AGAIN,
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_SEEK_NS_FROM_ORIGIN_METHOD_STATUS_ERROR		= __BT_FUNC_STATUS_ERROR,
	BT_COMPONENT_CLASS_MESSAGE_ITERATOR_SEEK_NS_FROM_ORIGIN_METHOD_STATUS_MEMORY_ERROR	= __BT_FUNC_STATUS_MEMORY_ERROR,
} bt_component_class_message_iterator_seek_ns_from_origin_method_status;

typedef enum bt_component_class_set_method_status {
	BT_COMPONENT_CLASS_SET_METHOD_STATUS_OK	=	__BT_FUNC_STATUS_OK,
} bt_component_class_set_method_status;

typedef enum bt_component_class_set_description_status {
	BT_COMPONENT_CLASS_SET_DESCRIPTION_STATUS_OK		= __BT_FUNC_STATUS_OK,
	BT_COMPONENT_CLASS_SET_DESCRIPTION_STATUS_MEMORY_ERROR	= __BT_FUNC_STATUS_MEMORY_ERROR,
} bt_component_class_set_description_status;

extern bt_component_class_set_description_status
bt_component_class_set_description(bt_component_class *component_class,
		const char *description);

typedef enum bt_component_class_set_help_status {
	BT_COMPONENT_CLASS_SET_HELP_STATUS_OK		= __BT_FUNC_STATUS_OK,
	BT_COMPONENT_CLASS_SET_HELP_STATUS_MEMORY_ERROR	= __BT_FUNC_STATUS_MEMORY_ERROR,
} bt_component_class_set_help_status;

extern bt_component_class_set_help_status bt_component_class_set_help(
		bt_component_class *component_class,
		const char *help);

#ifdef __cplusplus
}
#endif

#include <babeltrace2/undef-func-status.h>

#endif /* BABELTRACE2_GRAPH_COMPONENT_CLASS_H */
